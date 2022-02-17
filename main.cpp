#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>

#include "my_all.h"
#include "Bmp_class_dll.h"
#include "Lens_class_dll.h"
#include "complex_array_class.h"

#include <opencv2//opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>

//�ǉ��̈ˑ��t�@�C���ݒ�̑���
//opencv��DLL��PATH��ʂ��ē��I�����N���C�u����(�ÖٓI�����N)�Ƃ���
#pragma comment(lib, "opencv_world454.lib")
#pragma comment(lib, "opencv_world454d.lib")


//bmp��lens�N���X�𓮓I�����N(�ÖٓI�����N)
#pragma comment(lib, "Dll_bmp_class.lib")
#pragma comment(lib, "Dll_lens_class.lib")

//�]���Ȍx���폜
#pragma warning(disable:4996)

using namespace std;
using namespace cv;

//�p�����[�^1
#define SX 28       //bindat��
#define SY 28       //bindat�̏c

#define PJRSX 960     //SLM�ł̉���f��(4�Ŋ���鐮���Ɍ���)
#define PJRSY 540     //SLM�ł̏c��f��(4�Ŋ���鐮���Ɍ���)
#define short 540     //PJRSY��PJRSX�̒Z��
#define N 3       //�摜�̖���
#define LENS_SIZE 60 //�g�U�����Y�̃����Y�T�C�Y
#define CHECK_NUM N  //�V�~�����[�V�����摜���`�F�b�N����ԍ�
#define lam 532e-09  //�g��
#define d 1.496e-05 //��f�s�b�`
#define a 0.1 //�`������1
#define b 0.03 //�`������2
#define f 0.03 //�œ_����
#define resolution pow(2, 8) //�𑜓x

//�t�@�C���p�X
string binpath = "../../dat/bindat/1byte/fm_28_1.dat";
string simpath = "../../dat/simdat/SLM_phase/1byte/random/test_sim4.dat";
string oriimg = "./origimg/test.bmp";
string simimg = "./simimg/test.bmp";
string t = "exp.bmp";

