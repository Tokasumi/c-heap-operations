# c-heap-operations

Binary heap (priority queue) operations in plain C, single header, exploit C macro to support genric types.

## How to use

To use it, just include the header.

```c
#include "heap_operations.h"
```

### simple case

This code heapifys an array to a max-heap.

The `HEAP_MAX_SIFTDOWN` macro accepts 4 arguments: the array (or pointer) to heap body, the heap root index i, the heap size n, the element type (int in this case). The elements is expected to support `>` or `<`.

```c
int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
const size_t n = sizeof(arr) / sizeof(int); // n is the elements in arr

// heapify the array to max-heap
for (int i = n / 2 - 1; i >= 0; i--) {
    HEAP_MAX_SIFTDOWN(arr, i, n, int);
}

// this will print 9 8 7 4 5 6 3 2 1 0
for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
}
printf("\n");
```

### dealing with structures

`HEAP_MIN_SIFTUP_FGET` accepts one more argument at the last. `FGET` is a function-like (function or macro) that can map elements to priority values.

```c
struct student {
    char * name;
    int score;
};

char * names[] = {"Alice", "Bob", "Charlie", "David", "Eva", "Frank", "Grace", "Hank", "Ivy", "Jack"};
int scores[] = {85, 92, 78, 95, 88, 79, 91, 87, 93, 84};
struct student * students = malloc(10 * sizeof(struct student));

size_t heapsize = 0;

#define GET_SCORE(stu) (stu.score)

for (int i = 0; i < 10; i++) {
    // to insert an element into heap, first add the element to the array.
    students[heapsize].name = names[i];
    students[heapsize].score = scores[i];
    // then call siftup from the current index.
    HEAP_MIN_SIFTUP_FGET(students, i, struct student, GET_SCORE);
    // finnally, heapsize + 1
    heapsize++;
}

for (int i = 0; i < 10; i++) {
    printf("%s,%d ", students[i].name, students[i].score);
}
printf("\n");

free(students);
#undef GET_SCORE
```

The code should output `Charlie,78 Jack,84 Frank,79 Eva,88 Hank,87 Alice,85 Grace,91 David,95 Ivy,93 Bob,92`

### a more complex case: sorting strings

This repository provides `HEAP_SIFTDOWN_FCMP` and `HEAP_SIFTUP_FCMP`to supprot custom comparison function or macro.

if compare function (macro) is `f(a, b) -> (a > b)`, the heap will be a max-heap, if comapre function (macro) is `f(a, b) -> (a < b)`, the heap will be a min-heap.

The following case utilizes `strcmp` to sort strings in lexical order.

```c
static int strcmp_order(const char * a, const char * b) {
    return strcmp(a, b) >= 0;
}
```

```c
const char *words[] = {
"apple", "table", "purple", "orange", "banana", 
"grape", "water", "earth", "sunny", "happy", 
"music", "cloud", "ocean", "smile", "peace", 
"charm", "music", "sugar", "flame", "clever",
"zebra", "mirror", "garden", "moon", "velvet",
"silence", "sparkle", "whisper", "courage", "music"
};
const size_t n = sizeof(words) / sizeof(const char *);

// to do heapsort, build the heap first
for (int i = n / 2 - 1; i >= 0; i--) {
    HEAP_SIFTDOWN_FCMP(words, i, n, const char *, strcmp_order);
}

// to do heap sort, iteratively swap the heap top to last position and call siftdown()
for (size_t i = n - 1; i > 0; --i) {
    const char * swap = words[i];
    words[i] = words[0];
    words[0] = swap;
    HEAP_SIFTDOWN_FCMP(words, 0, i, const char *, strcmp_order);
}

// print the final result
for (size_t i = 0; i < n; ++i) {
    printf("%s ", words[i]);
}
printf("\n");
```

The code should print `apple banana charm clever cloud courage earth flame garden grape happy mirror moon music music music ocean orange peace purple silence smile sparkle sugar sunny table velvet water whisper zebra`

## Detailed Introduction of Algorithm

This repository implements two major heap operations: `siftUp` and `siftDown`.

### `siftUp` Operation:

The `siftUp` operation is used to maintain the heap property after inserting an element into a max binary heap. The max binary heap property ensures that the value of each node is greater than or equal to the values of its children. When a new element is inserted at the bottom of the heap, it may violate this property. `siftUp` is employed to restore the heap property by swapping the new element with its parent until the heap property is satisfied.

**Pseudocode:**

```python
procedure siftUp(heap, currentIndex):
    while currentIndex > 0:
        parentIndex = (currentIndex - 1) / 2
        if heap[currentIndex] > heap[parentIndex]:
            swap(heap[currentIndex], heap[parentIndex])
            currentIndex = parentIndex
        else:
            break
```

**Explanation:**

1. `currentIndex` is the index of the newly inserted element.
2. The loop continues as long as the current element is not the root (index 0).
3. `parentIndex` is calculated using the formula `(currentIndex - 1) / 2`, representing the index of the parent node.
4. If the value of the current element is greater than its parent's value, a swap is performed to move the current element up the heap.
5. The loop continues until the heap property is restored or until the current element reaches the root.

### `siftDown` Operation:

The `siftDown` operation is used to maintain the heap property after removing the root element from a max binary heap or replacing it with a smaller value. The idea is to move the element at the top (root) down the heap by swapping it with its larger child until the heap property is satisfied.

**Pseudocode:**

```python
procedure siftDown(heap, currentIndex, heapSize):
    while 2 * currentIndex + 1 < heapSize:
        leftChild = 2 * currentIndex + 1
        rightChild = 2 * currentIndex + 2
        maxIndex = currentIndex

        if leftChild < heapSize and heap[leftChild] > heap[maxIndex]:
            maxIndex = leftChild
        if rightChild < heapSize and heap[rightChild] > heap[maxIndex]:
            maxIndex = rightChild

        if maxIndex != currentIndex:
            swap(heap[currentIndex], heap[maxIndex])
            currentIndex = maxIndex
        else:
            break
```

**Explanation:**

1. `currentIndex` is the index of the element to be moved down in the heap.
2. The loop continues as long as the left child of the current element exists within the heap.
3. `leftChild` and `rightChild` are calculated to represent the indices of the left and right children, respectively.
4. `maxIndex` is initially set to the current index and then updated to the index of the larger child, if any.
5. If the value of the current element is less than the value of its larger child, a swap is performed, and the loop continues.
6. The loop continues until the heap property is restored or until the current element has no valid children.

Both `siftUp` and `siftDown` are crucial for maintaining the integrity of the max binary heap and ensuring efficient operations for insertion and removal.
