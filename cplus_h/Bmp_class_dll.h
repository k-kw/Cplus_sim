#pragma once

#ifdef DLLBMPCLASS_EXPORTS
#define BMP_CLASS_DLL_API __declspec(dllexport)
#else
#define BMP_CLASS_DLL_API __declspec(dllimport)
#endif

#include <string>

extern "C" BMP_CLASS_DLL_API class My_Bmp {

private:

	//�C���[�W�T�C�Y
	int im_x;
	int im_y;
	
	
	
public:
	//�C���[�W�f�[�^�̐擪�|�C���^
	unsigned char* img;

	BMP_CLASS_DLL_API My_Bmp(int sx, int sy);   //�R���X�g���N�^
	BMP_CLASS_DLL_API void img_read(std::string imgpath);           //BMP�ǂݍ���
	BMP_CLASS_DLL_API void ucimg_to_double(double* data_out);       //�ǂݍ���unsigned char��double�ɂ��Ċi�[
	
	//�������݂����f�[�^��256�K�����Aunsigned char�ɕϊ���img�Ɋi�[
	//���d��`
	BMP_CLASS_DLL_API void data_to_ucimg(double* data_in);
	BMP_CLASS_DLL_API void data_to_ucimg(int* data_in);
	BMP_CLASS_DLL_API void data_to_ucimg(float* data_in);
	
	BMP_CLASS_DLL_API void uc_to_img(unsigned char* data_in);       //unsigned char��img�Ɋi�[
	BMP_CLASS_DLL_API void img_write(std::string imgpath);          //BMP��������
	BMP_CLASS_DLL_API ~My_Bmp();                                    //�f�X�g���N�^

};

