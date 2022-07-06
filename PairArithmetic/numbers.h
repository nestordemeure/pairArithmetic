#pragma once

#include "EFT.h"

//-----------------------------------------------------------------------------
// compensated numbers, used to increase the precision of operations

template <typename T>
class CompensatedNumber
{
public:
    // true number ≈ number + errorComposants
    T number; // current computed number
    T error;  // approximation of the current error

    // constructors
    inline CompensatedNumber() : number(), error(){};
    inline CompensatedNumber(T numberArg) : number(numberArg), error(){}; // we accept implicit cast from T to S<T>
    inline CompensatedNumber(T numberArg, T errorArg) : number(numberArg), error(errorArg){};

    // cast
    inline explicit operator T() const { return number + error; };

    // operators
    CompensatedNumber &operator+=(const CompensatedNumber &n);
    CompensatedNumber &operator-=(const CompensatedNumber &n);
    CompensatedNumber &operator*=(const CompensatedNumber &n);
    CompensatedNumber &operator/=(const CompensatedNumber &n);
    CompensatedNumber &operator+=(const T &n);
    CompensatedNumber &operator-=(const T &n);
    CompensatedNumber &operator*=(const T &n);
    CompensatedNumber &operator/=(const T &n);
};

//-----------------------------------------------------------------------------
// ADDITION

// +=
template <typename T>
CompensatedNumber<T> &CompensatedNumber<T>::operator+=(const CompensatedNumber<T> &n)
{
    T result = number + n.number;
    T remainder = Eft::TwoSum(number, n.number, result);

    number = result;
    error += remainder + n.error;

    return *this;
};

// += (second member is a T)
template <typename T>
CompensatedNumber<T> &CompensatedNumber<T>::operator+=(const T &n)
{
    T result = number + n;
    T remainder = Eft::TwoSum(number, n, result);

    number = result;
    error += remainder;

    return *this;
};

// +
template <typename T>
const CompensatedNumber<T> operator+(const CompensatedNumber<T> &n1, const CompensatedNumber<T> &n2)
{
    T result = n1.number + n2.number;

    T remainder = Eft::TwoSum(n1.number, n2.number, result);
    T newError = remainder + n1.error + n2.error;

    return CompensatedNumber<T>(result, newError);
};

// + (first member is a T)
template <typename T>
const CompensatedNumber<T> operator+(const T &n1, const CompensatedNumber<T> &n2)
{
    T result = n1 + n2.number;

    T remainder = Eft::TwoSum(n1, n2.number, result);
    T newError = remainder + n2.error;

    return CompensatedNumber<T>(result, newError);
};

// + (second member is a T)
template <typename T>
const CompensatedNumber<T> operator+(const CompensatedNumber<T> &n1, const T &n2)
{
    T result = n1.number + n2;

    T remainder = Eft::TwoSum(n1.number, n2, result);
    T newError = remainder + n1.error;

    return CompensatedNumber<T>(result, newError);
};

//-----------------------------------------------------------------------------
// SUBTRACTION

// -=
template <typename T>
CompensatedNumber<T> &CompensatedNumber<T>::operator-=(const CompensatedNumber<T> &n)
{
    T result = number - n.number;
    T remainder = Eft::TwoSum(number, -n.number, result);

    number = result;
    error += remainder + n.error;

    return *this;
};

// -= (second member is a T)
template <typename T>
CompensatedNumber<T> &CompensatedNumber<T>::operator-=(const T &n)
{
    T result = number - n;
    T remainder = Eft::TwoSum(number, -n, result);

    number = result;
    error += remainder;

    return *this;
};

// unary -
template <typename T>
const CompensatedNumber<T> operator-(const CompensatedNumber<T> &n)
{
    T result = -n.number;
    T newError = -n.error;

    return CompensatedNumber<T>(result, newError);
};

// -
template <typename T>
const CompensatedNumber<T> operator-(const CompensatedNumber<T> &n1, const CompensatedNumber<T> &n2)
{
    T result = n1.number - n2.number;

    T remainder = Eft::TwoSum(n1.number, -n2.number, result);
    T newError = remainder + n1.error - n2.error;

    return CompensatedNumber<T>(result, newError);
};

