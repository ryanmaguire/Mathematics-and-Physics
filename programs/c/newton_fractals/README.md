# Table of Contents
1. [Newton Fractals](#nf)
2. [Compiling](#compiling)
3. [License](#license)

# Newton Fractals <a name="nf"></a>
This project renders Newton fractals. Given a complex polynomial
$p:\mathbb{C}\rightarrow\mathbb{C}$ and a point $z_{0}\in\mathbb{C}$ you can
apply Newton's method to this point and see if it converges to a root. Newton's
method is iterative. It defines:
$$z_{n+1}=z_{n}-\frac{p(z_{n})}{p'(z_{n})}$$
You may then ask *if this converges, to which root does it converge?* If there
are $N$ distinct roots, you can choose $N$ colors corresponding to each
and color $z_{0}$ based on which point Newton's method converges to. (If it
didn't converge, color it black. This is the Julia set of the Newton fractal).

The Newton fractal for $p(z)=z^{3}-1$ is given below.
![Newton Fractal](https://github.com/ryanmaguire/Mathematics-and-Physics/blob/master/images/newton_fractal_z_cubed_minus_one.png "Newton Fractal")

# Compiling
The files are written in plain C without any dependencies (other than the
standard library). You can compile with `clang` or `gcc`. For example:
```
gcc -Wall -Wextra -Wpedantic -O3 -flto newton_fractal_z_cubed_minus_one_real.c -o test.out -lm
```
Similarly:
```
clang -Wno-padded -Weverything -O3 -flto newton_fractal_z_cubed_minus_one_real.c -o test.out -lm
```
`clang` will complain about padding structs if `-Weverything` is passed without
`-Wno-padded`. I don't particularly care about how the compiler pads a struct,
so long as it works. This warning is of no consequence. `gcc` gives no warnings.

# License
    Mathematics-and-Physics is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Mathematics-and-Physics is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with Mathematics-and-Physics.  If not, see <https://www.gnu.org/licenses/>.
