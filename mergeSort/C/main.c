#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Contains entries that need to be sorted
#define PATH_TO_SORT "../toSort.txt"
// Contains already sorted entries
#define PATH_SORTED "../sorted.txt"

int* read_table(const char *path, int *amount) {
    // Reads the contents of an unsorted table and returns pointer to
    // User must provide amount argument, where the amount of numbers to sort
    // will be stored
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

static void _merge_sort(int *tab, int start, int end, int *buffer) {
    if (end - start < 2) {
        return;
    }

    int half = (end + start) / 2;
    _merge_sort(tab, start, half, buffer);
    _merge_sort(tab, half, end, buffer);

    int left = start;
    int right = half;
    int bufPtr = start;

    while ((left < half) && (right < end)) {
        if (tab[left] < tab[right]) {
            buffer[bufPtr++] = tab[left++];
        } else {
            buffer[bufPtr++] = tab[right++];
        }
    }

    while (left < half) {
        buffer[bufPtr++] = tab[left++];
    }

    while (right < end) {
        buffer[bufPtr++] = tab[right++];
    }

    for (left = start; left < end; ++left) {
        tab[left] = buffer[left];
    }
}

void merge_sort(int *tab, int amount) {
    int *buffer = (int *)malloc(sizeof(int) * amount);

    _merge_sort(tab, 0, amount, buffer);

    free(buffer);
}

int compare_table(int *tab1, int *tab2, int amount) {
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
        return errno;
    }

    merge_sort(to_sort, amount);

    if (compare_table(to_sort, sorted, amount) != 0) {
        printf("Table wasn't sorted correctly!\n");
        return -1;
    }

    printf("Table sorted correctly!\n");
    return 0;
}
