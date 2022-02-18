#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "complex_array_class.h"
#include "my_all.h"
#include "Fft_class.h"

#define sqr(x) ((x)*(x))

My_Complex_Array::My_Complex_Array(int s)
	:s(s)
{
	//this->s = s;
	
	Re = new double[this->s];
	Im = new double[this->s];

	//‰Šú‰»
	for (int i = 0; i < this->s; i++) {
		Re[i] = 0;
		Im[i] = 0;
	}
}


My_Complex_Array::~My_Complex_Array()
{
	std::cout << "delete" << std::endl;
	delete[]Re;
	delete[]Im;
}



//À•”A‹••”—¼•ûŠi”[
//double‚ğŠi”[
void My_Complex_Array::data_to_ReIm(double* Rein, double* Imin)
{
	for (int i = 0; i < s; i++) {
		Re[i] = Rein[i];
		Im[i] = Imin[i];
	}
}

//int‚ğŠi”[
void My_Complex_Array::data_to_ReIm(int* Rein, int* Imin)
{
	for (int i = 0; i < s; i++) {
		Re[i] = (double)Rein[i];
		Im[i] = (double)Imin[i];

	}
}

//unsigned char‚ğŠi”[
void My_Complex_Array::data_to_ReIm(unsigned char* Rein, unsigned char* Imin)
{
	for (int i = 0; i < s; i++) {

		long tmp = (long)Rein[i];
		Re[i] = (double)tmp;

		tmp = (long)Imin[i];
		Im[i] = (double)tmp;


	}
}


//À•”‚Ì‚İŠi”[
void My_Complex_Array::data_to_ReIm(double* Rein)
{
	for (int i = 0; i < s; i++) {
		Re[i] = Rein[i];
	}
}

void My_Complex_Array::data_to_ReIm(int* Rein)
{
	for (int i = 0; i < s; i++) {
		Re[i] = (double)Rein[i];

	}
}

void My_Complex_Array::data_to_ReIm(unsigned char* Rein)
{
	for (int i = 0; i < s; i++) {

		long tmp = (long)Rein[i];
		Re[i] = (double)tmp;

	}
}





//U•o—Í
void My_Complex_Array::power(double* pow)
{
	for (int i = 0; i < s; i++) {
		pow[i] = sqrt(sqr(Re[i]) + sqr(Im[i]));
	}
}




//•¡‘fæZ
void My_Complex_Array::mul_complex(My_Complex_Array* opponent, My_Complex_Array* out)
{
	double* Retmp, * Imtmp;
	Retmp = new double[s];
	Imtmp = new double[s];

	for (int i = 0; i < s; i++) {
		Retmp[i] = (Re[i] * opponent->Re[i]) - (Im[i] * opponent->Im[i]);
		Imtmp[i] = (Re[i] * opponent->Im[i]) + (Im[i] * opponent->Re[i]);

	}

	for (int i = 0; i < s; i++) {

		out->Re[i] = Retmp[i];
		out->Im[i] = Imtmp[i];

	}
	delete[]Retmp;
	delete[]Imtmp;
}

//Ši”[‚³‚ê‚Ä‚¢‚é•¡‘f”z—ñ‚Æw’è‚µ‚½•¡‘f”z—ñƒIƒuƒWƒFƒNƒg‚ÌæZŒ‹‰Ê‚ğA‚±‚ÌƒIƒuƒWƒFƒNƒg‚ÉŠi”[
void My_Complex_Array::mul_complex(My_Complex_Array* opponent)
{
	double* Retmp, * Imtmp;
	Retmp = new double[s];
	Imtmp = new double[s];

	for (int i = 0; i < s; i++) {
		Retmp[i] = (Re[i] * opponent->Re[i]) - (Im[i] * opponent->Im[i]);
		Imtmp[i] = (Re[i] * opponent->Im[i]) + (Im[i] * opponent->Re[i]);

	}
	for (int i = 0; i < s; i++) {

		Re[i] = Retmp[i];
		Im[i] = Imtmp[i];

	}

	delete[]Retmp;
	delete[]Imtmp;
}

//Ši”[‚³‚ê‚Ä‚¢‚é•¡‘f”z—ñ‚Æw’è‚µ‚½•¡‘f”z—ñ‚ÌæZŒ‹‰Ê‚ğA‚±‚ÌƒIƒuƒWƒFƒNƒg‚ÉŠi”[
void My_Complex_Array::mul_complex(double* Re2, double* Im2)
{
	double* Retmp, * Imtmp;
	Retmp = new double[s];
	Imtmp = new double[s];

	for (int i = 0; i < s; i++) {
		
		Retmp[i] = Re[i] * Re2[i] - Im[i] * Im2[i];
		
		Imtmp[i] = Re[i] * Im2[i] + Im[i] * Re2[i];
		
	}

	for (int i = 0; i < s; i++) {
		
		Re[i] = Retmp[i];
		Im[i] = Imtmp[i];

	}

	delete[]Retmp;
	delete[]Imtmp;
}





