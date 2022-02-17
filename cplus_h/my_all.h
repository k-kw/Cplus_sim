#pragma once
#include "complex_array_class.h"
//ヘッダ内に直接,外部結合を持った関数を定義してはいけない。宣言して、他のソースファイルで定義すべき
//内部結合を持つインライン関数等はヘッダで定義しないといけない。

//inline
//最大値
template <class Type>
inline Type get_max(Type* data, int size)
{
	Type max = data[0];
	for (int i = 0; i < size; i++) {
		if (max < data[i]) {
			max = data[i];
		}
	}

	return max;
}

//最小値
template <class Type>
inline Type get_min(Type* data, int size)
{
	Type min = data[0];
	for (int i = 0; i < size; i++) {
		if (min > data[i]) {
			min = data[i];
		}
	}

	return min;
}

//最大値で正規化
template <class Type>
inline void norm_max(Type* data_in, int size, double* data_out)
{
	Type max;
	max = get_max(data_in, size);

	for (int i = 0; i < size; i++) {
		data_out[i] = (double)((double)data_in[i] / (double)max);
	}

}

//最大値と最小値で正規化(確実に0~1)
template <class Type>
inline void norm_max_min(Type* data_in, int size, double* data_out)
{
	Type max;
	max = get_max(data_in, size);
	Type min;
	min = get_min(data_in, size);

	double* tmp;
	tmp = new double[size];

	for (int i = 0; i < size; i++) {
		tmp[i] = (double)((data_in[i] - min) / (max - min));
	}

	for (int i = 0; i < size; i++) {
		data_out[i] = tmp[i];
	}


	delete[]tmp;
}

//正規化後,n階調化,int型出力
template <typename Type>
inline void norm_reso_n(Type* data_in, int* data_out, int n, int size)
{
	double* tmp;
	tmp = new double[size];
	norm_max_min(data_in, size, tmp);

	for (int i = 0; i < size; i++) {
		data_out[i] = (int)(round(tmp[i] * n));
	}

	delete[]tmp;
}


//intデータをunsigned charに変換後、格納
//0~255のデータに限る
inline void to_uch(int* data_in, int size, unsigned char* data_img)
{
	for (int i = 0; i < size; i++) {
		data_img[i] = (unsigned char)data_in[i];
	}
}


//1次元画像の上下反転
template <class Type>
inline void invert_img(Type* data_in, Type* data_out, int im_x, int im_y)
{
	Type* tmp;
	tmp = new Type[im_x * im_y];

	for (int i = 0; i < im_y; i++) {
		for (int j = 0; j < im_x; j++) {
			tmp[i * im_x + j] = data_in[((im_y - 1) - i) * im_x + j];

		}
	}

	for (int i = 0; i < im_y; i++) {
		for (int j = 0; j < im_x; j++) {
			data_out[i * im_x + j] = tmp[i * im_x + j];

		}
	}



	delete[]tmp;
}


//中心1列取り出す
template <class Type>
inline void mid_line(Type* data_in, int sx, int sy, Type* data_out) {
	for (int i = 0; i < sx; i++) {
		data_out[i] = data_in[(sy / 2) * sx + i];
	}
}

//
////実行者に強制二択
////cfがに値が入る、oneは選択肢１の名称、the_otherは２の名称、valueは選択肢を選ぶとき入力させる数字
//void forced_two_select(int* cf, char one[], char the_other[], int one_value, int other_value) {
//
//	do {
//		printf("\n%s：%dを入力\t%s：%dを入力\n", one, one_value, the_other, other_value);
//		printf("Press 0 or 1 and enterkey : "); (void)scanf("%d", cf);
//	} while (*cf != one_value && *cf != other_value);
//}
//
////実行者に強制二択
////返却値に値が入る、oneは選択肢１の名称、the_otherは２の名称、valueは選択肢を選ぶとき入力させる数字
//int forced_two_select_ver2(char title[], char one[], char the_other[], int one_value, int other_value) {
//	int res = 0;
//	do {
//		printf("\n%s\n%s：%dを入力\t%s：%dを入力\n", title, one, one_value, the_other, other_value);
//		printf("Press 0 or 1 and enterkey : "); (void)scanf("%d", &res);
//	} while (res != one_value && res != other_value);
//	return res;











