// Seting output format to "pdf".
import settings;
import graph;
settings.outformat = "pdf";

// Size of the output.
size(230);

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

// Pens used for drawing lines and shading (Counter and Fill).
pen cpen = deepblue;
pen fpen = lightgreen+opacity(0.2)+evenodd;

// Distance between points.
real dist = 4;

// The first focii. The second focii is -A.
pair A = (dist/2, 0);

// The Cassini Oval structure is defined in CassiniOval.asy.
CassiniOval co, co2;

// Variable for indexing.
int i;

// The increment in oval parameter between successive Cassini ovals.
real steps = 0.5;

// Starting index, must be positive.
int start  = 1;

// Final index, determined by distance between focii and size of steps.
int finish = (int)(dist/steps);

// Draw the figure 8 Cassini oval.
co=CassiniOval(A, -A, dist);
draw(co.curve, cpen+2);

// Loop over successive ovals, shading in area around central figure 8.
for(i=start; i<finish; ++i){
    co  = CassiniOval(A, -A, dist+i*steps);
    co2 = CassiniOval(A, -A, dist-i*steps);

    // Create an array of paths and shade with the even-odd rule.
    path p1 = co.curve[0];
    path p2 = co2.curve[0];
    path p3 = co2.curve[1];
    path[] p = {p1, p2, p3};
    filldraw(p, fpen, cpen);
}