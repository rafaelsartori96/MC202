#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sorting.h"


/* Auxiliary functions headers */

void mergesort_r(int *vector, int *auxiliary, int start, int end);
void merge(int *vector, int *auxiliary, int start, int middle, int end);

void quicksort_p(int *vector, int start, int end);
void quicksort_np(int *vector, int start, int end);
int quicksort_p_(int *vector, int start, int end);

int qsort_comparator(const void *a, const void *b);

#define left(node) ((node << 1) + 1)
#define right(node) ((node + 1) << 1)
#define parent(node) ((node - 1) >> 1)

void maintain_maximum_heap(int *vector, int length, int current_position);


/* Auxiliary functions */

void swap(int *a, int *b) {
    int auxiliary = *a;
    *a = *b;
    *b = auxiliary;
}


int random_(int min, int max) {
    return min + (rand() % (max + 1 - min));
}


void print(int *vector, int start, int end) {
    for(int i = start; i <= end; i++) {
        if(i > start) {
            printf(", ");
        }
        printf("%d", *(vector + i));
    }
    printf("\n");
}


/* Sorting algorithms */

void quicksort_no_partition(int *vector, int length) {
    quicksort_np(vector, 0, length - 1);
}


void quicksort_np(int *vector, int start, int end) {
    int i = start, j = end, middle = ((i + j) >> 1);
    int pivot = *(vector + middle);

    do {
        while(*(vector + i) < pivot) i++;
        while(*(vector + j) > pivot) j--;

        if(i <= j) {
            int auxiliary = *(vector + i);
            *(vector + i) = *(vector + j);
            *(vector + j) = auxiliary;
            i++;
            j--;
        }
    } while(j > i);

    if(start < j) quicksort_np(vector, start, j);
    if(i < end) quicksort_np(vector, i, end);
}


void quicksort_partition(int *vector, int length) {
    srand(time(NULL));
    quicksort_p(vector, 0, length - 1);
}


void quicksort_p(int *vector, int start, int end) {
    if(start < end) {
        int partition = quicksort_p_(vector, start, end);
        quicksort_p(vector, start, partition - 1);
        quicksort_p(vector, partition + 1, end);
    }
}


int quicksort_p_(int *vector, int start, int end) {
    swap((vector + random_(start, end)), (vector + start));
    int partition = *(vector + start);

    int left = start, right = end;
    while(left < right) {
        /* Shift left position to the right until we find an element that is
        * greater than the partition or hit the end */
        while(*(vector + left) <= partition && left < end) {
            left++;
        }

        /* Shift right position to the left until we find an element that is
        * lower than the partition or hit the start */
        while(*(vector + right) > partition && right > start) {
            right--;
        }

        /* If there is an element that is greater than the partition on the
        * left side and a lower on the right side, swap them */
        if(left < right) {
            swap((vector + left), (vector + right));
        }
    }

    /* Since partition was kept on the first element, swap it to the position
    * it should be */
    swap((vector + start), (vector + right));
    return right;
}


void qsort_(int *vector, int length) {
    qsort(vector, length, sizeof(int), qsort_comparator);
}


int qsort_comparator(const void *a_, const void *b_) {
    int a = *((int *) a_), b = *((int *) b_);
    if(a > b) {
        /* 'a' should go after 'b', so return 1 */
        return 1;
    } else if(a == b) {
        return 0;
    } else {
        /* 'a' should go before 'b', so return -1 */
        return -1;
    }
}


void selectionsort(int *vector, int length) {
    /* Start with the last item, that should be the greatest one */
    for(int i = length - 1; i >= 0; i--) {
        /* Run the vector finding the greater value */
        int max = 0;
        for(int j = 0; j <= i; j++) {
            if(*(vector + j) > *(vector + max)) {
                max = j;
            }
        }

        swap((vector + max), vector + i);
    }
}


// void bogosort(int *vector, int length) {
//
// }


void mergesort(int *vector, int length) {
    int *auxiliary = malloc(length * sizeof(int));

    /* Merge sort recursively */
    mergesort_r(vector, auxiliary, 0, length - 1);

    /* Clean up resources */
    free(auxiliary);
}


void mergesort_r(int *vector, int *auxiliary, int start, int end) {
    if(start < end) {
        int middle = (start + end) / 2;

        /* Break vector recursively */
        mergesort_r(vector, auxiliary, start, middle);
        mergesort_r(vector, auxiliary, middle + 1, end);
        /* Merge vector using auxiliary */
        merge(vector, auxiliary, start, middle, end);
    }
}


void merge(int *vector, int *auxiliary, int start, int middle, int end) {
    /* Copy left side to the auxiliary, we can assume they're in order on the
    * left side */
    for(int i = start; i <= middle; i++) {
        *(auxiliary + i) = *(vector + i);
    }

    /* Copy right side. We again can assume they're in order on the right side,
    * just like the left one */
    for(int i = middle + 1; i <= end; i++) {
        *(auxiliary + end + middle + 1 - i) = *(vector + i);
    }

    int i = start, j = end;
    for(int k = start; k <= end; k++) {
        /* Copy back to the vector in order, merging both sides using the
        * auxiliary vector */
        if(*(auxiliary + i) <= *(auxiliary + j)) {
            *(vector + k) = *(auxiliary + i);
            i++;
        } else {
            *(vector + k) = *(auxiliary + j);
            j--;
        }
    }
}


void heapsort(int *vector, int length) {
    /* Note: this is a maximum heap, after building it, we will remove the
    * maximum and put it on the end of the vector */

    /* We will start 'inserting' items on the vector, just as a heap would.
    * Since we won't need to check the parent of the first node, start at
    * index 1 */
    for(int i = 1; i < length; i++) {
        int current_position = i, parent_position = parent(current_position);

        /* Check if the parent isn't greater than current node. This should be
        * done to every parent after swaps (but we don't need to re-check
        * everything if we don't swap) */
        while(*(vector + parent_position) < *(vector + current_position)) {
            /* Since we're building a maximum heap, we must swap with the
            * parent and check again for the parent_position */
            swap((vector + parent_position), (vector + current_position));
            current_position = parent_position;
            if(current_position == 0) break;
            parent_position = parent(current_position);
        }
    }

    /* Now that we have a maximum heap, let's start 'removing' items and
    * inserting the maximum nodes on the end of the vector. */
    while(1) {
        /* Like other heap removals, lets swap the maximum node with the last
        * position */
        swap((vector + length - 1), (vector + 0));
        /* Decrease the length. The removed node will be on its correct
        * place */
        length--;

        if(length > 0) {
            maintain_maximum_heap(vector, length, 0);
        } else {
            break;
        }
    }
}


void maintain_maximum_heap(int *vector, int length, int current_position) {
    /* Maintain heap: let's check if the child exists and it is not greater
    * than the current node */

    int max_child_position = left(current_position);
    /* Check if the node doesn't have a left child */
    if(max_child_position >= length) {
        return;
    }

    /* Set the minimum child as the left one */
    int max_child = *(vector + max_child_position);

    /* Check if there is a right child */
    int right_child_position = right(current_position);
    if(right_child_position < length) {
        /* Store right child value since we'll be going to use it later */
        int right_child = *(vector + right_child_position);

        if(right_child > max_child) {
            max_child_position = right_child_position;
            max_child = right_child;
        }
    }

    /* Check if the greatest child is greater than the parent */
    if(max_child > *(vector + current_position)) {
        swap((vector + current_position), (vector + max_child_position));

        /* Now do the same thing to the child position */
        maintain_maximum_heap(vector, length, max_child_position);
    }
}
