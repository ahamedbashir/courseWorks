// ************************************************************
//      Written by :    BASHIR AHAMED
//
//    https://github.com/ahamedbashir/imageProcessing
//
//      Semester   :    FALL 2018
// ************************************************************

#include "IP.h"

using namespace IP;

// ******** for FFT, input image must be zero padded to make length and width power of 2

// ********************************************************************
// 
// HW_utils.cpp includes the following functions
// void HW_fft2MagPhase(ImagePtr Ifft, ImagePtr Imag, ImagePtr Iphase);
// void zero_padding(ImagePtr I1, ImagePtr I2);
// void fft1D(complexP q1, int dir, complexP q2);
// void fft2D(ImagePtr I, int dir, ImagePtr Ifft);
// 
//	*******************************************************************


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_fft2MagPhase:
// Convert a FFT image (real + imaginary) to magnitute and phase.
// Ifft has two channel Ifft1[0] is real part and Ifft2[0] is imaginary
// 
//


void 
HW_fft2MagPhase(ImagePtr Ifft, ImagePtr Imag, ImagePtr Iphase)
{

	// allocate two float images for mag and phase
	IP_copyImageHeader(Ifft, Imag);
	IP_copyImageHeader(Ifft, Iphase);

	int w = Ifft->width();
	int h = Ifft->height();
	int total = w * h;

	ChannelPtr<float> real, imag, magPtr, phasePtr;
	int type;

// PUT YOUR CODE HERE...
	IP_getChannel(Ifft, 0, real, type);
	IP_getChannel(Ifft, 1, imag, type);

	IP_getChannel(Imag, 0, magPtr, type);
	IP_getChannel(Iphase,0, phasePtr, type);

	// compute sqrt( real^2 + imag^2 )
	// compute atan2( imag/real )

// PUT YOUR CODE HERE...

  // std::cout << "real = " << *real << " imag = " << *imag << std::endl;

	for(int i = 0; i < total; i++) {
		*magPtr = sqrt((*real)*(*real) + (*imag)*(*imag));

    // correct phase calculation but doesn't match with professors output
    *phasePtr = atan2(*imag, *real);

    // wrong phase calculation but matches with professors solution
		// *phasePtr = atan2( *real , *imag);
		
		real++;
		imag++;
		magPtr++;
		phasePtr++;

	}

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_fft2MagPhase:
// Convert magnitute and phase to a FFT Image.
// 
//
void 
HW_magPhase2FFT(ImagePtr Imag, ImagePtr Iphase, ImagePtr Ifft)
{

// PUT YOUR CODE HERE...

  int w = Imag->width();
  int h = Imag->height();
  int total = w * h;
  int float_channel[] = {4,4};

	// assign two channel to Ifft
  Ifft->allocImage(w, h, float_channel);
  
	ChannelPtr<float> magPtr, phasePtr, real, imag;
	int type;

  IP_getChannel(Imag, 0, magPtr, type);
  IP_getChannel(Iphase,0, phasePtr, type);

	IP_getChannel(Ifft, 0, real, type);
	IP_getChannel(Ifft, 1, imag, type);


	for(int i = 0; i < total; i++) {
		*real = (*magPtr) * cos(*phasePtr);
		*imag = (*magPtr) * sin(*phasePtr);

		magPtr++;
		phasePtr++;
		real++;
		imag++;
	}

}

// 
// ******************************************
//	void zero_padding(ImagePtr I1, ImagePtr I2);
// convert inpput image into a two channel image
// with padded zeros to make the width and height power of 2
// 

void zero_padding(ImagePtr I1, ImagePtr I2) {
	int w = I1->width();
	int h = I1->height();
	int type;
	int float_channel[] = {4,4};

	int pad_w = pow(2, ceil(log2(w))) ;
	int pad_h = pow(2, ceil(log2(h))) ;


	I2->allocImage(pad_w, pad_h, float_channel);

	ChannelPtr<uchar> I1Ptr;
	ChannelPtr<float> real, imag;

	IP_getChannel(I1, 0, I1Ptr, type);
	IP_getChannel(I2, 0, real, type);
	IP_getChannel(I2, 1, imag, type);

	for(int i = 0; i < pad_h; i++) {
		for(int j = 0; j < pad_w; j++) {
			if(i < h && j < w) {
				*(real + j + i * pad_w) = float(*(I1Ptr++));
			}
			else {
				*(real + j + i * pad_w) = 0;
			}
			*(imag + j + i * pad_w) = 0; 
		}
		
	}
}

// ******************************************

typedef struct {
        int len;	// length of complex number list
        float * real;	// pointer to real number list
        float * imag;	// pointer to imaginary number list
} complexS, *complexP;


// fft1D for 2D fourier transform
void fft1D(complexP q1, int dir, complexP q2);

// fft2D implemention using seperable fft1D

void fft2D(ImagePtr I1, int dir, ImagePtr I2) {

  IP_copyImageHeader(I1, I2);

  int w = I1->width();
  int h = I1->height();

  complexP input,output;
  input = (complexP) malloc(sizeof(complexS));
  output = (complexP) malloc(sizeof(complexS));
  
  // FFT by row
  input->len = w;
  input->real = (float*) malloc(sizeof(float)*input->len);
  input->imag = (float*) malloc(sizeof(float)*input->len);
  output->len = w;
  output->real = (float*) malloc(sizeof(float)*output->len);
  output->imag = (float*) malloc(sizeof(float)*output->len);

  ChannelPtr<float> I1_real, I1_imag, I2_real, I2_imag;
  int type;
  
  IP_getChannel(I1,0,I1_real,type);
  IP_getChannel(I1,1,I1_imag,type);

  IP_getChannel(I2,0,I2_real,type);
  IP_getChannel(I2,1,I2_imag,type);

  for (int y = 0; y < h; y++){
    for (int x = 0; x < w; x++){
      *(input->real+x) = *I1_real++;
      *(input->imag+x) = *I1_imag++;

    }

    fft1D(input, dir ,output);

    for (int x = 0; x < w; x++) {
      *(I2_real+x+w*y) = *(output->real+x);
      *(I2_imag+x+w*y) = *(output->imag+x);
    }
  }

  free(input->real);
  free(input->imag);
  free(output->real);
  free(output->imag);

  // FFT by column
  input->len = h;
  input->real = (float*) malloc(sizeof(float)*input->len);
  input->imag = (float*) malloc(sizeof(float)*input->len);
  output->len = h;
  output->real = (float*) malloc(sizeof(float)*output->len);
  output->imag = (float*) malloc(sizeof(float)*output->len);

  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      *(input->real+y) = *(I2_real + x + w*y);
      *(input->imag+y) = *(I2_imag + x + w*y);      
    }

    fft1D(input, dir , output);

    for (int y=0; y<h; y++) {
      *(I2_real + x + w*y ) = *(output->real + y);
      *(I2_imag + x + w*y ) = *(output->imag + y);
    }
  }

}


