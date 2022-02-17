#define _USE_MATH_DEFINES
#include <cmath>
#include <fftw3.h>
#include <stddef.h>
#include "my_all.h"

#pragma comment(lib, "libfftw3-3.lib")
#pragma comment(lib, "libfftw3f-3.lib")
#pragma comment(lib, "libfftw3l-3.lib")
#pragma warning(disable:4996)

//FFTä÷êîver2
//ÉÅÉÇÉäÇÃämï€Ç≈(size_t)Ç…ïœä∑
void fft_2D_ver2(double* Re_out, double* Im_out, int y, int x, double* Re_in, double* Im_in) {
	fftw_complex* in, * out;
	fftw_plan p;
	in = (fftw_complex*)fftw_malloc((size_t)y * (size_t)x * sizeof(fftw_complex));
	out = (fftw_complex*)fftw_malloc((size_t)y * (size_t)x * sizeof(fftw_complex));
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			in[i * x + j][0] = Re_in[i * x + j];
			in[i * x + j][1] = Im_in[i * x + j];
		}
	}
	p = fftw_plan_dft_2d(y, x, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			Re_out[i * x + j] = out[i * x + j][0];
			Im_out[i * x + j] = out[i * x + j][1];
		}
	}
	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
};

//FFTä÷êî
void fft_2D(double* Re_out, double* Im_out, int y, int x, double* Re_in, double* Im_in) {
	fftw_complex* in, * out;
	fftw_plan p;
	in = (fftw_complex*)fftw_malloc(y * x * sizeof(fftw_complex));
	out = (fftw_complex*)fftw_malloc(y * x * sizeof(fftw_complex));
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			in[i * x + j][0] = Re_in[i * x + j];
			in[i * x + j][1] = Im_in[i * x + j];
		}
	}
	p = fftw_plan_dft_2d(y, x, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			Re_out[i * x + j] = out[i * x + j][0];
			Im_out[i * x + j] = out[i * x + j][1];
		}
	}
	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
};

//IFFTä÷êî
void ifft_2D(double* Re_out, double* Im_out, int y, int x, double* Re_in, double* Im_in) {
	fftw_complex* in, * out;
	fftw_plan p;
	in = (fftw_complex*)fftw_malloc((size_t)y * (size_t)x * sizeof(fftw_complex));
	out = (fftw_complex*)fftw_malloc((size_t)y * (size_t)x * sizeof(fftw_complex));
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			in[i * x + j][0] = Re_in[i * x + j];
			in[i * x + j][1] = Im_in[i * x + j];
		}
	}
	p = fftw_plan_dft_2d(y, x, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			Re_out[i * x + j] = out[i * x + j][0];
			Im_out[i * x + j] = out[i * x + j][1];
		}
	}
	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
};

