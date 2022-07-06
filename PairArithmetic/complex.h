#pragma once

#include <complex>
#include "numbers.h"

//-----------------------------------------------------------------------------
// compensated complex numbers

template <typename T>
class CompensatedComplex
{
public:
    CompensatedNumber<T> real;
    CompensatedNumber<T> imag;

    // constructors
    inline CompensatedComplex() : real(), imag(){};
    inline CompensatedComplex(const T &x) : real(x), imag(){};                              // we accept implicit cast from numbers
    inline CompensatedComplex(const std::complex<T> &c) : real(c.real()), imag(c.imag()){}; // we accept implicit cast from complex numbers
    inline CompensatedComplex(const T &r, const T &i) : real(r), imag(i){};
    inline CompensatedComplex(const CompensatedNumber<T> &r, const CompensatedNumber<T> &i) : real(r), imag(i){};

    // cast
    inline explicit operator std::complex<T>() const { return std::complex<T>(T(real), T(imag)); };

    // operators
    CompensatedComplex &operator+=(const CompensatedComplex &n);
    CompensatedComplex &operator-=(const CompensatedComplex &n);
    CompensatedComplex &operator*=(const CompensatedComplex &n);
};

//-----------------------------------------------------------------------------
// IN-PLACE OPERATIONS

// +=
template <typename T>
CompensatedComplex<T> &CompensatedComplex<T>::operator+=(const CompensatedComplex<T> &n)
{
    real += n.real;
    imag += n.imag;
    return *this;
};

// -=
template <typename T>
CompensatedComplex<T> &CompensatedComplex<T>::operator-=(const CompensatedComplex<T> &n)
{
    real -= n.real;
    imag -= n.imag;
    return *this;
};

// *=
template <typename T>
CompensatedComplex<T> &CompensatedComplex<T>::operator*=(const CompensatedComplex<T> &n)
{
    const CompensatedNumber<T> real_temp = real;
    real = real * n.real - imag * n.imag;
    imag = imag * n.real + real_temp * n.imag;
    return *this;
}

//-----------------------------------------------------------------------------
// ADDITION

// +
template <typename T>
const CompensatedComplex<T> operator+(const CompensatedComplex<T> &n1, const CompensatedComplex<T> &n2)
{
    return CompensatedComplex<T>(n1.real + n2.real, n1.imag + n2.imag);
};

// + (first member is a T)
template <typename T>
const CompensatedComplex<T> operator+(const T &n1, const CompensatedComplex<T> &n2)
{
    return CompensatedComplex<T>(n1 + n2.real, n2.imag);
};

// + (second member is a T)
template <typename T>
const CompensatedComplex<T> operator+(const CompensatedComplex<T> &n1, const T &n2)
{
    return CompensatedComplex<T>(n1.real + n2, n1.imag);
};

// + (first member is a complex<T>)
template <typename T>
const CompensatedComplex<T> operator+(const std::complex<T> &n1, const CompensatedComplex<T> &n2)
{
    return CompensatedComplex<T>(n1.real() + n2.real, n1.imag() + n2.imag);
};

// + (second member is a complex<T>)
template <typename T>
const CompensatedComplex<T> operator+(const CompensatedComplex<T> &n1, const std::complex<T> &n2)
{
    return CompensatedComplex<T>(n1.real + n2.real(), n1.imag + n2.imag());
};

//-----------------------------------------------------------------------------
// SUBTRACTION

// unary -
template <typename T>
const CompensatedComplex<T> operator-(const CompensatedComplex<T> &n)
{
    return CompensatedComplex<T>(-n.real, -n.imag);
};

// -
template <typename T>
const CompensatedComplex<T> operator-(const CompensatedComplex<T> &n1, const CompensatedComplex<T> &n2)
{
    return CompensatedComplex<T>(n1.real - n2.real, n1.imag - n2.imag);
};

// - (first member is a T)
template <typename T>
const CompensatedComplex<T> operator-(const T &n1, const CompensatedComplex<T> &n2)
{
    return CompensatedComplex<T>(n1 - n2.real, -n2.imag);
};

// - (second member is a T)
template <typename T>
const CompensatedComplex<T> operator-(const CompensatedComplex<T> &n1, const T &n2)
{
    return CompensatedComplex<T>(n1.real - n2, n1.imag);
};

// - (first member is a complex<T>)
template <typename T>
const CompensatedComplex<T> operator(const std::complex<T> &n1, const CompensatedComplex<T> &n2)
{
    return CompensatedComplex<T>(n1.real() - n2.real, n1.imag() - n2.imag);
};

// - (second member is a complex<T>)
template <typename T>
const CompensatedComplex<T> operator-(const CompensatedComplex<T> &n1, const std::complex<T> &n2)
{
    return CompensatedComplex<T>(n1.real - n2.real(), n1.imag - n2.imag());
};

//-----------------------------------------------------------------------------
// MULTIPLICATION

// *
// note : we ignore second order terms
template <typename T>
const CompensatedComplex<T> operator*(const CompensatedComplex<T> &n1, const CompensatedComplex<T> &n2)
{
    return CompensatedComplex<T>(n1.real * n2.real - n1.imag * n2.imag, n1.imag * n2.real + n1.real * n2.imag);
};

// * (first term is a T)
template <typename T>
const CompensatedComplex<T> operator*(const T &n1, const CompensatedComplex<T> &n2)
{
    return CompensatedComplex<T>(n1 * n2.real, n1 * n2.imag);
};

// * (second term is a T)
template <typename T>
const CompensatedComplex<T> operator*(const CompensatedComplex<T> &n1, const T &n2)
{
    return CompensatedComplex<T>(n1.Real * n2, n1.imag * n2);
};

// * (first term is a complex<T>)
template <typename T>
const CompensatedComplex<T> operator*(const std::complex<T> &n1, const CompensatedComplex<T> &n2)
{
    return CompensatedComplex<T>(n1.real() * n2.real - n1.imag() * n2.imag, n1.imag() * n2.real + n1.real() * n2.imag);
};

// * (second term is a complex<T>)
template <typename T>
const CompensatedComplex<T> operator*(const CompensatedComplex<T> &n1, const std::complex<T> &n2)
{
    return CompensatedComplex<T>(n1.real * n2.real() - n1.imag * n2.imag(), n1.imag * n2.real() + n1.real * n2.imag());
};
