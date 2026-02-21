package main

import "fmt"

func DecimalToBinary(n int) []int {
	var bits []int	
	bits = []int{}
	temp := n 
	if temp ==0 {
		fmt.Println("Строго больше 0")
	}
	for temp > 0 {
		bit := temp % 2
		bits = append(bits, bit)
		temp = temp/2
	}

	for i := 0; i<len(bits); i++ {
		for j := 0; j <len(bits); j++ {
			if i > j {
			bits[i], bits[j] = bits[j], bits[i]
			}
		}
	}

	return bits
}

func printRow(row []int) {
	for i := 0; i <len(row); i++ {
		if row[i] == 1 {
			fmt.Print("X")
		} else {
			fmt.Print(" ")
		}
	}

	fmt.Println()
}

func nextGeneration(current []int) []int {
	n := len(current)
	next := make([]int, n)
	for i := 0; i < n; i++ {
		right := 0
		left := 0
		if i > 0 {
			left = current[i-1]
		}
		if i < n-1 {
			right = current[i+1]
		}
		if left == right{
			next[i] = 0
		} else{
			next[i] = 1
		}

	}
	return next
}

func main() {
	row := make([]int, 64)
	bits := DecimalToBinary(42)
	fmt.Println(bits)
	center := len(row)/2
	start := center - len(bits)/2
	for i, bit := range bits {
        if start+i < len(row) && start+i >= 0 {
            row[start+i] = bit
        }
    }
	for i := 0; i < 64; i++ {
        fmt.Print("=")
    }
    fmt.Println()

	// Здесь рисуем фрактал
	for i := 0; i < 32; i++ {
		printRow(row)
		row = nextGeneration(row)
	}
}