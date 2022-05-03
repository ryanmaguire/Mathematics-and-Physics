
#include <cmath>
#include <cstdlib> 
#include <cstdio>

/*  A simple structure for dealing with vectors. Vectors are treated as rays  *
 *  of light moving under the influence of the gravity of a black hole.       */
struct tmpl_simple_vector {

    /*  A vector will be defined by it's Euclidean components, x, y, z.       */
    double x, y, z;

    /*  Empty constructor. Simply return.                                     */
    tmpl_simple_vector(void)
    {
        return;
    }

    /*  Simple method for creating a vector. Simply set the x, y, and z parts *
     *  to the values a, b, and c, respectively.                              */
    tmpl_simple_vector(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    /*  This operator represents vector addition.                             */
    tmpl_simple_vector operator + (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x + r.x, y + r.y, z + r.z);
    }

    /*  Vector subtraction.                                                   */
    tmpl_simple_vector operator - (tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x - r.x, y - r.y, z - r.z);
    }

    /*  And here we have scalar multiplication.                               */
    tmpl_simple_vector operator * (double r)
    {
        return tmpl_simple_vector(x*r, y*r, z*r);
    }

    /*  Euclidean dot product.                                                */
    double dot(tmpl_simple_vector r)
    {
        return x*r.x + y*r.y + z*r.z;
    }

    /*  Component-wise multiplication.                                        */
    tmpl_simple_vector multiply(tmpl_simple_vector r)
    {
        return tmpl_simple_vector(x*r.x, y*r.y, z*r.y);
    }

    /*  Cross product.                                                        */
    tmpl_simple_vector cross(tmpl_simple_vector r)
    {
        return tmpl_simple_vector(y*r.z - z*r.y, z*r.x - x*r.z, x*r.y - y*r.x);
    }

    /*  A method for computing the Euclidean norm of a vector.                */
    double norm(void)
    {
        return std::sqrt(x*x + y*y + z*z);
    }

    /*  A method for computing the square of the Euclidean norm of a vector.  *
     *  This is computationally useful since it avoids redundant square roots.*/
    double normsq(void)
    {
        return x*x + y*y + z*z;
    }
};
/*  End of definition of tmpl_simple_vector.                                  */

struct tmpl_ray {
    tmpl_simple_vector origin, direction;
    
    tmpl_ray(void)
    {
        return;
    }
    
    tmpl_simple_ray (tmpl_simple_vector o, tmpl_simple_vector d)
    {
        origin = o;
        direction = d;
    }
};

enum Refl_t {DIFF, SPEC, REFR};

 
struct tmpl_sphere {
    double radius;
    tmpl_simple_vector center;
    tmpl_simple_vector emission, color; 
    Refl_t refl;

    tmpl_sphere(void)
    {
        return;
    }
    
    tmpl_sphere(double r, tmpl_simple_vector c,
                tmpl_simple_vector e, tmpl_simple_vector c)
    {
        radius = r;
        center = c;
        emission = e;
        color = c;
    }

   Sphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_t refl_): 
     rad(rad_), p(p_), e(e_), c(c_), refl(refl_) {} 
   double intersect(const Ray &r) const { // returns distance, 0 if nohit 
     Vec op = p-r.o; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0 
     double t, eps=1e-4, b=op.dot(r.d), det=b*b-op.dot(op)+rad*rad; 
     if (det<0) return 0; else det=sqrt(det); 
     return (t=b-det)>eps ? t : ((t=b+det)>eps ? t : 0); 
   } 
 }; 
 Sphere spheres[] = {//Scene: radius, position, emission, color, material 
   Sphere(1e5, Vec( 1e5+1,40.8,81.6), Vec(),Vec(.75,.25,.25),DIFF),//Left 
   Sphere(1e5, Vec(-1e5+99,40.8,81.6),Vec(),Vec(.25,.25,.75),DIFF),//Rght 
   Sphere(1e5, Vec(50,40.8, 1e5),     Vec(),Vec(.75,.75,.75),DIFF),//Back 
   Sphere(1e5, Vec(50,40.8,-1e5+170), Vec(),Vec(),           DIFF),//Frnt 
   Sphere(1e5, Vec(50, 1e5, 81.6),    Vec(),Vec(.75,.75,.75),DIFF),//Botm 
   Sphere(1e5, Vec(50,-1e5+81.6,81.6),Vec(),Vec(.75,.75,.75),DIFF),//Top 
   Sphere(16.5,Vec(27,16.5,47),       Vec(),Vec(1,1,1)*.999, SPEC),//Mirr 
   Sphere(16.5,Vec(73,16.5,78),       Vec(),Vec(1,1,1)*.999, REFR),//Glas 
   Sphere(600, Vec(50,681.6-.27,81.6),Vec(12,12,12),  Vec(), DIFF) //Lite 
 }; 
 inline double clamp(double x){ return x<0 ? 0 : x>1 ? 1 : x; } 
 inline int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); } 
 inline bool intersect(const Ray &r, double &t, int &id){ 
   double n=sizeof(spheres)/sizeof(Sphere), d, inf=t=1e20; 
   for(int i=int(n);i--;) if((d=spheres[i].intersect(r))&&d<t){t=d;id=i;} 
   return t<inf; 
 } 
 Vec radiance(const Ray &r, int depth, unsigned short *Xi){ 
   double t;                               // distance to intersection 
   int id=0;                               // id of intersected object 
   if (!intersect(r, t, id)) return Vec(); // if miss, return black 
   const Sphere &obj = spheres[id];        // the hit object 
   Vec x=r.o+r.d*t, n=(x-obj.p).norm(), nl=n.dot(r.d)<0?n:n*-1, f=obj.c; 
   double p = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z; // max refl 
   if (++depth>5) if (erand48(Xi)<p) f=f*(1/p); else return obj.e; //R.R. 
   if (obj.refl == DIFF){                  // Ideal DIFFUSE reflection 
     double r1=2*M_PI*erand48(Xi), r2=erand48(Xi), r2s=sqrt(r2); 
     Vec w=nl, u=((fabs(w.x)>.1?Vec(0,1):Vec(1))%w).norm(), v=w%u; 
     Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm(); 
     return obj.e + f.mult(radiance(Ray(x,d),depth,Xi)); 
   } else if (obj.refl == SPEC)            // Ideal SPECULAR reflection 
     return obj.e + f.mult(radiance(Ray(x,r.d-n*2*n.dot(r.d)),depth,Xi)); 
   Ray reflRay(x, r.d-n*2*n.dot(r.d));     // Ideal dielectric REFRACTION 
   bool into = n.dot(nl)>0;                // Ray from outside going in? 
   double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.d.dot(nl), cos2t; 
   if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)    // Total internal reflection 
     return obj.e + f.mult(radiance(reflRay,depth,Xi)); 
   Vec tdir = (r.d*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm(); 
   double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.dot(n)); 
   double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P); 
   return obj.e + f.mult(depth>2 ? (erand48(Xi)<P ?   // Russian roulette 
     radiance(reflRay,depth,Xi)*RP:radiance(Ray(x,tdir),depth,Xi)*TP) : 
     radiance(reflRay,depth,Xi)*Re+radiance(Ray(x,tdir),depth,Xi)*Tr); 
 } 
 int main(int argc, char *argv[]){ 
   int w=1024, h=768, samps = argc==2 ? atoi(argv[1])/4 : 1; // # samples 
   Ray cam(Vec(50,52,295.6), Vec(0,-0.042612,-1).norm()); // cam pos, dir 
   Vec cx=Vec(w*.5135/h), cy=(cx%cam.d).norm()*.5135, r, *c=new Vec[w*h]; 
 #pragma omp parallel for schedule(dynamic, 1) private(r)       // OpenMP 
   for (int y=0; y<h; y++){                       // Loop over image rows 
     fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1)); 
     for (unsigned short x=0, Xi[3]={0, 0, y*y*y}; x<w; x++)   // Loop cols 
       for (int sy=0, i=(h-y-1)*w+x; sy<2; sy++)     // 2x2 subpixel rows 
         for (int sx=0; sx<2; sx++, r=Vec()){        // 2x2 subpixel cols 
           for (int s=0; s<samps; s++){ 
             double r1=2*erand48(Xi), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1); 
             double r2=2*erand48(Xi), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2); 
             Vec d = cx*( ( (sx+.5 + dx)/2 + x)/w - .5) + 
                     cy*( ( (sy+.5 + dy)/2 + y)/h - .5) + cam.d; 
             r = r + radiance(Ray(cam.o+d*140,d.norm()),0,Xi)*(1./samps); 
           } // Camera rays are pushed ^^^^^ forward to start in interior 
           c[i] = c[i] + Vec(clamp(r.x),clamp(r.y),clamp(r.z))*.25; 
         } 
   } 
   FILE *f = fopen("image.ppm", "w");         // Write image to PPM file. 
   fprintf(f, "P3\n%d %d\n%d\n", w, h, 255); 
   for (int i=0; i<w*h; i++) 
     fprintf(f,"%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z)); 
 } 

