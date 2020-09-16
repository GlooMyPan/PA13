#include "Natuerlich.h"
#include <cmath>

Natuerlich::Natuerlich() {
    _nSign = 1;
    _ziffer = new int[1];
    _ziffer[0] = 0;
}

Natuerlich::Natuerlich(Natuerlich const &nat) {
    _nSign = nat._nSign;
    _ziffer = new int[_nSign];
    for (size_t i = 0; i < _nSign; ++i)
        _ziffer[i] = nat._ziffer[i];
}

void Natuerlich::operator=(Natuerlich const &nat) {
// Objekte gleich? -> nichts zu tun
    if (this == &nat)
        return;
// realloziere Array bei Bedarf
    if (_nSign != nat._nSign) {
        delete[] _ziffer;
        _nSign = nat._nSign;
        _ziffer = new int[_nSign];
    }
// weise Array zu
    for (size_t i = 0; i < _nSign; ++i)
        _ziffer[i] = nat._ziffer[i];
}

Natuerlich::~Natuerlich() {
    delete[] _ziffer;
}

// Umwandlungskonstruktor von string
Natuerlich::Natuerlich(string const &str) {
    this->_nSign = str.find_first_not_of("0123456789");
    if (this->_nSign == string::npos)
        this->_nSign = str.size();
    else
        this->_nSign = str.size() - this->_nSign;
    if (this->_nSign == 0) {
        this->_nSign = 1;
        this->_ziffer = new int[1];
        this->_ziffer[0] = 0;
    } else {
        this->_ziffer = new int[this->_nSign];
        for (int i = 0; i < this->_nSign; ++i)
            if (str[this->_nSign-i-1] >= '0' && str[this->_nSign-i-1] <= '9')
                this->_ziffer[i] = str[this->_nSign - i - 1] - '0';

        _formatiere();
    }
}


Natuerlich::Natuerlich(long long zahl) {
    zahl = abs(zahl);

    this->_nSign = 1;
    if (zahl > 0)
        this->_nSign = size_t(log10(zahl) + 1);
    this->_ziffer = new int[this->_nSign];
    for (size_t i = 0; i < this->_nSign; ++i) {
        this->_ziffer[i] = zahl % 10;
        zahl /= 10;
    }
}

int Natuerlich::Size() const {
    return this->_nSign;
}

Natuerlich Natuerlich::operator+(const Natuerlich &nat) const {
    // lege Ergebnisobjekt an
    size_t maxLaenge = _nSign;
    if (maxLaenge < nat._nSign)
        maxLaenge = nat._nSign; // = max( _nSign, nat._nSign )
    Natuerlich ergebnis(maxLaenge + 1); // privater Konstruktor

    // addiere Zahlen stellenweise
    int uebertrag = 0;
    for (size_t i = 0; i < ergebnis._nSign; ++i) {
        // berechne Summe der i. Ziffern
        int summe = uebertrag;
        if (i < _nSign)
            summe += _ziffer[i];
        if (i < nat._nSign)
            summe += nat._ziffer[i];
        // berechne i. Ziffer der Summe
        ergebnis._ziffer[i] = summe % 10;
        uebertrag = summe / 10;
    }

    // addiere Zahlen stellenweise
    ergebnis._ziffer[0] = 0;
    for (size_t i = 0; i < ergebnis._nSign - 1; ++i) {
// berechne Summe der i. Ziffern
        if (i < _nSign)
            ergebnis._ziffer[i] += _ziffer[i];
        if (i < nat._nSign)
            ergebnis._ziffer[i] += nat._ziffer[i];
// berechne i. Ziffer der Summe
        ergebnis._ziffer[i + 1] = ergebnis._ziffer[i] / 10;
        ergebnis._ziffer[i] %= 10;
    }

    // l¨osche f¨uhrende Nullen
    ergebnis._formatiere();
    return ergebnis;
}

