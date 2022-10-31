#include <stdio.h>
#include <math.h>
#include "cmplx.h"

// c = a / b;
void cmplx_div(cmplx_t a, cmplx_t b, cmplx_t c){
	c[0] = (a[0]*b[0] + a[1]*b[1]) / (b[0]*b[0] + b[1]*b[1]);
	c[1] = (a[1]*b[0] - a[0]*b[1]) / (b[0]*b[0] + b[1]*b[1]);
	return;
}


// c = a * b;
void cmplx_mul(cmplx_t a, cmplx_t b, cmplx_t c){
	c[0] = (a[0]*b[0] - a[1]*b[1]);
	c[1] = (a[0]*b[1] - a[1]*b[0]);
	return;
}


// returns |a|
double cmplx_mag(cmplx_t a){
	return (double) sqrtf(a[0]*a[0] + a[1]*a[1]);
}


// returns phase in radians of a 
double cmplx_phs(cmplx_t a){
	if(a[1] == 0) return a[0] >= 0 ? 0 : M_PI;
	if(a[0] == 0) return a[1] >= 0 ? M_PI/2 : 3*M_PI/2;
	double phs = (double) atanf(a[1]/a[0]);
	if(a[0] < 0 && a[1] > 0) phs += M_PI;
	if(a[0] < 0 && a[1] < 0) phs += M_PI;
	if(a[0] > 0 && a[1] < 0) phs += M_PI*2;
	return phs;
}


// returns real part of mag/_phs
double cmplx_real(double mag, double phs){
	return mag * cos(phs);
}


// returns imaginary part of mag/_phs
double cmplx_imag(double mag, double phs){
	return mag * sin(phs);
}


// returns dft transformation of complex input signal
void cmplx_dft(cmplx_t *input, cmplx_t *output, int N){
	// Xk = sum[0->N-1](xn * e^-i*2pikn/N)
	for(int k = 0; k < N; k++){
		*(*output + k*2 + 0) = 0.f;
		*(*output + k*2 + 1) = 0.f;
		for(int n = 0; n < N; n++){
			cmplx_t num;
			cmplx_t num2;
			num[0] = cos(2*M_PI/N * k * n);
			num[1] = -sin(2*M_PI/N * k * n);
			cmplx_mul(*input + 2*n, num, num2);
			*(*output + k*2 + 0) += num2[0];
			*(*output + k*2 + 1) += num2[1];
		}
	}
	return;
}


// returns inverse dft transformation of complex input signal
void cmplx_idft(cmplx_t *input, cmplx_t *output, int N){
	// x[n] = 1/N * sum[0->N-1](Xk * e^i*2pikn/N)
	for(int n = 0; n < N; n++){
		*(*output + n*2 + 0) = 0.f;
		*(*output + n*2 + 1) = 0.f;
		for(int k = 0; k < N; k++){
			cmplx_t num;
			cmplx_t num2;
			num[0] = cos(2*M_PI/N * k * n);
			num[1] = sin(2*M_PI/N * k * n);
			cmplx_mul(*input + 2*k, num, num2);
			*(*output + n*2 + 0) += num2[0] / N;
			*(*output + n*2 + 1) += num2[1] / N;
		}
	}
	return;
}