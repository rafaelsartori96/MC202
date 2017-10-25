#!/bin/sh
# Rafael Sartori Martins dos Santos (RA: 186154)

# Note: the output.txt can be easily imported at Google Docs
# and LibreOffice, just copy and paste ;)

# Define test variables
CREATE_VECTORS=1

#TESTS=1
TESTS=400

LIMIT_TIME_AVG=1
NANOSECONDS_LIMIT_AVG=100000000
LIMIT_TIME_TEST=0
NANOSECONDS_LIMIT_TEST=200000000

START=2500
STEP=2500
#END=2500
END=150000



# (Re)compiles the code
echo "Compiling code.."
if ! gcc -Wall -O3 -o lab10 *.c; then
    echo "Failed to compile. Stopping script."
    exit 0
fi


# Checks if we need to create the vector folder
if [[ $CREATE_VECTORS -eq 1 ]]; then
    # (Re)create vectors directory
    if [ -d 'Vectors' ]; then
        rm -rd 'Vectors'
    fi
    mkdir 'Vectors'



    echo "Creating tests..."
    # Generate all vector files
    for (( length=$START; length<=$END; length+=$STEP ))
    do
        # For each length, create tests
        for (( i=1; i<=$TESTS; i++ ))
        do
            file_name='vector_'$length'_'$i
            ./lab10 generate Vectors/$file_name $length
        done
    done
fi



echo "Testing..."

# Prepare file header on the format "Sort (length start .. length end)\n"
echo -e -n "Sort" > output.txt
for (( length=$START; length<=$END; length+=$STEP ))
do
    echo -n -e "\t$length" >> output.txt
done
echo >> output.txt


for sorting_method in 'qsort' 'mergesort' 'heapsort' 'quicksort_np' \
'quicksort_p' 'selectionsort'
do
    # Print the first column as the sorting method
    echo -n "$sorting_method" >> output.txt
    
    # For every length...
    for (( length=$START; length<=$END; length+=$STEP ))
    do
        # Store results
        result=0
        successfull_tests=0
        
        # For each test...
        for (( i=1; i<=$TESTS; i++ ))
        do
            # Test if vector is ordered for the first test
            if [[ $length -le $START ]]; then
                # This will execute the program checking if the final vector is
                # ordered
                sort='sortt'
            else
                # This will just execute the sorting method without checking the
                # if the result vector is correct
                sort='sort'
            fi

            file_name='vector_'$length'_'$i

            # Check for output (time in ns) and return status (check if it was
            # successfully ordered)
            if output=$(./lab10 $sort Vectors/$file_name $sorting_method); then
                # Since the vector was sorted (return status is successfull),
                # add to the result variable
                result=$(expr $result + $output)
                successfull_tests=$(expr $successfull_tests + 1)
            else
                # Do not continue testing a failed method
                break
            fi

            # Lets check if the test took more time than what we allow for any
            # test
            if [[
                $LIMIT_TIME_TEST -eq 1 && $output -gt $NANOSECONDS_LIMIT_TEST
            ]]; then
                break
            fi
        done
        
        # Since we finished all tests, check if any succeeded
        if [[ ! $successfull_tests -eq 0 ]]; then
            # Calculate the average
            average=$(expr $result / $successfull_tests)

            # Print the average for the vector of current length column
            echo -n -e "\t$average" >> output.txt


            # Check if the time taken to this test is too long than what we
            # expect
            if [[
                $LIMIT_TIME_AVG -eq 1 && $average -gt $NANOSECONDS_LIMIT_AVG
            ]]; then
                break
            fi
        else
            # Print fail message since the sort failed (no successful tests)
            echo -e "No tests were correct using $sorting_method for $length" \
            "elements" >> output.txt
            break
        fi
    done


    # End the line for this sorting method, continue to the next one.
    echo >> output.txt
done


# Close the file since we're done ;)
echo "Done! File \"output.txt\" was created!"
