#include "heap_operations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void example1() {
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
}

void example2() {
    
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

    // Charlie,78 Jack,84 Frank,79 Eva,88 Hank,87 Alice,85 Grace,91 David,95 Ivy,93 Bob,92
    for (int i = 0; i < 10; i++) {
        printf("%s,%d ", students[i].name, students[i].score);
    }
    printf("\n");

#undef GET_SCORE
}

static int strcmp_order(const char * a, const char * b) {
    return strcmp(a, b) >= 0;
}

void example3() {
    
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

}

int main() {

    example1();
    example2();
    example3();

    return 0;
}