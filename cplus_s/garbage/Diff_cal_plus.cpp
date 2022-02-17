#define _USE_MATH_DEFINES
#include <cmath>
#include "my_all.h"
#include "Fft_class.h"

#pragma warning(disable:4996)

#define sqr(x) ((x)*(x))

//2D�摜��0pad�֐�(�c�����ꂼ��Q�{�ɂ���0���߁Ain��out�̓T�C�Y�Ⴄ)
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

	//���͂��ꂽ�摜�f�[�^���O���߂��Ĕ{�̑傫���̉摜�ɂ���
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

//2D�摜��0pad��������菜���֐�(�c�����ꂼ��1/2�{�ɂ��Đ^�񒆂��擾�Ain��out�̓T�C�Y�Ⴄ)
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



//�p�X�y�N�g���@��H�𒼐ڌv�Z����֐�
void H_kaku(double* ReH, double* ImH, double lam, double z, double d, int x, int y) {
	double* Retmp, * Imtmp;
	Retmp = new double[x * y];
	Imtmp = new double[x * y];
	double u = 1 / ((double)x * d), v = 1 / ((double)y * d);
	//H�v�Z
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			Retmp[i * x + j] = cos(2 * M_PI * z * sqrt(sqr(1 / lam) - sqr(u * ((double)j - x / 2)) - sqr(v * ((double)i - y / 2))));
			Imtmp[i * x + j] = sin(2 * M_PI * z * sqrt(sqr(1 / lam) - sqr(u * ((double)j - x / 2)) - sqr(v * ((double)i - y / 2))));
		}
	}
	//H�V�t�g
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
////�p�X�y�N�g���@(���o�̓T�C�Y�͑S��x�Ey�A0���߂���Ă��Ȃ��摜�f�[�^����́A��ԍ���ifft��0pad������菜�������̂��o�́A���̉E��ifft���U���v�Z�����K����0pad�r���������̂��o��(��{�g��Ȃ�))
//void kaku(double* Re, double* Im, double* POWER, int x, int y, double lam, double z, double d, double* ReG, double* ImG) {
//	int X, Y;
//	X = 2 * x;
//	Y = 2 * y;
//
//	double* ReGtmp, * ImGtmp;
//	ReGtmp = new double[X * Y];
//	ImGtmp = new double[X * Y];
//
//	//���͂��ꂽ�摜�f�[�^���O���߂��Ĕ{�̑傫���̉摜�ɂ���
//	Opad(ReGtmp, x, y, ReG);
//	Opad(ImGtmp, x, y, ImG);
//
//	//G��fft
//	fft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//H�𒼐ڌv�Z
//	double* ReHtmp, * ImHtmp;
//	ReHtmp = new double[X * Y];
//	ImHtmp = new double[X * Y];
//
//	H_kaku(ReHtmp, ImHtmp, lam, z, d, X, Y);
//
//
//	//GXH���v�Z
//	mul_complex(Y * X, ReGtmp, ImGtmp, ReHtmp, ImHtmp, ReGtmp, ImGtmp);
//
//	//GXH��ifft
//	ifft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//�o�͂P
//	//0���ߕ������Ȃ�
//	double* Retmp, * Imtmp;
//	Retmp = new double[x * y];
//	Imtmp = new double[x * y];
//
//	elim_0(Retmp, X, Y, ReGtmp);
//	elim_0(Imtmp, X, Y, ImGtmp);
//
//	//�o�͂P�����o��
//	for (int i = 0; i < x * y; i++) {
//		Re[i] = Retmp[i];
//		Im[i] = Imtmp[i];
//	}
//
//	//�o��2
//	//�U���v�Z
//	power_complex(ReGtmp, X * Y, ReGtmp, ImGtmp);
//	//���K��
//	//normali_2(ReGtmp, X * Y, ReGtmp);
//	norm_max_min<double>(ReGtmp, X * Y, ReGtmp);
//	//0���ߕ������Ȃ�
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
////�p�X�y�N�g���@ver2(���o�̓T�C�Y�͑S��x�Ey�A0���߂���Ă��Ȃ��摜�f�[�^����́A��ԍ���ifft��0pad������菜�������̂��o�́A���̉E��ifft��0pad�r�����U���v�Z�����K���o��(��{�g��Ȃ�))
//void kaku_2(double* Re, double* Im, double* POWER, int x, int y, double lam, double z, double d, double* ReG, double* ImG) {
//	int X, Y;
//	X = 2 * x;
//	Y = 2 * y;
//
//	double* ReGtmp, * ImGtmp;
//	ReGtmp = new double[X * Y];
//	ImGtmp = new double[X * Y];
//
//	//���͂��ꂽ�摜�f�[�^���O���߂��Ĕ{�̑傫���̉摜�ɂ���
//	Opad(ReGtmp, x, y, ReG);
//	Opad(ImGtmp, x, y, ImG);
//
//	//G��fft
//	fft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//H�𒼐ڌv�Z
//	double* ReHtmp, * ImHtmp;
//	ReHtmp = new double[X * Y];
//	ImHtmp = new double[X * Y];
//
//	H_kaku(ReHtmp, ImHtmp, lam, z, d, X, Y);
//
//
//	//GXH���v�Z
//	mul_complex(Y * X, ReGtmp, ImGtmp, ReHtmp, ImHtmp, ReGtmp, ImGtmp);
//
//	//GXH��ifft
//	ifft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//�o�͂P
//	//0���ߕ������Ȃ�
//	double* Retmp, * Imtmp;
//	Retmp = new double[x * y];
//	Imtmp = new double[x * y];
//
//	elim_0(Retmp, X, Y, ReGtmp);
//	elim_0(Imtmp, X, Y, ImGtmp);
//
//	//�o�͂P�����o��
//	for (int i = 0; i < x * y; i++) {
//		Re[i] = Retmp[i];
//		Im[i] = Imtmp[i];
//	}
//
//	//�o��2
//	//�U���v�Z
//	power_complex(Retmp, x * y, Retmp, Imtmp);
//	//���K��
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
////�p�X�y�N�g���@ver3(�U�����o�͂��Ȃ�)
//void kaku_3(double* Re, double* Im, int x, int y, double lam, double z, double d, double* ReG, double* ImG) {
//	int X, Y;
//	X = 2 * x;
//	Y = 2 * y;
//
//	double* ReGtmp, * ImGtmp;
//	ReGtmp = new double[X * Y];
//	ImGtmp = new double[X * Y];
//
//	//���͂��ꂽ�摜�f�[�^���O���߂��Ĕ{�̑傫���̉摜�ɂ���
//	Opad(ReGtmp, x, y, ReG);
//	Opad(ImGtmp, x, y, ImG);
//
//	//G��fft
//	fft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//H�𒼐ڌv�Z
//	double* ReHtmp, * ImHtmp;
//	ReHtmp = new double[X * Y];
//	ImHtmp = new double[X * Y];
//
//	H_kaku(ReHtmp, ImHtmp, lam, z, d, X, Y);
//
//
//	//GXH���v�Z
//	mul_complex(Y * X, ReGtmp, ImGtmp, ReHtmp, ImHtmp, ReGtmp, ImGtmp);
//
//	//GXH��ifft
//	ifft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
//
//	//�o�͂P
//	//0���ߕ������Ȃ�
//	double* Retmp, * Imtmp;
//	Retmp = new double[x * y];
//	Imtmp = new double[x * y];
//
//	elim_0(Retmp, X, Y, ReGtmp);
//	elim_0(Imtmp, X, Y, ImGtmp);
//
//	//�o�͂P�����o��
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


