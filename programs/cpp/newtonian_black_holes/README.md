# Newtonian Black Holes
This is a very small project to experiment with ray tracing and
black holes using (and slightly abusing) Newtonian mechanics.

Newtonian mechanics predicts the existence of black holes.
Take the escape velocity formula and apply it to the speed of light.
The result is the the Schwarzschild radius, which is the same
formula one derives if they were to perform to full general
relativistic calculation.
$$$R=\frac{2GM}{c^{2}}$$$
where $$M$$ is the mass of the object, $$c$$ is the speed of light,
and $$G$$ is the universal gravitational constant. Next we abuse Newtonian
mechanics slightly. Newton's second law says
$$$
\mathbf{F}(t)=m\mathbf{a}=\ddot{\mathbf{r}}(t)
$$$
where $\mathbf{F}$ is the force on an object of mass $$m$$, $$\mathbf{a}$$ is
the acceleration vector, $$\mathbf{r}$$ is the position vector, and double-dots
denote the second derivative with respect to time. For gravity we have
$$$
m\ddot{\mathbf{r}}(t)=\frac{GMm}{||\mathbf{r}(t)||^{3}}\mathbf{r}(t)
$$$
where $$||\mathbf{r}(t)||$$ denotes the *norm* or Euclidean length of the
vector $$\mathbf{r}(t)$$ and $M$ is the mass of the gravitating object.
Dividing by $$m$$ we obtain the following equation of motion:
$$$
\ddot{\mathbf{r}}(t)=\frac{GM}{||\mathbf{r}(t)||^{3}}\mathbf{r}(t)
$$$
This is all fine and dandy so long as $$m\ne{0}$$, otherwise we have an
illegal division. Let us suppose that this final equation is true even for
massless particles (like light). Or pretend that light has a mass $$m$$ that
is so stupidly small (but positive) that it will never be measurable
(The reciprocal of [Graham's number](https://en.wikipedia.org/wiki/Graham%27s_number), if you'd like, in kilograms).
We may then take this equation and use it to approximate how light may
behave under the force of gravity of some object (such as a black hole).
We could then apply raytracing methods and draw a nice picture. This
directory contains files to do exactly this.

**This is not physically realistic**, obviously, but the resulting images
do look like what one might expect a black hole to be.
![Newtonian Black Hole](newtonian_black_hole.png "Newtonian Black Hole")
