#define _USE_MATH_DEFINES
#include <cmath>
#include "my_all.h"

#define sqr(x) ((x)*(x))

//振幅もしくは実部配列を256で割って、位相情報へ変換
void to256_phase(double* Re, double* Im, int size, double* orig) {

	//256で割って位相情報へ
	for (int i = 0; i < size; i++) {
		Re[i] = cos(2 * M_PI * orig[i] / 255);
		Im[i] = sin(2 * M_PI * orig[i] / 255);

	}
}


//振幅もしくは実部配列を正規化後、位相情報へ変換
void to_phase(double* Re, double* Im, int size, double* orig) {
	double* tmp;
	tmp = new double[size];

	//正規化
	norm_max_min<double>(orig, size, tmp);

	//位相情報へ
	for (int i = 0; i < size; i++) {
		Re[i] = cos(2 * M_PI * tmp[i]);
		Im[i] = sin(2 * M_PI * tmp[i]);

	}
	delete[]tmp;
}

//複素振幅計算関数
void power_complex(double* pow, int size, double* Re, double* Im) {
	double* tmp;

	tmp = new double[size];

	for (int i = 0; i < size; i++) {
		tmp[i] = sqrt(sqr(Re[i]) + sqr(Im[i]));
	}

	for (int i = 0; i < size; i++) {
		pow[i] = tmp[i];
	}

	delete[]tmp;
}

//複素振幅の2乗計算関数
void power_2_complex(double* pow, int size, double* Re, double* Im) {
	double* tmp;

	tmp = new double[size];

	for (int i = 0; i < size; i++) {
		tmp[i] = sqr(Re[i]) + sqr(Im[i]);
	}

	for (int i = 0; i < size; i++) {
		pow[i] = tmp[i];
	}

	delete[]tmp;
}

//複素数配列乗算関数
void mul_complex(int size, double* Re_in1, double* Im_in1, double* Re_in2, double* Im_in2, double* Re_out, double* Im_out) {
	double* Retmp, * Imtmp;
	Retmp = new double[size];
	Imtmp = new double[size];

	for (int i = 0; i < size; i++) {
		Retmp[i] = Re_in1[i] * Re_in2[i] - Im_in1[i] * Im_in2[i];
		Imtmp[i] = Re_in1[i] * Im_in2[i] + Im_in1[i] * Re_in2[i];
	}

	for (int i = 0; i < size; i++) {
		Re_out[i] = Retmp[i];
		Im_out[i] = Imtmp[i];
	}
	delete[]Retmp;
	delete[]Imtmp;
};