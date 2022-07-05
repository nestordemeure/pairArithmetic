#pragma once

/*
 * ERROR FREE TRANSFORM
 *
 * gives us the exact error|remainder of an arithmetic operation using :
 * - twoSum for + (might be killed by aggressive compilation in the absence of protection)
 * - std::fma for * (reliable independent of the compilations flags)
 */
namespace Eft
{
    // basic EFT for a sum
    // WARNING requires rounding to nearest (see Priest)
    // NOTE the volatile keyword is there to avoid the operation being optimized away by a compiler using associativity rules
    template <typename T>
    inline const T TwoSum(const T n1, const T n2, const volatile T result)
    {
        const T n22 = result - n1;
        const T n11 = result - n22;
        const volatile T epsilon2 = n2 - n22;
        const volatile T epsilon1 = n1 - n11;
        const T error = epsilon1 + epsilon2;
        return error;
    }

    // fast EFT for a multiplication
    // see also dekker's multiplication algorithm (rounding to nearest) when an FMA is unavailable
    // NOTE proof for rounding toward zero in "Error-Free Transformation in Rounding Mode toward Zero"
    // WARNING proved only for rounding to nearest and toward zero
    template <typename T>
    inline const T FastTwoProd(const T n1, const T n2, const T result)
    {
        const T error = std::fma(n1, n2, -result);
        return error;
    }

    // computes the remainder of the division
    // see the Handbook of floating point arithmetic
    template <typename T>
    inline const T RemainderDiv(const T n1, const T n2, const T result)
    {
        T remainder = -std::fma(n2, result, -n1);
        return remainder;
    }
}
