/******************************************************************************
 *                                 LICENSE                                    *
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
 ******************************************************************************/

import graph;

struct CassiniOval {
    pair A, B;
    int npoints;

    real a, c, C, alpha;
    transform transf;

    guide[] curve;

    real rho(real phi)
    {
        return c*sqrt(abs(cos(2*phi)+sqrt(abs(cos(2*phi)^2+(a/c)^4-1))));
    };

    real rho2(real phi)
    {
        return c*sqrt(abs(cos(2*phi)-sqrt(abs(cos(2*phi)^2+(a/c)^4-1))));
    };

    guide[] normLscate()
    {
        guide[] g;
        guide q;
        real xMax = sqrt(a^2+c^2);
        real xMin = -xMax;

        /*  Determine if one contour or two.                                  */
        if(a>=c){
            g.push(transf*(polargraph(rho, 0, 2pi, npoints)--cycle));
        }
        else {
            q=polargraph(rho, -alpha, alpha, npoints)
            --reverse(polargraph(rho2, -alpha, alpha, npoints))--cycle;
            g=(transf*q)^^(transf*reflect(N,S)*q);
        }
        return g;
    }

    void operator init(pair A, pair B, real C, int npoints=300)
    {
        assert(C>0);
        this.A=A;
        this.B=B;
        this.C=C;
        assert(npoints>1);
        this.npoints=npoints;
        this.c=arclength(A--B)/2;
        this.a=sqrt(C);
        transf=shift(A)*rotate(degrees(atan2(B.y-A.y, B.x-A.x)))*shift(c, 0);

        if(a<c) alpha=asin((a/c)^2)/2;
        curve = normLscate();
    }
}
