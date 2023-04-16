# Programs
This directory has a few uses.
  1. Contains several *mini-projects* using different programming languages.
     This includes raytracing, visualizing knots and complex functions, drawing
     fractals, rendering black holes, and more.
  2. The mini-projects are duplicated in different languages. For example,
     *newtonian_black_holes* which renders black holes by using
     (and every so slightly abusing) Newtonian mechanics, has implementations
     in `C`, `C++`, and more. This helps learn new languages, see how a
     specific algorithm may be used in different ways, and allow us to
     benchmark the same code with diffrent implementations.
  3. Several of the figures rendered in these mini projects are used in my
     notes. Newton fractals, for example, may be rendered rather quickly with
     a somewhat short `C` file. The process is practically impossible with
     `asymptote` or `tikz`, the standard lanuages used for graphics in `LaTeX`.

## Benchmarks

### Newtonian Black Holes

| Language               | Implementation | Time (s) | Flags              | Version                                  |
| ---------------------- | -------------- | -------- | ------------------ | ---------------------------------------- |
| C (w/OpenMP)           | gcc            |    1.322 | -O3 -flto -fopenmp | gcc (Debian 10.2.1-6) 10.2.1 20210110    |
| C (w/OpenMP)           | clang          |    1.704 | -O3 -flto -fopenmp | Debian clang version 11.0.1-2            |
| C++ (w/OpenMP)         | clang++        |    1.995 | -O3 -flto -fopenmp | Debian clang version 11.0.1-2            |
| C++ (w/OpenMP)         | g++            |    2.234 | -O3 -flto -fopenmp | g++ (Debian 10.2.1-6) 10.2.1 20210110    |
| go (w/Parallelization) | golang         |    2.646 |                    | go 1.15.15                               |
| go (w/Parallelization) | gccgo          |    2.921 | -O3 -flto          | gccgo (Debian 10.2.1-6) 10.2.1 20210110  |
| C                      | gcc            |   15.067 | -O3 -flto          | gcc (Debian 10.2.1-6) 10.2.1 20210110    |
| C                      | clang          |   16.440 | -O3 -flto          | Debian clang version 11.0.1-2            |
| Python                 | Pypy           |   18.324 |                    | PyPy 7.3.5 with GCC 10.2.1 20210110      |
| Go                     | golang         |   23.883 |                    | go 1.15.15                               |
| Go                     | gccgo          |   27.201 | -O3 -flto          | gccgo (Debian 10.2.1-6) 10.2.1 20210110  |
| C++                    | g++            |   27.566 | -O3 -flto          | g++ (Debian 10.2.1-6) 10.2.1 20210110    |
| C++                    | clang++        |   29.547 | -O3 -flto          | Debian clang version 11.0.1-2            |
| C                      | pcc            |   52.616 | -O2                | Portable C Compiler 1.2.0.DEVEL 20200630 |
| C                      | tcc            |   80.480 |                    | tcc version 0.9.27                       |
| Python                 | CPython        | 5552.407 |                    | Python 3.9.2                             |

Pleasantly surpised to see go can beat C++ in certain benchmarks.
Utterly surprised that third place (without parallelizing) is Pypy!
On the to-do list is adding a rust implementation.

All implementations render the same figure.
![Newtonian Black Hole](https://github.com/ryanmaguire/Mathematics-and-Physics/blob/master/images/newtonian_black_hole.png "Newtonian Black Hole")
