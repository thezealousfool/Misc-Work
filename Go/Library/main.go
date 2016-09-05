package main

import (
	"fmt"
	"mod"
)

func main() {
	var i, n mod.Integer = 1 << 9, 1 << 9
	i += 7
	i = mod.Exponent(i, 1, n)
	fmt.Printf("%v\n", i)
}
