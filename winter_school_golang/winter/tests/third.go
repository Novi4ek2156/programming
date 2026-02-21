package main

import (
	"fmt"
	"math/rand"
	"time"
)
const(
	h = 10
	w = 10
)

func seed(grid [][]bool) {
	for i := 0; i < len(grid) ; i++ {
		for j := 0; j < len(grid) ; j++ {
			live := rand.Intn(4)
			if live == 2{
				grid[i][j] = true
			}
		}
	}
	
}

func countNeighbors(grid [][]bool, row, col int) int{
	count := 0
	for i :=-1; i <= 1; i++{
		for j := -1; j <=1; j++{
			if i == 0 && j == 0{
				continue
			}
			r := (row + i + h) % h
			c := (col + j + w) % w


			if grid[r][c] {
				count++
			}


		}
	}
	return count
}

func nextGen(current [][]bool) [][]bool{
	h, w := len(current), len(current[0])

}




func main() {
	grid := make([][]bool, h)
	for i := range grid {
		grid[i] = make([]bool, w)
	}
	seed(grid)
	for {	
		// Очистка экрана для отрисовки следующего кадра
		fmt.Print("\033[H\033[2J") 

		// Рандом
		fmt.Printf("Random int [0, 99]: %d\n", rand.Intn(100))
		fmt.Print(grid)

		// Сон между кадрами
		time.Sleep(100 * time.Millisecond)
	}
}