// Use `go run foo.go` to run your program

package main

import (
	. "fmt"
	"runtime"
)

var i = 0

func server(operation chan string) {
	for {
		select {
		case op := <-operation:
			if op == "inc" {
				i++
			} else if op == "dec" {
				i--
			}
		default:
			// do nothing
		}
	}
}

func incrementing(operation chan string, finish chan bool) {
	//TODO: increment i 1000000 times
	for j := 0; j < 1000000; j++ {
		operation <- "inc"
	}

	finish <- true
}

func decrementing(operation chan string, finish chan bool) {
	//TODO: decrement i 1000000 times
	for j := 0; j < 1000000; j++ {
		operation <- "dec"
	}

	finish <- true
}

func main() {
	// What does GOMAXPROCS do? What happens if you set it to 1?
	runtime.GOMAXPROCS(2)

	operation := make(chan string)
	finish := make(chan bool)

	// TODO: Spawn both functions as goroutines
	go incrementing(operation, finish)
	go decrementing(operation, finish)

	go server(operation)

	// wait for the two goroutines to finish
	<-finish
	<-finish

	Println("Result: ", i)
}
