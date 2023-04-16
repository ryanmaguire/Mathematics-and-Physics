/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of Mathematics-and-Physics.                             *
 *                                                                            *
 *  Mathematics-and-Physics is free software: you can redistribute it and/or  *
 *  modify it under the terms of the GNU General Public License as published  *
 *  by the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  Mathematics-and-Physics is distributed in the hope that it will be useful *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with Mathematics-and-Physics.  If not, see                          *
 *  <https://www.gnu.org/licenses/>.                                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for drawing and visualizing complex plots.             *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/11                                                        *
 ******************************************************************************/

package main

/*  All packages needed for complex plots.                                    */
import (
    "os"            /*  os.File type is here.          */
    "log"           /*  log.Fatal function given here. */
    "math/cmplx"    /*  Basic complex math functions.  */
    "math"          /*  Real-valued math routines.     */
    "fmt"           /*  Printing functions.            */
)

/*  Parameters for the plots.                                                 */
const XMIN float64 = -2.0
const XMAX float64 = +2.0
const YMIN float64 = -2.0
const YMAX float64 = +2.0

/*  The number of pixels in the x and y axes.                                 */
const WIDTH uint32 = 1024
const HEIGHT uint32 = 1024

/*  Scale factors for converting between pixels and points in the plane.      */
const XFACTOR float64 = 3.91006842619745845213e-03
const YFACTOR float64 = 3.91006842619745845213e-03

/******************************************************************************
 *                              Types of Structs                              *
 ******************************************************************************/

/*  Simple struct for working with colors in RGB format.                      */
type Color struct {
    Red, Green, Blue uint8
}

/*  Struct for creating and writing to ppm files.                             */
type PPM struct {

    /*  The data in a PPM struct is the File pointer it represents.           */
    Fp *os.File
}

/******************************************************************************
 *                               Function Types                               *
 ******************************************************************************/

/*  Complex-valued functions.                                                 */
type ComplexFunc func(complex128) complex128

/*  Functions that convert complex numbers into colors.                       */
type Colorer func(complex128) Color

/******************************************************************************
 *                         PPM Functions and Methods                          *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      PPM.Create                                                            *
 *  Purpose:                                                                  *
 *      Creates a PPM file with a given file name.                            *
 *  Arguments:                                                                *
 *      name (const char *):                                                  *
 *          The file name of the output PPM (ex. "z_cubed_minus_one.ppm").    *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (ppm *PPM) Create(name string) {

    /*  Variable for the error message if os.Create fails.                    */
    var err error

    /*  Open the file and give it write permissions.                          */
    ppm.Fp, err = os.Create(name)

    if (err != nil) {
        log.Fatal(err)
    }
}
/*  End of PPM.Create.                                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      PPM.InitFromVals                                                      *
 *  Purpose:                                                                  *
 *      Print the preamble to the PPM file. A PPM file wants Pn followed by   *
 *      three numbers. P6 means we're encoding an RGB image in binary format. *
 *      The first two numbers are the number of pixels in the x and y axes.   *
 *      The last number is the size of our color spectrum, which is 255.      *
 *  Arguments:                                                                *
 *      x (uint32):                                                           *
 *          The number of pixels in the x axis.                               *
 *      y (uint32):                                                           *
 *          The number of pixels in the y axis.                               *
 *      type (int):                                                           *
 *          The type of the PPM, options are 1 through 6.                     *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (ppm *PPM) InitFromVals(x, y uint32, ptype int) {

    /*  For integers between 1 and 5 we can pass the value to the preamble.   */
    if (0 < ptype && ptype < 6) {
        fmt.Fprintf(ppm.Fp, "P%d\n%d %d\n255\n", ptype, x, y)

    /*  The only other legal value is 6. All illegal values default to 6.     */
    } else {
        fmt.Fprintf(ppm.Fp, "P6\n%d %d\n255\n", x, y)
    }
}
/*  End of PPM.InitFromVals.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      PPM.Init                                                              *
 *  Purpose:                                                                  *
 *      Initialize a PPM using the default values.                            *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Pass the default parameters to PPM.InitFromVals.                      *
 ******************************************************************************/
