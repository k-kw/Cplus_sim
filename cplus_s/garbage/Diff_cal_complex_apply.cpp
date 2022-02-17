#define _USE_MATH_DEFINES
#include <cmath>
#include "my_all.h"
#include "Fft_class.h"
#include "complex_array_class.h"

#pragma warning(disable:4996)

#define sqr(x) ((x)*(x))



//角スペクトル法のHを直接計算する関数
void H_kaku(double* ReH, double* ImH, double lam, double z, double d, int x, int y) {
	double* Retmp, * Imtmp;
	Retmp = new double[x * y];
	Imtmp = new double[x * y];
	double u = 1 / ((double)x * d), v = 1 / ((double)y * d);
	//H計算
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			Retmp[i * x + j] = cos(2 * M_PI * z * sqrt(sqr(1 / lam) - sqr(u * ((double)j - x / 2)) - sqr(v * ((double)i - y / 2))));
			Imtmp[i * x + j] = sin(2 * M_PI * z * sqrt(sqr(1 / lam) - sqr(u * ((double)j - x / 2)) - sqr(v * ((double)i - y / 2))));
		}
	}
	//Hシフト
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (j < x / 2 && i < y / 2) {
				ReH[i * x + j] = Retmp[(i + y / 2) * x + (j + x / 2)];
				ReH[(i + y / 2) * x + (j + x / 2)] = Retmp[i * x + j];
				ImH[i * x + j] = Imtmp[(i + y / 2) * x + (j + x / 2)];
				ImH[(i + y / 2) * x + (j + x / 2)] = Imtmp[i * x + j];
			}
			else if (j >= x / 2 && i < y / 2) {
				ReH[i * x + j] = Retmp[(i + y / 2) * x + (j - x / 2)];
				ReH[(i + y / 2) * x + (j - x / 2)] = Retmp[i * x + j];
				ImH[i * x + j] = Imtmp[(i + y / 2) * x + (j - x / 2)];
				ImH[(i + y / 2) * x + (j - x / 2)] = Imtmp[i * x + j];
			}
		}
	}


	delete[]Retmp;
	delete[]Imtmp;
}

//角スペクトル法ver4(H配列を引数として扱う)
void kaku_4(double* Re, double* Im, int x, int y, double* ReG, double* ImG, double* ReH, double* ImH) {
	
	My_Complex_Array* com;
	com = new My_Complex_Array(4 * x * y);
	

	//入力された画像データを0埋めして倍の大きさの画像にする
	Opad(com->Re, x, y, ReG);
	Opad(com->Im, x, y, ImG);
	

	//Gをfft
	My_Fft* fft1;
	fft1 = new My_Fft(2 * x, 2 * y);
	fft1->data_to_in(com->Re, com->Im);
	fft1->fft2d();
	fft1->out_to_data(com->Re, com->Im);

	//GXHを計算
	com->mul_complex(ReH, ImH);


	//GXHをifft
	fft1->data_to_in(com->Re, com->Im);
	fft1->ifft2d();
	fft1->out_to_data(com->Re, com->Im);

	delete fft1;

	//出力１
	//0埋め部分を省く
	My_Complex_Array* com2;
	com2 = new My_Complex_Array(x * y);

	

	elim_0(com2->Re, 2 * x, 2 * y, com->Re);
	elim_0(com2->Im, 2 * x, 2 * y, com->Im);

	

	//出力１書き出し
	for (int i = 0; i < x * y; i++) {
		Re[i] = com2->Re[i];
		Im[i] = com2->Im[i];
	}

	delete com;
	delete com2;
	
}


