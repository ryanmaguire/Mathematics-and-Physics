#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct vector {
    float x,y,z;
    vector operator + (vector r)
    {
        return vector(x+r.x, y+r.y, z+r.z);
    }

    vector operator * (float r)
    {
        return vector(x*r,y*r,z*r);
    }

    float operator % (vector r)
    {
        return x*r.x+y*r.y+z*r.z;
    }

    vector(){}vector

    operator ^ (vector r)
    {
        return vector(y*r.z - z*r.y, z*r.x - x*r.z, x*r.y - y*r.x);
    }

    vector(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }

    vector operator ! (void)
    {
        return *this*(1/sqrt(*this%*this));
    }
};

int G[9] = {
    65024, 33345, 139841, 148041, 164437, 197219, 164417, 147968, 249728
};

float R(void)
{
    return(float)rand()/RAND_MAX;
}

int T(vector o, vector d, float &t, vector &n)
{
    t=1e9;
    int m=0;
    float p=-o.z/d.z;

    if(0.01 < p)
        t = p, n = vector(0,0,1), m=1;

    for(int k=19; k--;)
        for(int j=9; j--;)
            if(G[j]&1<<k)
            {
                    vector p = o + vector(-k,0,-j-4);
                    float b = p%d, c=p%p-1, q=b*b-c;

                    if(q > 0)
                    {
                        float s = -b - sqrt(q);

                        if(s < t && s > 0.01)
                            t=s, n = !(p+d*t),m=2;

                    }
            }

    return m;
}

vector S(vector o, vector d)
{
    float t;
    vector n;
    int m=T(o,d,t,n);

    if (!m)
        return vector(0.7, 0.6, 1) * pow(1-d.z, 4);

    vector h = o+d*t, l=!(vector(9 + R(),9 + R(), 16) +h*-1);
    vector r = d + n*(n%d*-2);

    float b = l%n;

    if (b < 0 || T(h,l,t,n))
        b=0;

    float p=pow(l%r*(b>0),99);

    if (m&1)
    {
        h=h*.2;

        if ((int)(ceil(h.x)+ceil(h.y)) & 1)
            return vector(3,1,1);
        else
            return vector(3,3,3)*(b * 0.2+.1);
    }

    return vector(p,p,p) + S(h,r) * 0.5;;
}

int main(void)
{
    printf("P6 512 512 255 ");
    vector g = !vector(-6,-16,0);
    vector a = !(vector(0,0,1)^g)*.002;
    vector b = !(g^a)*.002;
    vector c = (a+b)*-256+g;
    for(int y=512;y--;)
        for(int x=512;x--;)
        {
            vector p(13,13,13);

            for(int r=64; r--;)
            {
                vector t=a*(R()-.5)*99+b*(R()-.5)*99;

                p=S(vector(17,16,8)+t,!(t*-1+(a*(R()+x)+b*(y+R())+c)*16))*3.5+p;
            }
            printf("%c%c%c", (int)p.x, (int)p.y, (int)p.z);
        }
}

