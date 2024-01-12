#include "heap_operations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif

// #define PRINT_ALL_RESULT

#ifdef PRINT_ALL_RESULT
#define cond_printf(...) printf(__VA_ARGS__)
#else
#define cond_printf(...) do {} while(0)
#endif

// heapify an int array to max heap
int heapify_int() {

    int arr[] = {5, 1, 19, 14, 6, 4, 7, 18, 16, 3, 10, 8, 20, 9, 2, 11, 12, 13, 17, 15};
    const size_t n = sizeof(arr) / sizeof(int);

    // heapify the array to max heap
    for (size_t i = n / 2 - 1; i != SIZE_MAX; --i) {
        HEAP_MAX_SIFTDOWN(arr, i, n, int);
    }

    // check if array is a max heap
    int test_ok = 1;
    for (size_t i = 0; i < n; ++i) {

        if (i * 2 + 1 < n) {
            test_ok = arr[i] > arr[i * 2 + 1] ? test_ok : 0;
        }

        if (i * 2 + 2 < n) {
            test_ok = arr[i] > arr[i * 2 + 2] ? test_ok : 0;
        }
    }

    // print result
    for (size_t i = 0; i < n; ++i) {
        cond_printf("%d ", arr[i]);
    }
    cond_printf("\n");

    return test_ok;
}

// heapify a struct array to min heap
int heapify_struct() {

    struct example {
        float key;
        int value;
    };

    struct example arr[] = {{0.72, 85}, {0.28, 84}, {0.66, 13}, {0.91, 25}, {0.46, 51}, {0.93, 27}, {0.13, 96}, {0.29, 59}, {0.15, 32}, {0.62, 77}};
    const size_t n = sizeof(arr) / sizeof(struct example);

#define EXAMPLE_GET_KEY(a) a.key

    // heapify the array to min heap
    for (size_t i = n / 2 - 1; i != SIZE_MAX; --i) {
        HEAP_MIN_SIFTDOWN_FGET(arr, i, n, struct example, EXAMPLE_GET_KEY);
    }

#undef EXAMPLE_GET_KEY

    // check if array is a min heap
    int test_ok = 1;
    for (size_t i = 0; i < n; ++i) {

        if (i * 2 + 1 < n) {
            test_ok = arr[i].key < arr[i * 2 + 1].key ? test_ok : 0;
        }

        if (i * 2 + 2 < n) {
            test_ok = arr[i].key < arr[i * 2 + 2].key ? test_ok : 0;
        }
    }

    // print result
    for (size_t i = 0; i < n; ++i) {
        cond_printf("(%.2f, %d) ", arr[i].key, arr[i].value);
    }
    cond_printf("\n");

    return test_ok;
}

int compare_double(double a, double b) {
    return a > b;
}

// sort a double sequence using strcmp function
int heapsort_double() {

    double arr[] = {0.06, -0.59, 0.8, 0.46, -0.37, -0.43, 0.69, -0.22, -0.82, 0.63, -0.23, -0.0, -0.14, 0.12, -0.89, 0.94, 0.53, 0.96, -0.32, 0.88};
    const size_t n = sizeof(arr) / sizeof(double);

    // to do heapsort, build the heap first
    for (size_t i = n / 2 - 1; i != SIZE_MAX; --i) {
        // HEAP_MAX_SIFTDOWN(arr, i, n, double);
        HEAP_SIFTDOWN_FCMP(arr, i, n, double, compare_double);
    }

    // print the intermidiate result
    for (size_t i = 0; i < n; ++i) {
        cond_printf("%.2lf ", arr[i]);
    }
    cond_printf("\n");

    // to do heap sort, iteratively swap the heap top to last position and call siftdown()
    for (size_t i = n - 1; i > 0; --i) {
        double swap = arr[i];
        arr[i] = arr[0];
        arr[0] = swap;

        // HEAP_MAX_SIFTDOWN(arr, 0, i, double);
        HEAP_SIFTDOWN_FCMP(arr, 0, i, double, compare_double);
    }

    // print the final result
    for (size_t i = 0; i < n; ++i) {
        cond_printf("%.2lf ", arr[i]);
    }
    cond_printf("\n");

    int test_ok = 1;
    for (size_t i = 0; i < n - 1; ++i) {
        test_ok = arr[i] <= arr[i + 1] ? test_ok : 0;
    }

    return test_ok;
}

