package main

import (
	"fmt"
	"time"
)

func main() {
	start := time.Now()

	for i := 0; i <= 10000; i++ {
		fmt.Printf("%v\n", i)
	}

	end := time.Now()
	dur := end.Sub(start)
	fmt.Printf("Time: %v milliseconds\n", int64(dur/time.Millisecond))
}
