#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long **alloc_mat_ll(int n) {
    long long **a = (long long**)malloc(n * sizeof(*a));
    if (!a) {
        perror("malloc");
        exit(1);
    }
    for (int i = 0; i < n; i++) { 
        a[i] = (long long*)malloc(n * sizeof(**a));
        if (!a[i]) {
            perror("malloc");
            exit(1);
        }
    }
    return a;
}

void free_mat_ll(long long **a, int n) {
    for (int i = 0; i < n; i++) free(a[i]);
    free(a);
}

double **alloc_mat_d(int n) {
    double **a = (double**)malloc(n * sizeof(*a));
    if (!a) {
        perror("malloc");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        a[i] = (double*)malloc(n * sizeof(**a));
        if (!a[i]) {
            perror("malloc");
            exit(1);
        }
        return a;
    }
}

void free_mat_d(double **a, int n) {
    for (int i = 0; i < n; i++) free(a[i]);
    free(a);
}