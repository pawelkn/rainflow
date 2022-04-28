Rainflow
========

[![Test rainflow](https://github.com/pawelkn/rainflow/actions/workflows/test.yml/badge.svg)](https://github.com/pawelkn/rainflow/rainflow/actions/workflows/test.yml)

`rainflow` is a C++ implementation of the ASTM E1049-85 rain flow cycle counting
algorithm for fatigue analysis. It is based on Python library [rainflow](https://github.com/iamlikeme/rainflow)

The implementation consists of a single header `rainflow.h` and source file `rainflow.cpp` and has zero dependencies.

Usage
-----

Function `RainFlow::count_cycles` returns a list of ranges and the corresponding number of cycles.

It takes two arguments:
* `RainFlow::Series series` - an input vector of samples to process,
* `double binsize` - (optional) specifies the width of each cycle-counting bin

Returns a `RainFlow::Counts` vector of `RainFlow::Count` structs.
`RainFlow::Count` struct has two fields: `range` and `cycles`.

Example:
```cpp
#include "rainflow.h"

int main()
{
    RainFlow::Series series { -2, 1, -3, 5, -1, 3, -4, 4, -2 };
    auto counts { RainFlow::count_cycles( series, 2.0 ) };
    /* counts:
        { 2, 0.0 },
        { 4, 2.0 },
        { 6, 0.5 },
        { 8, 1.0 },
        { 10, 0.5 }
    */
}
```

It is possible to obtain full information about each cycle using is an `extract_cycles` function.

It takes a single argument:
* `RainFlow::Series series` - an input vector of samples to process

Returns a `RainFlow::Cycles` vector of `RainFlow::Cycle` structs.
`RainFlow::Cycle` struct has fields: `range`, `mean`, `count`, `start_index` and `end_index`.

Example:
```cpp
#include "rainflow.h"

int main()
{
    RainFlow::Series series { -2, 1, -3, 5, -1, 3, -4, 4, -2 };
    auto cycles { RainFlow::extract_cycles( series ) };
    /* cycles:
        { 3, -0.5, 0.5, 0, 1 },
        { 4, -1.0, 0.5, 1, 2 },
        { 4, 1.0, 1.0, 4, 5 },
        { 8, 1.0, 0.5, 2, 3 },
        { 9, 0.5, 0.5, 3, 6 },
        { 8, 0.0, 0.5, 6, 7 },
        { 6, 1.0, 0.5, 7, 8 }
    */
}
```

Running example
-----

Build and run the example using `docker`:
```
docker build -t rainflow .
docker run --rm rainflow
```

or locally:
```
make
build/example_rainflow example/samples.txt 
```

Running tests
-----

Build and run unit tests using `docker`:
```
docker build -t rainflow .
docker run --rm rainflow make test
```

or localy:
```
make test
```

To run tests locally the [GoogleTest](https://github.com/google/googletest) library is requited. Under linux it can be installed via package manager eg.:

```sh
apt-get install -y libgtest-dev
```