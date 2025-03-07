#include <stdio.h>
#include <stdlib.h>

void swapRows(double **matrix, double **identity, int row1, int row2, int n) {
    for (int i = 0; i < n; i++) {
        double temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;

        temp = identity[row1][i];
        identity[row1][i] = identity[row2][i];
        identity[row2][i] = temp;
    }
}

int gaussJordanInverse(double **matrix, double **identity, int n) {
    double temp;
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 0) {
            // Search for non-zero element in the same column
            int j;
            for (j = i + 1; j < n; j++) {
                if (matrix[j][i] != 0) {
                    swapRows(matrix, identity, i, j, n);
                    break;
                }
            }
            if (j == n) {
                return 0; // Singular matrix, no inverse
            }
        }

        // Make the diagonal element 1 and other elements in the column 0
        temp = matrix[i][i];
        for (int j = 0; j < n; j++) {
            matrix[i][j] /= temp;
            identity[i][j] /= temp;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                temp = matrix[k][i];
                for (int j = 0; j < n; j++) {
                    matrix[k][j] -= matrix[i][j] * temp;
                    identity[k][j] -= identity[i][j] * temp;
                }
            }
        }
    }
    return 1; // Success, inverse found
}

int main() {
    int n;

    // Input the size of the matrix
    printf("Enter the size of the matrix (n x n): ");
    scanf("%d", &n);

    // Dynamically allocate memory for matrix and identity matrix
    double **matrix = (double **)malloc(n * sizeof(double *));
    double **identity = (double **)malloc(n * sizeof(double *));
    
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
        identity[i] = (double *)malloc(n * sizeof(double));
    }

    // Input the matrix elements
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matrix[i][j]);
            identity[i][j] = (i == j) ? 1 : 0; // Set identity matrix
        }
    }

    // Per

