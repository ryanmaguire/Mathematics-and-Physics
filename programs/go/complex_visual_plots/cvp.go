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

/*  os.File type is here.                                                     */
import "os"

/*  log.Fatal function given here.                                            */
import "log"

/*  Basic complex math function.                                              */
import "math/cmplx"

/*  Real-valued math routines.                                                */
import "math"

/*  Printing functions.                                                       */
import "fmt"

/*  Parameters for the plots.                                                 */
const XMIN float64 = -2.0
const XMAX float64 = +2.0
const YMIN float64 = -2.0
const YMAX float64 = +2.0
const WIDTH uint32 = 1024
const HEIGHT uint32 = 1024
const XFACTOR float64 = 3.91006842619745845213e-03
const YFACTOR float64 = 3.91006842619745845213e-03

/*  Simple struct for working with colors in RGB format.                      */
type Color struct {
    Red, Green, Blue uint8
}

/*  Complex-valued functions.                                                 */
type ComplexFunc func(complex128) complex128

/*  Functions that convert complex numbers into colors.                       */
type Colerer func(complex128) Color

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

    /*  There are 1535 possible colors given by the gradient. This scale      *
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

    /*  For 1280 <= val < 1526 transition from magent back to blue.           */
    } else {

        /*  Shift val back to the range (0, 256).                             */
        val -= 1280.0

        /*  Transition from red to magenta.                                   */
        out.Red = uint8(256.0 - val)
        out.Green = uint8(0)
        out.Blue = uint8(val)
    }

    /*  Scale the color by the atan factor and return.                        */
    ColorScaleBy(&out, t)
    return out
}
/*  End of ColorFromComplex.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      ComplexPlot                                                           *
 *  Purpose:                                                                  *
 *      Creates a plot from a complex function based on argument and modulus. *
 *  Arguments:                                                                *
 *      cfunc (ComplexFunc):                                                  *
 *          A complex-valued function of a complex variable.                  *
 *      color (Colerer):                                                      *
 *          Coloring function for converting complex numbers into colors.     *
 *      name (string):                                                        *
 *          The name of the output PPM file.                                  *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func ComplexPlot(cfunc ComplexFunc, color Colerer, name string) {

    var x, y uint32
    var z_re, z_im float64
    var z complex128
    var c Color

    var err error
    var fp *os.File

    fp, err = os.Create(name)

    if (err != nil) {
        log.Fatal(err)
    }

    fp.WriteString(fmt.Sprintf("P6\n%d %d\n255\n", WIDTH, HEIGHT))

    for y = 0; y < HEIGHT; y++ {
        z_im = YMAX - YFACTOR * float64(y)

        for x = 0; x < WIDTH; x++ {
            z_re = XMIN + XFACTOR * float64(x)
            z = complex(z_re, z_im)
            c = color(cfunc(z))
            c.WriteToFile(fp)
        }
    }

    err = fp.Close()

    if err != nil {
        log.Fatal(err)
    }
}
/*  End of ComplexPlot.                                                       */

func f(z complex128) complex128 {
    return z*z*z - 1.0
}

func main() {
    ComplexPlot(f, ColorWheelFromComplex, "z_cubed_minus_one.ppm")
}
