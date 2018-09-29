
#include "IP.h"

using namespace IP;


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

// PUT YOUR CODE HERE...

	// compute sqrt( real^2 + imag^2 )
	// compute atan2( imag/real )

// PUT YOUR CODE HERE...

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

}

