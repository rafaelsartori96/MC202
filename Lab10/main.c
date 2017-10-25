#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "sorting.h"


#define SECONDS_TO_NANOSECONDS 1000000000


/**
* Prints help message for program usage.
*/
void print_help();

/**
* Prints help message for the list of available sorting methods.
*/
void print_sorting_functions();

/**
* Generates a test: a vector of number_of_integers random integers to be sorted.
*/
void generate_test(FILE *file, int number_of_integers);

/**
* Sort the vector using the given function as a parameter. It'll print the time taken
* as microseconds.
*/
int sort(int *vector, int length, void (*sort_method)(int *, int), int test_method);

/**
* Check if the sorting was done right.
*
* Returns   0   if the vector was not sorted correcly,
*           1   if the vector was successfully sorted.
*/
int valid_sort(int *vector, int length);

/**
* Example function, just to test the script and passing functions as arguments.
*/
void sort_example(int *vector, int length) {
    //sleep(5);
    unsigned long int j =0;
    for(unsigned int i = 0; i < 3000000000; i++) {
        j += i;
    }
    printf("%lu\n", j);
}


int main(int arguments_count, char **arguments) {
    /* Ignore the program name */
    arguments_count--;
    arguments++;

    /* Check if we have enough arguments */
    if(arguments_count < 3) {
        print_help();
    }

    int sort_test = strcmp(*(arguments + 0), "sortt") == 0;
    if(sort_test || strcmp(*(arguments + 0), "sort") == 0) {
        /* Test vector of given file name */
        char file_name[32];
        strcpy(file_name, *(arguments + 1));

        char *sorting_method = *(arguments + 2);
        void (*sorting_function)(int *, int) = NULL;

        /* Check sorting method */
        if(strcmp("quicksort_p", sorting_method) == 0) {
            sorting_function = quicksort_partition;
        } else if(strcmp("quicksort_np", sorting_method) == 0) {
            sorting_function = quicksort_no_partition;
        } else if(strcmp("qsort", sorting_method) == 0) {
            sorting_function = qsort_;
        } else if(strcmp("heapsort", sorting_method) == 0) {
            sorting_function = heapsort;
        } else if(strcmp("selectionsort", sorting_method) == 0) {
            sorting_function = selectionsort;
        } else if(strcmp("mergesort", sorting_method) == 0) {
            sorting_function = mergesort;
        // } else if(strcmp("bogosort", sorting_method) == 0) {
        //     sorting_function = bogosort;
        } else if(strcmp("test", sorting_method) == 0) {
            sorting_function = sort_example;
        } else if(sorting_function == NULL) {
            print_sorting_functions();
            return 0;
        }

        /* Attempt to open test file */
        FILE *file = fopen(file_name, "r");
        if(file == NULL) {
            fprintf(stderr, "Failed to read file \"%s\".\n", file_name);
            return -1;
        }

        /* Receive the number of integers on the test */
        int number_of_integers;
        fscanf(file, "%d", &number_of_integers);

        /* Attempt to allocate memory for the test */
        int *vector = malloc(number_of_integers * sizeof(int));
        if(vector == NULL) {
            fprintf(stderr, "Failed to allocate memory for vector.\n");
            return -2;
        }

        /* Read all integers from test file */
        for(int i = 0; i < number_of_integers; i++) {
            fscanf(file, "%d", (vector + i));
        }

        /* Test the vector and prints the time taken */
        int sorted = sort(vector, number_of_integers, sorting_function, sort_test);

        /* Clear resources */
        free(vector);

        /* Close file */
        fclose(file);

        /* Return sort status (0 means success) */
        return sorted == 1 ? 0 : -1;
    } else if(strcmp(*(arguments + 0), "generate") == 0) {
        /* Generates a test on given file name */
        char file_name[32];
        strcpy(file_name, *(arguments + 1));

        /* Reads the number of integers */
        int number_of_integers;
        sscanf(*(arguments + 2), "%d", &number_of_integers);

        /* Attempt to create a file */
        FILE *file = fopen(file_name, "w");
        if(file == NULL) {
            fprintf(stderr, "Failed to write file \"%s\".\n", file_name);
            return -1;
        }

        /* Generate the file and closes */
        generate_test(file, number_of_integers);
        fclose(file);
    } else {
        print_help();
    }

    return 0;
}


void print_help() {
    printf(
        "./{program} {command} {options}\n\n"
        "Commands:\n"
        "sort {file name} {method}: sort a vector given sorting algorithm\n"
        "generate {file name} {number of integers}: generate a test for the"
        " program.\n"
        "sortt {file name} {method}: same as sort, but checks if the vector was"
        " sorted correcly.\n"
        "Note: file names must follow [a-zA-Z_-] and have less than 32 "
        "characters.\n"
    );
}


void print_sorting_functions() {
    printf(
        "Available sorting methods are: \"quicksort_p\" (partitioning), "
        "\"quicksort_np\" (no partitioning), \"heapsort\", "
        "\"selectionsort_mm\", \"mergesort\", \"selectionsort\" and \"qsort\"\n"
    );
}


void generate_test(FILE *file, int number_of_integers) {
    struct timespec spec;
    clock_gettime(CLOCK_MONOTONIC, &spec);

    /* Randomize the seed a bit since we'll be generating every test one after
    * another and time(NULL) won't be precise enough */
    srand((spec.tv_sec * SECONDS_TO_NANOSECONDS) + spec.tv_nsec);

    /* Creates the file header */
    fprintf(file, "%d\n", number_of_integers);

    /* Generates a number of random integers */
    for(int i = 0; i < number_of_integers; i++) {
        fprintf(file, "%d ", rand());
    }

    /* Creates a new line */
    fprintf(file, "\n");
}


int sort(int *vector, int length, void (*sort_method)(int *, int), int test_method) {
    struct timespec start;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

    /* Execute sort method using the given function pointer */
    sort_method(vector, length);

    struct timespec end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    /* Check if the sort was valid */
    if(test_method && !valid_sort(vector, length)) {
        fprintf(stderr, "Failed to sort!\n");
        return 0;
    }

    /* Prints out the elapsed time in nanoseconds */
    printf(
        "%ld\n",
        ((end.tv_sec - start.tv_sec) * SECONDS_TO_NANOSECONDS) +
        (end.tv_nsec - start.tv_nsec)
    );
    return 1;
}


int valid_sort(int *vector, int length) {
    for(int i = 0; i < length - 2; i++) {
        /* Check if the next element is smaller than the current one */
        if(*(vector + i + 1) < *(vector + i)) {
            return 0;
        }
    }

    return 1;
}
