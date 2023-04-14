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
 *      Provides functions for performing the Runge-Kutta method on ODEs.     *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/04/09                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef NBH_RK_H
#define NBH_RK_H

/*  NBH_INLINE macro found here.                                              */
#include "nbh_inline.h"

/*  Basic 3D vector struct given here.                                        */
#include "nbh_vec3.h"

/*  Basic 6D vector struct given here.                                        */
#include "nbh_vec6.h"

/*  Acceleration and stopper function typedefs here.                          */
#include "nbh_function_types.h"

/*  Time step used in the RK4 method. The user may change this.               */
static double nbh_rk_time_increment = 0.1;

/*  The max number of iterations in the RK4 method.                           */
static unsigned int nbh_rk_max_iters = 65535U;

/*  Function for reseting the max number of iterations allowed.               */
NBH_INLINE void
nbh_rk_reset_max_iters(unsigned int n)
{
    nbh_rk_max_iters = n;
}

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_rk4_factor                                                        *
 *  Purpose:                                                                  *
 *      Computes the Runge-Kutta factor at step "h" with direction "u1".      *
 *  Arguments:                                                                *
 *      u0 (const struct nbh_vec6 *):                                         *
 *          A pointer to a 6D vector, the initial condition for RK4.          *
 *      h (double):                                                           *
 *          The size of the step (usually dt or dt/2, pending factor).        *
 *      u1 (const struct nbh_vec6 *):                                         *
 *          A pointer to a 6D vector, the perturbing vector for u0.           *
 *      acc (acceleration):                                                   *
 *          The function that describes the ODE. We are numerically solving   *
 *          p''(t) = acc(p(t)).                                               *
 *  Outputs:                                                                  *
 *      out (struct nbh_vec6):                                                *
 *          The Runge-Kutta factor.                                           *
 *  Method:                                                                   *
 *      We need to compute:                                                   *
 *                                                                            *
 *          p_out = v0 + h * v1                                               *
 *          v_out = acc(p0 + h * p1)                                          *
 *                                                                            *
 *      Where u0 = (p0, v0), u1 = (p1, v1), and out = (p_out, v_out).         *
 ******************************************************************************/
NBH_INLINE struct nbh_vec6
nbh_rk4_factor(const struct nbh_vec6 *u0, double h,
               const struct nbh_vec6 *u1, acceleration acc)
{
    /*  Declare a variable for the output.                                    */
    struct nbh_vec6 out;

    /*  We can compute p0 + h*p1 in one step with the following.              */
    const struct nbh_vec3 p = nbh_vec3_scaled_add(&u0->p, h, &u1->p);

    /*  Compute the first factor, p_out = v0 + h * v1.                        */
    out.p = nbh_vec3_scaled_add(&u0->v, h, &u1->v);

    /*  Compute acc(p0 + h * p1) using "p" from before.                       */
    out.v = acc(&p);
    return out;
}
/*  End of nbh_rk4_factor.                                                    */

/******************************************************************************
 *  Function:                                                                 *
 *      nbh_rk_path                                                           *
 *  Purpose:                                                                  *
 *      Given a vector-valued acceleration a = acc(r), a starting position p, *
 *      an initial velocity v, and a stopping condition stop, perform the RK4 *
 *      method method to numerically solve the system of motion. The initial  *
 *      conditions (p, v) are given as the 6D vector u.                       *
 *  Arguments:                                                                *
 *      u (struct nbh_vec6 *):                                                *
 *          A pointer to a 6D vector that represents the initial position and *
 *          velocity vectors of the particle.                                 *
 *      acc (acceleration):                                                   *
 *          A function that describes the equation of motion for the particle.*
 *      stop (stopper):                                                       *
 *          A stopper function that determines when to stop the RK4 method.   *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Apply fourth order Runge-Kutta method. Given initial conditions       *
 *      (p0, v0) and time increment dt, we iteratively compute:               *
 *                                                                            *
 *          u_{n} = (p_{n}, v_{n})                                            *
 *          a_{n} = acc(p_{n})                                                *
 *          k1    = (v_{n}, a_{n})                                            *
 *          k2    = u_{n} + k1 * (dt/2)                                       *
 *          k3    = u_{n} + k2 * (dt/2)                                       *
 *          k4    = u_{n} + k2 * dt                                           *
 *                                                                            *
 *      These are the so-called RK factors. We update u_{n} via:              *
 *                                                                            *
 *          u_{n+1} = (dt/6) * (k1 + 2*k2 + 2*k3 + k4)                        *
 *                                                                            *
 *      Do this until the stopper function tells you to stop, or until you've *
 *      done to many iterations.                                              *
 ******************************************************************************/
NBH_INLINE void
nbh_rk_path(struct nbh_vec6 *u, acceleration acc, stopper stop)
{
    /*  Index for keeping track of the number of iterations performed.        */
    unsigned int n = 0U;

    /*  Constant multiples of dt used in the computation.                     */
    const double dt = nbh_rk_time_increment;
    const double h0 = 0.5 * dt;
    const double h1 = dt * 0.1666666666666667;

    /*  Current acceleration vector giving by the starting position.          */
    struct nbh_vec3 a = acc(&u->p);

    /*  Compute the initial Runge-Kutta factors.                              */
    struct nbh_vec6 k1 = nbh_vec6_from_vectors(&u->v, &a);
    struct nbh_vec6 k2 = nbh_rk4_factor(u, h0, &k1, acc);
    struct nbh_vec6 k3 = nbh_rk4_factor(u, h0, &k2, acc);
    struct nbh_vec6 k4 = nbh_rk4_factor(u, dt, &k2, acc);

    /*  Iteratively performed RK4.                                            */
    while (!stop(&u->p) && n < nbh_rk_max_iters)
    {
        /*  We numerically solve d^2/dt^2 p = F(p) in two steps. First we     *
         *  compute the velocity dp/dt, meaning we solve dv/dt = F(p). We     *
         *  solve numerically with the Runge-Kutta method. We use this v to   *
         *  compute p via dp/dt = v, solving numerically again. So long as dt *
         *  is small, the error should be small as well. Error is O(dt^4).    */
        u->p.x += h1 * (k1.p.x + 2.0*k2.p.x + 2.0*k3.p.x + k4.p.x);
        u->p.y += h1 * (k1.p.y + 2.0*k2.p.y + 2.0*k3.p.y + k4.p.y);
        u->p.z += h1 * (k1.p.z + 2.0*k2.p.z + 2.0*k3.p.z + k4.p.z);

        /*  Velocity component of the RK4 update.                             */
        u->v.x += h1 * (k1.v.x + 2.0*k2.v.x + 2.0*k3.v.x + k4.v.x);
        u->v.y += h1 * (k1.v.y + 2.0*k2.v.y + 2.0*k3.v.y + k4.v.y);
        u->v.z += h1 * (k1.v.z + 2.0*k2.v.z + 2.0*k3.v.z + k4.v.z);

        /*  Update the Runge-Kutta factors.                               */
        a = acc(&u->p);
        k1 = nbh_vec6_from_vectors(&u->v, &a);
        k2 = nbh_rk4_factor(u, h0, &k1, acc);
        k3 = nbh_rk4_factor(u, h0, &k2, acc);
        k4 = nbh_rk4_factor(u, dt, &k2, acc);

        /*  It is possible that a photon was captured into orbit, but not *
         *  absorbed into the black hole. To avoid an infinite loop,      *
         *  abort the computation once N gets to large.                   */
        ++n;
    }
}
/*  End of path function.                                                 */

#endif
/*  End of include guard.                                                     */
