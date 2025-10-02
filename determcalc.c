#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long long determinant(int **matrix, int n) {
    double **A = malloc(n * sizeof(double*));
    if (!A) { 
        perror("malloc"); 
        exit(EXIT_FAILURE); 
    }
    for (int i = 0; i < n; ++i) {
        A[i] = malloc(n * sizeof(double));
        if (!A[i]) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < n; ++j) {
            A[i][j] = (double)matrix[i][j];
        }
    }

    int swaps = 0;
    const double EPS = 1e-12;

    for (int i = 0; i < n; ++i) {
        if (fabs(A[i][i]) < EPS) {
            int found = -1;
            for (int k = i + 1; k < n; ++k) {
                if (fabs(A[k][i]) > EPS) {
                    found = k;
                    break;
                }
            }
            if (found == -1) {
                for (int r = 0; r < n; ++r) free(A[r]);
                free(A);
                return 0LL;
            } else {
                double *tmp = A[i];
                A[i] = A[found];
                A[found] = tmp;
                swaps++;
            }
        }
        for (int j = i + 1; j < n; ++j) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; ++k) {
                A[j][k] -= factor * A[i][k];
            }
        }
    }

    double det = 1.0;
    for (int i = 0; i < n; ++i) det *= A[i][i];

    if (swaps % 2 != 0) det -= det;

    long long result = llround(det);

    for (int r = 0; r < n; ++r) free(A[r]);
    free(A);

    return result;
}

int main(void) {
    int n;
    printf("Enter matrix size n (for n x n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid size\n");
        return EXIT_FAILURE;
    }

    int **mat = malloc(n * sizeof(int*));
    if (!mat) { 
        perror("malloc");
        return EXIT_FAILURE; 
    }
    for (int i = 0; i < n; ++i) {
        mat[i] = malloc(n * sizeof(int));
        if (!mat[i]) {
            perror("malloc");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("Enter [A]%d%d elem: ", i + 1, j + 1);
            if (scanf("%d", &mat[i][j]) != 1) {
                fprintf(stderr, "Invalid input\n");
                return EXIT_FAILURE;
            }
        }
    }

    int max_len = 1;
    char buf[64];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int l = snprintf(buf, sizeof(buf), "%d", mat[i][j]);
            if (l > max_len) {
                max_len = l;
            }
        }
    }

    long long det = determinant(mat, n);

    int mid_row = n / 2;
    for (int i = 0; i < n; ++i) {
        putchar('|');
        for (int j = 0; j < n; ++j) {
            printf(" %*d", max_len, mat[i][j]);
        }
        if (i == mid_row) {
            printf(" | = %lld\n", det);
        } else {
            printf(" |\n");
        }
    }

    for (int i = 0; i < n; ++i) free(mat[i]);
    free(mat);

    return 0;
}