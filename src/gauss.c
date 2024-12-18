#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

int eliminate(Matrix *mat, Matrix *b) {
    int n = mat->rows;

    if (mat->cols != n || b->rows != n || b->cols != 1) {
        fprintf(stderr, "Nieprawidłowe wymiary macierzy\n");
        return -1; // Kod błędu dla niezgodności wymiarów
    }

    for (int k = 0; k < n; ++k) {
        // Wybór elementu głównego (pivot)
        double max = fabs(mat->data[k][k]);
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (fabs(mat->data[i][k]) > max) {
                max = fabs(mat->data[i][k]);
                maxRow = i;
            }
        }

        // Zamiana wierszy
        if (maxRow != k) {
            double *temp = mat->data[k];
            mat->data[k] = mat->data[maxRow];
            mat->data[maxRow] = temp;

            double tempB = b->data[k][0];
            b->data[k][0] = b->data[maxRow][0];
            b->data[maxRow][0] = tempB;
        }

        // Sprawdzenie czy macierz jest osobliwa
        if (fabs(mat->data[k][k]) < 1e-12) {
            fprintf(stderr, "Macierz osobliwa\n");
            return 1; // Kod błędu dla macierzy osobliwej
        }

        // Eliminacja zmiennych
        for (int i = k + 1; i < n; ++i) {
            double factor = mat->data[i][k] / mat->data[k][k];
            for (int j = k; j < n; ++j) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }
            b->data[i][0] -= factor * b->data[k][0];
        }
    }

return 0;
}

