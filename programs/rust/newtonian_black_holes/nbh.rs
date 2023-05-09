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
 *      Routines for raytracing Newtonian black holes in rust.                *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/05/08                                                        *
 ******************************************************************************/

/*  Needed for operator overloading.                                          */
use std::ops;

/*  Simple struct for vectors in R^3.                                         */
struct Vec3 {

    /*  A vector is defined by it's Cartesian components.                     */
    x: f64,
    y: f64,
    z: f64
}

impl Copy for Vec3 {}

impl Clone for Vec3 {
    fn clone(&self) -> Vec3 {
        *self
    }
}

impl ops::Add<Vec3> for Vec3 {
    type Output = Vec3;

    fn add(self: Vec3, rhs: Vec3) -> Vec3 {
        return Vec3{x: self.x + rhs.x, y: self.y + rhs.y, z: self.z + rhs.z};
    }
}

impl ops::AddAssign<Vec3> for Vec3 {

    fn add_assign(self: &mut Vec3, rhs: Vec3) {
        self.x += rhs.x;
        self.y += rhs.y;
        self.z += rhs.z;
    }
}

impl Vec3 {
    fn cross(self: Vec3, rhs: Vec3) -> Vec3 {
        let x: f64 = self.y*rhs.z - self.z*rhs.y;
        let y: f64 = self.z*rhs.x - self.x*rhs.z;
        let z: f64 = self.x*rhs.y - self.y*rhs.x;
        return Vec3{x: x, y: y, z: z};
    }

    fn dot(self: Vec3, rhs: Vec3) -> f64 {
        return self.x*rhs.x + self.y*rhs.y + self.z*rhs.z;
    }
}

fn main() {
    let p = Vec3{x: 1.0, y: 2.0, z: 3.0};
    let q = Vec3{x: 4.0, y: 5.0, z: 6.0};
    let mut sum = p + q;
    let cross = p.cross(sum);
    sum += q;

    println!("<{}, {}, {}>", cross.x, cross.y, cross.z);
    println!("<{}, {}, {}>", sum.x, sum.y, sum.z);
    println!("{}", cross.dot(p));
}
