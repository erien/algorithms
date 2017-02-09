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

func cmpArrays(a []int, b []int) bool {
	if a == nil && b == nil {
		return true
	}

	if a == nil || b == nil {
		return false
	}

	if len(a) != len(b) {
		return false
	}

	for i := range a {
		if a[i] != b[i] {
			return false
		}
	}

	return true
}

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
	sorted := readNumber(file_sorted)

	if cmpArrays(toSort, sorted) == false {
		fmt.Println("Table wasn't sorted correctly")
		return
	}

	fmt.Println("Table was sorted correctly")
}
