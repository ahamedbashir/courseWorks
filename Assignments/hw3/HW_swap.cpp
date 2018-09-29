
extern void HW_fft2MagPhase(ImagePtr Ifft, ImagePtr Imag, ImagePtr Iphase);
extern void HW_magPhase2FFT(ImagePtr Imag, ImagePtr Iphase, ImagePtr Ifft);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_swap:
//
// swap phase of I1 with I2.
// I1_mag   + I2_phase -> II1
// I1_phase + I2_mag   -> II2
void
HW_swap(ImagePtr I1, ImagePtr I2, ImagePtr II1, ImagePtr II2)
{
	ImagePtr Ifft1, Ifft2, IinvFFT1, IinvFFT2;
	ImagePtr Imag1, Iphase1, Imag2, Iphase2;

	// compute FFT of I1 and I2
	
// PUT YOUR CODE HERE...

	// compute magnitude and phase from real and imaginary of FFT
	
// PUT YOUR CODE HERE...

	// swap phases of FFT1 and FFT2 and 
	// convert mag and phase to real and imaginary 
	
// PUT YOUR CODE HERE...

	// compute inverse FFT
	
// PUT YOUR CODE HERE...

	// compute magnitude and phase from real and imaginary of inversed FFT
	
// PUT YOUR CODE HERE...

	// allocate uchar image and cast float channel to uchar for mag1

// PUT YOUR CODE HERE...

	// allocate uchar image and cast float channel to uchar for mag2

// PUT YOUR CODE HERE...

}
