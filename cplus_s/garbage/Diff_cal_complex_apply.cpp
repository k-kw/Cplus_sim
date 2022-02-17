#define _USE_MATH_DEFINES
#include <cmath>
#include "my_all.h"
#include "Fft_class.h"
#include "complex_array_class.h"

#pragma warning(disable:4996)

#define sqr(x) ((x)*(x))



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
}

//�p�X�y�N�g���@ver4(H�z��������Ƃ��Ĉ���)
void kaku_4(double* Re, double* Im, int x, int y, double* ReG, double* ImG, double* ReH, double* ImH) {
	
	My_Complex_Array* com;
	com = new My_Complex_Array(4 * x * y);
	

	//���͂��ꂽ�摜�f�[�^��0���߂��Ĕ{�̑傫���̉摜�ɂ���
	Opad(com->Re, x, y, ReG);
	Opad(com->Im, x, y, ImG);
	

	//G��fft
	My_Fft* fft1;
	fft1 = new My_Fft(2 * x, 2 * y);
	fft1->data_to_in(com->Re, com->Im);
	fft1->fft2d();
	fft1->out_to_data(com->Re, com->Im);

	//GXH���v�Z
	com->mul_complex(ReH, ImH);


	//GXH��ifft
	fft1->data_to_in(com->Re, com->Im);
	fft1->ifft2d();
	fft1->out_to_data(com->Re, com->Im);

	delete fft1;

	//�o�͂P
	//0���ߕ������Ȃ�
	My_Complex_Array* com2;
	com2 = new My_Complex_Array(x * y);

	

	elim_0(com2->Re, 2 * x, 2 * y, com->Re);
	elim_0(com2->Im, 2 * x, 2 * y, com->Im);

	

	//�o�͂P�����o��
	for (int i = 0; i < x * y; i++) {
		Re[i] = com2->Re[i];
		Im[i] = com2->Im[i];
	}

	delete com;
	delete com2;
	
}


