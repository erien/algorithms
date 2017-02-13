#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Contains entries that need to be sorted
#define PATH_TO_SORT "../../toSort.txt"
// Contains already sorted entries
#define PATH_SORTED "../../sorted.txt"

static int* read_table(const char *path, int *amount) {
    // Reads the contents of an unsorted table and returns pointer to it.
    // User must provide amount argument, where the amount of numbers to sort
    // will be stored (that amount is read from  the file)
    //
    // Args:
    //   path: Path to file to open. First two lines are comments,
    //         third line is the amount of numbers to sort
    //   amount: Will store the size of the returned table of ints
    //
    // Returns:
    //   Pointer to allocated table filled with unsorted ints. If 0, than
    //   reading file has failed.
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Failed to open file: %s\n", path);
        return 0;
    }

    // Omit the first two lines, there are just comments
    char *line;
    size_t len = 0;
    size_t read;

    read = getline(&line, &len, f);
    if (read == -1) {
        printf("Failed while reading file: %s\n", path);
        return 0;
    }

    read = getline(&line, &len, f);
    if (read == -1) {
        printf("Failed while reading file: %s\n", path);
        return 0;
    }

    // Store the amount of numbers to sort
    fscanf(f, "%d", amount);

    int *tab = (int *)malloc(sizeof(int) * *amount);
    int i;

    for (i = 0; i < *amount; ++i) {
        fscanf(f, "%d", &tab[i]);
    }

    fclose(f);
    return tab;
}

static int compare_table(int *tab1, int *tab2, int amount) {
    // Compares two tables, it is quietly assumed, that both have the same
    // amount of entries. If there are is a single diffirence, it is pointed out
    //
    // Args:
    //   tab1: First table of ints to compare
    //   tab2: Second table of ints to compare
    //   amount: Amount of entries in the table
    //
    // Returns:
    //   0 if tables are the same, -1 if not
    int i;
    for (i = 0; i < amount; ++i) {
        if (tab1[i] != tab2[i]) {
            printf("Diffirence at: %d\n", i);
            printf(">>>%d %d\n", tab1[i], tab2[i]);
            return -1;
        }
    }

    return 0;
}

void quick_sort(int *tab, int amount) {
    // Performs quick sort algorithm on provided table
    return;
}


int main(int argc, char *argv[]) {
    int amount;
    int *to_sort = read_table(PATH_TO_SORT, &amount);

    if (to_sort == 0) {
        printf("Failed to read table from file: %s\n", PATH_TO_SORT);
        return errno;
    }

    int *sorted = read_table(PATH_SORTED, &amount);

    if (sorted == 0) {
        printf("Failed to read table from file: %s\n", PATH_SORTED);
        free(to_sort);
        return errno;
    }

    quick_sort(to_sort, amount);

    if (compare_table(to_sort, sorted, amount) != 0) {
        printf("Table wasn't sorted correctly!\n");
        free(to_sort);
        free(sorted);
        return -1;
    }

    free(to_sort);
    free(sorted);

    printf("Table sorted correctly!\n");
    return 0;
}