// - (first member is a T)
template <typename T>
const CompensatedNumber<T> operator-(const T &n1, const CompensatedNumber<T> &n2)
{
    T result = n1 - n2.number;

    T remainder = Eft::TwoSum(n1, -n2.number, result);
    T newError = remainder - n2.error;

    return CompensatedNumber<T>(result, newError);
};

// - (second member is a T)
template <typename T>
const CompensatedNumber<T> operator-(const CompensatedNumber<T> &n1, const T &n2)
{
    T result = n1.number - n2;

    T remainder = Eft::TwoSum(n1.number, -n2, result);
    T newError = remainder + n1.error;

    return CompensatedNumber<T>(result, newError);
};

//-----------------------------------------------------------------------------
// MULTIPLICATION

// *=
template <typename T>
CompensatedNumber<T> &CompensatedNumber<T>::operator*=(const CompensatedNumber<T> &n)
{
    T result = number * n.number;
    T remainder = Eft::FastTwoProd(number, n.number, result);

    error = n.number * error + remainder + number * n.error;
    number = result;

    return *this;
}

// *= (second member is a T)
template <typename T>
CompensatedNumber<T> &CompensatedNumber<T>::operator*=(const T &n)
{
    T result = number * n;
    T remainder = Eft::FastTwoProd(number, n, result);

    error = n * error + remainder;
    number = result;

    return *this;
}

// *
// note : we ignore second order terms
template <typename T>
const CompensatedNumber<T> operator*(const CompensatedNumber<T> &n1, const CompensatedNumber<T> &n2)
{
    T result = n1.number * n2.number;

    T remainder = Eft::FastTwoProd(n1.number, n2.number, result);
    T newError = remainder + (n1.number * n2.error + n2.number * n1.error);

    return CompensatedNumber<T>(result, newError);
};

// * (first term is a T)
template <typename T>
const CompensatedNumber<T> operator*(const T &n1, const CompensatedNumber<T> &n2)
{
    T result = n1 * n2.number;

    T remainder = Eft::FastTwoProd(n1, n2.number, result);
    T newError = remainder + n1 * n2.error;

    return CompensatedNumber<T>(result, newError);
};

// * (second term is a T)
template <typename T>
const CompensatedNumber<T> operator*(const CompensatedNumber<T> &n1, const T &n2)
{
    T result = n1.number * n2;

    T remainder = Eft::FastTwoProd(n1.number, n2, result);
    T newError = remainder + n2 * n1.error;

    return CompensatedNumber<T>(result, newError);
};

//-----------------------------------------------------------------------------
// DIVISION

// /=
template <typename T>
CompensatedNumber<T> &CompensatedNumber<T>::operator/=(const CompensatedNumber<T> &n)
{
    T result = number / n.number;
    T remainder = Eft::RemainderDiv(number, n.number, result);

    T nPrecise = n.number + n.error;
    error = ((remainder + error) - result * n.error) / n2Precise;
    number = result;

    return *this;
}

// /= (second member is a T)
template <typename T>
CompensatedNumber<T> &CompensatedNumber<T>::operator/=(const T &n)
{
    T result = number / n;
    T remainder = Eft::RemainderDiv(number, n, result);

    error = (remainder + error) / n;
    number = result;

    return *this;
}

// /
template <typename T>
const CompensatedNumber<T> operator/(const CompensatedNumber<T> &n1, const CompensatedNumber<T> &n2)
{
    T result = n1.number / n2.number;

    T remainder = EFT::RemainderDiv(n1.number, n2.number, result);
    T n2Precise = n2.number + n2.error;
    T newError = ((remainder + n1.error) - result * n2.error) / n2Precise;

    return CompensatedNumber<T>(result, newError);
};

// / (first term is a T)
template <typename T>
const CompensatedNumber<T> operator/(const T &n1, const CompensatedNumber<T> &n2)
{
    T result = n1 / n2.number;

    T remainder = EFT::RemainderDiv(n1, n2.number, result);
    T n2Precise = n2.number + n2.error;
    T newError = (remainder - result * n2.error) / n2Precise;

    return CompensatedNumber<T>(result, newError);
};

// / (second term is a T)
template <typename T>
const CompensatedNumber<T> operator/(const CompensatedNumber<T> &n1, const T &n2)
{
    T result = n1.number / n2;

    T remainder = EFT::RemainderDiv(n1.number, n2, result);
    T newError = (remainder + n1.error) / n2;

    return CompensatedNumber<T>(result, newError);
};