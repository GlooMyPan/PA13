//
// Created by Xuantong Pan on 2020/9/15.
//
#include "Ganzzahl.h"

/*** Konstruktoren ***/
Ganzzahl::Ganzzahl() {
    this->_value = 0;
    this->_vorzeichen = POSITIV;
}

Ganzzahl::Ganzzahl(long long zahl) {
    this->_value = zahl;
    this->_vorzeichen = zahl < 0;
}

Ganzzahl::Ganzzahl(const string &str) {
    this->_value = str;
    int i = str.find_first_not_of("0123456789");
    if (i == string::npos)
        this->_vorzeichen = this->POSITIV;
    else if (i > 0 && str[i-1] == '-' || str[0] == '-')
        this->_vorzeichen = this->NEGATIV;
    else
        this->_vorzeichen = this->POSITIV;

}

Ganzzahl::Ganzzahl(const Natuerlich &nat, bool vorzeichen) {
    this->_value = nat;
    this->_vorzeichen = vorzeichen;
}

/*** abs() ***/

Ganzzahl abs(Ganzzahl const & gzahl) {
    if (gzahl >= 0)
        return gzahl;
    else
        return -gzahl;
}

/*** Rechenmethoden ***/
Ganzzahl Ganzzahl::operator/(Ganzzahl const& gzahl) const {
    Ganzzahl ans;
    ans._value = this->_value / gzahl._value;
    ans._vorzeichen = this->_vorzeichen ^ gzahl._vorzeichen; // 0 ^ 1 = 1
                                                             // 0 ^ 0 = 0
                                                             // 1 ^ 1 = 0
    return ans;
}

void Ganzzahl::operator/=(Ganzzahl const& gzahl) {
    *this = *this / gzahl;
}

Ganzzahl Ganzzahl::operator%(Ganzzahl const& gzahl) const {
    Ganzzahl ans;
    ans._value = this->_value % gzahl._value;
    ans._value == 0 ? ans._vorzeichen = POSITIV : ans._vorzeichen = this->_vorzeichen;
    return ans;
}

Ganzzahl Ganzzahl::operator*(Ganzzahl const& gzahl) const {
    Ganzzahl ans;
    ans._value = this->_value * gzahl._value;

    ans._vorzeichen = this->_vorzeichen ^ gzahl._vorzeichen;
    return ans;
}
void Ganzzahl::operator*=(Ganzzahl const& gzahl) {
    *this = *this * gzahl;
}

Ganzzahl Ganzzahl::operator+(Ganzzahl const& gzahl) const {
    Ganzzahl ans;
    if (this->_vorzeichen == gzahl._vorzeichen) {
        ans._value = this->_value + gzahl._value;
        ans._vorzeichen = gzahl._vorzeichen;
    }
    else if (this->_vorzeichen) // x < 0
        ans = gzahl - (-*this);
    else if (gzahl._vorzeichen) // y < 0
        ans = *this - (-gzahl);
    return ans;
}

Ganzzahl Ganzzahl::operator-(Ganzzahl const& gzahl) const {
    Ganzzahl ans;
    if (this->_vorzeichen == gzahl._vorzeichen) {
        ans._value = this->_value - gzahl._value;
        if (!this->_vorzeichen) //alle POSITIV
            if (this->_value >= gzahl._value)
                ans._vorzeichen = POSITIV;
            else
                ans._vorzeichen = NEGATIV;
        else // alle NEGATIV
            if (this->_value > gzahl._value)
                ans._vorzeichen = NEGATIV;
            else
                ans._vorzeichen = POSITIV;
    }
    else if (this->_vorzeichen) // x < 0
        ans = -(-*this + gzahl);
    else if (gzahl._vorzeichen) // y < 0
        ans = *this + (-gzahl);
    return ans;
}


/*** Vergleichsoperatoren ***/
bool Ganzzahl::operator==(Ganzzahl const& gzahl) const {
    return this->_vorzeichen == gzahl._vorzeichen && this->_value == gzahl._value;
}
bool Ganzzahl::operator<(Ganzzahl const& gzahl) const {
    if (this->_vorzeichen && !gzahl._vorzeichen)
        return true;
    else if (this->_vorzeichen && gzahl._vorzeichen)
        return this->_value > gzahl._value;
    else if (!this->_vorzeichen && gzahl._vorzeichen)
        return false;
    else
        return this->_value < gzahl._value;
}
bool Ganzzahl::operator>=(Ganzzahl const& gzahl) const {
    return gzahl < *this || gzahl == *this;
}
Ganzzahl Ganzzahl::operator-() const {
    return Ganzzahl(this->_value, !this->_vorzeichen);
}
