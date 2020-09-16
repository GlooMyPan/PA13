#include "projekt13.h"

Bruch *loeseLGS(Bruch *A[], Bruch b[])
{
    for (size_t i = 0; i < Dim; ++i)
    {
/*** Pivotisierung ***/
// bestimme Index der Pivot-Zeile
        size_t p = i;
        for (size_t k = i + 1; k < Dim; ++k)
            if (abs(A[p][i]) < abs(A[k][i]))
                p = k;
// tausche ggf. Pivot-Zeile des LGS mit Zeile i
        if (p != i)
        {
            Bruch *temp1 = A[p];
            A[p] = A[i];
            A[i] = temp1;

            Bruch temp2 = b[p];
            b[p] = b[i];
            b[i] = temp2;
        }
// Pivot-Element == 0 => keine L¨osung
        if (A[i][i] == 0)
            return nullptr;


/*** Vorw¨arts-Elimination ***/
// Gauß-Elimination der Zeilen unterhalb i
        for (size_t k = i + 1; k < Dim; ++k)
        {
            Bruch faktor = A[k][i] / A[i][i];
            for (size_t j = i + 1; j < Dim; ++j)
                A[k][j] -= faktor * A[i][j];
            b[k] -= faktor * b[i];
        }
    } // for ( i )
    /*** R¨uckw¨arts-Elimination ***/
    for (int i = Dim - 1; i >= 0; --i)
    {
        for (size_t k = i + 1; k < Dim; ++k)
            b[i] -= (A[i][k] * b[k]);
        b[i] /= A[i][i];
    }
    return b;
} // loeseLGS()