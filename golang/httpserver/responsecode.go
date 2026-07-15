package main

import (
	"context"
    "errors"
    "fmt"
    "io"
	"net"
    "net/http"

)

const keyServerAddr = "serverAddr"

func loggingMiddleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        fmt.Printf("started %s %s\n", r.Method, r.URL.Path)

        next.ServeHTTP(w, r)

        fmt.Printf("completed %s %s\n", r.Method, r.URL.Path)
    })
}

func headerMiddleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        w.Header().Set("X-App-Version", "1.0")

        next.ServeHTTP(w, r)
    })
}

func getRoot(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()

	myName := r.PostFormValue("myName")
    if myName == "" {
        myName = "HTTP"
    }

	body, err := io.ReadAll(r.Body)
	if err != nil {
		fmt.Printf("could not read body: %s\n", err)
	}

	hasFirst := r.URL.Query().Has("first")
    first := r.URL.Query().Get("first")
    hasSecond := r.URL.Query().Has("second")
    second := r.URL.Query().Get("second")

    fmt.Printf("%s: got / request. first(%t)=%s, second(%t)=%s\n, body:\n%s\n, myName: %s",
        ctx.Value(keyServerAddr),
        hasFirst, first,
        hasSecond, second,
		body, myName)
    io.WriteString(w, "This is my website!\n")
}

func getHello(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()

	myName := r.PostFormValue("myName")
    if myName == "" {
        w.Header().Set("x-missing-field", "myName")
        w.WriteHeader(http.StatusBadRequest)
        return
    }


    fmt.Printf("got /hello request\n", ctx.Value(keyServerAddr))
    io.WriteString(w, fmt.Sprintf("Hello, %s!\n", myName))
}

func main() {
	mux := http.NewServeMux()
    mux.HandleFunc("/", getRoot)
    mux.HandleFunc("/hello", getHello)

	handler := loggingMiddleware(headerMiddleware(mux))

	ctx, cancelCtx := context.WithCancel(context.Background())
	serverOne := &http.Server{
		Addr:	":3333",
		Handler: handler,
		BaseContext: func(l net.Listener) context.Context {
			ctx = context.WithValue(ctx, keyServerAddr, l.Addr().String())

			return ctx
		},
	}

    go func() {
        err := serverOne.ListenAndServe()
        if errors.Is(err, http.ErrServerClosed) {
            fmt.Printf("server one closed\n")
        } else if err != nil {
            fmt.Printf("error listening for server one: %s\n", err)
        }
        cancelCtx()
    }()

	<-ctx.Done()
}