func (ppm *PPM) Init() {
    ppm.InitFromVals(WIDTH, HEIGHT, 6)
}
/*  End of PPM.Init.                                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      PPM.Close                                                             *
 *  Purpose:                                                                  *
 *      Closes the file pointer in a PPM struct.                              *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (ppm *PPM) Close() {

    /*  Ensure the pointer is not nil before trying to close it.              */
    if (ppm.Fp != nil) {
        ppm.Fp.Close()
    }
}
/*  End of PPM.Close.                                                         */

/******************************************************************************
 *                        Color Functions and Methods                         *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      Color.WriteToFile                                                     *
 *  Purpose:                                                                  *
 *      Writes a color to a File pointer.                                     *
 *  Arguments:                                                                *
 *      fp (*os.File):                                                        *
 *          A pointer to the file the color is being written to.              *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (c *Color) WriteToFile(fp *os.File) {
    rgb := []byte{c.Red, c.Green, c.Blue}
    fp.Write(rgb)
}
/*  End of Color.WriteToFile.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      Color.WriteToPPM                                                      *
 *  Purpose:                                                                  *
 *      Writes a color to a PPM file.                                         *
 *  Arguments:                                                                *
 *      ppm (*PPM):                                                           *
 *          A pointer to a PPM struct.                                        *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (c *Color) WriteToPPM(ppm *PPM) {
    c.WriteToFile(ppm.Fp)
}
/*  End of Color.WriteToPPM.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      ColorScale                                                            *
 *  Purpose:                                                                  *
 *      Scales a color by a real number. Used for darkening a color.          *
 *  Arguments:                                                                *
 *      c (*Color):                                                           *
 *          A pointer to a color.                                             *
 *      t (float64):                                                          *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      scaled_c (Color):                                                     *
 *          The input color c with RGB components scaled by t.                *
 ******************************************************************************/
func ColorScale(c *Color, t float64) Color {
    var r uint8 = uint8(t * float64(c.Red))
    var g uint8 = uint8(t * float64(c.Green))
    var b uint8 = uint8(t * float64(c.Blue))
    return Color{r, g, b}
}
/*  End of ColorScale.                                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      ColorScaleBy                                                          *
 *  Purpose:                                                                  *
 *      Scales a color by a real number. Used for darkening a color.          *
 *  Arguments:                                                                *
 *      c (*Color):                                                           *
 *          A pointer to a color.                                             *
 *      t (float64):                                                          *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func ColorScaleBy(c *Color, t float64) {
    c.Red = uint8(t * float64(c.Red))
    c.Green = uint8(t * float64(c.Green))
    c.Blue = uint8(t * float64(c.Blue))
}
/*  End of ColorScaleBy.                                                      */

/******************************************************************************
 *  Function:                                                                 *
 *      Color.Normalize                                                       *
 *  Purpose:                                                                  *
 *      Normalizes a color to unit intensity.                                 *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Treat the color c = (r, g, b) as a vector and normalize.              *
 ******************************************************************************/
func (c *Color) Normalize() {

    /*  Treat the RGB components as a vector (r, g, b).                       */
    var r float64 = float64(c.Red)
    var g float64 = float64(c.Green)
    var b float64 = float64(c.Blue)

    /*  Compute the norm of the vector (r, g, b) using Pythagoras.            */
    var norm float64 = math.Sqrt(r*r + g*g + b*b)

    /*  For non-zero norm (i.e. colors other than black) normalize intensity. */
    if norm != 0.0 {
        ColorScaleBy(c, 255.0 / norm)
    }
}
/*  End of Color.Normalize.                                                   */

/******************************************************************************
 *                              Complex Colorers                              *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      ColorFromComplex                                                      *
 *  Purpose:                                                                  *
 *      Creates an RGB color from a complex number. The intensity is given by *
 *      the magnitude of the number, and the color is from the argument.      *
 *  Arguments:                                                                *
 *      z (complex128):                                                       *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (Color):                                                            *
 *          The color given by the modulus and argument of the input.         *
 *  Method:                                                                   *
 *      Create a rainbow gradient red-to-blue from the argument of the input  *
 *      and then scale this by the magnitude.                                 *
 ******************************************************************************/
