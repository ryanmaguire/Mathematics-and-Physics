#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <fftw3.h>

/*  Define the Boolean type as a single unsigned byte.                        */
typedef unsigned char bool;

/*  Define True and False.                                                    */
#define True 1
#define False 0

/*  Structure that contains all of the necessary data.                        */
typedef struct _graddesfinobj {
    complex double *T_in;
    double *rho_km_vals;
    double *F_km_vals;
    double *phi_rad_vals;
    double *kd_vals;
    double *B_rad_vals;
    double *D_km_vals;
    double *w_km_vals;
    double ecc;
    double peri;
    double perturb[5];
    long start;
    long n_used;
    bool use_norm;
    bool use_fwd;
    unsigned char wtype;
    unsigned char order;
    unsigned char interp;
    unsigned char status;
    complex double *T_out;
} GradDesFin;

// Void function that takes in a pointer and changes it to a vector of ones.
void ones(double *array, long length){
    long i;
    for (i=0; i<length; ++i) array[i] = 1.0;
}

// Functions used to approximate partial derivatives.
double PartialX(double *f, long i, long j, long n){return f[i*n+j]-f[i*n+j-1];}
double PartialX(double *f, long i, long j, long n){return f[i*n+j]-f[(i-1)*n+j];}

fftw_complex *Kern(long n, double s){
    long i, j, n2, a1, a2;
    fftw_complex *out;
    fftw_plan p;
	n2 = n/2;

    double s_factor1 = 0.5/(s*s);
    double s_factor2 = s_factor1/M_PI;

	double *M = (double *)malloc(sizeof(double)*n2*n2);

	for (i=0; i<n2; ++i){
        a1 = i-n2;
        a1 = -a1*a1;
		for (j=0; j<n2; ++j){
            a2 = j-n2;
            a2 = -a2*a2;
			M[i*n2+j] = s_factor2*exp((a1+a2)*s_factor1);
        }
    }

    p = fftw_plan_dft_r2c_2d(n2, n2, M, out, FFTW_ESTIMATE);
	fftw_execute(p);
    fftw_destroy(p);
    free(M);
	return out;
}

double RCPR_Phi_Func(double **f, long i, long j, double del, double b){
    double out, dx2, dy2;
    dx2  = PartialX(f, i, j);
    dx2 *= dx2;
    dy2  = PartialY(f, i, j);
    dy2 *= dy2;

    out  = del*b;
    out *= out;
    return sqrtl(out + dx2+dy2);
}

double PhiFunc(double **f, long i, long j, double del, double b){
	return 1.0/RCPR_Phi_Func(f, i, j, del, b);
}

double J(double **f, long n, double del, double b){
	double out = 0.0;
    double add;
    int i, j;

	for (i=2; i<n; ++i){
		for (j=2; j<n; ++j){
			out = out + RCPR_Phi_Func(f, i, j, del, b);
        }
    }
	return del*out;
}

/*
function GradDesFin(d,s,a,b,w,t,e)

	n = length(d[:,1])
	del = 1/n
	f = d 

	function Kern(n,s)
		n2 = div(n,2)
		M = zeros(n,n)
		for i = 1 : n
			for j = 1 : n
				M[i,j] = (1/(s^2*2*pi))*exp(-((i-n2-1)^2+(j-n2-1)^2)/(2*s^2))
			end
		end
		
		n2 = div(size(M,1),2)
		ker = [M[n2+1:end,n2+1:end] M[n2+1:end,1:n2]; M[1:n2,n2+1:end] M[1:n2,1:n2]]
		kerfft = fft(ker)
		return kerfft
	end

	kerfft = Kern(n,s)
	
	function K(f)
		
		tmp = fft(f).*kerfft
		F = real(ifft(tmp))
		
		return F
		
	end
	
	function J(f)
		out = 0
		for i = 2 : n
			for j = 2 : n
				add = (Dx(f,i,j))^2+(Dy(f,i,j))^2+del^2*b^2
				add = sqrt(add)
				out = out + add
			end
		end
		out = del*out
		return out
	end

	function T(f)
		return (1/2)*norm(d-K(f),2)^2 + a*J(f)
	end
	
	function dv(f)
		v = zeros(n-1)
		for j = 1 : n-1
			v[j] = Phi(f,j+1,2)
		end
		for k = 3 : n 
			add = zeros(n-1)
			for j = 1 : n-1 
				add[j] = Phi(f,j+1,k)
			end
			v = [v;add]
		end
		out = spdiagm(1=>v)
		return out
	end
	
	function dJ(f)
		td = ones(n-1)
		A = spdiagm(0 => -td,1 => td)
		A = A[1:end-1,:]
		Itrunc = spdiagm(1=>ones(n-1))
		Itrunc = Itrunc[1:end-1,:]
		DX = kron(Itrunc,A)
		DY = kron(A,Itrunc)
		Mid = dv(f)
		Mid = Mid[1:end-1,2:end]
		out = transpose(DX)*Mid*DX*f[:]
		out = out + transpose(DY)*Mid*DY*f[:]
		out = del*out
		return out
	end
	
	function dT(f)
		tmp = K(d-K(f))
		tmp1 = tmp[:]
		return tmp1 + a*dJ(f)
	end
	
	lim = 0
	while ((dot(dT(f),dT(f)) >= e)&&(lim < 2000))
		p = 0.2
		dTf = dT(f)
		dTf1 = reshape(dTf,n,n)
		Tf = T(f)
		bound = dot(dTf,dTf)
		lim = lim + 1
		println(lim)
		while (  T(f-p*dTf1)  -  Tf  )/p > -w*bound
			p = t*p 
		end
		f = f - p*dTf1
	end
	return f 
end

*/

int main(){
    puts("Hi!");
    return 0;
}