////FFT
//
////FFT関数ver2
//void fft_2D_ver2(double* Re_out, double* Im_out, int y, int x, double* Re_in, double* Im_in);
//
////FFT関数
//void fft_2D(double* Re_out, double* Im_out, int y, int x, double* Re_in, double* Im_in);
//
////IFFT関数
//void ifft_2D(double* Re_out, double* Im_out, int y, int x, double* Re_in, double* Im_in);


////complex_array
////振幅もしくは実部配列を正規化後、位相情報へ変換
//void to_phase(double* Re, double* Im, int size, double* orig);
//
//
////複素振幅計算関数
//void power_complex(double* pow, int size, double* Re, double* Im);
//
////複素振幅の2乗計算関数
//void power_2_complex(double* pow, int size, double* Re, double* Im);
//
////複素数配列乗算関数
//void mul_complex(int size, double* Re_in1, double* Im_in1, double* Re_in2, double* Im_in2, double* Re_out, double* Im_out);
//
//2D画像の0pad関数(縦横それぞれ２倍にして0埋め、inとoutはサイズ違う)


inline void Opad(double* img_out, int in_x, int in_y, double* img_in) {
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
inline void elim_0(double* img_out, int in_x, int in_y, double* img_in) {
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


//Diiffrential_calculation
//
////角スペクトル法のHを直接計算する関数、xとyは計算自体画像サイズの2倍
//void H_kaku(double* ReH, double* ImH, double lam, double z, double d, int x, int y);
//
//////角スペクトル法(入出力サイズは全てx・y、0埋めされていない画像データを入力、一番左はifft後0pad部を取り除いたものを出力、その右はifft→振幅計算→正規化→0pad排除したものを出力)
////void kaku(double* Re, double* Im, double* POWER, int x, int y, double lam, double z, double d, double* ReG, double* ImG);
////
//////角スペクトル法(入出力サイズは全てx・y、0埋めされていない画像データを入力、一番左はifft後0pad部を取り除いたものを出力、その右はifft→振幅計算→正規化→0pad排除したものを出力)
////void kaku_2(double* Re, double* Im, double* POWER, int x, int y, double lam, double z, double d, double* ReG, double* ImG);
////
//////角スペクトル法ver3(振幅を出力しない)
////void kaku_3(double* Re, double* Im, int x, int y, double lam, double z, double d, double* ReG, double* ImG);
//
////角スペクトル法ver4(H配列を引数として扱う)
//void kaku_4(double* Re, double* Im, int x, int y, double* ReG, double* ImG, double* ReH, double* ImH);
//
////多重定義
//
////角スペクトル法のHを複素配列クラスで作成、xとyは計算自体画像サイズの2倍
//void H__kaku(My_Complex_Array* H, double lam, double z, double d, int x, int y);
//
//
////角スペクトル法ver4を複素配列クラスで計算
//void kaku_4(My_Complex_Array*out, int x, int y, );



////フレネル回折のhを計算
//void fresnel_h(double* Re, double* Im, double lam, double z, double d, int x, int y);





////Lens and Diffuser
//
////レンズの位相変換作用近似なし
//void lens_non_approx(double* Relens, double* Imlens, int x, int y, double d, double lam, double f);
//
////レンズの位相変換配列作成関数
//void lens(double* Relens, double* Imlens, int x, int y, double d, double lam, double f);
//
////シリンドリカルレンズ,縦方向のみ集光
//void cylin_lens_y(double* Relens, double* Imlens, int x, int y, double d, double lam, double f);
//
////シリンドリカルレンズ,横方向のみ集光
//void cylin_lens_x(double* Relens, double* Imlens, int x, int y, double d, double lam, double f);
//
////シリンドリカルレンズ,横方向のみ拡散
//void cylin_lens_x_concave(double* Relens, double* Imlens, int x, int y, double d, double lam, double f);
//
////ランダム位相拡散板配列関数
//void diffusionplate_random(double* Re, double* Im, int x, int y);
//
////レンズ拡散板配列関数(正方形の画像のみ)
//void diffusionplate_lens(double* Re, double* Im, int im_size, int lens_size, double d, double lam, double f, bool approx);
//
////レンズ拡散板配列関数(正方形画像以外もOK)
//void diffusionplate_lens_ver2(double* Re, double* Im, int im_size_x, int im_size_y, int lens_size, double d, double lam, double f, bool approx);







