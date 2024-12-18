#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int backsubst(Matrix *x, Matrix *mat, Matrix *b) {
    // sprawdzenie zgodnosci wymiarow macierzy
    if (mat->r != mat->c || b->r != mat->r || b->c != 1 || x->r != mat->r || x->c != 1) {
        return 2; // blad
    }

    int n = mat->r; // Rozmiar macierzy A

    // iteracja wsteczna
    for (int i = n - 1; i >= 0; i--) {
        // sprawdzenie elementu zerowego
        if (mat->data[i][i] == 0) {
            return 1; // blad dzielenia przez 0
        }

        double sum = 0.0;
        // Liczymy sumę dla znanych już wartości niewiadomych
        for (int j = i + 1; j < n; j++) {
            sum += mat->data[i][j] * x->data[j][0];
        }

        // Obliczamy wartość x[i]
        x->data[i][0] = (b->data[i][0] - sum) / mat->data[i][i];
    }

    return 0; // udane wyliczenie
}
