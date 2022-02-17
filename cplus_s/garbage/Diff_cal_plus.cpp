#define _USE_MATH_DEFINES
#include <cmath>
#include "my_all.h"
#include "Fft_class.h"

#pragma warning(disable:4996)

#define sqr(x) ((x)*(x))

//2D画像の0pad関数(縦横それぞれ２倍にして0埋め、inとoutはサイズ違う)
void Opad(double* img_out, int in_x, int in_y, double* img_in) {
	int x, y, X, Y;
	x = in_x;
	y = in_y;
	X = 2 * x;
	Y = 2 * y;

	double* img_tmp;
	img_tmp = new double[X * Y];

	for (int i = 0; i < X * Y; i++) {
		img_tmp[i] = 0;
	}

	//入力された画像データを０埋めして倍の大きさの画像にする
	for (int i = Y / 4; i < y + Y / 4; i++) {
		for (int j = X / 4; j < x + X / 4; j++) {
			img_tmp[i * X + j] = img_in[(i - Y / 4) * x + (j - X / 4)];
		}
	}

	for (int i = 0; i < X * Y; i++) {
		img_out[i] = img_tmp[i];
	}

	delete[]img_tmp;

}

//2D画像の0pad部分を取り除く関数(縦横それぞれ1/2倍にして真ん中を取得、inとoutはサイズ違う)
void elim_0(double* img_out, int in_x, int in_y, double* img_in) {
	int x, y, X, Y;
	X = in_x;
	Y = in_y;
	x = X / 2;
	y = Y / 2;

	double* tmp;
	tmp = new double[x * y];
	for (int i = 0; i < y * x; i++) {
		tmp[i] = 0;
	}

	for (int i = Y / 4; i < y + Y / 4; i++) {
		for (int j = X / 4; j < x + X / 4; j++) {
			tmp[(i - Y / 4) * x + (j - X / 4)] = img_in[i * X + j];
		}
	}

	for (int i = 0; i < x * y; i++) {
		img_out[i] = tmp[i];
	}

	delete[]tmp;
}



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
};
//
////角スペクトル法(入出力サイズは全てx・y、0埋めされていない画像データを入力、一番左はifft後0pad部を取り除いたものを出力、その右はifft→振幅計算→正規化→0pad排除したものを出力(基本使わない))
//void kaku(double* Re, double* Im, double* POWER, int x, int y, double lam, double z, double d, double* ReG, double* ImG) {
//	int X, Y;
//	X = 2 * x;
//	Y = 2 * y;
//
//	double* ReGtmp, * ImGtmp;
//	ReGtmp = new double[X * Y];
//	ImGtmp = new double[X * Y];
//
//	//入力された画像データを０埋めして倍の大きさの画像にする
//	Opad(ReGtmp, x, y, ReG);
//	Opad(ImGtmp, x, y, ImG);
//
//	//Gをfft
//	fft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//Hを直接計算
//	double* ReHtmp, * ImHtmp;
//	ReHtmp = new double[X * Y];
//	ImHtmp = new double[X * Y];
//
//	H_kaku(ReHtmp, ImHtmp, lam, z, d, X, Y);
//
//
//	//GXHを計算
//	mul_complex(Y * X, ReGtmp, ImGtmp, ReHtmp, ImHtmp, ReGtmp, ImGtmp);
//
//	//GXHをifft
//	ifft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//出力１
//	//0埋め部分を省く
//	double* Retmp, * Imtmp;
//	Retmp = new double[x * y];
//	Imtmp = new double[x * y];
//
//	elim_0(Retmp, X, Y, ReGtmp);
//	elim_0(Imtmp, X, Y, ImGtmp);
//
//	//出力１書き出し
//	for (int i = 0; i < x * y; i++) {
//		Re[i] = Retmp[i];
//		Im[i] = Imtmp[i];
//	}
//
//	//出力2
//	//振幅計算
//	power_complex(ReGtmp, X * Y, ReGtmp, ImGtmp);
//	//正規化
//	//normali_2(ReGtmp, X * Y, ReGtmp);
//	norm_max_min<double>(ReGtmp, X * Y, ReGtmp);
//	//0埋め部分を省く
//	double* Ptmp;
//	Ptmp = new double[x * y];
//	elim_0(Ptmp, X, Y, ReGtmp);
//
//	for (int i = 0; i < x * y; i++) {
//		POWER[i] = Ptmp[i];
//	}
//
//	delete[]ReGtmp;
//	delete[]ImGtmp;
//	delete[]ReHtmp;
//	delete[]ImHtmp;
//	delete[]Retmp;
//	delete[]Imtmp;
//	delete[]Ptmp;
//}
//
////角スペクトル法ver2(入出力サイズは全てx・y、0埋めされていない画像データを入力、一番左はifft後0pad部を取り除いたものを出力、その右はifft→0pad排除→振幅計算→正規化出力(基本使わない))
//void kaku_2(double* Re, double* Im, double* POWER, int x, int y, double lam, double z, double d, double* ReG, double* ImG) {
//	int X, Y;
//	X = 2 * x;
//	Y = 2 * y;
//
//	double* ReGtmp, * ImGtmp;
//	ReGtmp = new double[X * Y];
//	ImGtmp = new double[X * Y];
//
//	//入力された画像データを０埋めして倍の大きさの画像にする
//	Opad(ReGtmp, x, y, ReG);
//	Opad(ImGtmp, x, y, ImG);
//
//	//Gをfft
//	fft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//Hを直接計算
//	double* ReHtmp, * ImHtmp;
//	ReHtmp = new double[X * Y];
//	ImHtmp = new double[X * Y];
//
//	H_kaku(ReHtmp, ImHtmp, lam, z, d, X, Y);
//
//
//	//GXHを計算
//	mul_complex(Y * X, ReGtmp, ImGtmp, ReHtmp, ImHtmp, ReGtmp, ImGtmp);
//
//	//GXHをifft
//	ifft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//出力１
//	//0埋め部分を省く
//	double* Retmp, * Imtmp;
//	Retmp = new double[x * y];
//	Imtmp = new double[x * y];
//
//	elim_0(Retmp, X, Y, ReGtmp);
//	elim_0(Imtmp, X, Y, ImGtmp);
//
//	//出力１書き出し
//	for (int i = 0; i < x * y; i++) {
//		Re[i] = Retmp[i];
//		Im[i] = Imtmp[i];
//	}
//
//	//出力2
//	//振幅計算
//	power_complex(Retmp, x * y, Retmp, Imtmp);
//	//正規化
//	//normali_2(Retmp, x * y, Retmp);
//	norm_max_min<double>(Retmp, x * y, Retmp);
//
//	for (int i = 0; i < x * y; i++) {
//		POWER[i] = Retmp[i];
//	}
//
//	delete[]ReGtmp;
//	delete[]ImGtmp;
//	delete[]ReHtmp;
//	delete[]ImHtmp;
//	delete[]Retmp;
//	delete[]Imtmp;
//
//}
//
////角スペクトル法ver3(振幅を出力しない)
//void kaku_3(double* Re, double* Im, int x, int y, double lam, double z, double d, double* ReG, double* ImG) {
//	int X, Y;
//	X = 2 * x;
//	Y = 2 * y;
//
//	double* ReGtmp, * ImGtmp;
//	ReGtmp = new double[X * Y];
//	ImGtmp = new double[X * Y];
//
//	//入力された画像データを０埋めして倍の大きさの画像にする
//	Opad(ReGtmp, x, y, ReG);
//	Opad(ImGtmp, x, y, ImG);
//
//	//Gをfft
//	fft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//Hを直接計算
//	double* ReHtmp, * ImHtmp;
//	ReHtmp = new double[X * Y];
//	ImHtmp = new double[X * Y];
//
//	H_kaku(ReHtmp, ImHtmp, lam, z, d, X, Y);
//
//
//	//GXHを計算
//	mul_complex(Y * X, ReGtmp, ImGtmp, ReHtmp, ImHtmp, ReGtmp, ImGtmp);
//
//	//GXHをifft
//	ifft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//出力１
//	//0埋め部分を省く
//	double* Retmp, * Imtmp;
//	Retmp = new double[x * y];
//	Imtmp = new double[x * y];
//
//	elim_0(Retmp, X, Y, ReGtmp);
//	elim_0(Imtmp, X, Y, ImGtmp);
//
//	//出力１書き出し
//	for (int i = 0; i < x * y; i++) {
//		Re[i] = Retmp[i];
//		Im[i] = Imtmp[i];
//	}
//
//
//	delete[]ReGtmp;
//	delete[]ImGtmp;
//	delete[]ReHtmp;
//	delete[]ImHtmp;
//	delete[]Retmp;
//	delete[]Imtmp;
//}


