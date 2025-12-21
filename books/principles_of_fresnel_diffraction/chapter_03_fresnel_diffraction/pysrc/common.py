import numpy
import matplotlib.pyplot as plt

# Parameters for the monochromatic wave.
# Wavelength (lambda) is set to red, in the visible spectrum.
wavelength = 6.5E-07
initial_intensity = 1.0

# We'll clip the colors a bit so we can see the pattern more clearly.
clip = 0.5 * initial_intensity

# Parameters for the image.
x_size = 5.0E-03
y_size = 5.0E-03
x_pixels = 2048
y_pixels = 2048
plot_boundaries = [-x_size, x_size, -y_size, y_size]

# Step sizes used for sampling the x and y axes.
x_displacement = 2.0 * x_size / float(x_pixels)
y_displacement = 2.0 * y_size / float(y_pixels)

# Arrays for the two axes.
x_vals = numpy.arange(-x_size, x_size, x_displacement)
y_vals = numpy.arange(-y_size, y_size, y_displacement)

def make_plots(intensity, file_name):
    """
        Makes plots.
    """
    # Make the plots.
    figure, axes = plt.subplots()
    image = axes.imshow(
        intensity,
        extent = plot_boundaries,
        cmap = 'hot',
        vmin = 0.0,
        vmax = clip
    )

    # Add labels for the axes and the plot.
    axes.set_xlabel("x (meters)")
    axes.set_ylabel("y (meters)")
    axes.set_title("Fresnel Diffraction: Rectangular Aperture")
    figure.colorbar(image, ax = axes)

    # Render the image.
    plt.savefig(file_name.rsplit('.', 1)[0] + ".png")
