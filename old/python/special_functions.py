import numpy
from rss_ringoccs.tools import error_check
try:
    from ._special_functions import *
    from . import _special_functions
except:
    raise ImportError(
        """
        \r\tError: rss_ringoccs\n\r\t\tdiffrec.special_functions\n
        \r\tCould Not Import C Code. There was most likely an error
        \r\tin your installation of rss_ringoccs. Install GCC (C Compiler)
        \r\tand see the User's Guide for installation instructions.
        """
    )

func_dict = {
    "rect":   {"func": rect,   "normeq": 1.00000000, "wnum": 0},
    "coss":   {"func": coss,   "normeq": 1.50000000, "wnum": 1},
    "kb20":   {"func": kb20,   "normeq": 1.49634231, "wnum": 2},
    "kb25":   {"func": kb25,   "normeq": 1.65191895, "wnum": 3},
    "kb35":   {"func": kb35,   "normeq": 1.92844639, "wnum": 4},
    "kbmd20": {"func": kbmd20, "normeq": 1.52048382, "wnum": 5},
    "kbmd25": {"func": kbmd25, "normeq": 1.65994438, "wnum": 6},
    "kbmd35": {"func": kbmd35, "normeq": 1.52048382, "wnum": 7}
}

#TODO
def savitzky_golay(y, window_size, order, deriv=0, rate=1):
    """
    Purpose:
        To smooth data with a Savitzky-Golay filter. This removes
        high frequency noise while maintaining many of the
        original features of the input data.
    Arguments:
        :y (*numpy.ndarray*):
            The input "Noisy" data.
        :window_size (*int*):
            The length of the window. Must be an odd number.
        :order (*int*):
            The order of the polynomial used for filtering.
            Must be less then window_size - 1.
    Keywords:
        :deriv (*int*):
            The order of the derivative what will be computed.
    Output:
        :y_smooth (*numpy.ndarray*):
            The data smoothed by Savitzky-Golay filter.
    """
    try:
        y = numpy.array(y)
        window_size = numpy.abs(numpy.int(window_size))
        order = numpy.abs(numpy.int(order))
    except KeyboardInterrupt:
        raise
    except:
        raise TypeError(
            """
            \r\tError Encountered: rss_ringoccs
            \r\t\tdiffrec.special_functions.savitzky_golay\n
            \r\tUsage:
            \r\t\tysmooth = savitzky_golay(y, Window_Size, Poly_Order)
            \r\t\ty:            Numpy Array (Floating Point)
            \r\t\tWindow_Size   Positive Odd Integer
            \r\t\tPoly_Order    Positive Integer (Poly_Order > Window_Size)
            """
        )

    if (window_size % 2 != 1) or (window_size < 1):
        raise ValueError(
            """
            \r\tError Encountered: rss_ringoccs
            \r\t\tdiffrec.special_functions.savitzky_golay\n
            \r\twindow_size must be an odd integer.
            """
        )
    elif (window_size < order + 2):
        raise ValueError(
            """
            \r\tError Encountered: rss_ringoccs
            \r\t\tdiffrec.special_functions.savitzky_golay\n
            \r\twindow_size must be less than Poly_Order.
            """
        )
    else:
        pass

    half_window = (window_size - 1) // 2

    # precompute coefficients
    b = numpy.zeros((window_size, order+1))
    b[..., 0] = 1
    for k in range(half_window):
        n0 = (half_window) - k
        m = n0
        n = -n0
        for j in range(1, order+1):
            b[k, j] = n
            b[window_size-1-k, j] = m
            n *= -n0
            m *= n0

    b = numpy.mat(b)

    m = 1
    for i in range(deriv):
        m *= rate*(deriv-i)

    m *= numpy.linalg.pinv(b).A[deriv]

    # Pad the endpoints with values from the signal.
    firstvals = y[0] - numpy.abs(y[1:half_window+1][::-1] - y[0])
    lastvals = y[-1] + numpy.abs(y[-half_window-1:-1][::-1] - y[-1])
    y = numpy.concatenate((firstvals, y, lastvals))

    return numpy.convolve(m[::-1], y, mode='valid')

def fresnel_psi(kD, r, r0, phi, phi0, B, D):
    """
    Purpose:
        Compute :math:`\\psi` (MTR Equation 4)
    Arguments:
        :kD (*float*):
            Wavenumber, unitless.
        :r (*float*):
            Radius of reconstructed point, in kilometers.
        :r0 (*numpy.ndarray*):
            Radius of region within window, in kilometers.
        :phi (*numpy.ndarray*):
            Ring azimuth angle corresponding to r, radians.
        :phi0 (*numpy.ndarray*):
            Ring azimuth angle corresponding to r0, radians.
        :B (*float*):
            Ring opening angle, in radians.
        :D (*float*):
            Spacecraft-RIP distance, in kilometers.
    Outputs:
        :psi (*numpy.ndarray*):
            Geometric Function from Fresnel Kernel.
    """
    try:
        return _special_functions.fresnel_psi(kD, r, r0, phi, phi0, B, D)
    except KeyboardInterrupt:
        raise
    except:
        raise TypeError(
            """
            \r\tError: rss_ringoccs
            \r\t\tdiffrec.special_functions.fresnel_psi\n
            \r\tInput should be seven numpy arrays of real numbers.\n
            \r\tUsage:
            \r\t\t>>> y = fresnel_psi(kD, r, r0, phi, phi0, B, D)\n
            """
        )

