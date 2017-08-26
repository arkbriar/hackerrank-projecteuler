package main

import (
	"fmt"
	"math/big"
)

func main() {
	t := 0
	n := 0
	fmt.Scanf("%d", &t)

	for i := 0; i < t; i++ {
		fmt.Scanf("%d", &n)

		r := &big.Int{}
		r.SetBit(r, n, 1)

		digits := r.Text(10)

		res := 0
		for _, d := range digits {
			res += int(d - '0')
		}

		fmt.Println(res)
	}
}