//角スペクトル法ver4(H配列を引数として扱う)
void kaku_4(double* Re, double* Im, int x, int y, double lam, double d, double* ReG, double* ImG, double* ReH, double* ImH) {
	int X, Y;
	X = 2 * x;
	Y = 2 * y;

	double* ReGtmp, * ImGtmp;
	ReGtmp = new double[X * Y];
	ImGtmp = new double[X * Y];

	//入力された画像データを0埋めして倍の大きさの画像にする
	Opad(ReGtmp, x, y, ReG);
	Opad(ImGtmp, x, y, ImG);
	//fft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
	//fft_2D_ver2(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);

	//Gをfft
	My_Fft* fft1;
	fft1 = new My_Fft(X, Y);
	fft1->data_to_in(ReGtmp, ImGtmp);
	fft1->fft2d();
	fft1->out_to_data(ReGtmp, ImGtmp);

	//GXHを計算
	mul_complex(Y * X, ReGtmp, ImGtmp, ReH, ImH, ReGtmp, ImGtmp);

	//GXHをifft
	fft1->data_to_in(ReGtmp, ImGtmp);
	fft1->ifft2d();
	fft1->out_to_data(ReGtmp, ImGtmp);

	delete fft1;

	//ifft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);

	//出力１
	//0埋め部分を省く
	double* Retmp, * Imtmp;
	Retmp = new double[x * y];
	Imtmp = new double[x * y];

	elim_0(Retmp, X, Y, ReGtmp);
	elim_0(Imtmp, X, Y, ImGtmp);
	delete[]ReGtmp;
	delete[]ImGtmp;

	//出力１書き出し
	for (int i = 0; i < x * y; i++) {
		Re[i] = Retmp[i];
		Im[i] = Imtmp[i];
	}

	
	delete[]Retmp;
	delete[]Imtmp;
}