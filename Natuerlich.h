#pragma once

#include <iostream>
#include <string>

using namespace std;

class Natuerlich
{
/*** private Elemente ***/

    // Array der Ziffernfolge
    int *_ziffer;

    // Anzahl signifikanter Ziffern
    size_t _nSign;

    // stelle internes Datenformat her
    void _formatiere ()
    {
        while (_nSign > 1 && _ziffer[_nSign - 1] <= 0) // f¨uhrende Null
            --_nSign ;
    }

    explicit Natuerlich(size_t laenge)
    {
        this->_nSign = laenge;
        this->_ziffer = new int[laenge];
    }

    int _vergleiche(Natuerlich const & nat) const;

public:
/*** Konstruktoren ***/

// Standardkonstruktor
    Natuerlich();

// Kopierkonstruktor
    Natuerlich(Natuerlich const &nat);

    // Umwandlungskonstruktor von primitiver Zahl
    Natuerlich(long long zahl);

// Umwandlungskonstruktor von string
    Natuerlich(string const &str);

/*** set-Methoden ***/
// Standard-Zuweisungsoperator
    void operator=(Natuerlich const &nat);
    int Size() const;
/*** Rechenmethoden ***/
// addiere Objekt und nat zu einem neuem Objekt
    Natuerlich operator+(Natuerlich const &nat) const;
    Natuerlich operator-(Natuerlich const& nat) const;
    Natuerlich operator/(Natuerlich const& nat) const;
    Natuerlich operator%(Natuerlich const& nat) const;
    Natuerlich operator*(Natuerlich const& nat) const;

/*** Ausgabe-Funktionen ***/
// gebe nat als Ziffernkette auf ostr aus
    friend ostream &operator<<(ostream &ostr, Natuerlich const &nat);

/*** Vergleichsoperatoren ***/
    bool operator==(Natuerlich const & nat) const;
    bool operator!=(Natuerlich const & nat) const;
    bool operator<(Natuerlich const & nat) const;
    bool operator<=(Natuerlich const & nat) const;
    bool operator>=(Natuerlich const & nat) const;
    bool operator>(Natuerlich const & nat) const;


/*** Destruktor ***/
    ~Natuerlich();

    // gebe nat als Ziffernkette auf ostr aus
    friend
    ostream& operator<<(ostream& ostr, Natuerlich const& nat)
    {
        for (int i = nat._nSign - 1 ; i >= 0 ; --i)
            ostr << nat._ziffer[i];
        return ostr ;
    }

};
