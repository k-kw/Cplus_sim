#pragma once

class My_Lens {
private:
	//�����Y�T�C�Y
	int lx;
	int ly;

	////�g��
	//double lamda;
	////�s�b�`
	//double d;
	

public:
	//�����Y�z��擪�|�C���^
	double* lens_Re;
	double* lens_Im;


	My_Lens(int lsx, int lsy/*, double lam, double dx, double* Re_pr, double* Im_pr*/);  //�R���X�g���N�^
	void a_Lens(int approx, double f, double lamda, double d);                           //�P�ꃌ���Y
	
    //���������Ă邩�킩��Ȃ�����������Ȃ�
	//void cylind_Lens(int approx, int vert_hori, double f);                            //�V�����h���J�������Y

	void diffuser_Random(int rand_seed);                                                //�����_���g�U��
	void diffuser_Lensarray(int ls, int approx, double f, double lamda, double d);      //�����Y�A���C�g�U��
	~My_Lens();

};