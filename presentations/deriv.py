import sympy, sympy.vector

r, r0, phi, phi0 = sympy.symbols("r r_0 phi phi_0")
B, D = sympy.symbols("B D", positive = True)
x, y, z = sympy.symbols("x y z")

N = sympy.vector.CoordSys3D("N")

rho = r*sympy.cos(phi)*N.i + r*sympy.sin(phi)*N.j
rho0 = r0*sympy.cos(phi0)*N.i + r0*sympy.sin(phi0)*N.j

u = D*sympy.cos(B)*N.i + D*sympy.sin(B)*N.k
un = u.normalize()

print(f"||rho - R_c|| = {sympy.simplify((rho - rho0 - u).magnitude())}")
print(f"u_hat . (rho - R_c) = {sympy.simplify(un.dot(rho - rho0 - u))}")
