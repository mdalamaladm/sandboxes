package main

import (
    "context"
    "fmt"
	"io"
    "net/http"
    "os"
    "os/signal"
    "syscall"
    "time"
)

const keyServerAddr = "serverAddr"

func getRoot(w http.ResponseWriter, r *http.Request) {
	ctx := r.Context()

	time.Sleep(40 * time.Second)

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


func main() {
    mux := http.NewServeMux()
    mux.HandleFunc("/", getRoot)
    mux.HandleFunc("/hello", getHello)

    server := &http.Server{
        Addr:         ":3333",
        Handler:      mux,
        ReadTimeout:  10 * time.Second,
        WriteTimeout: 10 * time.Second,
        IdleTimeout:  120 * time.Second,
    }

    // Start server in a goroutine
    go func() {
        fmt.Println("Server starting on :3333")
        if err := server.ListenAndServe(); err != nil && err != http.ErrServerClosed {
            fmt.Printf("error starting server: %s\n", err)
            os.Exit(1)
        }
    }()

    // Set up channel to listen for interrupt signals
    quit := make(chan os.Signal, 1)
    signal.Notify(quit, syscall.SIGINT, syscall.SIGTERM)
    
    // Block until signal is received
    <-quit
    fmt.Println("Server is shutting down...")

    // Create a context with timeout for shutdown
    ctx, cancel := context.WithTimeout(context.Background(), 30*time.Second)
    defer cancel()

    // Attempt graceful shutdown
    if err := server.Shutdown(ctx); err != nil {
        fmt.Printf("Server forced to shutdown: %s\n", err)
    }

    fmt.Println("Server stopped")
}
