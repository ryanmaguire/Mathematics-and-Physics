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

For each mini-project I had more-or-less than same predictions.
  1. `C (gcc)`: The GNU compiler collections C compiler is extremely
     optimized. In almost any scenario I would imagine this creates the fastest
     code.
  2. `C (clang)`: LLVM's compiler is also extremely good.
  3. `C++ (clang++)`: In many cases C and C++ are neck-and-neck. In my
     experience LLVM's compiler is slightly faster than `g++`.
  4. `C++ (g++)`: Also very good. Again, experience seems to indicate
     `g++` generates slightly slower binaries than the equivalent `gcc` code.
  5. `Go (gccgo)`: I figured the GNU compiler might just convert the language
     to C and then use `gcc`. My guess was this would be faster than the
     default `golang` implementation by Google.
  6. `Go (golang)`: This is still a new language, I thought the optimizations
     would not be as great as those found in C/C++.
  7. `C (pcc)`: The portable C compiler usually creates binaries that are an
     order of magnitude slower than `gcc`.
  8. `C (tcc)`: The same can be said for the Tiny C compiler.
  9. `Python (CPython)`: Python is a great language, but is notoriously slow.
     Unless your code uses `C/C++` extensions to do the bulk of your
     computations, Python will most likely be slower than the
     other languages.
  10. `Python (Pypy)`: I'd never used this implementation before, but my
      naive guess was that it'd be slower than the default `CPython`. 

I was pleasantly surprised to learn this is *not* always the case.

### Newtonian Black Holes

| Language       | Implementation | Time (s) | Flags              | Version                                  |
| -------------- | -------------- | -------- | ------------------ | ---------------------------------------- |
| C (w/OpenMP)   | gcc            |    1.322 | -O3 -flto -fopenmp | gcc (Debian 10.2.1-6) 10.2.1 20210110    |
| C (w/OpenMP)   | clang          |    1.704 | -O3 -flto -fopenmp | Debian clang version 11.0.1-2            |
| C++ (w/OpenMP) | clang++        |    1.995 | -O3 -flto -fopenmp | Debian clang version 11.0.1-2            |
| C++ (w/OpenMP) | g++            |    2.234 | -O3 -flto -fopenmp | g++ (Debian 10.2.1-6) 10.2.1 20210110    |
| C              | gcc            |   15.067 | -O3 -flto          | gcc (Debian 10.2.1-6) 10.2.1 20210110    |
| C              | clang          |   16.440 | -O3 -flto          | Debian clang version 11.0.1-2            |
| Python         | Pypy           |   18.324 |                    | PyPy 7.3.5 with GCC 10.2.1 20210110      |
| Go             | golang         |   23.883 |                    | go 1.15.15                               |
| Go             | gccgo          |   27.201 | -O3 -flto          | gccgo (Debian 10.2.1-6) 10.2.1 20210110  |
| C++            | g++            |   27.566 | -O3 -flto          | g++ (Debian 10.2.1-6) 10.2.1 20210110    |
| C++            | clang++        |   29.547 | -O3 -flto          | Debian clang version 11.0.1-2            |
| C              | pcc            |   52.616 | -O2                | Portable C Compiler 1.2.0.DEVEL 20200630 |
| C              | tcc            |   80.480 |                    | tcc version 0.9.27                       |
| Python         | CPython        | 5552.407 |                    | Python 3.9.2                             |

  1. No surprise that C is at the top, nor that C/C++ with
     OpenMP is lightning fast.
  2. Go beat C++? `golang` ran slightly faster than `gccgo`? Shocking!
     Note that `gccgo` and `g++` times are basically identical.
  3. Pypy?!? Wow!
  4. `CPython` takes over 90 minutes! Ouch!

All implementations render the same figure.
![Newtonian Black Hole](https://github.com/ryanmaguire/Mathematics-and-Physics/blob/master/images/newtonian_black_hole.png "Newtonian Black Hole")
