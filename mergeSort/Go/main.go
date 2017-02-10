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

func readNumbers(path string) []int {
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

func _merge(toSort []int, start int, half int, end int, buffer []int) {
	left := start
	right := half
	i := start

	for left < half && right < end {
		if toSort[left] < toSort[right] {
			buffer[i] = toSort[left]
			left += 1
		} else {
			buffer[i] = toSort[right]
			right += 1
		}
		i += 1
	}

	for left < half {
		buffer[i] = toSort[left]
		i += 1
		left += 1
	}

	for right < end {
		buffer[i] = toSort[right]
		i += 1
		right += 1
	}

	i = start
	for i < end {
		toSort[i] = buffer[i]
		i += 1
	}

}

func _mergeSort(toSort []int, start int, end int, buffer []int) {
	if end-start <= 1 {
		return
	}

	half := (end + start) / 2
	_mergeSort(toSort, start, half, buffer)
	_mergeSort(toSort, half, end, buffer)
	_merge(toSort, start, half, end, buffer)
}

func mergeSort(toSort []int) {
	buffer := make([]int, len(toSort))
	_mergeSort(toSort, 0, len(toSort), buffer)
}

func main() {
	toSort := readNumbers(file_to_sort)
	sorted := readNumbers(file_sorted)

	mergeSort(toSort)

	if cmpArrays(toSort, sorted) == false {
		fmt.Println("Table wasn't sorted correctly")
		return
	}

	fmt.Println("Table was sorted correctly")
}