def fresnel_dpsi_dphi(kD, r, r0, phi, phi0, B, D):
    """
        Purpose:
            Compute :math:`\\mathrm{d}\\psi/\\mathrm{d}\\phi`
        Arguments:
            :kD (*float*):
                Wavenumber, unitless.
            :r (*float*):
                Radius of reconstructed point, in kilometers.
            :r0 (*numpy.ndarray*):
                Radius of region within window, in kilometers.
            :phi (*numpy.ndarray*):
                Ring azimuth angle corresponding to r, radians.
            :phi0 (*numpy.ndarray*):
                Ring azimuth angle corresponding to r0, radians.
            :B (*float*):
                Ring opening angle, in radians.
            :D (*float*):
                Spacecraft-RIP distance, in kilometers.
        Outputs:
            :dpsi (*array*):
                Partial derivative of :math:`\\psi` with
                respect to :math:`\\phi`.
    """
    try:
        return _special_functions.fresnel_dpsi_dphi(kD, r, r0, phi, phi0, B, D)
    except KeyboardInterrupt:
        raise
    except:
        raise TypeError(
            """
            \r\tError: rss_ringoccs
            \r\t\tdiffrec.special_functions.fresnel_dpsi_dphi\n
            \r\tInput should be seven numpy arrays of real numbers.\n
            \r\tUsage:
            \r\t\t>>> y = fresnel_dpsi_dphi(kD, r, r0, phi, phi0, B, D)\n
            """
        )

def fresnel_dpsi_dphi_ellipse(kD, r, r0, phi, phi0, B, D, ecc, peri):
    try:
        return _special_functions.fresnel_dpsi_dphi_ellipse(
            kD, r, r0, phi, phi0, B, D, ecc, peri
        )
    except KeyboardInterrupt:
        raise
    except:
        raise TypeError(
            """
            \r\tError: rss_ringoccs
            \r\t\tdiffrec.special_functions.fresnel_dpsi_dphi_ellipse\n
            \r\tInput should be nine numpy arrays of real numbers.\n
            """
        )

def fresnel_d2psi_dphi2(kD, r, r0, phi, phi0, B, D):
    """
    Purpose:
        Compute :math:`\\psi` (MTR Equation 4)
    Arguments:
        :kD (*float*):
            Wavenumber, unitless.
        :r (*float*):
            Radius of reconstructed point, in kilometers.
        :r0 (*numpy.ndarray*):
            Radius of region within window, in kilometers.
        :phi (*numpy.ndarray*):
            Ring azimuth angle corresponding to r, radians.
        :phi0 (*numpy.ndarray*):
            Ring azimuth angle corresponding to r0, radians.
        :B (*float*):
            Ring opening angle, in radians.
        :D (*float*):
            Spacecraft-RIP distance, in kilometers.
    Outputs:
        :psi (*numpy.ndarray*):
            Geometric Function from Fresnel Kernel.
    """
    try:
        return _special_functions.fresnel_d2psi_dphi2(kD, r, r0,
                                                      phi, phi0, B, D)
    except KeyboardInterrupt:
        raise
    except:
        raise TypeError(
            """
            \r\tError: rss_ringoccs
            \r\t\tdiffrec.special_functions.fresnel_psi\n
            \r\tInput should be seven numpy arrays of real numbers.\n
            \r\tUsage:
            \r\t\t>>> y = fresnel_psi(kD, r, r0, phi, phi0, B, D)\n
            """
        )

def window_width(res, normeq, fsky, fres, rho_dot, sigma, bfac=True):
    """
    Purpose:
        Compute the window width as a function of ring radius.
        This is given from MTR86 Equations 19, 32, and 33.
    Variables:
        :res (*float*):
            The requested resolution.
        :normeq (*float*):
            The normalized equivalent width. Unitless.
        :fsky (*float* or *numpy.ndarray*):
            The sky frequency.
        :fres (*float* or *numpy.ndarray*):
            The Fresnel scale.
        :rdot (*float*) or (*numpy.ndarray*):
            The time derivative of the ring radius.
    Output:
        :w_vals (*numpy.ndarray*):
            The window width as a function of ring radius.
    """
    if bfac:
        omega = 2.0*numpy.pi * fsky
        alpha = numpy.square(omega * sigma) / (2.0 * rho_dot)
        P = res / (alpha * numpy.square(fres))

        # Create a variable specifying where P>1 occurs.
        Prange = (P > 1.0).nonzero()[0]

        if (numpy.size(Prange) == 0):
            raise IndexError(
                """
                \r\tError Encountered: rss_ringoccs
                \r\t\tdiffrec.special_functions.window_width\n
                \r\tThe P parameter in window width computation is less than
                \r\tone for the entirety of the data set. Either
                \r\trho_dot_km_vals is too small, tor F_km_vals is too large.
                \r\tRequest a coarser resolution, or check your data for
                \r\terrors. Alternatively, you may set bfac=False as a keyword.
                \r\tThis may result in inaccurate window width.
                """
            )
        else:
            pass

        P = P[Prange]
        alpha = alpha[Prange]

        w_vals = numpy.zeros(numpy.size(rho_dot))
        w_vals[Prange] = resolution_inverse(P)/alpha

    else:
        w_vals = 2.0*numpy.square(fres)/res
        Prange = (fres > 0.0).nonzero()[0]

    w_vals *= normeq

    return w_vals, Prange
