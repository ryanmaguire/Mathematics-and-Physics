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
 *      Provides functions for performing Euler's method on ODEs.             *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/02/28                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NBH_EULER_HPP
#define NBH_EULER_HPP

/*  Basic 3D vector struct given here.                                        */
#include "nbh_vector.hpp"

/*  Namespace for the mini-project. "Newtonian Black Holes."                  */
namespace nbh {

    /*  To avoid name conflicts with Runge-Kutta, use another namespace.      */
    namespace euler {

        /*  Time step used in Euler's method. The user may change this.       */
        static double time_increment = 0.01;

        /*  The max number of iterations in Euler's method. Unsigned int is   *
         *  required (in C, at least) to be at least 16 bits. It is usually   *
         *  32. Regardless, it is wide enough to store 65535U safely.         */
        static unsigned int max_iters = 65535U;

        /*  Function for reseting the max number of iterations allowed.       */
        inline void reset_max_iters(unsigned int n);

        /*  Function for performing Euler's method, provided below.           */
        inline nbh::vec3 path(nbh::vec3 p,
                              nbh::vec3 v,
                              nbh::vec3 (*acc)(const nbh::vec3 &),
                              bool (*stop)(const nbh::vec3 &));
    }
    /*  End of euler namespace.                                               */


    /*  Function for reseting the max number of iterations allowed.           */
    inline void euler::reset_max_iters(unsigned int n)
    {
        euler::max_iters = n;
    }

    /*  Given a vector-valued acceleration a = acc(r), a starting position p, *
     *  an initial velocity v, and a stopping condition stop, perform Euler's *
     *  method to numerically solve the system of motion.                     */
    inline nbh::vec3 euler::path(nbh::vec3 p,
                                 nbh::vec3 v,
                                 nbh::vec3 (*acc)(const nbh::vec3 &),
                                 bool (*stop)(const nbh::vec3 &))
    {
        /*  Use of this function with nbh makes a very naive assumption.      *
         *  Newton's Second Law states that F = ma, where a is the            *
         *  acceleration. So, for gravity, we obtain the vector-valued        *
         *  differential equation:                                            *
         *      -GMm p / ||p||^3 = m d^2/dt^2 p                               *
         *  Where G is the universal gravitational constant, and M is the     *
         *  mass of the black hole (m being the mass of the object under      *
         *  consideration). We can take G*M to be 1 for simplicity, since we  *
         *  never specified the units we're in. Now, if m is any non-zero     *
         *  value we can cancel to get:                                       *
         *      p / ||p||^3 = d^2/dt^2 p                                      *
         *  Solving this vector-valued differential equation results in the   *
         *  trajectory of the object. The only problem is it is generally     *
         *  believed that photons, which are particles of light, have zero    *
         *  mass. So let's pretend they have a mass that is so stupidly small *
         *  it would be impossible to measure, but not zero. If this were     *
         *  true, we could apply Newtonian mechanics to get a rough idea as   *
         *  to what a black hole would look like.                             */

        /*  In the main use of this function, the black hole is of radius r   *
         *  at the origin, and our detector is the plane z = z0. Our source   *
         *  of light is some plane z = z1. So the light is coming             *
         *  down and heading towards our detector. We'll increment time using *
         *  a small value dt, and we'll keep incrementing until the light     *
         *  either hits the detector, or is absorbed by the black hole. dt is *
         *  given by the time_increment value, and the stopping condition     *
         *  (hitting the detector, or being absorbed by a black hole) is      *
         *  determined by the "stop" function.                                */
        unsigned int n = 0U;

        /*  Keep performing Euler's method until we hit the detector, or      *
         *  perform too many iterations.                                      */
        while (!stop(p) && n < euler::max_iters)
        {
            /*  We numerically solve d^2/dt^2 p = F(p) in two steps. First,   *
             *  we compute the velocity dp/dt, meaning we need to solve       *
             *  dv/dt = F(p). We solve numerically with Euler's method. Then  *
             *  we use this v to compute p via dp/dt = v, again solving       *
             *  numerically with Euler's method. So long as dt is small,      *
             *  the error should be small as well.                            */
            p += v * euler::time_increment;
            v += acc(p) * euler::time_increment;

            /*  It is possible that a photon was captured into orbit, but not *
             *  absorbed into the black hole. To avoid an infinite loop,      *
             *  abort the computation once n gets too large.                  */
            ++n;
        }

        return p;
    }
    /*  End of euler function.                                                */
}
/*  End of namespace nbh.                                                     */

#endif
/*  End of include guard.                                                     */
