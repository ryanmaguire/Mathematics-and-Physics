package nbh

import "math"

/*  Basic struct for vectors in R^3.                                          */
type Vec3 struct {

    /*  A vector is represented by its Cartesian coordinates.                 */
    x, y, z float64
}

func Vec3Rect(x, y, z float64) Vec3 {
    return Vec3{x, y, z}
}

func Vec3Add(v, w *Vec3) Vec3 {
    return Vec3Rect(v.x + w.x, v.y + w.y, v.z + w.z)
}

func Vec3AddTo(v, w *Vec3) {
    v.x += w.x
    v.y += w.y
    v.z += w.z
}

func Vec3Subtract(v, w *Vec3) Vec3 {
    return Vec3Rect(v.x - w.x, v.y - w.y, v.z - w.z)
}

func Vec3SubtractFrom(v, w *Vec3) {
    v.x -= w.x
    v.y -= w.y
    v.z -= w.z
}

func (v *Vec3) Dot(w *Vec3) float64 {
    return v.x*w.x + v.y*w.y + v.z*w.z
}

func (v *Vec3) Norm() float64 {
    return math.Sqrt(v.x*v.x + v.y*v.y + v.z*v.z)
}
