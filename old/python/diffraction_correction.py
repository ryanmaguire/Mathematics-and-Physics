"""
Purpose:
    Provide the DiffractionCorrection class for performing the
    necessary mathematics to correct for the diffraction effects that
    are obtained during occultation observations of planetary rings.
Dependencies:
    #. numpy
    #. rss_ringoccs
"""
# Import dependencies for the diffcorr module
import numpy as np
from rss_ringoccs.tools.history import write_history_dict
from rss_ringoccs.tools.write_output_files import write_output_files
from rss_ringoccs.tools import error_check
from . import special_functions

# Dictionary containing regions of interest within the Saturnian Rings.
region_dict = {
    'all':             [1.0, 400000.0],
    'besselbarnard':   [120210.0, 120330.0],
    'bessel-barnard':  [120210.0, 120330.0],
    'cringripples':    [77690.0, 77760.0],
    'encke':           [132900.0, 134200.0],
    'enckegap':        [132900.0, 134200.0],
    'herschel':        [118100.0, 118380.0],
    'herschelgap':     [118100.0, 118380.0],
    'huygens':         [117650.0, 117950.0],
    'huygensringlet':  [117650.0, 117950.0],
    'janusepimetheus': [96200.0, 96800.0],
    'jeffreys':        [118900.0, 119000.0],
    'jeffreysgap':     [118900.0, 119000.0],
    'kuiper':          [119300.0, 119500.0],
    'kuipergap':       [119300.0, 119500.0],
    'maxwell':         [87410.0, 87610.0],
    'maxwellringlet':  [87410.0, 87610.0],
    'russell':         [118550.0, 118660.0],
    'russellgap':      [118550.0, 118660.0],
    'titan':           [77870.0, 77930.0],
    'titanringlet':    [77870.0, 77930.0]
}