func ColorFromComplex(z complex128) Color {

    /*  There are 1024 possible colors given by the gradient. This scale      *
     *  factor helps normalize the argument.                                  */
    const gradient_factor float64 = 1023.0 / (2.0 * math.Pi)

    /*  Compute the argument and modulus of the input complex number.         */
    var arg_z float64 = cmplx.Phase(z)
    var abs_z float64 = cmplx.Abs(z)

    /*  Scale the argument from (-pi, pi) to (0, 1023).                       */
    var val float64 = (arg_z + math.Pi) * gradient_factor

    /*  The atan function compresses the intensity to prohibit arbitrarily    *
     *  bright points. This allows the drawing to fit into an actual PPM.     */
    var t float64 = (2.0 / math.Pi) * math.Atan(5.0*abs_z)

    /*  Lastly, a color for the output.                                       */
    var out Color

    /*  For 0 <= val < 256 transition from blue to cyan.                      */
    if (val < 256.0) {
        out.Red = uint8(0)
        out.Green = uint8(val)
        out.Blue = uint8(255)

    /*  For 256 <= val < 512 transition from cyan to green.                   */
    } else if (val < 512.0) {

        /*  Shift val back to the range (0, 256).                             */
        val -= 256.0

        /*  Transition from cyan to green.                                    */
        out.Red = uint8(0)
        out.Green = uint8(255)
        out.Blue = uint8(256.0 - val)

    /*  For 512 <= val < 768 transition from green to yellow.                 */
    } else if (val < 768.0) {

        /*  Shift val back to the range (0, 256).                             */
        val -= 512.0

        /*  Transition from green to yellow.                                  */
        out.Red = uint8(val)
        out.Green = uint8(255)
        out.Blue = uint8(0)

    /*  For 768 <= val < 1024 transition from yellow to red.                  */
    } else {

        /*  Shift val back to the range (0, 256).                             */
        val -= 768.0

        /*  Transition from yellow to red.                                    */
        out.Red = uint8(255)
        out.Green = uint8(256.0 - val)
        out.Blue = uint8(0)
    }

    /*  Scale the color by the atan factor and return.                        */
    ColorScaleBy(&out, t)
    return out
}
/*  End of ColorFromComplex.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      ColorWheelFromComplex                                                 *
 *  Purpose:                                                                  *
 *      Creates an RGB color from a complex number. The intensity is given by *
 *      the magnitude of the number, and the color is from the argument.      *
 *  Arguments:                                                                *
 *      z (complex128):                                                       *
 *          A complex number.                                                 *
 *  Outputs:                                                                  *
 *      c (Color):                                                            *
 *          The color given by the modulus and argument of the input.         *
 *  Method:                                                                   *
 *      Create a rainbow gradient red-to-blue-to-red from the argument of the *
 *      input and then scale this by the magnitude.                           *
 ******************************************************************************/
