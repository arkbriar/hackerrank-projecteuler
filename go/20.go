package main

import (
	"fmt"
	"math/big"
)

func main() {
	t, n := 0, 0
	fmt.Scanf("%d", &t)

	for i := 0; i < t; i++ {
		fmt.Scanf("%d", &n)

		r := &big.Int{}
		r.MulRange(int64(2), int64(n))

		res := 0
		s := r.Text(10)
		for _, d := range s {
			res += int(d - '0')
		}

		fmt.Println(res)
	}
}
