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
    CompensatedComplex &operator/=(const CompensatedComplex &n);
};

//-----------------------------------------------------------------------------
// ADDITION

// +=
template <typename T>
CompensatedComplex<T> &CompensatedComplex<T>::operator+=(const CompensatedComplex<T> &n)
{
    real += n.real;
    imag += n.imag;
    return *this;
};

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

// -=
template <typename T>
CompensatedComplex<T> &CompensatedComplex<T>::operator-=(const CompensatedComplex<T> &n)
{
    real -= n.real;
    imag -= n.imag;
    return *this;
};

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
const CompensatedComplex<T> operator-(const std::complex<T> &n1, const CompensatedComplex<T> &n2)
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

// *=
template <typename T>
CompensatedComplex<T> &CompensatedComplex<T>::operator*=(const CompensatedComplex<T> &n)
{
    const CompensatedNumber<T> real_temp = real;
    real = real * n.real - imag * n.imag;
    imag = imag * n.real + real_temp * n.imag;
    return *this;
}

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

//-----------------------------------------------------------------------------
// DIVISION

// /=
// Uses a [complex division algorithm](https://arxiv.org/pdf/1210.4539.pdf) picked to:
// - mitigate overflows/underflows (common with the naive algorithm),
// - avoid using an FMA (unpractical with Pair arithmetic).
// NOTE: one could probably design a better algorithm by dropping at the (number,error) level
template <typename T>
CompensatedComplex<T> &CompensatedComplex<T>::operator/=(const CompensatedComplex<T> &n)
{
    if (std::abs(static_cast<T>(n.imag)) <= std::abs(static_cast<T>(n.real)))
    {
        const CompensatedNumber<T> ratio = n.imag / n.real;
        const CompensatedNumber<T> denom = n.real + n.imag * ratio;
        real = (real + imag * ratio) / denom;
        imag = (imag - real * ratio) / denom;
    }
    else
    {
        const CompensatedNumber<T> ratio = n.real / n.imag;
        const CompensatedNumber<T> denom = n.real * ratio + n.imag;
        real = (real * ratio + imag) / denom;
        imag = (imag * ratio - real) / denom;
    }

    return *this;
}

// /
// Uses a [complex division algorithm](https://arxiv.org/pdf/1210.4539.pdf) picked to:
// - mitigate overflows/underflows (common with the naive algorithm),
// - avoid using an FMA (unpractical with Pair arithmetic).
// NOTE: one could probably design a better algorithm by dropping at the (number,error) level
template <typename T>
const CompensatedComplex<T> operator/(const CompensatedComplex<T> &n1, const CompensatedComplex<T> &n2)
{
    if (std::abs(static_cast<T>(n2.imag)) <= std::abs(static_cast<T>(n2.real)))
    {
        const CompensatedNumber<T> n2Ratio = n2.imag / n2.real;
        const CompensatedNumber<T> denom = n2.real + n2.imag * n2Ratio;
        const CompensatedNumber<T> re = (n1.real + n1.imag * n2Ratio) / denom;
        const CompensatedNumber<T> im = (n1.imag - n1.real * n2Ratio) / denom;

        return CompensatedComplex<T>(re, im);
    }
    else
    {
        const CompensatedNumber<T> n2Ratio = n2.real / n2.imag;
        const CompensatedNumber<T> denom = n2.real * n2Ratio + n2.imag;
        const CompensatedNumber<T> re = (n1.real * n2Ratio + n1.imag) / denom;
        const CompensatedNumber<T> im = (n1.imag * n2Ratio - n1.real) / denom;

        return CompensatedComplex<T>(re, im);
    }
};