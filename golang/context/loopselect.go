package main

import (
	"context"
	"fmt"
	"time"
)

func loopselect(ch chan<- int) {
	for i := 1; i <= 10; i++ {
		time.Sleep(2 * time.Second)
		fmt.Println("Send Data")
		ch <- i
	}

	close(ch)
}

func main() {
	ctx := context.Background()
	// ctx, cancel := context.WithCancel(context.Background())
	ch := make(chan int)

	go loopselect(ch)
	// go func() {
	//	time.Sleep(9 * time.Second)
	//	fmt.Println("Cancelling...")
	//	cancel()
	// }()

	for {
		select {
		case <- ctx.Done():
			fmt.Println("Done or Interupted")
			// The context is over, stop processing results
			return
		case result, ok := <- ch:
			if !ok {
				fmt.Println("Value all received")
				return
			}
			
			fmt.Println("Value received: ", result)	
			// Process the results received
		default:
			fmt.Println("Waiting for data")
			time.Sleep(1 * time.Second)
		}
	}
}
