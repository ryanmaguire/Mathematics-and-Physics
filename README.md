## Friendly Warnings
  1. There are many typos and incorrect information. This is obviously not
     intentional, many of the notes were taken mid-lecture via LaTeX and I have
     not had the time to correct them yet. I am working though in order,
     correcting information, and have made good progress in book 1 on Logic and
     Set Theory.
  2. I'm experimenting with writing figures in different languages. I used to
     use tikz, now I mostly use asymptote. Lately I've been experimenting with
     a library I've written in C to produce SVG figures. Currently the figures
     in the text use both tikz and asymptote. This will likely change over time
     to just asymptote.

# Compiling
You will need:
  1. `asy` - The Asymptote Vector Graphics Language.
  2. `pdflatex` - A LaTeX compiler.
  3. `gcc` - The GNU C compiler.
  4. `convert` - Image Magick tool for converting images to different formats.

TeX-Live and Mac-Tex (GNU/Linux and macOS, respectively) have both `pdflatex`
and asymptote. macOS users cab find this at <https://www.tug.org/mactex/>.
GNU/Linux users for Debian based distributions (Debian, Ubuntu, Pop!_OS, etc.)
can install tex-live using their package manager:
```
sudo apt-get install texlive-full
```
Different Linux distributions will need to use their respective package manager.
`gcc` comes pre-installed on many GNU/Linux distributions. If it is not,
install it via:
```
sudo apt-get install gcc
```
macOS users will need to install `xcode` to use Apple's C compiler
(it is labelled `gcc` but is actually based on LLVM's `clang`). This is done
via:
```
xcode-select --install
```
As of this writing, `convert` comes pre-installed on macOS and Debian. If it is
not available for a particular GNU/Linux distribution, try:
```
sudo apt-get install imagemagick
```
To make the figures, give the `make_figs.sh` executable permissions, and then
run it:
```
chmod +x make_figs.sh
./make_figs.sh
```
There are several hundred figures, so this will take a while. 10 minutes on a
fast computer, about 30 minutes on a slower one.
To make the C figures, do the same with `make_cfigs.sh`.
```
chmod +x make_cfigs.sh
./make_cfigs.sh
```

# Mathematics_and_Physics
Various notes on mathematics and physics organized in several volumes. **This
project is currently incomplete and will remain so for quite some time**. I am
actively working on it, but the end goal is rather big. Recently I've updated
the geometry to be A5 paper with 14mm margins and some of the older notes that
I have not yet gotten to will have equations falling out of the page. I've
also rewritten several environments for displaying and emphasizing theorems and
definitions, but this means some of the older ones will be poorly formatted. I
am working to getting this project both aesthetically appealing and
mathematically accurate. Suggestions are more than welcome.

The books are currently arranged as follows:

## Foundations
Notes on set theory, logic, model theory, arithmetic, and the structure of the
real numbers (including the calculus of one variable).

## Algebra
Group theory, rings and fields, as well as vector spaces, modules, and linear
algebra.

## Topology
Point set topology covering topological spaces, continuity, separation,
connectedness, compactness, and a myriad of other properties. Many examples and
counterexamples are provided and a great number of spaces are discussed.
Homotopy, homology, cohomology, and related topics are developed, and
topological manifolds are described. Smooth and differentiable manifolds are
saved for **Geometry** since we will need many of the results from **Analysis**,
and hence there's a bit of a gap between studying topological manifolds and
studying smooth manifolds.

## Analysis
Calculus, measure theory, functional analysis, probability theory,
multivariate calculus, ordinary and partial differential equations, and
Fourier analysis. Special functions such as Fresnel integrals and Bessel
functions are constructed and discussed throughout.

## Geometry
Differential topology and Riemannian geometry, Convex and Euclidean geometry.

## Geometric Topology
Knot theory, low dimensional topology, and surgery theory.

## Physics
Classical mechanics, electromagnetism, quantum mechanics, and astronomy.

