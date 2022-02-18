#pragma once

class My_Complex_Array
{
private:
	
public:
	//サイズ
	int s;
	//配列ポインタ
	double* Re;
	double* Im;

	//コンストラクタ
	My_Complex_Array(int s);
	//デストラクタ
	~My_Complex_Array();

	//配列に格納
	//多重定義
	void data_to_ReIm(double* Rein, double* Imin);
	void data_to_ReIm(int* Rein, int* Imin);
	void data_to_ReIm(unsigned char* Rein, unsigned char* Imin);
	void data_to_ReIm(double* Rein);
	void data_to_ReIm(int* Rein);
	void data_to_ReIm(unsigned char* Rein);


	//振幅出力
	void power(double* pow);
	
	//複素乗算多重定義
	//格納されている複素配列と指定した複素配列オブジェクトの乗算結果を、別の複素配列に格納
	void mul_complex(My_Complex_Array* opponent, My_Complex_Array* out);

	//格納されている複素配列と指定した複素配列オブジェクトの乗算結果を、このオブジェクトに格納
	void mul_complex(My_Complex_Array* opponent);

	//格納されている複素配列と指定した複素配列の乗算結果を、このオブジェクトに格納
	void mul_complex(double* Re2, double* Im2);


	//振幅(実部)情報inを正規化後、位相情報に変換
	void to_phase(double* in);

	//振幅(実部)情報inを255で割って、位相情報に変換
	void to256_phase(double* in);


	//0埋めして拡大、ins = inx * iny、outx > inx、outy > iny
	void zeropad(My_Complex_Array* out, int outx, int outy, int inx, int iny);

	//中心を取り出して縮小、ins = inx * iny、outx < inx、outy < iny
	void extract_center(My_Complex_Array* out, int outx, int outy, int inx, int iny);

};


//複素配列クラスを継承した２次元複素配列クラス

class My_ComArray_2D : public My_Complex_Array
{
private:

public:
	//縦横 (s = x * y)
	int x, y;

	//コンストラクタ
	My_ComArray_2D(int s, int x, int y) :My_Complex_Array(s), x(x), y(y) {};

	//デストラクタは基底クラスのものを自動で使える

	//0埋めして拡大、ins = inx * iny、outx > inx、outy > iny
	void zeropad(My_ComArray_2D* out);

	//中心を取り出して縮小、ins = inx * iny、outx < inx、outy < iny
	void extract_center(My_ComArray_2D* out);


	//角スペクトル法のHを格納、画像の縦横倍の大きさで用意
	void H_kaku(double lam, double z, double d);

	//現在格納されいてるHを使って、指定したinの角スペクトル法を実行後、結果をoutに格納
	//inとoutは、Hの縦横半分。入力データをそのままinにすればOK、
	void kaku(My_ComArray_2D* out, My_ComArray_2D* in);
};


//2次元複素配列クラスを継承したレンズ配列クラス
class My_LensArray :public My_ComArray_2D
{
private:
public:

};
