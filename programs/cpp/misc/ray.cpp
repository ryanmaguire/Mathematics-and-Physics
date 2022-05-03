#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//  Define a vector class with constructor and operator: 'v'
struct vector
{
    float x;
    float y;
    float z;

    vector operator+(vector r)
    {
        return vector(x+r.x,y+r.y,z+r.z);
    }

    vector operator*(float r)
    {
        return vector(x*r,y*r,z*r);
    }

    //  Dot product.
    float operator%(vector r)
    {
        return x*r.x+y*r.y+z*r.z;
    }

    //  Empty constructor
    vector (void){}

    //  Cross-product
    vector operator^(vector r){
        return vector(y*r.z-z*r.y,z*r.x-x*r.z,x*r.y-y*r.x);
    }

    //  Constructor
    vector(float a, float b, float c)
    {
        x=a;
        y=b;
        z=c;
    }

    // Used later for normalizing
    vector operator!(void)
    {
        return *this*(1 /sqrt(*this%*this));
    }
};

int  G[] = {
    247570,
    280596,
    280600,
    249748,
    18578,
    18577,
    231184,
    16,
    16
};

float frand(void)
{
    return (float)rand()/RAND_MAX;
}

//The intersection test for line [o,v].
// Return 2 if a hit was found (and also return distance t and bouncing ray n).
// Return 0 if no hit was found but ray goes upward
// Return 1 if no hit was found but ray goes downward
int Tracer(vector o, vector d, float& t, vector& n)
{
    int k, j;
    float s, b, c, q;
    vector P;
    t=1e9;
    int m=0;
    float p = -o.z/d.z;
    if (.01<p)
    {
        t = p;
        n = vector(0,0,1);
        m = 1;
    }

    //  The world is encoded in G, with 9 lines and 19 columns

    //  For each columns of objects
    for (k=19; k--;)
    {
        for (j=9; j--;)   //For each line on that columns
        {
            //  For this line j, is there a sphere at column i ?
            if (G[j]&1<<k)
            {
                // There is a sphere but does the ray hits it ?
                P = o + vector(-k,0,-j-4);
                b = P%d;
                c = P%P-1;
                q = b*b-c;

                //  Does the ray hit the sphere ?
                if(q>0)
                {
                    //  It does, compute the distance camera-sphere
                    s = -b-sqrt(q);

                    //  So far this is the minimum distance, save it. And also
                    //  compute the bouncing ray vector into 'n'
                    if(s<t && s>.01)
                    {
                        t = s;
                        n = !(P + d*t);
                        m = 2;
                    }
                }
            }
        }
    }
    return m;
}

// (S)ample the world and return the pixel color for
// a ray passing by point o (Origin) and d (Direction)
vector Shader(vector o, vector d)
{
    float t;
    vector n;
    float b, p;

    //  Search for an intersection ray Vs World.
    int m = Tracer(o, d, t, n);

    //  No sphere found and the ray goes upward: Generate a sky color.
    if (m==0)
        return vector(.7,.6,1)*pow(1-d.z, 4);

    //  A sphere was maybe hit.

    // h = intersection coordinate
    vector h = o + d*t;

    // 'l' = direction to light (random delta for shadows).
    vector l = !(vector(9 + frand(), 9+frand(), 16) + h*-1);

    // r = The half-vector
    vector r = d + n*(n%d*-2);

    //  Calculated the lambertian factor
    b = l%n;

    //  Calculate illumination factor (lambertian coefficient > 0 or in shadow)?
    if (b<0 || Tracer(h,l,t,n))
        b=0;

    // Calculate the color 'p' with diffuse and specular component
    p = pow(l%r*(b>0),99);

    //  m == 1
    if(m&1)
    {
        //  No sphere was hit and the ray was going downward.
        //  Generate a floor color.
        h = h*0.2;
        if ((int)(ceil(h.x)+ceil(h.y)) & 1)
            return vector(3,1,1)*(b*0.2 + 0.1);
        else
            return vector(3,3,3)*(b*0.2 + 0.1);
      }

    //  m == 2 A sphere was hit.
    //  Cast an ray bouncing from the sphere surface.
    //  Attenuate color by 50% since it is bouncing (* .5)
    return vector(p, p, p) + Shader(h,r)*.5;
  }

//  The main function. It generates a PPM image to stdout.
//  Usage of the program is hence: ./card > erk.ppm
int main(void)
{
    // The '!' are for normalizing each vectors with ! operator.
    FILE *fp = fopen("ray.ppm", "w");

    //  Camera direction
    vector g=!vector(-6,-16,0);

    // Camera up vector... Seem Z is pointing up :/ WTF !
    vector a=!(vector(0,0,1)^g)*.002;

    //  The right vector, obtained via traditional cross-product
    vector b=!(g^a)*.002;

    //  WTF ? See https://news.ycombinator.com/item?id=6425965.
    vector c=(a+b)*-256+g;

    int x, y, r;
    vector p, t;

    //  The PPM Header is issued
    fprintf(fp, "P6\n512 512\n255\n");

    //For each column
    for(y=512;y--;)
    {
        // For each pixel in a line
        for(x=512;x--;)
        {
            //  Reuse the vector class to store not XYZ but a RGB pixel color
            p = vector(13, 13, 13);

            //  Cast 64 rays per pixel (For blur (stochastic sampling)
            //  and soft-shadows.
            for(r=64;r--;)
            {
                //  The delta to apply to the origin of the view
                //  (For Depth of View blur).

                // A little bit of delta
                t = a*(frand()-.5)*99+b*(frand()-.5)*99;

                // Set the camera focal point v(17,16,8) and Cast the ray
                // Accumulate the color returned in the p variable
                p = Shader(
                    //  Ray Origin
                    vector(17,16,8)+t,

                    //  Ray Direction with random deltas for stochastic sampling
                    !(t*-1+(a*(frand()+x)+b*(y+frand())+c)*16)
                // +p for color accumulation
                )*3.5 + p;
            }

            fprintf(fp, "%c%c%c", (int)p.x, (int)p.y, (int)p.z);
        }
    }
}
