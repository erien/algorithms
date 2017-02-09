package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

const file_to_sort = "../toSort.txt"
const file_sorted = "../sorted.txt"

func readNumber(path string) []int {
	file, err := os.Open(path)

	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)
	// Omit first two lines
	scanner.Scan()
	scanner.Scan()

	// Store the amount
	scanner.Scan()
	amount, _ := strconv.Atoi(scanner.Text())

	// Fill the array with data
	toSort := make([]int, amount)
	i := 0
	for scanner.Scan() {
		toSort[i], _ = strconv.Atoi(scanner.Text())
		i = i + 1
	}

	return toSort
}

func main() {
	toSort := readNumber(file_to_sort)
	if toSort[0] > 1 {
		fmt.Println("done")
	}

	sorted := readNumber(file_sorted)
	if sorted[0] != 1 {
		fmt.Println("done")
	}

	fmt.Println("Table wasn't sorted correctly")
}