// sort a string (const char *) sequence using strcmp function
int heapsort_lexical() {
    
    const char *words[] = {
    "apple", "table", "purple", "orange", "banana",
    "grape", "water", "earth", "sunny", "happy",
    "music", "cloud", "ocean", "smile", "peace",
    "charm", "flame", "clever", "zebra", "mirror",
    "garden", "moon", "velvet", "silence", "sparkle",
    "whisper", "courage", "ruby", "jazz", "breeze",
    "novel", "crimson", "twilight", "cascade", "serene",
    "lively", "piano", "emerald", "whimsical", "serendipity",
    "ethereal", "rhythm", "harmony", "gratitude", "tranquil",
    "passion", "enchant", "azure", "cascade", "radiant"
};

    const size_t n = sizeof(words) / sizeof(const char *);

// strcmp returns either (1, 0, -1), to sort lexically, should modify strcmp
#define MY_STRCMP_(s1, s2) (strcmp(s1, s2) >= 0)

    // to do heapsort, build the heap first
    for (size_t i = n / 2 - 1; i != SIZE_MAX; --i) {
        HEAP_SIFTDOWN_FCMP(words, i, n, const char *, MY_STRCMP_);
    }

    // print the intermidiate result
    for (size_t i = 0; i < n; ++i) {
        cond_printf("%s ", words[i]);
    }
    cond_printf("\n");

    // to do heap sort, iteratively swap the heap top to last position and call siftdown()
    for (size_t i = n - 1; i > 0; --i) {
        const char * swap = words[i];
        words[i] = words[0];
        words[0] = swap;

        HEAP_SIFTDOWN_FCMP(words, 0, i, const char *, MY_STRCMP_);
    }

    // print the final result
    for (size_t i = 0; i < n; ++i) {
        cond_printf("%s ", words[i]);
    }
    cond_printf("\n");

    // check lexical order
    int test_ok = 1;
    for (size_t i = 0; i < n - 1; ++i) {
        test_ok = MY_STRCMP_(words[i + 1], words[i]) ? test_ok : 0;
    }

#undef MY_STRCMP_

    return test_ok;
}

// test the heap push and pop
int heap_pushpop() {

    struct point {
        int x;
        int y;
    };

#define COMPARE_POINT_X(p1, p2) (p1.x < p2.x)

    struct point * points = malloc(50 * sizeof(struct point));
    size_t heapsize = 0;
    int test_ok = 1;

#define PUSH(ptx, pty)                                                     \
    do                                                                     \
    {                                                                      \
        points[heapsize] = (struct point){.x = ptx, .y = pty};             \
        HEAP_SIFTUP_FCMP(points, heapsize, struct point, COMPARE_POINT_X); \
        heapsize++;                                                        \
    } while (0)

#define POP(...)                                                                    \
    do                                                                              \
    {                                                                               \
        if (heapsize)                                                               \
        {                                                                           \
            points[0] = points[--heapsize];                                         \
            HEAP_SIFTDOWN_FCMP(points, 0, heapsize, struct point, COMPARE_POINT_X); \
        }                                                                           \
    } while (0)

    PUSH(3, 5);
    PUSH(1, 2);
    PUSH(5, 0);

    test_ok = points[0].y == 2 ? test_ok : 0;
    cond_printf("top: %d,%d\n", points[0].x, points[0].y);

    PUSH(8, 1);
    PUSH(2, 4);
    PUSH(4, 7);

    test_ok = points[0].y == 2 ? test_ok : 0;
    cond_printf("top: %d,%d\n", points[0].x, points[0].y);

    POP();
    POP();

    test_ok = points[0].y == 5 ? test_ok : 0;
    cond_printf("top: %d,%d\n", points[0].x, points[0].y);

    POP();
    POP();

    test_ok = points[0].y == 0 ? test_ok : 0;
    cond_printf("top: %d,%d\n", points[0].x, points[0].y);

    POP();
    POP();
    test_ok = heapsize == 0 ? test_ok : 0;

#undef COMPARE_POINT_X
#undef PUSH
#undef POP

    free(points);

    return test_ok;
}

int main() {

    printf(" * correctness of heapify_int is: %d\n", heapify_int());
    printf(" * correctness of heapify_struct is: %d\n", heapify_struct());
    printf(" * correctness of heapsort_double is: %d\n", heapsort_double());
    printf(" * correctness of heapsort_lexical is: %d\n", heapsort_lexical());
    printf(" * correctness of heap_pushpop is: %d\n", heap_pushpop());

    return 0;
}