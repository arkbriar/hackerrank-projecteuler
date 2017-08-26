package main

import (
	"fmt"
	"math/big"
	"sort"
)

const (
	N = 5000
	C = N * 5
)

func main() {
	t, n := 0, 0
	fmt.Scanf("%d", &t)

	fib_len := make([]int, C, C)

	a, b, c := big.NewInt(int64(1)), big.NewInt(int64(1)), &big.Int{}
	fib_len[0] = 1
	fib_len[1] = 1

	for i := 2; i < C; i++ {
		c.Add(a, b)
		fib_len[i] = len(c.Text(10))
		a.Set(b)
		b.Set(c)
	}

	for i := 0; i < t; i++ {
		fmt.Scanf("%d", &n)
		fmt.Println(sort.Search(len(fib_len), func(i int) bool {
			return fib_len[i] >= n
		}) + 1)
	}
}
