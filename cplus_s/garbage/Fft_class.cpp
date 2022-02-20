#define _USE_MATH_DEFINES
#include <cmath>
#include <fftw3.h>
#include <stddef.h>
#include "Fft_class.h"

//fftw3はDLLをプロジェクトのフォルダに置いて動的リンクライブラリ（暗黙的リンク）として
//.defがあるので明示的リンクも可？
#pragma comment(lib, "libfftw3-3.lib")
#pragma comment(lib, "libfftw3f-3.lib")
#pragma comment(lib, "libfftw3l-3.lib")

My_Fft::My_Fft(int sx, int sy)
{
	x = sx;
	y = sy;
	Re_in = new double[x * y];
	Im_in = new double[x * y];
	Re_out = new double[x * y];
	Im_out = new double[x * y];

}


void My_Fft::data_to_in(double* Re, double* Im)
{
	for (int i = 0; i < x * y; i++) {
		Re_in[i] = Re[i];
		Im_in[i] = Im[i];
	}
}


void My_Fft::out_to_data(double* Re, double* Im)
{
	for (int i = 0; i < x * y; i++) {
		Re[i] = Re_out[i];
		Im[i] = Im_out[i];
	}
}



void My_Fft::fft2d()
{
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

	//正規化
	for (int i = 0; i < y * x; i++) {
		out[i][0] /= (double)(y * x);
		out[i][1] /= (double)(y * x);

	}


	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			Re_out[i * x + j] = out[i * x + j][0];
			Im_out[i * x + j] = out[i * x + j][1];
		}
	}

	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
}


void My_Fft::ifft2d()
{
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
}



My_Fft::~My_Fft()
{
	delete[]Re_in;
	delete[]Im_in;
	delete[]Re_out;
	delete[]Im_out;

}