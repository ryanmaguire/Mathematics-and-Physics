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

# Installation
This details how to go about reading the contents of Mathematics-and-Physics.
The repository has been updated so that the actual `png` and `pdf` files used
for images through the project are not included in the `images/` folder. This is
to save space on the repository and prevent git from keeping track of changes to
the images themselved. Git should only be used to keep track of changes to the
code. All of the images are made from code (tikz, asymptote, and the C
programming language). To run the setup scripts you will need `gcc` which is the
standard C compiler, and a latex distribution which has asympote (tex-live and
mactex both provide the `asy` command). In creating and organizing figures,
Linux users will need `ImageMagick`, which is free and open source. Mac users
will also need this, but it comes standard with OSX. See the README in `images/`
to installation instructions. If you are not interested in the code, but simply
want access to the document, see `The Easiest Method`.

## The Easiest Method
Download Mathematics_and_Physics.pdf file and read away. Note, you will not be
able to compile `main.tex` or have access to the high resolution standalone
figures (The figures will be in the PDF document, however).

## Full Installation
**You will need:**
  1. `gcc` The GNU Compiler Collection (Only C compiler is needed).
  2. `asy` The Asymptote Compiler (Comes with tex-live and mactex).
  3. `ImageMagick` (comes standard with OSX).

See `images/README.md` for installation instructions. Once these are installed:
  1. Cloan or Download the repository onto your computer.
  2. Navigate to where it's located (ex: /Documents/Mathematics_and_Physics)
  ```Bash
    Ryans-iMac:~ ryan$ cd ~/GitHub/Mathematics_and_Physics/
  ```
  3. Make sure `make_main.sh` has executable permissions:
  ```Bash
    Ryans-iMac:Mathematics_and_Physics ryan$ chmod +x make_main.sh
  ```
  4. Run the make_main.sh shell script.
  ```Bash
    Ryans-iMac:Mathematics_and_Physics ryan$ ./make_main.sh
  ```
Since there are a lot of figures to generate this will take about 10 minutes.