Natuerlich Natuerlich::operator-(Natuerlich const &nat) const {
    // lege Ergebnisobjekt an
    bool kleiner = (*this < nat);
    Natuerlich const &linkerOp = (kleiner ? nat : *this);
    Natuerlich const &rechterOp = (kleiner ? *this : nat);
    Natuerlich ergebnis(linkerOp._nSign);

    // subtrahiere Zahlen stellenweise
    int wert = 0;

    for (size_t i = 0; i < ergebnis._nSign; ++i) {
        wert += linkerOp._ziffer[i];
        if (i < rechterOp._nSign)
            wert -= rechterOp._ziffer[i];

        if (wert >= 0) {
            ergebnis._ziffer[i] = wert;
            wert = 0;
        } else {
            ergebnis._ziffer[i] = wert + 10;
            wert = -1;
        }
    }  // for ( i )

    // lösche führende Nullen
    ergebnis._formatiere();

    return ergebnis;

}  // Natuerlich::operator -

Natuerlich Natuerlich::operator/(Natuerlich const &nat) const {
    // Objekt ist kleiner -> Abrundung wird zur 0
    if (*this < nat)
        return 0;


    // initialisiere ergebnis = 0
    Natuerlich ergebnis(_nSign - nat._nSign + 1);
    for (size_t i = 0; i < ergebnis._nSign; ++i)
        ergebnis._ziffer[i] = 0;

    // initialisiere Rechenvariable
    Natuerlich temp(nat._nSign);
    for (size_t i = 0; i < temp._nSign; ++i)
        temp._ziffer[i] = _ziffer[i + _nSign - nat._nSign];

    // berechne Quotient stellenweise
    for (int i = ergebnis._nSign - 1; i >= 0; --i) {
        // ergebnis._ziffer[ i ] = floor( temp / nat )
        while (temp >= nat) {
            temp = temp - nat;
            ++ergebnis._ziffer[i];
        }

        if (i > 0)
            temp = temp * 10 + _ziffer[i - 1];
    }

    // lösche führende Nullen
    ergebnis._formatiere();

    return ergebnis;

}  // Natuerlich::operator /

Natuerlich Natuerlich::operator*(const Natuerlich &nat) const {
    Natuerlich ans(this->_nSign + nat._nSign);
    // initialisiere ans = 0
    for (int i = 0; i < ans._nSign; ++i)
        ans._ziffer[i] = 0;
    for (int i = 0; i < this->_nSign; ++i) {
        for (int j = 0; j < nat._nSign ; ++j) {
            ans._ziffer[i+j] += this->_ziffer[i] * nat._ziffer[j];
            ans._ziffer[i+j+1] += ans._ziffer[i+j] / 10;
            ans._ziffer[i+j] %= 10;
        }
    }
    ans._formatiere();
    return ans;
}

Natuerlich Natuerlich::operator%(const Natuerlich &nat) const {
    return Natuerlich(*this - (*this / nat) * nat);
}

/*** Vergleichsoperatoren ***/
bool Natuerlich::operator==(Natuerlich const &nat) const {
    if (this->_nSign != nat._nSign)
        return false;
    for (size_t i = 0; i < this->_nSign; ++i)
        if (this->_ziffer[i] != nat._ziffer[i])
            return false;

    return true;
}

bool Natuerlich::operator!=(Natuerlich const &nat) const {
    return !(*this == nat);
}

bool Natuerlich::operator<(Natuerlich const &nat) const {
    if (this->_nSign > nat._nSign)
        return false;
    else if (this->_nSign < nat._nSign)
        return true;
    else {
        if (*this == nat)
            return false;
        for (int i = this->_nSign - 1; i >= 0; --i) {
            if (this->_ziffer[i] < nat._ziffer[i])
                return true;
            if (this->_ziffer[i] > nat._ziffer[i])
                return false;
        }
        return false;
    }

}

bool Natuerlich::operator<=(Natuerlich const &nat) const {
    return *this == nat || *this < nat;
}

bool Natuerlich::operator>=(Natuerlich const &nat) const {
    return nat <= *this;
}

bool Natuerlich::operator>(Natuerlich const &nat) const {
    return nat < *this;
}

int Natuerlich::_vergleiche(const Natuerlich &nat) const {
    if (*this < nat)
        return -1;
    if (*this > nat)
        return 1;
    return 0;
}
