#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


#define SECONDS_TO_MICROSECONDS 1000000


/**
* Prints help message for program usage
*/
void print_help();

/**
* Generates a test: a vector of number_of_integers random integers to be sorted.
*/
void generate_test(FILE *file, int number_of_integers);

/**
* Sort the vector using the given function as a parameter. It'll print the time taken
* as microseconds.
*/
void sort(int *vector, int length, void (*sort_method)(int *, int));

/**
* Example function, just to test the script and passing functions as arguments.
*/
void sort_example(int *vector, int length) {
    int i, j = 0;
    for(i = 0; i < 50000; i++) {
        j += i;
    }
}


int main(int arguments_count, char **arguments) {
    /* Ignore the program name */
    arguments_count--;
    arguments++;

    /* Check if we have enough arguments */
    if(arguments_count < 2) {
        print_help();
    }

    if(strcmp(*(arguments + 0), "sort") == 0) {
        /* Test vector of given file name */
        char file_name[32];
        strcpy(file_name, *(arguments + 1));

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
        int i;
        for(i = 0; i < number_of_integers; i++) {
            fscanf(file, "%d", (vector + i));
        }

        /* Test the vector and prints the time taken */
        sort(vector, number_of_integers, sort_example);

        /* Clear resources */
        free(vector);
    } else if(strcmp(*(arguments + 0), "generate") == 0) {
        if(arguments_count < 3) {
            print_help();
        } else {
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
        }
    }

    return 0;
}


void print_help() {
    printf(
        "./{program} {command} {options}\n\n"
        "Commands:\n"
        "test {file name}: test a vector using some sorting algorithms\n"
        "generate {file name} {number of integers}: generate a test for the"
        " program.\n"
        "Note: file names must follow [a-zA-Z_-] and have less than 32 "
        "characters.\n"
    );
}


void generate_test(FILE *file, int number_of_integers) {
    struct timeval time_val;
    gettimeofday(&time_val, NULL);

    /* Randomize the seed a bit since we'll be generating every test one after
    * another and time(NULL) won't be precise enough */
    srand((time_val.tv_sec * SECONDS_TO_MICROSECONDS) + time_val.tv_usec);

    /* Creates the file header */
    fprintf(file, "%d\n", number_of_integers);

    /* Generates a number of random integers */
    int i;
    for(i = 0; i < number_of_integers; i++) {
        fprintf(file, "%d ", rand());
    }

    /* Creates a new line */
    fprintf(file, "\n");
}


void sort(int *vector, int length, void (*sort_method)(int *, int)) {
    struct timeval start;
    gettimeofday(&start, NULL);

    /* Execute sort method using the given function pointer */
    sort_method(vector, length);

    struct timeval end;
    gettimeofday(&end, NULL);

    /* Prints out the elapsed time in microseconds */
    printf(
        "%ld\n",
        ((end.tv_sec - start.tv_sec) * SECONDS_TO_MICROSECONDS) +
        (end.tv_usec - start.tv_usec)
    );
}
