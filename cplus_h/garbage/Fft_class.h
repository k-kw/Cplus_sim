#pragma once

class My_Fft {
private:
	int x;
	int y;
public:
	double* Re_in, * Im_in, * Re_out, * Im_out;

	My_Fft(int sx, int sy);  //�R���X�g���N�^
	
	//interface
	void data_to_in(double* Re, double* Im);  //double�f�[�^��Re_in��Im_in�Ɋi�[
	void out_to_data(double* Re, double* Im); //Re_out��Im_out��double�Ɋi�[
	
	//FFT
	void fft2d();  //2����FFT
	void ifft2d(); //2����IFFT

	~My_Fft(); //�f�X�g���N�^
};
