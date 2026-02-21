package main

import (
	"fmt"
	"math/rand"
	"time"
)

const (
	width  = 40
	height = 20
)

// Функция для инициализации сетки случайными значениями
func seed(grid [][]bool) {
	for i := 0; i < len(grid); i++ {
		for j := 0; j < len(grid[i]); j++ {
			// Шанс живой клетки примерно 25%
			if rand.Intn(4) == 0 {
				grid[i][j] = true
			}
		}
	}
}

// Функция для подсчета живых соседей клетки
func countNeighbors(grid [][]bool, row, col int) int {
	count := 0
	
	// Проверяем все 8 соседей
	for i := -1; i <= 1; i++ {
		for j := -1; j <= 1; j++ {
			// Пропускаем саму клетку
			if i == 0 && j == 0 {
				continue
			}
			
			// Вычисляем координаты соседа с учетом тора (тороидальная геометрия)
			r := (row + i + height) % height
			c := (col + j + width) % width
			
			// Если сосед живой, увеличиваем счетчик
			if grid[r][c] {
				count++
			}
		}
	}
	
	return count
}

// Функция для создания нового поколения
func nextGeneration(current [][]bool) [][]bool {
	// Создаем новую сетку для следующего поколения
	next := make([][]bool, height)
	for i := range next {
		next[i] = make([]bool, width)
	}
	
	// Применяем правила игры жизни
	for i := 0; i < height; i++ {
		for j := 0; j < width; j++ {
			neighbors := countNeighbors(current, i, j)
			
			// Правила:
			// 1. Живая клетка с 2-3 соседями выживает
			// 2. Мертвая клетка с 3 соседями оживает
			// 3. В остальных случаях клетка умирает или остается мертвой
			
			if current[i][j] {
				// Живая клетка
				if neighbors == 2 || neighbors == 3 {
					next[i][j] = true
				} else {
					next[i][j] = false
				}
			} else {
				// Мертвая клетка
				if neighbors == 3 {
					next[i][j] = true
				} else {
					next[i][j] = false
				}
			}
		}
	}
	
	return next
}

// Функция для отображения сетки
func display(grid [][]bool, generation int) {
	// Очищаем экран
	fmt.Print("\033[H\033[2J")
	
	// Отображаем номер поколения
	fmt.Printf("Поколение: %d\n", generation)
	fmt.Println("Нажмите Ctrl+C для выхода")
	fmt.Println()
	
	// Отображаем сетку
	for i := 0; i < height; i++ {
		for j := 0; j < width; j++ {
			if grid[i][j] {
				// Живая клетка - цветной блок
				fmt.Print("\033[42m  \033[0m")
			} else {
				// Мертвая клетка - пробел
				fmt.Print("  ")
			}
		}
		fmt.Println()
	}
}

func main() {
	// Инициализируем генератор случайных чисел
	rand.Seed(time.Now().UnixNano())
	
	// Создаем начальную сетку
	grid := make([][]bool, height)
	for i := range grid {
		grid[i] = make([]bool, width)
	}
	
	// Заполняем сетку случайными значениями
	seed(grid)
	
	generation := 0
	
	fmt.Println("Игра жизни Конвея")
	fmt.Println("=================")
	
	// Основной игровой цикл
	for {
		// Отображаем текущее состояние
		display(grid, generation)
		
		// Обновляем сетку
		grid = nextGeneration(grid)
		generation++
		
		// Задержка между поколениями
		time.Sleep(200 * time.Millisecond)
	}
}