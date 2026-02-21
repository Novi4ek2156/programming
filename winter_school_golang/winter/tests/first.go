package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Введите число!")
		return
	} 
	N, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Printf("error")
		return
	}
		slice := make([]int, N)
		var newElem int
		newElem = 0
		for i := 0; i < N; i++{
			slice[i] = i * i
			fmt.Println(slice[i])
			
			newElem += slice[i] 
			}
		slice = append(slice, newElem)
		var filtered []int 
		for i := 0; i< len(slice); i++ {
			if (slice[i] % 3 == 0) {
				filtered = append(filtered, slice[i])
			}
		}
		fmt.Println("Original:", slice, "Filtered:", filtered)
		notDivisible := len(slice) - len(filtered)
		ans := float64(notDivisible) / float64(len(slice)) * 100
		fmt.Printf("Процент элементов, которые не делятся на 3: %.2f%%\n", ans)
}