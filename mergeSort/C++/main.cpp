#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::string;

// Contains entries that need to be sorted
#define PATH_TO_SORT "../toSort.txt"
// Contains already sorted entries
#define PATH_SORTED "../sorted.txt"

vector<int>* read_table(const char *path) {
    // Reads the contents of an unsorted table and returns pointer to
    // User must provide amount argument, where the amount of numbers to sort
    // will be stored
    //
    // Args:
    //   path: Path to file to open
    //
    // Returns:
    //   Pointer to vector containing integers
    ifstream f(path);
    if (!f.is_open()) {
        cout << "Failed to open file: " << path << endl;
        return 0;
    }

    // Omit the first two lines, there are just comments
    string line;
    getline(f, line);
    getline(f, line);

    // Store the amount
    int amount;
    f >> amount;

    // Create the vector to hold the data
    vector<int> *tab = new vector<int>();
    int i;
    while (f >> i) {
        tab->push_back(i);
    }

    f.close();
    return tab;
}

static void _merge(vector<int> *tab, int start, int end, vector<int> *buffer) {
    // Merges table
    //
    // Args:
    //   tab: table to merge
    //   start: start of the table
    //   end: end of the table
    //   buffer: buffer to store temporary values
    int left = start;
    int half = (end + start) / 2;
    int right = half;
    int bufPtr = start;

    // Copy data into buffer, it will be sorted data
    while ((left < half) && (right < end)) {
        if ((*tab)[left] < (*tab)[right]) {
            (*buffer)[bufPtr++] = (*tab)[left++];
        } else {
            (*buffer)[bufPtr++] = (*tab)[right++];
        }
    }

    while (left < half) {
        (*buffer)[bufPtr++] = (*tab)[left++];
    }

    while (right < end) {
        (*buffer)[bufPtr++] = (*tab)[right++];
    }

    // Now copy the sorted data to original table
    for (left = start; left < end; ++left) {
        (*tab)[left] = (*buffer)[left];
    }
}

static void _merge_sort(vector<int> *tab, int start, int end, vector<int> *buffer) {
    // Sort the provided table from start to end. Allocated buffer must be
    // provided to store the sorted data
    //
    // Args:
    //   tab: Table of ints to sort
    //   start: start of the table
    //   end: end of table (note, range is [start; end)
    //   buffer: Allocated buffer. Should be at least the same size as tab

    // We only have one element? Nothing to sort...
    if (end - start < 2) {
        return;
    }

    // Divide and conquer!
    int half = (end + start) / 2;
    _merge_sort(tab, start, half, buffer);
    _merge_sort(tab, half, end, buffer);
    _merge(tab, start, end, buffer);
}

void merge_sort(vector<int> *tab) {
    // Calls the underlying mergeSort algorithm and sorts the provided vector
    //
    // Args:
    //   tab: vector to sort
    vector<int> *buffer = new vector<int>(tab->size());
    _merge_sort(tab, 0, tab->size(), buffer);

    delete buffer;
}

int compare_table(vector<int> *tab1, vector<int> *tab2) {
    // Compares two tables, it is quietly assumed, that both have the same
    // amount of entries. If there are is a single diffirence, it is pointed out
    //
    // Args:
    //   tab1: First vector of ints to compare
    //   tab2: Second vector of ints to compare
    //
    // Returns:
    //   0 if vectors are the same
    int i;
    for (i = 0; i < tab1->size(); ++i) {
        if ((*tab1)[i] != (*tab2)[i]) {
            cout << "Diffirence at: " << i << endl;
            cout << ">>>" << (*tab1)[i] << " " << (*tab2)[i] << endl;
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    vector<int> *to_sort = read_table(PATH_TO_SORT);

    if (to_sort == 0) {
        cout << "Failed to read table from file: " << PATH_TO_SORT << endl;
        return -1;
    }
    vector<int> *sorted = read_table(PATH_SORTED);

    if (sorted == 0) {
        cout << "Failed to read table from file: " << PATH_SORTED << endl;
        delete to_sort;
        return -1;
    }

    merge_sort(to_sort);

    if (compare_table(to_sort, sorted) != 0) {
        cout << "Table wasn't sorted correctly!" << endl;
        delete to_sort;
        delete sorted;
        return -1;
    }

    delete to_sort;
    delete sorted;
    cout << "Table sorted correctly!" << endl;
    return 0;
}
