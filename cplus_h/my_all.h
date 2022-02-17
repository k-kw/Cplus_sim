#pragma once
#include "complex_array_class.h"
//�w�b�_���ɒ���,�O���������������֐����`���Ă͂����Ȃ��B�錾���āA���̃\�[�X�t�@�C���Œ�`���ׂ�
//�������������C�����C���֐����̓w�b�_�Œ�`���Ȃ��Ƃ����Ȃ��B

//inline
//�ő�l
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

//�ŏ��l
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

//�ő�l�Ő��K��
template <class Type>
inline void norm_max(Type* data_in, int size, double* data_out)
{
	Type max;
	max = get_max(data_in, size);

	for (int i = 0; i < size; i++) {
		data_out[i] = (double)((double)data_in[i] / (double)max);
	}

}

//�ő�l�ƍŏ��l�Ő��K��(�m����0~1)
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

//���K����,n�K����,int�^�o��
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


//int�f�[�^��unsigned char�ɕϊ���A�i�[
//0~255�̃f�[�^�Ɍ���
inline void to_uch(int* data_in, int size, unsigned char* data_img)
{
	for (int i = 0; i < size; i++) {
		data_img[i] = (unsigned char)data_in[i];
	}
}


//1�����摜�̏㉺���]
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


//���S1����o��
template <class Type>
inline void mid_line(Type* data_in, int sx, int sy, Type* data_out) {
	for (int i = 0; i < sx; i++) {
		data_out[i] = data_in[(sy / 2) * sx + i];
	}
}

//
////���s�҂ɋ������
////cf���ɒl������Aone�͑I�����P�̖��́Athe_other�͂Q�̖��́Avalue�͑I������I�ԂƂ����͂����鐔��
//void forced_two_select(int* cf, char one[], char the_other[], int one_value, int other_value) {
//
//	do {
//		printf("\n%s�F%d�����\t%s�F%d�����\n", one, one_value, the_other, other_value);
//		printf("Press 0 or 1 and enterkey : "); (void)scanf("%d", cf);
//	} while (*cf != one_value && *cf != other_value);
//}
//
////���s�҂ɋ������
////�ԋp�l�ɒl������Aone�͑I�����P�̖��́Athe_other�͂Q�̖��́Avalue�͑I������I�ԂƂ����͂����鐔��
//int forced_two_select_ver2(char title[], char one[], char the_other[], int one_value, int other_value) {
//	int res = 0;
//	do {
//		printf("\n%s\n%s�F%d�����\t%s�F%d�����\n", title, one, one_value, the_other, other_value);
//		printf("Press 0 or 1 and enterkey : "); (void)scanf("%d", &res);
//	} while (res != one_value && res != other_value);
//	return res;











////FFT
//
////FFT�֐�ver2
//void fft_2D_ver2(double* Re_out, double* Im_out, int y, int x, double* Re_in, double* Im_in);
//
////FFT�֐�
//void fft_2D(double* Re_out, double* Im_out, int y, int x, double* Re_in, double* Im_in);
//
////IFFT�֐�
//void ifft_2D(double* Re_out, double* Im_out, int y, int x, double* Re_in, double* Im_in);


////complex_array
////�U���������͎����z��𐳋K����A�ʑ����֕ϊ�
//void to_phase(double* Re, double* Im, int size, double* orig);
//
//
////���f�U���v�Z�֐�
//void power_complex(double* pow, int size, double* Re, double* Im);
//
////���f�U����2��v�Z�֐�
//void power_2_complex(double* pow, int size, double* Re, double* Im);
//
////���f���z���Z�֐�
//void mul_complex(int size, double* Re_in1, double* Im_in1, double* Re_in2, double* Im_in2, double* Re_out, double* Im_out);
//
//2D�摜��0pad�֐�(�c�����ꂼ��Q�{�ɂ���0���߁Ain��out�̓T�C�Y�Ⴄ)


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
////�p�X�y�N�g���@��H�𒼐ڌv�Z����֐��Ax��y�͌v�Z���̉摜�T�C�Y��2�{
//void H_kaku(double* ReH, double* ImH, double lam, double z, double d, int x, int y);
//
//////�p�X�y�N�g���@(���o�̓T�C�Y�͑S��x�Ey�A0���߂���Ă��Ȃ��摜�f�[�^����́A��ԍ���ifft��0pad������菜�������̂��o�́A���̉E��ifft���U���v�Z�����K����0pad�r���������̂��o��)
////void kaku(double* Re, double* Im, double* POWER, int x, int y, double lam, double z, double d, double* ReG, double* ImG);
////
//////�p�X�y�N�g���@(���o�̓T�C�Y�͑S��x�Ey�A0���߂���Ă��Ȃ��摜�f�[�^����́A��ԍ���ifft��0pad������菜�������̂��o�́A���̉E��ifft���U���v�Z�����K����0pad�r���������̂��o��)
////void kaku_2(double* Re, double* Im, double* POWER, int x, int y, double lam, double z, double d, double* ReG, double* ImG);
////
//////�p�X�y�N�g���@ver3(�U�����o�͂��Ȃ�)
////void kaku_3(double* Re, double* Im, int x, int y, double lam, double z, double d, double* ReG, double* ImG);
//
////�p�X�y�N�g���@ver4(H�z��������Ƃ��Ĉ���)
//void kaku_4(double* Re, double* Im, int x, int y, double* ReG, double* ImG, double* ReH, double* ImH);
//
////���d��`
//
////�p�X�y�N�g���@��H�𕡑f�z��N���X�ō쐬�Ax��y�͌v�Z���̉摜�T�C�Y��2�{
//void H__kaku(My_Complex_Array* H, double lam, double z, double d, int x, int y);
//
//
////�p�X�y�N�g���@ver4�𕡑f�z��N���X�Ōv�Z
//void kaku_4(My_Complex_Array*out, int x, int y, );



////�t���l����܂�h���v�Z
//void fresnel_h(double* Re, double* Im, double lam, double z, double d, int x, int y);





////Lens and Diffuser
//
////�����Y�̈ʑ��ϊ���p�ߎ��Ȃ�
//void lens_non_approx(double* Relens, double* Imlens, int x, int y, double d, double lam, double f);
//
////�����Y�̈ʑ��ϊ��z��쐬�֐�
//void lens(double* Relens, double* Imlens, int x, int y, double d, double lam, double f);
//
////�V�����h���J�������Y,�c�����̂ݏW��
//void cylin_lens_y(double* Relens, double* Imlens, int x, int y, double d, double lam, double f);
//
////�V�����h���J�������Y,�������̂ݏW��
//void cylin_lens_x(double* Relens, double* Imlens, int x, int y, double d, double lam, double f);
//
////�V�����h���J�������Y,�������̂݊g�U
//void cylin_lens_x_concave(double* Relens, double* Imlens, int x, int y, double d, double lam, double f);
//
////�����_���ʑ��g�U�z��֐�
//void diffusionplate_random(double* Re, double* Im, int x, int y);
//
////�����Y�g�U�z��֐�(�����`�̉摜�̂�)
//void diffusionplate_lens(double* Re, double* Im, int im_size, int lens_size, double d, double lam, double f, bool approx);
//
////�����Y�g�U�z��֐�(�����`�摜�ȊO��OK)
//void diffusionplate_lens_ver2(double* Re, double* Im, int im_size_x, int im_size_y, int lens_size, double d, double lam, double f, bool approx);







