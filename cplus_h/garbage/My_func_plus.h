#pragma once
//
////�ő�l���߂�
//template <class Type>
//Type get_max(Type* data, int size);
//
////�ŏ��l���߂�
//template <class Type>
//Type get_min(Type* data, int size);
//
////�ő�l�Ő��K��,double�^�o��
//template <class Type>
//void norm_max(Type* data_in, int size, double* data_out);
//
////�ő�l�ƍŏ��l�Ő��K��(�m����0~1),double�^�o��
//template <class Type>
//void norm_max_min(Type* data_in, int size, double* data_out);
//
////���K����,n�K����,int�^�o��
//template <class Type>
//void norm_reso_n(Type* data_in, int* data_out, int n, int size);
//
//
////int�f�[�^��unsigned char�ɕϊ���A�i�[
////0~255�̃f�[�^�Ɍ���
//void to_uch(int* data_in, int size, unsigned char* data_img);
//
//
////1�����摜�̏㉺���]
//template <class Type>
//void invert_img(Type* data_in, Type* data_out, int im_x, int im_y);
//
////���S1����o��
//template <class Type>
//void mid_line(Type* data_in, int sx, int sy, Type* data_out);
//
//
////���s�҂ɋ������
////cf���ɒl������Aone�͑I�����P�̖��́Athe_other�͂Q�̖��́Avalue�͑I������I�ԂƂ����͂����鐔��
//void forced_two_select(int* cf, char one[], char the_other[], int one_value, int other_value);
//
//
//
////���s�҂ɋ������
////�ԋp�l�ɒl������Aone�͑I�����P�̖��́Athe_other�͂Q�̖��́Avalue�͑I������I�ԂƂ����͂����鐔��
//int forced_two_select_ver2(char title[] ,char one[], char the_other[], int one_value, int other_value);

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
template <class Type>
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
//}