func ColorWheelFromComplex(z complex128) Color {

    /*  There are 1535 possible colors given by the gradient. This scale      *
     *  factor helps normalize the argument.                                  */
    const gradient_factor float64 = 1535.0 / (2.0 * math.Pi)

    /*  Compute the argument and modulus of the input complex number.         */
    var arg_z float64 = cmplx.Phase(z)
    var abs_z float64 = cmplx.Abs(z)

    /*  Scale the argument from (-pi, pi) to (0, 1535).                       */
    var val float64 = (arg_z + math.Pi) * gradient_factor

    /*  The atan function compresses the intensity to prohibit arbitrarily    *
     *  bright points. This allows the drawing to fit into an actual PPM.     */
    var t float64 = (2.0 / math.Pi) * math.Atan(5.0*abs_z)

    /*  Lastly, a color for the output.                                       */
    var out Color

    /*  For 0 <= val < 256 transition from blue to cyan.                      */
    if (val < 256.0) {
        out.Red = uint8(0)
        out.Green = uint8(val)
        out.Blue = uint8(255)

    /*  For 256 <= val < 512 transition from cyan to green.                   */
    } else if (val < 512.0) {

        /*  Shift val back to the range (0, 256).                             */
        val -= 256.0

        /*  Transition from cyan to green.                                    */
        out.Red = uint8(0)
        out.Green = uint8(255)
        out.Blue = uint8(256.0 - val)

    /*  For 512 <= val < 768 transition from green to yellow.                 */
    } else if (val < 768.0) {

        /*  Shift val back to the range (0, 256).                             */
        val -= 512.0

        /*  Transition from green to yellow.                                  */
        out.Red = uint8(val)
        out.Green = uint8(255)
        out.Blue = uint8(0)

    /*  For 768 <= val < 1024 transition from yellow to red.                  */
    } else if (val < 1024.0) {

        /*  Shift val back to the range (0, 256).                             */
        val -= 768.0

        /*  Transition from yellow to red.                                    */
        out.Red = uint8(255)
        out.Green = uint8(256.0 - val)
        out.Blue = uint8(0)

    /*  For 1024 <= val < 1280 transition from red to magenta.                */
    } else if (val < 1280.0) {

        /*  Shift val back to the range (0, 256).                             */
        val -= 1024.0

        /*  Transition from red to magenta.                                   */
        out.Red = uint8(255)
        out.Green = uint8(0)
        out.Blue = uint8(val)

    /*  For 1280 <= val < 1526 transition from magenta back to blue.          */
    } else {

        /*  Shift val back to the range (0, 256).                             */
        val -= 1280.0

        /*  Transition from magenta to blue.                                  */
        out.Red = uint8(256.0 - val)
        out.Green = uint8(0)
        out.Blue = uint8(255)
    }

    /*  Scale the color by the atan factor and return.                        */
    ColorScaleBy(&out, t)
    return out
}
/*  End of ColorWheelFromComplex.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      ComplexPlot                                                           *
 *  Purpose:                                                                  *
 *      Creates a plot from a complex function based on argument and modulus. *
 *  Arguments:                                                                *
 *      cfunc (ComplexFunc):                                                  *
 *          A complex-valued function of a complex variable.                  *
 *      color (Colorer):                                                      *
 *          Coloring function for converting complex numbers into colors.     *
 *      name (string):                                                        *
 *          The name of the output PPM file.                                  *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func ComplexPlot(cfunc ComplexFunc, color Colorer, name string) {

    /*  Variables for the x and y coordinates of a given pixel.               */
    var x, y uint32

    /*  Variables for the real and imaginary parts of a given complex number. */
    var z_re, z_im float64

    /*  Variable for the complex number z_re + i*z_im.                        */
    var z complex128

    /*  Color for the pixel corresponding to z.                               */
    var c Color

    /*  Variable for the ppm file.                                            */
    var ppm PPM

    /*  Create the ppm file.                                                  */
    ppm.Create(name)

    /*  Initialize the ppm file to the default values.                        */
    ppm.Init()

    /*  Loop over the y coordinates of the ppm file.                          */
    for y = 0; y < HEIGHT; y++ {

        /*  Compute the y coordinate in the plane corresponding to the pixel. */
        z_im = YMAX - YFACTOR * float64(y)

        /*  Loop over the x coordinates of the ppm file.                      */
        for x = 0; x < WIDTH; x++ {

            /*  Compute the corresponding x coordinate.                       */
            z_re = XMIN + XFACTOR * float64(x)

            /*  Treat the ordered pair (z_re, z_im) as a complex number.      */
            z = complex(z_re, z_im)

            /*  Get the color corresponding to this pixel.                    */
            c = color(cfunc(z))

            /*  Write the color to the ppm file.                              */
            c.WriteToPPM(&ppm)
        }
    }

    /*  Close the ppm file.                                                   */
    ppm.Close()
}
/*  End of ComplexPlot.                                                       */

