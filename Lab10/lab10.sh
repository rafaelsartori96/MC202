#!/bin/sh

# Recompiles the code
echo "Compiling code.."
gcc -Wall -o lab10 *.c


# Create vectors directory
if [ ! -d 'Vectors' ]; then
    mkdir 'Vectors'
fi


echo "Creating tests..."
# Generate all files
for length in 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 \
40000 50000 60000 70000 80000 90000 100000
do
    # For each length, create 10 tests
    for i in {1..10}
    do
        file_name='vector_'$length'_'$i
        ./lab10 generate Vectors/$file_name $length
    done
done


echo "Testing..."
# Now, lets test them
for length in 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 20000 30000 \
40000 50000 60000 70000 80000 90000 100000
do
    # For each length, do the 10 tests
    result=0
    for i in {1..10}
    do
        file_name='vector_'$length'_'$i
        # ./lab10 sort Vectors/$file_name
        output=$(./lab10 sort Vectors/$file_name)
        result=$(expr $result + $output)
        # echo "$result | $output for test $file_name"
    done
    echo "Average: $(expr $result / 10)µs on test vector_$length"
    # echo
done