//U•(À•”)î•ñin‚ğ³‹K‰»ŒãAˆÊ‘Šî•ñ‚É•ÏŠ·
void My_Complex_Array::to_phase(double* in)
{
	double* tmp;
	tmp = new double[s];

	norm_max_min<double>(in, s, tmp);

	for (int i = 0; i < s; i++) {
		Re[i] = cos(2 * M_PI * tmp[i]);
		Im[i] = sin(2 * M_PI * tmp[i]);
	}

	delete[]tmp;
}

//U•(À•”)î•ñin‚ğ255‚ÅŠ„‚Á‚ÄAˆÊ‘Šî•ñ‚É•ÏŠ·
void My_Complex_Array::to256_phase(double* in)
{
	for (int i = 0; i < s; i++) {
		Re[i] = cos(2 * M_PI * in[i] / 255);
		Im[i] = sin(2 * M_PI * in[i] / 255);
	}
}




//0–„‚ß‚µ‚ÄŠg‘åAins = inx * inyAoutx > inxAouty > iny
void My_Complex_Array::zeropad(My_Complex_Array* out,int outx, int outy, int inx, int iny)
{
	int* sx, * sy;
	sx = new int;
	sy = new int;

	*sx = (int)((outx - inx) / 2);
	*sy = (int)((outy - iny) / 2);

	for (int i = *sy; i < (*sy) + iny; i++) {
		for (int j = *sx; j < (*sx) + inx; j++) {

			out->Re[i * outx + j] = this->Re[(i - (*sy)) * inx + (j - (*sx))];
			out->Im[i * outx + j] = this->Im[(i - (*sy)) * inx + (j - (*sx))];
		}
	}

	delete sx;
	delete sy;
}

//’†S‚ğæ‚èo‚µ‚Äk¬Ains = inx * inyAoutx < inxAouty < iny
void My_Complex_Array::extract_center(My_Complex_Array* out, int outx, int outy, int inx, int iny)
{
	int* sx, * sy;
	sx = new int;
	sy = new int;

	*sx = (int)((inx - outx) / 2);
	*sy = (int)((iny - outy) / 2);


	for (int i = *sy; i < (*sy) + outy; i++) {
		for (int j = *sx; j < (*sx) + outx; j++) {

			out->Re[(i - (*sy)) * outx + (j - (*sx))] = this->Re[i * inx + j];
			out->Im[(i - (*sy)) * outx + (j - (*sx))] = this->Im[i * inx + j];
		}
	}


	delete sx;
	delete sy;
}





//------------------------------------------2D--------------------------------------------



//0–„‚ß‚µ‚ÄŠg‘åAins = inx * inyAoutx > inxAouty > iny
void My_ComArray_2D::zeropad(My_ComArray_2D* out)
{
	int* sx, * sy;
	sx = new int;
	sy = new int;

	*sx = (int)((out->x - this->x) / 2);
	*sy = (int)((out->y - this->y) / 2);

	for (int i = *sy; i < (*sy) + this->y; i++) {
		for (int j = *sx; j < (*sx) + this->x; j++) {

			out->Re[i * out->x + j] = this->Re[(i - (*sy)) * this->x + (j - (*sx))];
			out->Im[i * out->x + j] = this->Im[(i - (*sy)) * this->x + (j - (*sx))];
		}
	}

	delete sx;
	delete sy;
}

//’†S‚ğæ‚èo‚µ‚Äk¬Ains = inx * inyAoutx < inxAouty < iny
void My_ComArray_2D::extract_center(My_ComArray_2D* out)
{
	int* sx, * sy;
	sx = new int;
	sy = new int;

	*sx = (int)((this->x - out->x) / 2);
	*sy = (int)((this->y - out->y) / 2);


	for (int i = *sy; i < (*sy) + out->y; i++) {
		for (int j = *sx; j < (*sx) + out->x; j++) {

			out->Re[(i - (*sy)) * out->x + (j - (*sx))] = this->Re[i * this->x + j];
			out->Im[(i - (*sy)) * out->x + (j - (*sx))] = this->Im[i * this->x + j];
		}
	}


	delete sx;
	delete sy;
}




