# Pair Arithmetic

A very simple, *header only*, implementation of pair arithmetic (see [Faithfully Rounded Floating-point Computations](https://dl.acm.org/doi/10.1145/3290955)).
Destined to be used when a C++ program needs a local boost in accuracy but cannot easily be refactored to be more numerically stable.

## Instalation

To use this library, you just need to drop the `PairArithmetic` folder in your program.

## Usage

We provide compensated numbers that can be cast from and to IEEE-754 types (such as float and double) in `PairArithmetic/numbers.h` and compensated complex numbers (to reduce casting needs) in `PairArithmetic/complex.h`.

```cpp
#include "PairArithmetic/numbers.h"

using Pdouble = CompensatedNumber<double>;

double x = 1e100;
Pdouble y = 1.0;

// you can mix double and Pdouble in your computations
// the error will be compensated as long as one argument of the operations is a Pdouble
Pdouble z = x + y;

// and use in-place operators
z -= 1e100;

// cast back to double in order to get the compensated, improved-precision, result
double z_corrected = (double)z; // 1.0
```

*Note:* our numbers implement additions and multiplications (and the associated in-place operations) but not divisions.
Do not hesitate to add an issue if you need this operation as it would be easy to fix.

