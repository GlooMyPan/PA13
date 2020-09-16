
#ifndef PA13_GANZZAHL_H
#define PA13_GANZZAHL_H
#include "Natuerlich.h"
#include <iomanip>
#endif //PA13_GANZZAHL_H



class Ganzzahl {
public:
    friend Ganzzahl abs(Ganzzahl const & gzahl);
    friend ostream& operator<<(ostream& ostr, Ganzzahl const& gzahl)
    {
        int laenge = ostr.width();
        if (laenge && !gzahl._vorzeichen)
            cout << setw(laenge - gzahl._value.Size());
        else if (laenge && gzahl._vorzeichen)
            cout << setw(laenge - 1 - gzahl._value.Size());
        if (gzahl._vorzeichen)
            ostr << '-';
        ostr << gzahl._value;

        return ostr ;
    }
/*** Konstruktoren ***/
    Ganzzahl();
    Ganzzahl(long long zahl);
    Ganzzahl(string const& str);
    Ganzzahl(Natuerlich const& nat, bool vorzeichen = POSITIV);

/*** Rechenmethoden ***/
    Ganzzahl operator/(Ganzzahl const& gzahl) const;
    void operator/=(Ganzzahl const& gzahl);
    Ganzzahl operator%(Ganzzahl const& gzahl) const;
    Ganzzahl operator*(Ganzzahl const& gzahl) const;
    void operator*=(Ganzzahl const& gzahl);
    Ganzzahl operator-() const;
    Ganzzahl operator-(Ganzzahl const& gzahl) const;
    Ganzzahl operator+(Ganzzahl const& gzahl) const;

/*** Vergleichsoperatoren ***/
    bool operator==(Ganzzahl const& gzahl) const;
    bool operator<(Ganzzahl const& gzahl) const;
    bool operator>=(Ganzzahl const& gzahl) const;

private:
/*** private Elemente ***/
    Natuerlich _value;
    bool _vorzeichen;
    static const bool POSITIV = false;
    static const bool NEGATIV = true;
};
