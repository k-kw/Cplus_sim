#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>


class My_Bmp {

private:

	//イメージサイズ
	int im_x;
	int im_y;
	
	
	
public:
	//イメージデータの先頭ポインタ
	unsigned char* img;

	My_Bmp(int sx, int sy);   //コンストラクタ
	void img_read(std::string imgpath);           //BMP読み込み
	void ucimg_to_double(double* data_out);       //読み込んだunsigned charをdoubleにして格納
	
	//書き込みたいデータを256階調化、unsigned charに変換後imgに格納
	//多重定義
	void data_to_ucimg(double* data_in);
	void data_to_ucimg(int* data_in);
	void data_to_ucimg(float* data_in);
	
	void uc_to_img(unsigned char* data_in);       //unsigned charをimgに格納
	void img_write(std::string imgpath);          //BMP書き込み
	~My_Bmp();                                    //デコンストラクタ

};


//
////最大値求める
//template <class Type>
//Type get_max(Type* data, int size);
//
////最小値求める
//template <class Type>
//Type get_min(Type* data, int size);
//
////最大値で正規化,double型出力
//template <class Type>
//void norm_max(Type* data_in, int size, double* data_out);
//
////最大値と最小値で正規化(確実に0~1),double型出力
//template <class Type>
//void norm_max_min(Type* data_in, int size, double* data_out);
//
////正規化後,n階調化,int型出力
//template <class Type>
//void norm_reso_n(Type* data_in, int* data_out, int n, int size);
//
//
////intデータをunsigned charに変換後、格納
////0~255のデータに限る
//void to_uch(int* data_in, int size, unsigned char* data_img);
//
//
////1次元画像の上下反転
//template <class Type>
//void invert_img(Type* data_in, Type* data_out, int im_x, int im_y);
//
////中心1列取り出す
//template <class Type>
//void mid_line(Type* data_in, int sx, int sy, Type* data_out);