//ŠpƒXƒyƒNƒgƒ‹–@‚ÌH‚ğŠi”[A‰æ‘œ‚Ìc‰¡”{‚Ì‘å‚«‚³‚Å—pˆÓ
void My_ComArray_2D::H_kaku(double lam, double z, double d)
{
	double* u, * v, * Retmp, * Imtmp;
	u = new double;
	v = new double;

	Retmp = new double[x * y];
	Imtmp = new double[x * y];

	*u = 1 / ((double)x * d);
	*v = 1 / ((double)y * d);

	//HŒvZ
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			Retmp[i * x + j] = cos(2 * M_PI * z * sqrt(sqr(1 / lam) - sqr((*u) * ((double)j - x / 2)) - sqr((*v) * ((double)i - y / 2))));
			Imtmp[i * x + j] = sin(2 * M_PI * z * sqrt(sqr(1 / lam) - sqr((*u) * ((double)j - x / 2)) - sqr((*v) * ((double)i - y / 2))));
		}
	}

	//HƒVƒtƒg
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			if (j < x / 2 && i < y / 2) {
				this->Re[i * x + j] = Retmp[(i + y / 2) * x + (j + x / 2)];
				this->Re[(i + y / 2) * x + (j + x / 2)] = Retmp[i * x + j];
				this->Im[i * x + j] = Imtmp[(i + y / 2) * x + (j + x / 2)];
				this->Im[(i + y / 2) * x + (j + x / 2)] = Imtmp[i * x + j];
			}
			else if (j >= x / 2 && i < y / 2) {
				this->Re[i * x + j] = Retmp[(i + y / 2) * x + (j - x / 2)];
				this->Re[(i + y / 2) * x + (j - x / 2)] = Retmp[i * x + j];
				this->Im[i * x + j] = Imtmp[(i + y / 2) * x + (j - x / 2)];
				this->Im[(i + y / 2) * x + (j - x / 2)] = Imtmp[i * x + j];
			}
		}
	}

	delete[]Retmp;
	delete[]Imtmp;
	delete u;
	delete v;
}

//Œ»İŠi”[‚³‚ê‚¢‚Ä‚éH‚ğg‚Á‚ÄAw’è‚µ‚½in‚ÌŠpƒXƒyƒNƒgƒ‹–@‚ğÀsŒãAŒ‹‰Ê‚ğout‚ÉŠi”[
void My_ComArray_2D::kaku(My_ComArray_2D* out, My_ComArray_2D* in)
{
	//H‚Ì‘å‚«‚³‚Å—pˆÓ
	My_ComArray_2D* inpad;
	inpad = new My_ComArray_2D(this->s, this->x, this->y);

	//in(G)‚ğ0–„‚ß‚µ‚Ä2”{‚Ì‘å‚«‚³
	in->zeropad(inpad);

	//G‚ğfft
	My_Fft* fft1;
	fft1 = new My_Fft(this->x, this->y);
	fft1->data_to_in(inpad->Re, inpad->Im);
	fft1->fft2d();
	fft1->out_to_data(inpad->Re, inpad->Im);

	//GXH‚ğŒvZ
	inpad->mul_complex(this);


	//GXH‚ğifft
	fft1->data_to_in(inpad->Re, inpad->Im);
	fft1->ifft2d();
	fft1->out_to_data(inpad->Re, inpad->Im);

	delete fft1;

	//0–„‚ß‚µ‚½•”•ª‚ğæ‚èœ‚¢‚ÄAout‚ÉŠi”[
	inpad->extract_center(out);


	delete inpad;
}



//ƒ‰ƒ“ƒ_ƒ€ˆÊ‘ŠŠgU”Â
void My_ComArray_2D::diffuser_Random(int rand_seed)
{
	srand(rand_seed);
	double random_num;

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {

			random_num = rand();
			this->Re[i * x + j] = cos(((double)random_num / RAND_MAX) * 2 * M_PI);
			this->Im[i * x + j] = sin(((double)random_num / RAND_MAX) * 2 * M_PI);
		}
	}
}


//--------------------------------------------LENS-------------------------------------------

void My_LensArray::Lens()
{
	if (approx) {
		//‹ß—
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				double dx, dy;
				dx = ((double)j - (x / 2)) * d;
				dy = ((double)i - (y / 2)) * d;

				this->Re[i * x + j] = cos((-2 * M_PI / lamda) * (sqr(dx) + sqr(dy)) / (2 * f));
				this->Im[i * x + j] = sin((-2 * M_PI / lamda) * (sqr(dx) + sqr(dy)) / (2 * f));
			}
		}

	}
	else {
		//‹ß—‚È‚µ
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				double dx, dy;
				dx = ((double)j - (x / 2)) * d;
				dy = ((double)i - (y / 2)) * d;

				this->Re[i * x + j] = cos((-2 * M_PI / lamda) * (sqr(dx) + sqr(dy)) / (2 * f));
				this->Im[i * x + j] = sin((-2 * M_PI / lamda) * (sqr(dx) + sqr(dy)) / (2 * f));
			}
		}

	}
}


void My_LensArray::diffuser_Lensarray(int ls)
{
	
	//”÷¬’PˆêƒŒƒ“ƒYì¬
	My_LensArray* mini_lens;
	mini_lens = new My_LensArray(s, ls, ls, approx, f, lamda, d);
	mini_lens->Lens();


	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			this->Re[i * x + j] = mini_lens->Re[(i % ls) * ls + (j % ls)];
			this->Im[i * x + j] = mini_lens->Im[(i % ls) * ls + (j % ls)];
		}
	}

	//”÷¬’PˆêƒŒƒ“ƒYíœ
	delete mini_lens;

}