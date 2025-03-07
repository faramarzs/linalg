#include <stdio.h>
#include <stdlib.h>

// Function to multiply two matrices
void multiplyMatrices(int **firstMatrix, int **secondMatrix, int **result, int n) {
    // Loop through rows of firstMatrix
    for (int i = 0; i < n; i++) {
        // Loop through columns of secondMatrix
        for (int j = 0; j < n; j++) {
            result[i][j] = 0; // Initialize the result element to 0
            // Perform the multiplication
            for (int k = 0; k < n; k++) {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
}

// Function to get the cofactor of the matrix
void getCofactor(int **matrix, int **temp, int p, int q, int n) {
    int i = 0, j = 0;
    
    // Loop through the matrix to get the cofactor
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = matrix[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Function to calculate the determinant of a matrix
int determinant(int **matrix, int n) {
    int D = 0;
    if (n == 1) {
        return matrix[0][0];
    }
    
    int **temp = (int **)malloc(n * sizeof(int *));  // Temporary matrix to store cofactors
    for (int i = 0; i < n; i++) {
        temp[i] = (int *)malloc(n * sizeof(int));
    }
    
    int sign = 1;  // Sign of the cofactor matrix
    
    // Loop through the first row to calculate the determinant
    for (int f = 0; f < n; f++) {
        getCofactor(matrix, temp, 0, f, n);
        D += sign * matrix[0][f] * determinant(temp, n - 1);
        sign = -sign;  // Alternate signs
    }

    // Free dynamically allocated memory for the temporary matrix
    for (int i = 0; i < n; i++) {
        free(temp[i]);
    }
    free(temp);
    
    return D;
}

int main() {
    int n;

    // Input size of the matrix
    printf("Enter the size of the matrices (n x n): ");
    scanf("%d", &n);

    // Dynamically allocate memory for matrices
    int **firstMatrix = (int **)malloc(n * sizeof(int *));
    int **secondMatrix = (int **)malloc(n * sizeof(int *));
    int **result = (int **)malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; i++) {
        firstMatrix[i] = (int *)malloc(n * sizeof(int));
        secondMatrix[i] = (int *)malloc(n * sizeof(int));
        result[i] = (int *)malloc(n * sizeof(int));
    }

    // Input elements of first matrix
    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &firstMatrix[i][j]);
        }
    }

    // Input elements of second matrix
    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &secondMatrix[i][j]);
        }
    }

    // Multiply matrices
    multiplyMatrices(firstMatrix, secondMatrix, result, n);

    // Output the result
    printf("Resultant matrix after multiplication:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Calculate and print the determinant of the first matrix
    int det = determinant(firstMatrix, n);
    printf("Determinant of the first matrix: %d\n", det);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(firstMatrix[i]);
        free(secondMatrix[i]);
        free(result[i]);
    }
    free(firstMatrix);
    free(secondMatrix);
    free(result);

    return 0;
}