int main() {
    clock_t start, lap;
    start = clock();

    //�ǂݍ��݃o�C�g�m�F
    int byte_num;
    do {
        cout << "\n�o�C�i���f�[�^��4�o�C�g�œǂݍ��݁F4�����\t1�o�C�g�œǂݍ��݁F1�����\n";
        cout << " 1 or 4: "; cin >> byte_num;

    } while (byte_num != 4 && byte_num != 1);


    //�������݃o�C�g�m�F
    int byte_numw;
    do {
        cout << "\n�o�C�i���f�[�^��4�o�C�g�ŏ������݁F4�����\t1�o�C�g�ŏ������݁F1�����\n";
        cout << " 1 or 4: "; cin >> byte_numw;

    } while (byte_numw != 4 && byte_numw != 1);



    //�摜�f�[�^��U�����(����)�Ƃ��邩�A�ʑ��ɕϊ����邩�m�F
    int ampl_or_phase;
    do {
        cout << "\n�摜�f�[�^��U�����(����)�Ƃ���ꍇ�F0�����\t���K����A�ʑ����Ƃ���ꍇ�F1�����\n";
        cout << " 0 or 1 : "; cin >> ampl_or_phase;

    } while (ampl_or_phase != 0 && ampl_or_phase != 1);



    //�����_���ʑ��������Y�A���C���m�F
    int rand_or_lsd;
    do {
        cout << "\n�g�U�������_���ʑ��Ƃ���ꍇ�F0�����\t�g�U����������Y�A���C�Ƃ���ꍇ�F1�����\n";
        cout << " 0 or 1 : "; cin >> rand_or_lsd;

    } while (rand_or_lsd != 0 && rand_or_lsd != 1);


    //�����Y�̎��ߎ��̊m�F
    int approx;
    if (rand_or_lsd == 1) {
        do {
            cout << "\n�����Y�̎����ߎ�����F0�����\t�ߎ����Ȃ��F1�����\n";
            cout << " 0 or 1 : "; cin >> approx;

        } while (approx != 0 && approx != 1);
    }



    //�t�@�C�����́E�o�C�i���X�g���[���I�[�v��
    ifstream ifs(binpath, ios::binary /*| ios::in*/);
    //�t�@�C���o�́E�o�C�i���X�g���[���I�[�v��
    ofstream ofs(simpath, ios::binary/* | ios::out*/);



    //�����I�[�v���ł������m�F
    if ((ifs) && (ofs)) {



        My_Lens* Lens;
        Lens = new My_Lens(PJRSX, PJRSY);


        if (rand_or_lsd == 0) {
            //�����_���g�U��


            Lens->diffuser_Random(0);

        }
        else {
            //�����Y�A���C�g�U��
            Lens->diffuser_Lensarray(LENS_SIZE, approx, f, lam, d);


        }

        //Lens->a_Lens(approx, f, lam, d);



        //H�z�񒼐ڌv�Z
        //��ʑ̂���g�U��
        My_ComArray_2D* Ha, * Hb;
        Ha = new My_ComArray_2D(4 * PJRSX * PJRSY, 2 * PJRSX, 2 * PJRSY);

        Ha->H_kaku(lam, a, d);


        //��ʑ̂���Z���T
        Hb = new My_ComArray_2D(4 * PJRSX * PJRSY, 2 * PJRSX, 2 * PJRSY);

        Hb->H_kaku(lam, b, d);
       


        for (int k = 0; k < N; k++) {
            //�i���󋵕\��
            if (k == 0) {
                cout << "\n\n\n-------------------------------simdata�t�@�C���쐬��---------------------------------\n\n\n";
            }

            //�o�C�i���ǂݍ��ݔz��|�C���^
            unsigned char* chRe;
            int* intRe;



            chRe = new unsigned char[SX * SY];
            intRe = new int[SX * SY];



            //data�ǂݎ��
            if (byte_num == 1) {
                //1byte�ňꖇ���ǂݍ���
                ifs.read((char*)chRe, sizeof(unsigned char) * SX * SY);
                //�㉺���]
                invert_img<unsigned char>(chRe, chRe, SX, SY);

            }
            else {
                //4byte�ňꖇ���ǂݍ���
                ifs.read((char*)intRe, sizeof(int) * SX * SY);
                //�㉺���]
                invert_img<int>(intRe, intRe, SX, SY);


            }


            //�摜�f�[�^�m�F
            if (k == N - 1) {

                My_Bmp* check;
                check = new My_Bmp(SX, SY);

                if (byte_num == 1) {

                    check->uc_to_img(chRe);
                    check->img_write(oriimg);
                }
                else {
                    check->data_to_ucimg(intRe);
                    check->img_write(oriimg);

                }



                delete check;
            }
            delete[]intRe;

            //�摜�f�[�^���g�傷��Ƃ�CV_8U�ł��
            //�摜�f�[�^��cv::Mat�ɃR�s�[
            Mat bin_mat(SY, SX, CV_8U);
            memcpy(bin_mat.data, chRe, SX * SY * sizeof(unsigned char));
            /*imshow("View", bin_mat);
            waitKey(0);*/
            delete[]chRe;

            //�g��
            Mat bin_mat_res(short, short, CV_8U);
            resize(bin_mat, bin_mat_res, Size(short, short));
            bin_mat.release();
            /*string resizeimg = "resize.bmp";
            imwrite(resizeimg, bin_mat_res);
            imshow("View", bin_mat_res);
            waitKey(0);*/

            //�[�����߂��č��킹��
            Mat bin_mat_pjr(PJRSY, PJRSX, CV_8U);
            copyMakeBorder(bin_mat_res, bin_mat_pjr, (int)(PJRSY - short) / 2, (int)(PJRSY - short) / 2, (int)(PJRSX - short) / 2, (int)(PJRSX - short) / 2, BORDER_CONSTANT, 0);
            bin_mat_res.release();
            /*string padimg = "pad.bmp";
            imwrite(padimg, bin_mat_pjr);
            imshow("View", bin_mat_pjr);
            waitKey(0);*/

            unsigned char* padRe;
            padRe = new unsigned char[PJRSX * PJRSY];


            //�g�債��cv::Mat��padRe�ɃR�s�[
            memcpy(padRe, bin_mat_pjr.data, PJRSX * PJRSY * sizeof(unsigned char));
            bin_mat_pjr.release();



            //�摜�f�[�^�m�F
            if (k == N - 1) {
                

                My_Bmp* check;
                check = new My_Bmp(PJRSX, PJRSY);

                check->uc_to_img(padRe);
                check->img_write(t);

                delete check;

            }


            
            My_ComArray_2D* Complex;
            Complex = new My_ComArray_2D(PJRSX * PJRSY, PJRSX, PJRSY);

            Complex->data_to_ReIm(padRe);



            delete[]padRe;


            if (ampl_or_phase == 1) {
                //�ʑ����ɂ���
                Complex->to_phase(Complex->Re);
            }



            //�g�U�܂ł̓`���v�Z
            Ha->kaku(Complex, Complex);
            
            //�g�U��X�摜
            Complex->mul_complex(Lens->lens_Re, Lens->lens_Im);

            //���C���Z���T�܂œ`���v�Z
            Hb->kaku(Complex, Complex);



            //�U���v�Z
            Complex->power(Complex->Re);

            if (k == CHECK_NUM - 1) {

                My_Bmp* check;
                check = new My_Bmp(PJRSX, PJRSY);

                check->data_to_ucimg(Complex->Re);
                check->img_write(simimg);

                delete check;

            }


            double* Pline;
            Pline = new double[PJRSX];

            mid_line<double>(Complex->Re, PJRSX, PJRSY, Pline);
            delete Complex;

            //�������ݔz��
            int* intw;
            unsigned char* chw;
            intw = new int[PJRSX];
            chw = new unsigned char[PJRSX];

            norm_reso_n<double>(Pline, intw, (int)(resolution - 1), PJRSX);
            delete[]Pline;
            to_uch(intw, PJRSX, chw);


            //��������
            if (byte_numw == 1) {
                ofs.write((char*)chw, sizeof(unsigned char) * PJRSX);

            }
            else {
                ofs.write((char*)intw, sizeof(int) * PJRSX);

            }


            delete[]intw;
            delete[]chw;


            if ((k + 1) % 100 == 0) {
                cout << k + 1 << "�܂Ŋ���----------------------------------------------\n";
                lap = clock();
                cout << setprecision(4) << (double)(lap - start) / CLOCKS_PER_SEC / 60 << "���o��\n\n";

            }
        }
        delete Lens;

        delete Ha;
        delete Hb;

    }

    else {
        cout << "�f�[�^�t�@�C�����J���܂���ł���\n�I�����܂��B";

    }

    return 0;
}