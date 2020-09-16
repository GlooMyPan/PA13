//
// Created by Xuantong Pan on 26.08.20.
//
#include "Bruch.h"

/***  ggT  ***/
static Ganzzahl ggT(Ganzzahl m, Ganzzahl n)
{
    while (n != 0)
    {
        Ganzzahl k = m % n;
        m = n;
        n = k;
    }
    return m;
}

/***  Konstruktoren  ***/
Bruch::Bruch()
{
    this->_zaehler = 0;
    this->_nenner = 1;
}

Bruch::Bruch(Ganzzahl const & l)
{
    this->_zaehler = l;
    this->_nenner = 1;
}

Bruch::Bruch(long long i) {
    this->_zaehler = i;
    this->_nenner = 1;
}

Bruch::Bruch(Ganzzahl const & zaehler, Ganzzahl const & nenner)
{
    this->_zaehler = zaehler;
    this->_nenner = nenner;
    _formatiere();
}

void Bruch::_formatiere()
{
    if (this->_nenner == 0)
    {
        cerr << "Der Nenner darf nicht = 0 sein!" << endl;
        return;
    }
    //1.
    if (this->_nenner < 0)
    {
        this->_zaehler = -this->_zaehler;
        this->_nenner = -this->_nenner;
    }
    //2.
    if (this->_zaehler != 0)
    {
        Ganzzahl teiler = ggT(abs(this->_zaehler), this->_nenner);
        this->_zaehler /= teiler;
        this->_nenner /= teiler;
    }
    else
        this->_nenner = 1;
}

/***  Interaktionsmethoden, z.B. Vergleiche  ***/
bool Bruch::operator!=(int i) const
{
    return this->_zaehler != i || this->_nenner != 1;
}

bool Bruch::operator==(int i) const
{
    return this->_zaehler == i && this->_nenner == 1;
}

bool Bruch::operator>=(int i) const
{
    return this->_zaehler >= this->_nenner * i;
}

bool Bruch::operator<(const Bruch &bruch) const
{
    return (this->_zaehler * bruch._nenner) < (bruch._zaehler * this->_nenner);
}

/***  Rechenmethoden  ***/
Bruch Bruch::operator*(Bruch const &bruch) const
{
    return Bruch(this->_zaehler * bruch._zaehler, this->_nenner * bruch._nenner);
}

Bruch Bruch::operator/(const Bruch &bruch) const
{
    return Bruch(this->_zaehler * bruch._nenner, this->_nenner * bruch._zaehler);
}

void Bruch::operator/=(const Bruch &bruch)
{
    this->_zaehler *= bruch._nenner;
    this->_nenner *= bruch._zaehler;
    this->_formatiere();
}

Bruch Bruch::operator-() const
{
    return Bruch(-this->_zaehler, this->_nenner);
}

void Bruch::operator-=(Bruch const &bruch)
{
    this->_zaehler = (this->_zaehler * bruch._nenner) - (this->_nenner * bruch._zaehler);
    this->_nenner *= bruch._nenner;
    this->_formatiere();
}

/***  globale Funktionen  ***/
ostream &operator<<(ostream &cout, Bruch const &bruch)
{
    if (bruch._nenner != 1)
        cout << bruch._zaehler << "/" << bruch._nenner;
    else
        cout << bruch._zaehler;
    return cout;
}

Bruch abs(Bruch const &bruch)
{
    if (bruch >= 0)
        return bruch;
    else
        return -bruch;
}

Bruch pow ( Bruch const& b, size_t n )
{
    Bruch potenz = 1 ;
    for ( size_t i = 1 ; i <= n ; ++i )
        potenz = potenz * b ;
    return potenz ;
}
