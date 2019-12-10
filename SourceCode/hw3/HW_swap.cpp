// ************************************************************
// ************************************************************

// complex struct data type for fft1D

typedef struct {
        int len;	// length of complex number list
        float * real;	// pointer to real number list
        float * imag;	// pointer to imaginary number list
} complexS, *complexP;


extern void HW_fft2MagPhase(ImagePtr Ifft, ImagePtr Imag, ImagePtr Iphase);
extern void HW_magPhase2FFT(ImagePtr Imag, ImagePtr Iphase, ImagePtr Ifft);
extern void fft1D(complexP q1, int dir, complexP q2);
extern void fft2D(ImagePtr I, int dir, ImagePtr Ifft);
extern void zero_padding(ImagePtr I1, ImagePtr I2);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_swap:
//
// swap phase of I1 with I2.
// I1_mag   + I2_phase -> II1
// I1_phase + I2_mag   -> II2
void
HW_swap(ImagePtr I1, ImagePtr I2, ImagePtr II1, ImagePtr II2)
{
	// i can make both picture with same width if time permits
	ImagePtr Ifft1, Ifft2, IinvFFT1, IinvFFT2;
	ImagePtr Imag1, Iphase1, Imag2, Iphase2;


	IP_copyImageHeader(I1, II1);
	IP_copyImageHeader(I2, II2);

	int w = I1->width();
	int h = I1->height();

	if(I1->width() != I2->width() || I1->height() != I2->height()) {
		// this condition ensures to not crash the program but giving the
		// user another chance to select proper images to swap,
		std::cout << "\t****  Images to swap must be of same dimension  ****\n";
		std::cout << "\t***  partially swapped images will be printed  ***\n";
		std::cout << "\t***  Please, select SAME dimensional images to SWAP  ***\n";
		return;
	}

	// compute FFT of I1 and I2
	ImagePtr I1_pad, I2_pad;
	zero_padding(I1, I1_pad);
	zero_padding(I2, I2_pad);
	
	fft2D(I1_pad, 0, Ifft1);
	fft2D(I2_pad, 0, Ifft2);

// PUT YOUR CODE HERE...

	// compute magnitude and phase from real and imaginary of FFT

	HW_fft2MagPhase(Ifft1, Imag1, Iphase1);
	HW_fft2MagPhase(Ifft2, Imag2, Iphase2);

// PUT YOUR CODE HERE...

	// swap phases of FFT1 and FFT2 and 

		// after swapping code

	// convert mag and phase to real and imaginary 

	HW_magPhase2FFT(Imag1, Iphase2, Ifft1);
	HW_magPhase2FFT(Imag2, Iphase1, Ifft2);


// PUT YOUR CODE HERE...

	// compute inverse FFT
	
	fft2D(Ifft1, 1, IinvFFT1);
	fft2D(Ifft2, 1,IinvFFT2);
	
// PUT YOUR CODE HERE...
	// compute magnitude and phase from real and imaginary of inversed FFT

	HW_fft2MagPhase(IinvFFT1, Imag1, Iphase1);
	HW_fft2MagPhase(IinvFFT2, Imag2, Iphase2);
	
// PUT YOUR CODE HERE...

	// allocate uchar image and cast float channel to uchar for mag1
	int type;
	ChannelPtr<float> mag1, mag2;
	ChannelPtr<uchar> II1Ptr, II2Ptr;

	IP_getChannel(II1, 0, II1Ptr, type);
	IP_getChannel(Imag1, 0, mag1, type);
	int pad_w = Imag1->width();
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			*II1Ptr++ = CLIP(*(mag1 + j + i*pad_w),0,MaxGray);
		}
	}

// PUT YOUR CODE HERE...

	// allocate uchar image and cast float channel to uchar for mag2
	IP_getChannel(II2, 0, II2Ptr, type);
	IP_getChannel(Imag2, 0, mag2, type);
	*II2Ptr = *mag2;
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			*II2Ptr++ = CLIP(*(mag2 + j + i * pad_w), 0, MaxGray);
		}
	}

// PUT YOUR CODE HERE...

}
