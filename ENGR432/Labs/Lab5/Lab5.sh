#!/bin/bash

# Define matrix size
MATRIX_SIZE=1000

# Generate two random matrices
echo "Generating matrices..."
matrix1_file=$(mktemp)
matrix2_file=$(mktemp)
shuf -i 0-9 -n $((MATRIX_SIZE*MATRIX_SIZE)) | tr '\n' ' ' > $matrix1_file
shuf -i 0-9 -n $((MATRIX_SIZE*MATRIX_SIZE)) | tr '\n' ' ' > $matrix2_file

# Perform matrix multiplication
echo "Multiplying matrices..."
result_file=$(mktemp)
for i in $(seq 0 $((MATRIX_SIZE-1))); do
  for j in $(seq 0 $((MATRIX_SIZE-1))); do
    sum=0
    for k in $(seq 0 $((MATRIX_SIZE-1))); do
      index1=$((i*MATRIX_SIZE+k+1))
      index2=$((k*MATRIX_SIZE+j+1))
      element1=$(sed -n ${index1}p $matrix1_file)
      element2=$(sed -n ${index2}p $matrix2_file)
      product=$((element1*element2))
      sum=$((sum+product))
    done
    echo -n "$sum " >> $result_file
  done
  echo >> $result_file
done

# Print result
echo "Result saved to $result_file:"
head -n 10 $result_file