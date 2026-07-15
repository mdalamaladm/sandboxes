package main

import (
	"context"
    "errors"
	"encoding/json"
    "fmt"
	"net"
    "net/http"
)

type Message struct {
	Name string `json:"name"`
	Body string `json:"body"`
}

const keyServerAddr = "serverAddr"

func handleJSON(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
		return
	}

	var msg Message

	err := json.NewDecoder(r.Body).Decode(&msg)
	
	if err != nil {
		http.Error(w, "invalid JSON payload", http.StatusBadRequest)
		return
	}

	response := map[string]string {
		"status": "success",
		"message": "Received message from " + msg.Name,
		"body": msg.Body,
	}

	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusOK)

	json.NewEncoder(w).Encode(response)
}

func main() {
	mux := http.NewServeMux()
    mux.HandleFunc("/api/message", handleJSON)

	ctx, cancelCtx := context.WithCancel(context.Background())
	serverOne := &http.Server{
		Addr:	":3333",
		Handler: mux,
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
