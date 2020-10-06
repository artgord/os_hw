#include "complex.h"
#include <cmath>
double Complex::getReal()
{
    return mReal;
}

double Complex::getImaginary()
{
    return mImaginary;
}

Complex::Complex(double real, double imaginary)
    : mReal{real}
    , mImaginary{imaginary}
{}

Complex Complex::operator+(const Complex& rhs)
{
    return Complex{mReal + rhs.mReal, mImaginary + rhs.mImaginary};
}

Complex Complex::operator-(const Complex& rhs)
{
    return Complex{mReal - rhs.mReal, mImaginary - rhs.mImaginary};
}

Complex Complex::operator*(double number)
{
    return Complex{mReal*number, mImaginary*number};
}

double Complex::absoluteValue()
{
    return sqrt(mReal*mReal + mImaginary*mImaginary);
}