/******************************************************************************
 *  Function:                                                                 *
 *      IterPlot                                                              *
 *  Purpose:                                                                  *
 *      Plots F_{n}(z) = f(f(...f(z)...)) where there are n iterations. This  *
 *      can be used to visualize Newton fractals, which is the "F_{infinity}" *
 *      iteration of particular functions.                                    *
 *  Arguments:                                                                *
 *      cfunc (ComplexFunc):                                                  *
 *          A complex-valued function of a complex argument.                  *
 *      iters (uint32):                                                       *
 *          The number of iterations to perform for cfunc.                    *
 *      color (Colorer):                                                      *
 *          The color scheme for the plane.                                   *
 *      name (string):                                                        *
 *          The name of the ppm file.                                         *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func IterPlot(cfunc ComplexFunc, iters uint32, color Colorer, name string) {

    /*  Variables for the x and y coordinates of a given pixel.               */
    var x, y uint32

    /*  Variable for iteratively computing the function.                      */
    var n uint32

    /*  Variables for the real and imaginary parts of a given complex number. */
    var z_re, z_im float64

    /*  Variable for the complex number z_re + i*z_im.                        */
    var z complex128

    /*  Color for the pixel corresponding to z.                               */
    var c Color

    /*  Variable for the ppm file.                                            */
    var ppm PPM

    /*  Create the ppm file.                                                  */
    ppm.Create(name)

    /*  Initialize the ppm file to the default values.                        */
    ppm.Init()

    /*  Loop over the y coordinates of the ppm file.                          */
    for y = 0; y < HEIGHT; y++ {

        /*  Compute the y coordinate in the plane corresponding to the pixel. */
        z_im = YMAX - YFACTOR * float64(y)

        /*  Loop over the x coordinates of the ppm file.                      */
        for x = 0; x < WIDTH; x++ {

            /*  Compute the corresponding x coordinate.                       */
            z_re = XMIN + XFACTOR * float64(x)

            /*  Treat the ordered pair (z_re, z_im) as a complex number.      */
            z = complex(z_re, z_im)

            /*  Iteratively compute the function.                             */
            for n = 0; n < iters; n += 1 {
                z = cfunc(z)
            }

            /*  Get the color corresponding to this pixel.                    */
            c = color(z)

            /*  Write the color to the ppm file.                              */
            c.WriteToPPM(&ppm)
        }
    }

    /*  Close the ppm file.                                                   */
    ppm.Close()
}
/*  End of IterPlot.                                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      MandelPlot                                                            *
 *  Purpose:                                                                  *
 *      Given a complex function f, computes w_{0} = z, w_{1} = f(w_{0}) + z, *
 *      w_{2} = f(w_{1}) + z, and so on, a specified number of times. This    *
 *      can be used to visualize the Mandelbrot set and similar structures.   *
 *  Arguments:                                                                *
 *      cfunc (ComplexFunc):                                                  *
 *          A complex-valued function of a complex argument.                  *
 *      iters (uint32):                                                       *
 *          The number of iterations to perform for cfunc.                    *
 *      color (Colorer):                                                      *
 *          The color scheme for the plane.                                   *
 *      name (string):                                                        *
 *          The name of the ppm file.                                         *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func MandelPlot(cfunc ComplexFunc, iters uint32, color Colorer, name string) {

    /*  Variables for the x and y coordinates of a given pixel.               */
    var x, y uint32

    /*  Variable for iteratively computing the function.                      */
    var n uint32

    /*  Variables for the real and imaginary parts of a given complex number. */
    var z_re, z_im float64

    /*  Variable for the complex number z_re + i*z_im.                        */
    var z complex128

    /*  Variable for computing the Mandelbrot iterations.                     */
    var w complex128

    /*  Color for the pixel corresponding to z.                               */
    var c Color

    /*  Variable for the ppm file.                                            */
    var ppm PPM

    /*  Create the ppm file.                                                  */
    ppm.Create(name)

    /*  Initialize the ppm file to the default values.                        */
    ppm.Init()

    /*  Loop over the y coordinates of the ppm file.                          */
    for y = 0; y < HEIGHT; y++ {

        /*  Compute the y coordinate in the plane corresponding to the pixel. */
        z_im = YMAX - YFACTOR * float64(y)

        /*  Loop over the x coordinates of the ppm file.                      */
        for x = 0; x < WIDTH; x++ {

            /*  Compute the corresponding x coordinate.                       */
            z_re = XMIN + XFACTOR * float64(x)

            /*  Treat the ordered pair (z_re, z_im) as a complex number.      */
            z = complex(z_re, z_im)

            /*  The first iteration is w = z.                                 */
            w = z

            /*  Iteratively compute the function.                             */
            for n = 0; n < iters; n += 1 {
                w = cfunc(w) + z
            }

            /*  Get the color corresponding to this pixel.                    */
            c = color(w)

            /*  Write the color to the ppm file.                              */
            c.WriteToPPM(&ppm)
        }
    }

    /*  Close the ppm file.                                                   */
    ppm.Close()
}
/*  End of MandelPlot.                                                        */