class DiffractionCorrection(object):
    """
    Purpose:
        Perform diffraction correction for a ring occultation
        on a data set that is a near radially symmetric function
        of the ring radius, or ring intercept point (RIP).
    Arguments:
        :DLP (*object*):
            The data set, usually an instance of the
            DiffractionLimitedProfile class from the rss_ringoccs
            Calibration subpackage. This instance MUST contain
            the following attributes and have the same names.

            |   rho_km_vals:      Ring Radius (km)
            |   phi_rad_vals:     Ring Azimuth Angle (Radians)
            |   p_norm_vals:      Normalized Power
            |   phase_rad_vals:   Phase (Radians)
            |   B_rad_vals:       Elevation Angle (Radians)
            |   D_km_vals:        RIP-Distance (km)
            |   f_sky_hz_vals:    Sky Frequency (Hertz)
            |   rho_dot_kms_vals: RIP-velocity (km/s)
            |   history:          History dictionary

        :res (*float* or *int*):
            The (positive) requested resolution for processing (km).
    Keywords:
        :rng (*list* or *str*):
            The requested range for diffraction correction.
            Preferred input is rng = [a,b]. Arrays are
            allowed and the range will be set as:

            |    rng = [MIN(array), MAX(array)]

            Strings containing a few regions of interests within the
            rings of Saturn are allowed. Permissable strings are:

            |    'all'             [1.0, 400000.0]
            |    'cringripples'    [77690.0, 77760.0]
            |    'encke'           [132900.0, 134200.0]
            |    'enckegap'        [132900.0, 134200.0]
            |    'janusepimetheus' [96200.0, 96800.0]
            |    'maxwell'         [87410.0, 87610.0]
            |    'maxwellringlet'  [87410.0, 87610.0]
            |    'titan'           [77870.0, 77930.0]
            |    'titanringlet'    [77870.0, 77930.0]
            |    'huygens'         [117650.0, 117950.0]
            |    'huygensringlet'  [117650.0, 117950.0]

            Strings are neither case nor space sensitive.
            Values MUST be set in kilometers. Default is 'all'.
        :wtype (*str):
            The requested tapering function for diffraction
            correction. A string with several allowed inputs:

            |    'rect'      Rectangular Window.
            |    'coss'      Squared Cosine Window.
            |    'kb20'      Kaiser-Bessel 2.0 Window.
            |    'kb25'      Kaiser-Bessel 2.5 Window.
            |    'kb35'      Kaiser-Bessel 3.5 Window.
            |    'kbmd20'    Modified kb20 Window.
            |    'kbmd25'    Modified kb25 Window.
            |    'kbmd35'    Modified kb35 Window.

            The variable is neither case nor space sensitive.
            Default window is set to 'kb25'. See window_functions
            submodule for further documentation.
        :fwd (*bool*):
            Boolean for running forward modelling. This is good
            test for deciding if the diffraction correction is
            physically significant or valid. If the reconstruction is
            good the forward model should reproduce the p_norm_vals
            attribute from the input DLP instance. Default is False.
        :norm (*bool*):
            A Boolean for normalizing the reconstructed complex
            transmittance by the window width. Default is True.
        :bfac (*bool*):
            A Boolean for determining whether or not the 'b' factor
            in the window width computation is used. If False,
            the Allen Deviation is assumed to be zero. If True,
            the Allen Deviation is determined by the sigma keyword
            (see below). Default is True.
        :sigma (*float*):
            The Allen deviation for the spacecraft. If the bfac
            keyword (See above) is set to False, this is ignored.
            If bfac is set to True, and sigma is NOT specified,
            then sigma=2e-13 will be used, which is the Allen
            deviation for Cassini with 1 second integration time.
            For spacecraft other than Cassini, you should provide
            the Allen deviation yourself. Default is sigma=2e-13
        :psitype (*str*):
            A string for determining what approximation to the
            Fresnel kernel. is used. Several strings are allowed:

            |    'full'      No Approximation is applied.
            |    'fresnel'   Standard Fresnel approximation.
            |    'fresnel3'  Cubic approximation.
            |    'fresnel4'  Quartic approximation.
            |    'fresnel6'  Sextic approximation.
            |    'fresnel8'  Octic approximation.

            Neither case nor space sensitive. Default is 'full'.
        :verbose (*bool*):
            Boolean for determining if various pieces of information
            are printed or not. Default is False.
    Attributes:
        :bfac (*bool*):
            Boolean for bfac (See keywords).
        :dathist (*dict*):
            History from DLP instance.
        :dx_km (*float*):
            Radial spacing for the data points (km).
        :f_sky_hz_vals (*numpy.ndarray*):
            Recieved frequency from the spacecraft (Hz).
        :finish (*int*):
            Final point that was reconstructed.
        :fwd (*bool*):
            Boolean for fwd (See keywords).
        :history (*dict*):
            History for the DiffractionCorrection class.
            This contains system info and user info, including
            what operating system was used, username, hostname,
            computer name, and the inputs provided.
        :lambda_sky_km_vals (*numpy.ndarray*):
            Wavelength of recieved signal from spacecraft (km).
        :mu_vals (*numpy.ndarray*):
            The sine of the ring opening angle (Unitless).
        :n_used (*int*):
            Number of points that were reconstructed.
        :norm (*bool*):
            Boolean for norm (See keywords).
        :norm_eq (*float*):
            Normalized equivalent width computed from window
            that was used during reconstruction. See the
            window_functions submodule for more information.
        :p_norm_fwd_vals (*numpy.ndarray*):
            Normalized power computer from the forward modelling
            of the reconstructed data. This will be a None type
            variable unless fwd=True is set. If the
            reconstruction went well, this should mimic the raw
            data, p_norm_vals.
        :p_norm_vals (*numpy.ndarray*):
            Normalized power from the diffracted signal. This is
            the square of the absolute value of the recieved
            complex transmittance.
        :phase_fwd_vals (*numpy.ndarray*):
            Phase computed from the forward model of the
            reconstructed data. This will be a None type
            variable unless fwd=True is set. If the
            reconstruction went well, this should mimic
            phase_rad_vals. This variable is in radians.
        :phase_rad_vals (*numpy.ndarray*):
            Phase from the diffracted signal (Radians).
        :phase_vals (*numpy.ndarray*):
            Reconstructed phase (Radians).
        :phi_rad_vals (*numpy.ndarray*):
            Ring azimuth angle of the ring intercept (Radians).
        :phi_rl_rad_vals (*numpy.ndarray*):
            Ring longitude angle (Radians).
        :power_vals (*numpy.ndarray*):
            Normalized reconstructed power.
        :psitype (*str*):
            String for psitype (See keywords).
        :raw_tau_threshold_vals (*numpy.ndarray*):
            Threshold optical depth for the diffracted data.
        :res (*float*):
            Requested resolution (See arguments). In kilometers.
        :rho_corr_pole_km_vals (*numpy.ndarray*):
            Radial corrections from the Planet's pole. This will
            be a None type variable unless provided in the
            DLP class. Otherwise, this is in kilometers.
        :rho_corr_timing_km_vals (*numpy.ndarray*):
            Radial corrections from timing offsets. This will be
            a None type variable unless provided in the DLP
            class. Otherwise, this is in kilometers.
        :rho_dot_kms_vals (*numpy.ndarray*):
            Time derivative of the ring intercept point (km/s).
        :rho_km_vals (*numpy.ndarray*):
            Ring-intercept-point (RIP) in kilometers.
        :rng (*list*):
            Range that was used for reconstruction. The actual
            range takes into account limits in the available data
            and limits in the required window sizes.
        :rngreq (*str* or *list*):
            Requested range (See 'rng' in keywords).
        :sigma (*float*):
            Requested Allen deviation (See keywords).
        :start (*int*):
            First point that was reconstructed.
        :t_oet_spm_vals (*numpy.ndarray*):
            Time the signal is measured on Earth.
        :t_ret_spm_vals (*numpy.ndarray*):
            Time the signal passes through the diffracting medium.
        :t_set_spm_vals (*numpy.ndarray*):
            Time the signal is emitted from the spacecraft.
        :tau_threshold_vals (*numpy.ndarray*):
            Threshold optical depth of the reconstructed data.
        :tau_vals (*numpy.ndarray*):
            Optical depth of the reconstructed data.
        :verbose (*bool*):
            Boolean for Verbose (See keywords).
        :w_km_vals (*numpy.ndarray*):
            Window width as a function of radius (km).
        :wtype (*str*):
            String for wtype (See keywords).
    """
    def __init__(self, DLP, res, rng="all", wtype="kbmd20", fwd=False,
                 norm=True, use_fft=False, verbose=False, bfac=True,
                 sigma=2.e-13, psitype="fresnel4", write_file=False,
                 res_factor=0.75, ecc=0.0, peri=0.0, perturb=[0,0,0,0,0],
                 interp=0):

        # Store the name of this class as a string (The "function name").
        fn = "diffrec.diffraction_correction.DiffractionCorrection"
        error_check.check_type(verbose, bool, "verbose", fn)

        if verbose:
            print("Processing Diffraction Correction:")
            print("\tRunning Error Check on Input Arguments...")

        error_check.check_type(perturb, list, "perturb", fn)

        if (len(perturb) != 5):
            raise IndexError(
                "\rError Encountered: rss_ringoccs\n"
                "\r\tdiffrec.diffraction_correction.DiffractionCorrection\n\n"
                "\rperturb should be a list of five floating point numbers.\n"
            )
        else:
            pass

        for i in range(5):
            perturb[i] = error_check.check_type_and_convert(perturb[i], float,
                                                            "perturb", fn)

        error_check.check_type(fwd, bool, "fwd", fn)
        error_check.check_type(bfac, bool, "bfac", fn)
        error_check.check_type(norm, bool, "norm", fn)
        error_check.check_type(use_fft, bool, "use_fft", fn)
        error_check.check_type(write_file, bool, "write_file", fn)
        error_check.check_type(interp, int, "interp", fn)

        res = error_check.check_type_and_convert(res, float, "res", fn)
        sigma = error_check.check_type_and_convert(sigma, float, "sigma", fn)
        res_factor = error_check.check_type_and_convert(res_factor, float,
                                                        "res_factor", fn)
        ecc = error_check.check_type_and_convert(ecc, float, "ecc", fn)
        peri = error_check.check_type_and_convert(peri, float, "peri", fn)

        # Check that these variables are positive.
        error_check.check_positive(res, "res", fn)
        error_check.check_positive(sigma, "sigma", fn)
        error_check.check_positive(res_factor, "res_factor", fn)
        error_check.check_non_negative(ecc, "ecc", fn)

        # Check that the periapse is within [0, 2pi)
        error_check.check_two_pi(peri, "peri", fn)

        # Check that wtype is in the allowed list of window types.
        wtype = error_check.check_wtype(wtype, fn)

        # Check that range and psitype are legal inputs.
        rng = error_check.check_range_input(rng, fn)
        psitype = error_check.check_psitype(psitype, fn)

        # Assign variables as attributes.
        self.p_norm_fwd_vals = None
        self.T_hat_fwd_vals = None
        self.phase_fwd_vals = None
        self.input_res = res
        self.perturb = perturb
        self.verbose = verbose
        self.psitype = psitype
        self.use_fft = use_fft
        self.rngreq = rng
        self.interp = interp
        self.wtype = wtype
        self.sigma = sigma
        self.norm = norm
        self.bfac = bfac
        self.peri = peri
        self.res = res*res_factor
        self.fwd = fwd
        self.ecc = ecc

        # Retrieve variables from the DLP class, setting as attributes.
        if verbose:
            print("\tRetrieving variables from DLP instance...")

        try:
            erm = "rho_km_vals"
            self.rho_km_vals = np.array(DLP.rho_km_vals).astype(float)
            erm = "p_norm_vals"
            self.p_norm_vals = np.array(DLP.p_norm_vals).astype(float)
            erm = "phase_rad_vals"

            # Negate phase for mathematical conventations.
            self.phase_rad_vals = -np.array(DLP.phase_rad_vals).astype(float)

            erm = "B_rad_vals"
            self.B_rad_vals = np.array(DLP.B_rad_vals).astype(float)
            erm = "D_km_vals"
            self.D_km_vals = np.array(DLP.D_km_vals).astype(float)
            erm = "phi_rad_vals"
            self.phi_rad_vals = np.array(DLP.phi_rad_vals).astype(float)
            erm = "f_sky_hz_vals"
            self.f_sky_hz_vals = np.array(DLP.f_sky_hz_vals).astype(float)
            erm = "rho_dot_kms_vals"
            self.rho_dot_kms_vals = np.array(DLP.rho_dot_kms_vals).astype(float)
            erm = "t_oet_spm_vals"
            self.t_oet_spm_vals = np.array(DLP.t_oet_spm_vals).astype(float)
            erm = "t_ret_spm_vals"
            self.t_ret_spm_vals = np.array(DLP.t_ret_spm_vals).astype(float)
            erm = "t_set_spm_vals"
            self.t_set_spm_vals = np.array(DLP.t_set_spm_vals).astype(float)
            erm = "rho_corr_pole_km_vals"
            self.rho_corr_pole_km_vals = np.array(DLP.rho_corr_pole_km_vals)
            erm = "rho_corr_timing_km_vals"
            self.rho_corr_timing_km_vals = np.array(DLP.rho_corr_timing_km_vals)
            erm = "phi_rl_rad_vals"
            self.phi_rl_rad_vals = np.array(DLP.phi_rl_rad_vals).astype(float)
            erm = "raw_tau_threshold_vals"
            self.raw_tau_threshold_vals = np.array(DLP.raw_tau_threshold_vals)
            if hasattr(DLP, 'ul_rho_km_vals'):
                erm = 'ul_rho_km_vals'
                self.ul_rho_km_vals = np.array(DLP.ul_rho_km_vals)

                erm = 't_ul_spm_vals'
                self.t_ul_spm_vals = np.array(DLP.t_ul_spm_vals)

                erm = 't_ul_ret_spm_vals'
                self.t_ul_ret_spm_vals = np.array(DLP.t_ul_ret_spm_vals)

                erm = 'ul_phi_rl_deg_vals'
                self.ul_phi_rl_deg_vals = np.array(DLP.ul_phi_rl_deg_vals)

                erm = 'ul_phi_ora_deg_vals'
                self.ul_phi_ora_deg_vals = np.array(DLP.ul_phi_ora_deg_vals)
        except (TypeError, ValueError, NameError, AttributeError):
            raise TypeError(
                """
                \r\tError Encountered: rss_ringoccs\n\r\t\t%s\n
                \r\t%s could not be converted into a numpy array.\n
                \r\tCheck your DLP instance for errors.
                """ % (fn, erm)
            )

        try:
            self.dathist = DLP.history
        except:
            raise AttributeError(
                """
                \r\tError Encountered: rss_ringoccs\n\r\t\t%s\n
                \r\tYour DLP instance has no history attribute.
                """ % fn
        )

        # Run various error checks on all variables.
        error_check.check_is_real(self.D_km_vals, "D_km_vals", fn)
        error_check.check_is_real(self.B_rad_vals, "B_rad_vals", fn)
        error_check.check_is_real(self.rho_km_vals, "rho_km_vals", fn)
        error_check.check_is_real(self.p_norm_vals, "p_norm_vals", fn)
        error_check.check_is_real(self.phi_rad_vals, "phi_rad_vals", fn)
        error_check.check_is_real(self.f_sky_hz_vals, "f_sky_hz_vals", fn)
        error_check.check_is_real(self.phase_rad_vals, "phase_rad_vals", fn)
        error_check.check_is_real(self.rho_dot_kms_vals, "rho_dot_kms_vals", fn)

        # Check that these variables are positive.
        error_check.check_positive(self.D_km_vals, "D_km_vals", fn)
        error_check.check_positive(self.rho_km_vals, "rho_km_vals", fn)
        error_check.check_positive(self.f_sky_hz_vals, "f_sky_hz_vals", fn)

        # Check that p_norm_vals is non-negative.
        error_check.check_non_negative(self.p_norm_vals, "p_norm_vals", fn)

        # Check that these variables are within the range [0, 2pi)
        error_check.check_two_pi(self.B_rad_vals, "B_rad_vals", fn)
        error_check.check_two_pi(self.phi_rad_vals, "phi_rad_vals", fn)
        error_check.check_two_pi(self.phase_rad_vals, "phase_rad_vals", fn)

        if (np.size(self.rho_km_vals) < 2):
            raise IndexError(
                """
                \r\tError Encountered: rss_ringoccs\n\r\t\t%s\n
                \r\trho_km_vals has less than 2 points.
                """ % fn
            )
        else:
            self.rho_km_vals = self.rho_km_vals.astype(float)

        error_check.check_lengths(self.rho_dot_kms_vals, self.rho_km_vals,
                                  "rho_dot_kms_vals", "rho_km_vals", fn)
        error_check.check_lengths(self.phase_rad_vals, self.rho_km_vals,
                                  "phase_rad_vals", "rho_km_vals", fn)
        error_check.check_lengths(self.f_sky_hz_vals, self.rho_km_vals,
                                  "f_sky_hz_vals", "rho_km_vals", fn)
        error_check.check_lengths(self.phi_rad_vals, self.rho_km_vals,
                                  "phi_rad_vals", "rho_km_vals", fn)
        error_check.check_lengths(self.p_norm_vals, self.rho_km_vals,
                                  "p_norm_vals", "rho_km_vals", fn)
        error_check.check_lengths(self.B_rad_vals, self.rho_km_vals,
                                  "B_rad_vals", "rho_km_vals", fn)
        error_check.check_lengths(self.D_km_vals, self.rho_km_vals,
                                  "D_km_vals", "rho_km_vals", fn)

        # Compute sampling distance (km)
        self.dx_km = self.rho_km_vals[1] - self.rho_km_vals[0]

        # Check that the data is well sampled for the requested resolution.
        if (self.dx_km == 0.0):
            raise ValueError(
                """
                \r\tError Encountered: rss_ringoccs\n\r\t\t%s\n
                \r\tThe sample spacing (dx_km) is zero.
                """ % fn
            )
        elif self.res < 1.999999*self.dx_km:
            raise ValueError(
                """
                \r\tError Encountered: rss_ringoccs\n\r\t\t%s\n
                \r\tResolution is less than twice the sample spacing.
                \r\t\tRequested Resolution (km):    %f
                \r\t\tSample Spacing (km):          %f\n
                \r\tChoose a resolution GREATER than %f km\n
                \r\tPLEASE NOTE:
                \r\t\tTo be consistent with PDS results, a factor of 0.75
                \r\t\tis applied to the requested resolution. To ignore
                \r\t\tthis set the keyword 'res_factor=1.0'.
                \r\t\tres_factor is currently set to: %f
                """ % (fn, self.res, self.dx_km,
                       2.0*self.dx_km/res_factor, res_factor)
            )
        else:
            pass

        if verbose:
            print("\tChecking Variables for Errors...")

        # Check that rho_km_vals is increasing and the rev isn't a chord occ.
        drho = [np.min(self.rho_dot_kms_vals), np.max(self.rho_dot_kms_vals)]

        if (drho[0] < 0) and (drho[1] > 0):
            raise ValueError(
                """
                \r\tError Encountered: rss_ringoccs\n\r\t\t%s\n
                \r\tdrho/dt has positive and negative values.
                \r\tYour input file is probably a chord occultation.
                \r\tDiffraction Correction can only be performed for
                \r\tone event at a time. That is, ingress or egress.\n
                \r\tTO CORRECT THIS:
                \r\t\tSplit the input into two parts: Ingress and Engress
                \r\t\tand perform diffraction correction twice.
                """ % fn
            )
        elif ((drho[0] == 0.0) or (drho[1] == 0.0)):
            raise ValueError(
                """
                \r\tError Encountered: rss_ringoccs\n\r\t\t%s\n
                \r\tdrho/dt has zero valued elements.
                \r\tYour input file is probably a chord occultation.
                \r\tDiffraction Correction can only be performed for
                \r\tone event at a time. That is, ingress or egress.\n
                \r\tTO CORRECT THIS:
                \r\t\tSplit the input into two parts: Ingress and Engress
                \r\t\tand perform diffraction correction twice.
                """ % fn
            )
        elif (self.dx_km > 0) and (drho[1] < 0):
            self.rho_dot_kms_vals = np.abs(self.rho_dot_kms_vals)
        elif (self.dx_km < 0) and (drho[0] > 0):
            raise ValueError(
                """
                \r\tError Encountered:\n\r\t\t%s\n
                \r\trho_km_vals is decreasing yet rho_dot_kms_vals
                \r\tis positiive. Check DLP class for errors.
                """ % fn
            )
        elif (self.dx_km < 0):
            self.rho_km_vals = self.rho_km_vals[::-1]
            self.phase_rad_vals = self.phase_rad_vals[::-1]
            self.p_norm_vals = self.p_norm_vals[::-1]
            self.phi_rad_vals = self.phi_rad_vals[::-1]
            self.B_rad_vals = self.B_rad_vals[::-1]
            self.f_sky_hz_vals = self.f_sky_hz_vals[::-1]
            self.D_km_vals = self.D_km_vals[::-1]
            self.rho_dot_kms_vals = np.abs(self.rho_dot_kms_vals[::-1])
            self.dx_km *= -1.0
        else:
            del drho

        if verbose:
            print("\tComputing Necessary Variables...")

        # Compute various variables.
        self.lambda_sky_km_vals = special_functions.frequency_to_wavelength(
            self.f_sky_hz_vals
        )
        self.mu_vals = np.sin(np.abs(self.B_rad_vals))
        self.T_hat_vals = np.exp(1j*self.phase_rad_vals)
        self.T_hat_vals *= np.sqrt(self.p_norm_vals)

        # Compute geometric qunatities and the Fresnel Scale.
        self.F_km_vals = special_functions.fresnel_scale(
            self.lambda_sky_km_vals, self.D_km_vals,
            self.phi_rad_vals, self.B_rad_vals
        )

        # Compute the Normalized Equaivalent Width (See MTR86 Equation 20)
        self.norm_eq = special_functions.func_dict[wtype]["normeq"]

        # Compute the window width. (See MTR86 Equations 19, 32, and 33).
        self.w_km_vals, Prange = special_functions.window_width(
            self.res, self.norm_eq, self.f_sky_hz_vals, self.F_km_vals,
            self.rho_dot_kms_vals, self.sigma, bfac=self.bfac
        )

        # From the requested range, extract array of the form [a, b]
        if (isinstance(rng, str)):
            self.rng = np.array(region_dict[rng])
        else:
            self.rng = np.array([np.min(rng), np.max(rng)])

        # Compute the smallest and largest allowed radii for reconstruction.
        rho = self.rho_km_vals[Prange]
        w = self.w_km_vals[Prange]
        rho_min = self.rho_km_vals[Prange]-self.w_km_vals[Prange]/2.0
        rho_max = self.rho_km_vals[Prange]+self.w_km_vals[Prange]/2.0

        wrange = Prange[np.where((rho_min >= np.min(rho)) &
                                 (rho_max <= np.max(rho)))]

        # Check that there is enough data for reconstruction.
        if (np.size(wrange) == 0):
            raise ValueError(
                """
                \r\tError Encountered: rss_ringoccs\n\r\t\t%s\n
                \r\tThe window width is too large to reconstruct anything.
                \r\t\tMinimum Available Radius:         %f
                \r\t\tMaximum Available Radius:         %f
                \r\t\tMinimum Required Window Width:    %f
                \r\t\tMaximum Required Window Width:    %f
                """ % (fn, np.min(rho), np.max(rho), np.min(w), np.max(w))
            )
        elif (np.max(rho) < np.min(self.rng)):
            raise ValueError(
                """
                \r\tError Encountered: rss_ringoccs\n\r\t\t%s\n
                \r\tMinimum requested range is greater than available data.
                \r\tYour Requested Minimum (km):    %f
                \r\tYour Requested Maximum (km):    %f
                \r\tMaximum Available Data (km):    %f
                """ % (fn, np.min(self.rng), np.max(self.rng), np.max(rho))
            )
        elif (np.min(rho) > np.max(self.rng)):
            raise ValueError(
                """
                \r\tError Encountered: rss_ringoccs\n\r\t\t%s\n
                \r\tMaximum requested range is less than available data.
                \r\tYour Requested Minimum (km):    %f
                \r\tYour Requested Maximum (km):    %f
                \r\tMinimum Available Data (km):    %f
                """ % (fn, np.min(self.rng), np.max(self.rng), np.min(rho))
            )
        else:
            rho_min = np.min(rho[wrange])
            rho_max = np.max(rho[wrange])
            wrange = wrange[np.where((rho[wrange] >= np.min(self.rng)) &
                                    (rho[wrange] <= np.max(self.rng)))]

        if (np.size(wrange) <= 1):
            raise IndexError(
            """
            \r\tError Encountered: rss_ringoccs\n\r\t\t%s\n
            \r\tRequested range is beyond available data.
            \r\t\tMinimum Possible Radius: %f
            \r\t\tMaximum Possible Radius: %f
            \r\t\tMinimum Requested Range: %f
            \r\t\tMaximum Requested Range: %f
            """ % (fn, rho_min, rho_max, np.min(self.rng), np.max(self.rng))
            )
        else:
            self.start = wrange[0]
            self.finish = wrange[-1]
            self.n_used = self.finish - self.start

        # Create input variable and keyword dictionaries for history.
        input_vars = {
            'dlp_inst': DLP.history,
            'res':      res
        }

        input_kwds = {
            'rng':          rng,
            'wtype':        wtype,
            'fwd':          fwd,
            'norm':         norm,
            'use_fft':      use_fft,
            'bfac':         bfac,
            'sigma':        sigma,
            'psitype':      psitype,
            'res_factor':   res_factor,
            'peri':         peri,
            'ecc':          ecc
        }

        # Delete unnecessary variables for clarity.
        del rho, rho_min, rho_max, rng, norm, fwd, bfac, psitype, verbose

        if self.verbose:
            print("\tRunning Fresnel Inversion...")

        # Compute product of wavenumber and RIP distance.
        self.kD_vals = special_functions.wavelength_to_wavenumber(
            self.lambda_sky_km_vals
        ) * self.D_km_vals

        # Compute the Fresnel transform.
        self.T_vals = special_functions.fresnel_transform(
            self.T_hat_vals, self.rho_km_vals, self.F_km_vals,
            self.phi_rad_vals, self.kD_vals, self.B_rad_vals, self.D_km_vals,
            self.w_km_vals, self.perturb, self.start, self.n_used, self.wtype,
            self.psitype, self.norm, False, self.use_fft, self.interp, self.ecc,
            self.peri
        )

        self.tau_threshold_vals = (self.raw_tau_threshold_vals -
                                   self.mu_vals*np.log(self.dx_km/self.res))

        self.__trim_attributes(fwd=False)

        # Compute power and phase.
        if self.verbose:
            print("\tComputing Power and Phase...")

        self.power_vals = np.square(np.abs(self.T_vals))

        # Return phase to original sign.
        self.phase_rad_vals *= -1
        self.phase_vals = -np.arctan2(np.imag(self.T_vals),
                                      np.real(self.T_vals))

        if self.verbose:
            print("\tInversion Complete.")

        if self.fwd:
            nw_fwd = int(np.ceil(np.max(self.w_km_vals) / (2.0 * self.dx_km)))
            self.start = int(nw_fwd)
            self.n_used = int(self.n_used - 2 * nw_fwd)

            if self.verbose:
                print("\tComputing Forward Transform...")

            self.T_hat_fwd_vals = special_functions.fresnel_transform(
                self.T_vals, self.rho_km_vals, self.F_km_vals, self.w_km_vals,
                self.start, self.n_used, self.wtype, self.norm, True,
                self.psitype, self.phi_rad_vals, self.kD_vals, self.B_rad_vals,
                self.D_km_vals, self.ecc, self.peri
            )
            self.__trim_attributes(fwd=True)

            self.p_norm_fwd_vals = np.square(np.abs(self.T_hat_fwd_vals))
            self.phase_fwd_vals = -np.arctan2(np.imag(self.T_hat_fwd_vals),
                                              np.real(self.T_hat_fwd_vals))
            if self.verbose:
                print("\tForward Transform Complete.")

        # Compute regions of non-zero power.
        crange = (self.power_vals > 0.0).nonzero()

        # Compute the normalized optical depth.
        self.tau_vals = np.zeros(np.size(self.power_vals))
        self.tau_vals[crange] = np.log(self.power_vals[crange])
        self.tau_vals[crange] *= -self.mu_vals[crange]

        self.history = write_history_dict(input_vars, input_kwds, __file__)

        # Set rev_info attribute from DLP instance.
        self.rev_info = DLP.rev_info
        if write_file:
            self.outfiles = write_output_files(self)
        else:
            self.outfiles = None

        if self.verbose:
            print("\tDiffraction Correction Complete.")

    def __trim_attributes(self, fwd):
        """
            Purpose:
                Trim the attributes in the DiffractionCorrection
                class so that only reconstructed points will be
                returned to the user. All other unused points are
                discarded.
        """
        # Get rid of uncomputed values and keep only what was processed.
        start = self.start
        n_used = self.n_used
        crange = np.arange(n_used+1)+start

        # Ring radius, azimuth angle, diffracted power, and phase.
        self.rho_km_vals = self.rho_km_vals[crange]
        self.p_norm_vals = self.p_norm_vals[crange]
        self.phi_rad_vals = self.phi_rad_vals[crange]
        self.phase_rad_vals = self.phase_rad_vals[crange]

        # Ring opening angle, normalized power, phase, and transmittance.
        self.B_rad_vals = self.B_rad_vals[crange]
        self.T_hat_vals = self.T_hat_vals[crange]

        # Fresnel scale, window width, and RIP-Spacecraft distance.
        self.F_km_vals = self.F_km_vals[crange]
        self.w_km_vals = self.w_km_vals[crange]
        self.D_km_vals = self.D_km_vals[crange]
        self.kD_vals = self.kD_vals[crange]

        # Ring radius corrections.
        self.rho_corr_pole_km_vals = self.rho_corr_pole_km_vals[crange]
        self.rho_corr_timing_km_vals = self.rho_corr_timing_km_vals[crange]

        # Various time attributes.
        self.t_oet_spm_vals = self.t_oet_spm_vals[crange]
        self.t_ret_spm_vals = self.t_ret_spm_vals[crange]
        self.t_set_spm_vals = self.t_set_spm_vals[crange]

        # All other attributes.
        self.mu_vals = self.mu_vals[crange]
        self.f_sky_hz_vals = self.f_sky_hz_vals[crange]
        self.phi_rl_rad_vals = self.phi_rl_rad_vals[crange]
        self.rho_dot_kms_vals = self.rho_dot_kms_vals[crange]
        self.lambda_sky_km_vals = self.lambda_sky_km_vals[crange]
        self.raw_tau_threshold_vals = self.raw_tau_threshold_vals[crange]
        self.tau_threshold_vals = self.tau_threshold_vals[crange]

        # Uplink geometry attributes.
        if hasattr(self, 'ul_rho_km_vals'):
            self.ul_rho_km_vals = self.ul_rho_km_vals[crange]
            self.t_ul_spm_vals = self.t_ul_spm_vals[crange]
            self.t_ul_ret_spm_vals = self.t_ul_ret_spm_vals[crange]
            self.ul_phi_rl_deg_vals = self.ul_phi_rl_deg_vals[crange]
            self.ul_phi_ora_deg_vals = self.ul_phi_ora_deg_vals[crange]

        if fwd:
            self.power_vals = self.power_vals[crange]
            self.phase_vals = self.phase_vals[crange]