//�p�X�y�N�g���@ver4(H�z��������Ƃ��Ĉ���)
void kaku_4(double* Re, double* Im, int x, int y, double lam, double d, double* ReG, double* ImG, double* ReH, double* ImH) {
	int X, Y;
	X = 2 * x;
	Y = 2 * y;

	double* ReGtmp, * ImGtmp;
	ReGtmp = new double[X * Y];
	ImGtmp = new double[X * Y];

	//���͂��ꂽ�摜�f�[�^��0���߂��Ĕ{�̑傫���̉摜�ɂ���
	Opad(ReGtmp, x, y, ReG);
	Opad(ImGtmp, x, y, ImG);
	//fft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);
	//fft_2D_ver2(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);

	//G��fft
	My_Fft* fft1;
	fft1 = new My_Fft(X, Y);
	fft1->data_to_in(ReGtmp, ImGtmp);
	fft1->fft2d();
	fft1->out_to_data(ReGtmp, ImGtmp);

	//GXH���v�Z
	mul_complex(Y * X, ReGtmp, ImGtmp, ReH, ImH, ReGtmp, ImGtmp);

	//GXH��ifft
	fft1->data_to_in(ReGtmp, ImGtmp);
	fft1->ifft2d();
	fft1->out_to_data(ReGtmp, ImGtmp);

	delete fft1;

	//ifft_2D(ReGtmp, ImGtmp, Y, X, ReGtmp, ImGtmp);

	//�o�͂P
	//0���ߕ������Ȃ�
	double* Retmp, * Imtmp;
	Retmp = new double[x * y];
	Imtmp = new double[x * y];

	elim_0(Retmp, X, Y, ReGtmp);
	elim_0(Imtmp, X, Y, ImGtmp);
	delete[]ReGtmp;
	delete[]ImGtmp;

	//�o�͂P�����o��
	for (int i = 0; i < x * y; i++) {
		Re[i] = Retmp[i];
		Im[i] = Imtmp[i];
	}

	
	delete[]Retmp;
	delete[]Imtmp;
}