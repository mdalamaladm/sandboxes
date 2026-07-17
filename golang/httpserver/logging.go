package main

import (
	"errors"
    "fmt"
	"io"
	"log"
    "net/http"
    "time"
)

type DataBase struct {}

func (DataBase) Ping() error {
	return errors.New("Ping Error!")
}

const keyServerAddr = "serverAddr"

func loggingMiddleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        start := time.Now()
        
        // Call the next handler
        next.ServeHTTP(w, r)
        
        // Log request details
        log.Printf(
            "%s %s %s %s",
            r.Method,
            r.RequestURI,
            r.RemoteAddr,
            time.Since(start),
        )
    })
}

func getRoot(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()

	time.Sleep(5 * time.Second)

	myName := r.PostFormValue("myName")
    if myName == "" {
        myName = "HTTP"
    }

	// io.ReadAll() will read all body including FormData until EOF
	// put it after r.PostFormValue so it can extract FormData first
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

func healthCheck(w http.ResponseWriter, r *http.Request) {
	db := DataBase{}
	// Check database connection
    if err := db.Ping(); err != nil {
        w.Header().Set("Content-Type", "application/json")
        w.WriteHeader(http.StatusServiceUnavailable)
        w.Write([]byte(`{"status":"unhealthy","reason":"database connection failed"}`))
        return
    }


    w.Header().Set("Content-Type", "application/json")
    w.WriteHeader(http.StatusOK)
    w.Write([]byte(`{"status":"healthy"}`))
}


func securityHeadersMiddleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        // Prevent clickjacking attacks
        w.Header().Set("X-Frame-Options", "DENY")
        
        // Prevent MIME type sniffing
        w.Header().Set("X-Content-Type-Options", "nosniff")
        
        // Enable XSS protection
        w.Header().Set("X-XSS-Protection", "1; mode=block")
        
        // Enforce HTTPS
        w.Header().Set("Strict-Transport-Security", "max-age=31536000; includeSubDomains")
        
        // Control what resources can be loaded
        w.Header().Set("Content-Security-Policy", "default-src 'self'")
        
        next.ServeHTTP(w, r)
    })
}

func main() {
    mux := http.NewServeMux()
    mux.HandleFunc("/", getRoot)
    mux.HandleFunc("/hello", getHello)
	mux.HandleFunc("/health", healthCheck)

    // Wrap your mux with security headers
    securedMux := securityHeadersMiddleware(loggingMiddleware(mux))

    server := &http.Server{
        Addr:    ":3333",
        Handler: securedMux,
    }

    server.ListenAndServe()
}
