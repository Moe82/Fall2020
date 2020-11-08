#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

class Rational {
        public:
                Rational(int num, int denom);
                Rational(int num);

                
                Rational(Rational &r);

                Rational add(const Rational &r) const;
                Rational &addInPlace(const Rational &r);

                Rational sub(const Rational &r) const;
                Rational &subInPlace(const Rational &r);

                Rational mul(const Rational &r) const;
                Rational &mulInPlace(const Rational &r);

                Rational div(const Rational &r) const;
                Rational &divInPlace(const Rational &r);

                int getNumerator() const;
                int getDenominator() const;

                bool equals(Rational &r) const;
                bool compareTo(Rational &r) const;

                Rational neg() const;
                Rational inv() const;

                void norm() const; 
                void print(std::ostream &os) const;

        private:
                int num, denom;
};

inline std::ostream &operator <<(std::ostream &os, const Rational &r) {r.print(os); return os;}
#endif