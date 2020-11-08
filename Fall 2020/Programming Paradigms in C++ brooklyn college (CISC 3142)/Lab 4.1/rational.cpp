#include <iostream>
#include <cmath> 
using namespace std;
#include "rational.h"
#include "rational_exception.h"

namespace rational{
	int gcd(int numerator, int denominator) {
	    if (denominator == 0)
	        return numerator;
	    else
	        return gcd(denominator, numerator%denominator);
		}
}

Rational::Rational(int numerator, int denominator){
    if (denominator == 0)
        throw RationalException("Denominator can't be zero!");
    this->num = numerator/rational::gcd(numerator,denominator);
    this->denom = denominator/rational::gcd(numerator,denominator);
}

Rational Rational::neg() const{
    return Rational(-1*this->num,this->denom);
}

Rational Rational::inv() const{
    return Rational(this->denom,this->num);
}

Rational Rational::add(const Rational &operande) const{
    return Rational(
        this->num* operande.denom + operande.num * this->denom,
        this->denom * operande.denom
        );
}

Rational Rational::sub(const Rational &operande) const{
    Rational operandNegated = operande.neg();
    return this->add(operandNegated);
}

Rational Rational::mul(const Rational &operande) const{
    return Rational(this->num * operande.num, this->denom * operande.denom);
}

Rational Rational::div(const Rational &operande) const{
    Rational operandeInv = operande.inv();
    return this->mul(operandeInv);
}

int Rational::getNumerator() const{
    return this->num;
}

int Rational::getDenominator() const{
    return this->denom;
}

Rational &Rational::addInPlace(const Rational &operade){
    Rational sum = this->add(operade);
    this->num = sum.num;
    this->denom = sum.denom;
    return *this;
}

Rational &Rational::subInPlace(const Rational &operade){
    Rational difference = this->sub(operade);
    this->num = difference.num;
    this->denom = difference.denom;
    return *this;
}

Rational &Rational::mulInPlace(const Rational &operade){
    Rational product = this->sub(operade);
    this->num = product.num;
    this->denom = product.denom;
    return *this;
}

Rational &Rational::divInPlace(const Rational &operade){
    Rational quotient = this->sub(operade);
    this->num = quotient.num;
    this->denom = quotient.denom;
    return *this;
}

void Rational::print(ostream &os) const{
    if (this->denom == 1) 
        os << this->num;
    else if (this->num == this->denom)
        os << 1;
    else 
        os << this->num << "/" << this->denom;
}

int Rational::compareTo(const Rational &operande) const{
    float a = (float)this->getNumerator()/(float)this->getDenominator();
    float b = (float)operande.getNumerator()/(float)operande.getDenominator();
    if (a < b)
        return -1;
    else if (abs(a-b) <= 0.0001) 
        return 0;
    else
        return 1;
}

bool Rational::equals(const Rational &operande) const{
    return (this->compareTo(operande) == 0);
}