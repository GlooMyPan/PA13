#pragma once

#include <iostream>       // f¸r ostream
#include "Ganzzahl.h"
using namespace std;


/**
  * Klasse f¸r Br¸che als Quotienten ganzer Zahlen
  *
  * Datenformat:
  *		- Der Nenner ist echt positiv.
  *		- Bei Z‰hler == 0 ist Nenner == 1.
  *		- Z‰hler und Nenner sind ausgek¸rzt.
  */

class Bruch
{
/***  private Elemente ***/

    // Z‰hler und Nenner des Objekts
    Ganzzahl _zaehler, _nenner;

    // stelle Datenformat des Objekts her
    void _formatiere();

public:

    friend ostream &operator<<(ostream &cout, Bruch const &bruch);

    /***  Konstruktoren  ***/
    Bruch();

    Bruch(Ganzzahl const & l);

    Bruch(long long i);

    Bruch(Ganzzahl const & zaehler, Ganzzahl const & nenner);


/***  Interaktionsmethoden, z.B. Vergleiche  ***/
    bool operator!=(int i) const;

    bool operator==(int i) const;

    bool operator>=(int i) const;

    bool operator<(Bruch const &bruch) const;


/***  Rechenmethoden  ***/

    Bruch operator*(Bruch const &bruch) const;

    Bruch operator/(Bruch const &bruch) const;

    void operator/=(Bruch const &bruch);

    void operator-=(Bruch const &bruch);

    Bruch operator-() const;


};  // class Bruch


/***  globale Funktionen  ***/
Bruch abs(Bruch const &bruch);
Bruch pow(Bruch const& b, size_t n);