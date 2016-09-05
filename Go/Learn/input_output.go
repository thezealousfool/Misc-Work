package main

import (
	"fmt"
)

func main() {
	var a, b int64
	fmt.Scan(&a, &b)
	fmt.Printf("%v + %v = %v\n", a, b, a+b)
}
