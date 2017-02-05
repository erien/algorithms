TO_SORT = "../toSort.txt"
SORTED = "../sorted.txt"

def read_table_from_file(path:str) -> list:
    """Reads table from a file and creates appropriate table...
    I mean list!
    
    Args:
        path: Path to the file

    Returns:
        Read table
    """
    with open(path, "r") as f:
        # Omit first two lines (they're comments)
        f.readline()
        f.readline()
        # Omit the line with amount, we don't need that
        f.readline()

        # Now read the rest of the numbers
        tab = []
        for line in f.readlines():
            tab.append(int(line))

        return tab

def _merge(tab:list, start:int, end:int):
    """Merges tables

    Args:
        tab: Table to merge
        start: start of the chunk to merge
        end: end of the chunk (not included) to merge
    """
    half = (end + start) // 2
    left = start
    right = half
    buffer = []

    while ((left < half) and (right < end)):
        if (tab[left] < tab[right]):
            buffer.append(tab[left])
            left += 1
        else:
            buffer.append(tab[right])
            right += 1

    while (left < half):
        buffer.append(tab[left])
        left += 1

    while (right < end):
        buffer.append(tab[right])
        right += 1

    i = 0
    while (start < end):
        tab[start] = buffer[i]
        start += 1
        i += 1


def _merge_sort(tab:list, start:int, end:int):
    """Performs merge sort, what did you expect?
    The range is [start; end)

    Args:
        tab: Table to sort
        start: start of the chunk to sort
        end: end of the chunk (not included) to sort
    """
    if end - start < 2:
        return

    half = (end + start) // 2
    _merge_sort(tab, start, half)
    _merge_sort(tab, half, end)

    _merge(tab, start, end)

def merge_sort(tab:list):
    """Sortes the table using merge sort algorithm

    Args:
        tab: tab to be sorted
    """
    _merge_sort(tab, 0, len(tab))

def main():
    to_sort = read_table_from_file(TO_SORT)
    sorted = read_table_from_file(SORTED)

    merge_sort(to_sort)

    assert(to_sort == sorted)

    print("Table was sorted correctly!")
    return 0

main()

