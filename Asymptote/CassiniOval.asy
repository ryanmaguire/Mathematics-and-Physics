import graph;

struct CassiniOval{
    pair A, B;
    int npoints;

    real a, c, C, alpha;
    transform transf;

    guide[] curve;

    real rho(real phi){
        return c*sqrt(abs(cos(2*phi)+sqrt(abs(cos(2*phi)^2+(a/c)^4-1))));
    };

    real rho2(real phi){
        return c*sqrt(abs(cos(2*phi)-sqrt(abs(cos(2*phi)^2+(a/c)^4-1))));
    };

    guide[] normLscate(){
        guide[] g;
        guide q;
        real xMax = sqrt(a^2+c^2);
        real xMin = -xMax;

        // Determine if one contour or two.
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

    void operator init(pair A, pair B, real C, int npoints=300){
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