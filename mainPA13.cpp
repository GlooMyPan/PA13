#include <iomanip>
#include "projekt13.h"

// Dimension des Vektorraums

size_t Dim;

int main(int narg, char *argv[]) {
/***  gebe Usage aus  ***/

// TODO: Wenn auﬂer dem Programmnamen keine Argumente gegeben sind
//       oder eine ungerade Anzahl von Punktkoordinaten, dann wird
//       hier ein Hilfetext ausgegeben, der dem Benutzer mitteilt,
//       welche Argumente er eingeben kann und was das Programm
//       dann mit ihnen macht.

    if (narg == 1 || narg % 2 != 1) {
        cout << "Usage: " << argv[0] << "x1 y1 [x2 y2 ...]\n"
             << setw(7) << " " << "x1, y1: ganzz. Koordinaten eines Punktes\n"
             << setw(7) << " " << "x2, y2, ...: Koordinaten weiterer Punkte\n"
             << "Bestimmt das durch die Punkte festgelegte Polynom." << endl;
        return 0;
    }

/***  setze Daten des Gleichungssystems  ***/

//     setze Dimension des Vektorraums
    Dim = (narg - 1) / 2;
//
//     alloziere und initialisiere Matrix A und rechte Seite b

// TODO: Hier wird dynamischer Speicher reserviert f¸r die Dim x Dim-
//       Matrix A des Gleichungssystems und den Dim-dimensionalen Vektor
//       b der rechten Seite. Die Punktkoordinaten aus der Kommandozeile
//       werden umgesetzt in die Initialisierung von A und b.

    Bruch **A = new Bruch *[Dim];
    Bruch *b = new Bruch[Dim];
    for (size_t i = 0; i < Dim; ++i) {
// Koordinaten des aktuell gelesenen Punkts
        Bruch x = Ganzzahl(argv[2 * i + 1]);

        Bruch y = Ganzzahl(argv[2 * i + 2]);
// init. Matrix A mit Potenzen von x
        A[i] = new Bruch[Dim];
        A[i][0] = 1;
        for (size_t j = 1; j < Dim; ++j)
            A[i][j] = x * A[i][j - 1];

// init. rechte Seite b mit Funktionswerten y
        b[i] = y;
    }


/***  gebe Gleichungssystem A|b zur Kontrolle aus  ***/

    cout << "das LGS lautet:" << endl;

    zeigeLGS(A, b);
//
/***  berechne Lˆsung, gebe Ergebnispolynom aus  ***/
//
    Bruch *x = loeseLGS(A, b);

    // wurde Lˆsung gefunden?
    if (x == nullptr)
        cout << "Es gibt keine Loesung!" << endl;
    else {
        cout << "finde Polynom p(x) = ";
        zeigePolynom(x);
    }

/***  r‰ume Speicher auf  ***/

// TODO: A, b sind dynamischer Speicher, der wieder
//       gelˆscht werden muss. Hier ist der Ort.
    delete[] b ;
    for ( size_t i = 0 ; i < Dim ; ++i )
        delete[] A[ i ] ;
    delete[] A ;


    return 0;    // alles OK

}  // main()