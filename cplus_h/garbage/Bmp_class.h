#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>


class My_Bmp {

private:

	//�C���[�W�T�C�Y
	int im_x;
	int im_y;
	
	
	
public:
	//�C���[�W�f�[�^�̐擪�|�C���^
	unsigned char* img;

	My_Bmp(int sx, int sy);   //�R���X�g���N�^
	void img_read(std::string imgpath);           //BMP�ǂݍ���
	void ucimg_to_double(double* data_out);       //�ǂݍ���unsigned char��double�ɂ��Ċi�[
	
	//�������݂����f�[�^��256�K�����Aunsigned char�ɕϊ���img�Ɋi�[
	//���d��`
	void data_to_ucimg(double* data_in);
	void data_to_ucimg(int* data_in);
	void data_to_ucimg(float* data_in);
	
	void uc_to_img(unsigned char* data_in);       //unsigned char��img�Ɋi�[
	void img_write(std::string imgpath);          //BMP��������
	~My_Bmp();                                    //�f�R���X�g���N�^

};


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

