#pragma once

#include <string>

namespace ariel {

    class Complex {
    public:
        double real;
        double imag;

        Complex(double r = 0, double i = 0) : real(r), imag(i) {}

        std::string to_string() const {
            return std::to_string(real) + " + " + std::to_string(imag) + "i";
        }
    };

}

