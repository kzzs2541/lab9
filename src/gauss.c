#include "gauss.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Zwraca 0 - eliminacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int r = mat->r;
    int c = mat->c;
    double **A = mat->data;
    double **B = b->data;

    for (int k = 0; k < r; k++) {
        // Znajdowanie maksymalnego elementu w kolumnie dla stabilnosci numerycznej
        int maxRow = k;
        for (int i = k + 1; i < r; i++) {
            if (fabs(A[i][k]) > fabs(A[maxRow][k])) {
                maxRow = i;
            }
        }

        // Sprawdzenie, czy macierz jest osobliwa
        if (fabs(A[maxRow][k]) < 1e-9) {
            return 1; // Macierz osobliwa
        }

        // Zamiana wierszy w A i B
        if (maxRow != k) {
            double *temp = A[k];
            A[k] = A[maxRow];
            A[maxRow] = temp;

            temp = B[k];
            B[k] = B[maxRow];
            B[maxRow] = temp;
        }

        // Eliminacja wierszami
        for (int i = k + 1; i < r; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < c; j++) {
                A[i][j] -= factor * A[k][j];
            }
            B[i][0] -= factor * B[k][0];
        }
    }
    return 0;
}

