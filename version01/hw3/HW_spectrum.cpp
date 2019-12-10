
// ************************************************************


//extern void HW_fft2MagPhase(ImagePtr Ifft, ImagePtr Imag, ImagePtr Iphase);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_Spectrum:
//
// Compute magnitude and phase of I1 fourier transform.

#include "HW_utils.cpp"
// HW_utils.cpp includes the following functions
// void HW_fft2MagPhase(ImagePtr Ifft, ImagePtr Imag, ImagePtr Iphase);
// void zero_padding(ImagePtr I1, ImagePtr I2);
// void fft1D(complexP q1, int dir, complexP q2);
// void fft2D(ImagePtr I, int dir, ImagePtr Ifft);
// 
//	*****************************************

void
HW_spectrum(ImagePtr I1, ImagePtr Imag, ImagePtr Iphase)
{

	ImagePtr I1_cmp , Ifft;

	// pad zeros to make the length power of 2
	zero_padding(I1, I1_cmp);

	int w = I1_cmp->width();
	int h = I1_cmp->height();
	int total = w * h;
	int type;
	int uc_channel[1] = {0}; 

	// compute FFT of the input image
	fft2D(I1_cmp, 0, Ifft);	

// PUT YOUR CODE HERE...
	
	// compute magnitute and phase of FFT

	ImagePtr Imag_temp, Iphase_temp;
	HW_fft2MagPhase(Ifft, Imag_temp, Iphase_temp);
	
// PUT YOUR CODE HERE...

	// find min and max of magnitude
	ChannelPtr<float> tempPtr1;
	IP_getChannel(Imag_temp, 0, tempPtr1, type);
	float max = *tempPtr1;
	float min = *tempPtr1;

	for(int i = 0; i < total; i++) {
		if( max < tempPtr1[i] )
			max = tempPtr1[i] ;
		if( min > tempPtr1[i] )
			min = tempPtr1[i] ;
	}

// PUT YOUR CODE HERE...

	Imag->allocImage( w, h, uc_channel);
	Imag->freeChannels(1);
	ChannelPtr<uchar> magPtr;

// PUT YOUR CODE HERE...

	//scale magnitude to fit between [0, 255]
	max /=(2*max);
	float diff = abs(max - min);
	IP_getChannel(Imag_temp, 0, tempPtr1, type);
	IP_getChannel(Imag, 0, magPtr, type);

	for(int i = 0; i < total; i++) {
		magPtr[i] = CLIP(((tempPtr1[i] - min)/diff*MaxGray) ,0, MaxGray);
	}

// PUT YOUR CODE HERE...
	
	//find min and max of phase
	ChannelPtr<float> tempPtr2;
	IP_getChannel(Iphase_temp, 0, tempPtr2, type);
	max = *tempPtr2;
	min = *tempPtr2;

	for(int i = 0; i < total; i++) {
		if( max < tempPtr2[i] )
			max = tempPtr2[i];
		if( min > tempPtr2[i] )
			min = tempPtr2[i];
		//std::cout << tempPtr[i] << " ";
	}

// PUT YOUR CODE HERE...
	
	// allocate uchar image for displaying phase
	Iphase->allocImage(w, h, uc_channel);
	Iphase->freeChannels(1);
	ChannelPtr<uchar> phasePtr;
	
// PUT YOUR CODE HERE...

	//scale magnitude to fit between [0, 255]
	diff = abs(max - min);
	IP_getChannel(Iphase_temp, 0, tempPtr2, type);
	IP_getChannel(Iphase, 0, phasePtr, type);

	for(int i = 0; i < total; i++) {
		phasePtr [i] = CLIP(((tempPtr2[i] - min)/diff*MaxGray),0, MaxGray);	
	}

// PUT YOUR CODE HERE...

}
