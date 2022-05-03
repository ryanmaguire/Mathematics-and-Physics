package main

import "os"
import "log"
import "math/cmplx"
import "math"
import "fmt"

type color struct {
    red, green, blue byte
}

func write_color(fp *os.File, c color) {
    rgb := []byte{c.red, c.green, c.blue}
    fp.Write(rgb)
}

func f(z complex128) complex128 {
    return z*z*z - 1.0
}

func scale_color(c color, t float64) color {
    var out color
    out.red = byte(t * float64(c.red))
    out.green = byte(t * float64(c.green))
    out.blue = byte(t * float64(c.blue))
    return out
}

func get_color(z complex128) color {
    const gradient_factor float64 = 1023 / (2.0 * math.Pi)
    var arg_z float64 = cmplx.Phase(z)
    var abs_z float64 = cmplx.Abs(z)
    var val float64 = (arg_z + math.Pi) * gradient_factor
    var t float64 = (2.0 / math.Pi) * math.Atan(5.0*abs_z)
    var out color

    if (val < 256.0) {
        out.red = 0
        out.green = byte(val)
        out.blue = 255
    } else if (val < 512.0) {
        val -= 256.0
        out.red = 0
        out.green = 255
        out.blue = byte(256.0 - val)
    } else if (val < 768.0) {
        val -= 512.0
        out.red = byte(val)
        out.green = 255
        out.blue = 0
    } else {
        val -= 768.0;
        out.red = 255
        out.green = byte(256.0 - val)
        out.blue = 0
    }
    return scale_color(out, t)
}

func main() {
    const width uint = 1024
    const height uint = 1024
    const xmin float64 = -2.0
    const xmax float64 =  2.0
    const ymin float64 = -2.0
    const ymax float64 =  2.0
    const xfactor float64 = (xmax - xmin) / float64(width - 1)
    const yfactor float64 = (ymax - ymin) / float64(height - 1)
    var x, y uint
    var z_re, z_im float64
    var z complex128
    var c color

    var err error
    var fp *os.File

    fp, err = os.Create("z3_minus_1_go.ppm")

    if (err != nil) {
        log.Fatal(err)
    }

    fp.WriteString(fmt.Sprintf("P6\n%d %d\n255\n", width, height))

    for y = 0; y < height; y++ {
        z_im = ymax - yfactor * float64(y)

        for x = 0; x < width; x++ {
            z_re = xmin + xfactor * float64(x)
            z = complex(z_re, z_im)
            c = get_color(f(z))
            write_color(fp, c)
        }
    }

    err = fp.Close()

    if err != nil {
        log.Fatal(err)
    }
}
