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

    fmt.Printf("got / request\n", ctx.Value(keyServerAddr))
    io.WriteString(w, "This is my website!\n")
}

func getHello(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()

    fmt.Printf("got /hello request\n", ctx.Value(keyServerAddr))
    io.WriteString(w, "Hello, HTTP!\n")
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
