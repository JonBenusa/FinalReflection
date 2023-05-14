import random
import time

# Matrix dimensions
M = 1000
N = 1000
K = 1000

# Create two matrices of random integers
matrix_a = [[random.randint(1, 10) for j in range(K)] for i in range(M)]
matrix_b = [[random.randint(1, 10) for j in range(N)] for i in range(K)]

# Create an empty result matrix
result_matrix = [[0 for j in range(N)] for i in range(M)]

# Start the timer
start_time = time.time()

# Multiply the matrices
for i in range(M):
    print('\n')
    for j in range(N):
        for k in range(K):
            result_matrix[i][j] += matrix_a[i][k] * matrix_b[k][j]
            print(str(result_matrix[i][j]),  end=', ')

# End the timer
end_time = time.time()

# Print the elapsed time
print("Elapsed time: %.3f seconds" % (end_time - start_time))
print(result_matrix)
