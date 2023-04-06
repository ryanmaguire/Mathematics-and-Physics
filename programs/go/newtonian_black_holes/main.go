package main

import (
    "nbh"
    "fmt"
)

func main() {
    var v nbh.Vec3 = nbh.Vec3Rect(1.0, 1.0, 0.0)
    var w nbh.Vec3 = nbh.Vec3Rect(1.0, 0.0, 1.0)
    fmt.Println(v.Norm())
    fmt.Println(v.Dot(&w))
}
