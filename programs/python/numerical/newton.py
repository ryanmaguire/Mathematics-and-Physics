from PIL import Image
import numpy as np

# Set range for x and y axes.
x_min, x_max = -1.0, 1.0
y_min, y_max = -1.0, 1.0

# Colors for the roots (Red, Green, Blue).
colors = [(255, 0, 30), (0, 255, 30), (0, 30, 255)]

size = 512
img = Image.new("RGB", (size, size), (255, 255, 255))
image = Image.new("RGB", (size, size))

roots = [1.0+0.0j, -0.5+0.8660254037844386j, -0.5-0.8660254037844386j]
roots = np.array(roots)

for y in range(size):
    z_y = y * (y_max - y_min)/(size - 1) + y_min
    for x in range(size):
        z_x = x * (x_max - x_min)/(size - 1) + x_min
        z = complex(z_x, z_y)

        # Allow 40 iterations for Newton-Raphson.
        for iters in range(40):
            # Perfrom Newton-Raphson on z^3 - 1 (Simplifying as well).
            root = (2.0*z*z*z + 1)/(3.0*z*z)

            # Checks for convergence
            if abs(root - z) < 10e-10:
                break
            z = root

        ind = np.min((
            np.abs(root-roots) == np.min(np.abs(root-roots))
        ).nonzero())
        col = colors[ind]
        col = [k for k in col]

        # Create a gradient in color to emphasize rate of convergence.
        col[ind] -= 10*iters
        col = tuple([k for k in col])

        img.putpixel((x, y), col)

        # Extra code for an alternative fractal.
        image.putpixel((x, y), ((iters%4)*64, (iters%8)*32, (iters%16)*16))
    print("Pt: %d" % y, "Tot: %d" % size, "Iters: %d" % iters, end="\r")
img.save("NewtonRoots.png", "PNG")

# Save the alternative fractal, if not commented out.
image.save("NewtonFractal.png", "PNG")
print("Done")
