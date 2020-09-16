/**
 *  Prog a SS 2020
 *  Header f¸r die 11. Projektaufgabe
 */

#pragma once
#include <iostream>
#include "Bruch.h"
using namespace std ;


// Dimension des Vektorraums


// TODO: Hier wird die globale Variable, die in mainPA9.cpp
//       definiert ist, f¸r das ganze Projekt deklariert.

extern size_t Dim;
/***  AUSGABE.CPP  ***/

// Gebe Vektor vec[] mit Name name[] auf cout aus.
// Falls name[] == "", nur den Vektor.
void zeigeVektor  ( char const name[], Bruch const vec[] ) ;

// Gebe das lineare Gleichungssystem A|b auf cout aus.
void zeigeLGS     ( Bruch* const A[], Bruch const b[] ) ;

// Gebe das Polynom mit Koeffizienten koeff[] auf cout aus.
void zeigePolynom ( Bruch const koeff[] ) ;


/***  GAUSS.CPP  ***/

// Lˆse das lineare Gleichungssystem Ax = b. Gebe Lˆsung
// x zur¸ck oder nullptr, wenn es keine Lˆsung gibt.
Bruch* loeseLGS ( Bruch* A[], Bruch b[] ) ;

