// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_gammaCorrect:
//
// Gamma correct image I1. Output is in I2.
//
void
HW_gammaCorrect(ImagePtr I1, double gamma, ImagePtr I2)
{
	IP_copyImageHeader(I1, I2);

	int w = I1->width();
	int h = I1->height();
	int total = w*h;

	double expGamma = 1/gamma;

	int i,  lut[MXGRAY];
	
	for(i = 0; i < MXGRAY; ++i)
		// PixelOut = Constant * PixelInput^gamma
		// here to make it linear gamma = 1/given gamma
		// distribute i over the range (0, MXGRAY)
		lut[i] = CLIP(int(pow((double)i/MaxGray, expGamma ) * MaxGray), 0,MaxGray);
	
	ChannelPtr<uchar> p1, p2, endPtr;
	int type;

	// update the corresponding output pixel of the imput image pixel
	// based on the lut values 

	for(int ch = 0; IP_getChannel(I1, ch, p1, type); ++ch) {
		IP_getChannel(I2, ch, p2, type);
		
		for(endPtr = p1 + total; endPtr > p1; )
			*p2++ = lut[*p1++];
	}
}
