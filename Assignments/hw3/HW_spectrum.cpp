
extern void HW_fft2MagPhase(ImagePtr Ifft, ImagePtr Imag, ImagePtr Iphase);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_Spectrum:
//
// Compute magnitude and phase of I1 fourier transform.
// 
//
void
HW_spectrum(ImagePtr I1, ImagePtr Imag, ImagePtr Iphase)
{


	// compute FFT of the input image
	
// PUT YOUR CODE HERE...
	
	// compute magnitute and phase of FFT
	
// PUT YOUR CODE HERE...

	// find min and max of magnitude

// PUT YOUR CODE HERE...

	// allocate uchar image for displaying magnitude

// PUT YOUR CODE HERE...
	
	//scale magnitude to fit between [0, 255]

// PUT YOUR CODE HERE...
	
	//find min and max of phase 

// PUT YOUR CODE HERE...
	
	// allocate uchar image for displaying phase
	
// PUT YOUR CODE HERE...
	
	//scale magnitude to fit between [0, 255]

// PUT YOUR CODE HERE...
}
