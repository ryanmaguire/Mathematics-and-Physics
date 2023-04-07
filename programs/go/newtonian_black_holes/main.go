package main

import "fmt"

func main() {
    var v Vec3 = Vec3Rect(1.0, 1.0, 0.0)
    var w Vec3 = Vec3Rect(1.0, 0.0, 1.0)
    var u Vec6 = Vec6{v, w}
    fmt.Println(v.Norm())
    fmt.Println(v.Dot(&w))
    fmt.Println(u)
}