void fft1D(complexP q1, int dir, complexP q2)
{
  int i, N, N2;
  float * r1, * i1, * r2, * i2, * ra, * ia, * rb, * ib;
  float FCTR, fctr, a, b, c, s;
  complexP qa, qb;

  N = q1 -> len;
  r1 = (float * ) q1 -> real;
  i1 = (float * ) q1 -> imag;
  r2 = (float * ) q2 -> real;
  i2 = (float * ) q2 -> imag;

  if (N == 2) {
    a = r1[0] + r1[1];  // F(0)=f(0)+f(1);F(1)=f(0)-f(1)
    b = i1[0] + i1[1];  // a,b needed when r1=r2
    r2[1] = r1[0] - r1[1];
    i2[1] = i1[0] - i1[1];
    r2[0] = a;
    i2[0] = b;

  } else {
    N2 = N / 2;
    qa = (complexP) malloc(sizeof(complexS));
    qa -> len = N2;
    qa -> real = (float * ) malloc(sizeof(float) * qa -> len);
    qa -> imag = (float * ) malloc(sizeof(float) * qa -> len);

    qb = (complexP) malloc(sizeof(complexS));
    qb -> len = N2;
    qb -> real = (float * ) malloc(sizeof(float) * qb -> len);
    qb -> imag = (float * ) malloc(sizeof(float) * qb -> len);

    ra = (float * ) qa -> real;
    ia = (float * ) qa -> imag;
    rb = (float * ) qb -> real;
    ib = (float * ) qb -> imag;

    // split list into 2 halves; even and odd
    for (i = 0; i < N2; i++) {
      ra[i] = * r1++;
      ia[i] = * i1++;
      rb[i] = * r1++;
      ib[i] = * i1++;
    }

    // compute fft on both lists
    fft1D(qa, dir, qa);
    fft1D(qb, dir, qb);

    // build up coefficients
    if (!dir) // forward
      FCTR = -2 * PI / N;
    else 
      FCTR =  2 * PI / N;

    for (fctr = i = 0; i < N2; i++, fctr += FCTR) {
      c = cos(fctr);
      s = sin(fctr);
      a = c * rb[i] - s * ib[i];
      r2[i] = ra[i] + a;
      r2[i + N2] = ra[i] - a;

      a = s * rb[i] + c * ib[i];
      i2[i] = ia[i] + a;
      i2[i + N2] = ia[i] - a;
    }

    free(qa);
    free(qb);
  }

  if (!dir) { // inverse : divide by logN
    for (i = 0; i < N; i++) {
      q2 -> real[i] = q2 -> real[i]/2;
      q2 -> imag[i] = q2 -> imag[i]/2;
    }
  }
}

