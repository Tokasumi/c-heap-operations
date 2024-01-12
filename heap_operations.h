#ifndef _HEAP_OPERATIONS_H_
#define _HEAP_OPERATIONS_H_

#include <stddef.h> /* size_t */

#define _HEAP_COMPERATOR(objA, objB, fCmp, fGet) fCmp(fGet(objA), fGet(objB))

#define _HEAP_GET_IDENTITY(objA) objA

#define _HEAP_CMP_LT(objA, objB) (objA < objB)
#define _HEAP_CMP_GT(objA, objB) (objA > objB)

#define _HEAP_SIFTUP_PROTOTYPE(heap, pos, type, comperator, fcmp, fget) \
    do                                                                  \
    {                                                                   \
        size_t i_ = (size_t)pos; /* the `pos` variable may be const */  \
        type t_ = heap[i_];                                             \
        while (i_ > 0)                                                  \
        {                                                               \
            size_t parent_ = (i_ - 1) >> 1;                             \
            if (comperator(heap[parent_], t_, fcmp, fget))              \
            {                                                           \
                break;                                                  \
            }                                                           \
            heap[i_] = heap[parent_];                                   \
            i_ = parent_;                                               \
        }                                                               \
        heap[i_] = t_;                                                  \
    } while (0)

#define _HEAP_SIFTDOWN_PROTOTYPE(heap, pos, size, type, comperator, fcmp, fget)              \
    do                                                                                       \
    {                                                                                        \
        size_t root_ = (size_t)pos; /* the `pos` variable may be const */                    \
        size_t child_;                                                                       \
        while ((child_ = (root_ << 1) + 1) < size)                                           \
        {                                                                                    \
            if (child_ + 1 < size && comperator(heap[child_ + 1], heap[child_], fcmp, fget)) \
                child_++;                                                                    \
            if (comperator(heap[child_], heap[root_], fcmp, fget))                           \
            {                                                                                \
                type t_ = heap[root_];                                                       \
                heap[root_] = heap[child_];                                                  \
                heap[child_] = t_;                                                           \
                root_ = child_;                                                              \
            }                                                                                \
            else                                                                             \
            {                                                                                \
                break;                                                                       \
            }                                                                                \
        }                                                                                    \
    } while (0)

#define HEAP_SIFTUP_FCMP(pHeap, iPos, kwType, fCmp) \
    _HEAP_SIFTUP_PROTOTYPE(pHeap, iPos, kwType, _HEAP_COMPERATOR, fCmp, _HEAP_GET_IDENTITY)
#define HEAP_SIFTDOWN_FCMP(pHeap, iPos, iSize, kwType, fCmp) \
    _HEAP_SIFTDOWN_PROTOTYPE(pHeap, iPos, iSize, kwType, _HEAP_COMPERATOR, fCmp, _HEAP_GET_IDENTITY)

#define HEAP_MAX_SIFTUP_FGET(pHeap, iPos, kwType, fGet) \
    _HEAP_SIFTUP_PROTOTYPE(pHeap, iPos, kwType, _HEAP_COMPERATOR, _HEAP_CMP_GT, fGet)
#define HEAP_MIN_SIFTUP_FGET(pHeap, iPos, kwType, fGet) \
    _HEAP_SIFTUP_PROTOTYPE(pHeap, iPos, kwType, _HEAP_COMPERATOR, _HEAP_CMP_LT, fGet)

#define HEAP_MAX_SIFTDOWN_FGET(pHeap, iPos, iSize, kwType, fGet) \
    _HEAP_SIFTDOWN_PROTOTYPE(pHeap, iPos, iSize, kwType, _HEAP_COMPERATOR, _HEAP_CMP_GT, fGet)
#define HEAP_MIN_SIFTDOWN_FGET(pHeap, iPos, iSize, kwType, fGet) \
    _HEAP_SIFTDOWN_PROTOTYPE(pHeap, iPos, iSize, kwType, _HEAP_COMPERATOR, _HEAP_CMP_LT, fGet)

#define HEAP_MAX_SIFTUP(pHeap, iPos, kwType) \
    _HEAP_SIFTUP_PROTOTYPE(pHeap, iPos, kwType, _HEAP_COMPERATOR, _HEAP_CMP_GT, _HEAP_GET_IDENTITY)
#define HEAP_MIN_SIFTUP(pHeap, iPos, kwType) \
    _HEAP_SIFTUP_PROTOTYPE(pHeap, iPos, kwType, _HEAP_COMPERATOR, _HEAP_CMP_LT, _HEAP_GET_IDENTITY)

#define HEAP_MAX_SIFTDOWN(pHeap, iPos, iSize, kwType) \
    _HEAP_SIFTDOWN_PROTOTYPE(pHeap, iPos, iSize, kwType, _HEAP_COMPERATOR, _HEAP_CMP_GT, _HEAP_GET_IDENTITY)
#define HEAP_MIN_SIFTDOWN(pHeap, iPos, iSize, kwType) \
    _HEAP_SIFTDOWN_PROTOTYPE(pHeap, iPos, iSize, kwType, _HEAP_COMPERATOR, _HEAP_CMP_LT, _HEAP_GET_IDENTITY)

#endif /* _HEAP_OPERATIONS_H_ */