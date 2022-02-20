#pragma once

class My_Fft {
private:
	int x;
	int y;
public:
	double* Re_in, * Im_in, * Re_out, * Im_out;

	My_Fft(int sx, int sy);  //コンストラクタ
	
	//interface
	void data_to_in(double* Re, double* Im);  //doubleデータをRe_inとIm_inに格納
	void out_to_data(double* Re, double* Im); //Re_outとIm_outをdoubleに格納
	
	//FFT
	void fft2d();  //2次元FFT
	void ifft2d(); //2次元IFFT

	~My_Fft(); //デストラクタ
};
