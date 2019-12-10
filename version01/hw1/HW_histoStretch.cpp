// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_histoStretch:
//
// Apply histogram stretching to I1. Output is in I2.
// Stretch intensity values between t1 and t2 to fill the range [0,255].


void
HW_histoStretch(ImagePtr I1, int t1, int t2, ImagePtr I2)
{

	// Image header
	IP_copyImageHeader(I1, I2);

	int w = I1->width();
	int h = I1->height();
	int total = w*h;

	int i, lut[MXGRAY];

	// get the max differce to distribute the values
	int minMaxDiff = t2 - t1;
	//  distribute the values over the range (0,255) inclusive
	for(i = 0; i < MXGRAY; ++i)
		lut[i] = CLIP( floor((double)(i-t1)/minMaxDiff * MaxGray) ,0,MaxGray);

	
	ChannelPtr<uchar> p1, p2, endPtr;
	int type;

	for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
		IP_getChannel(I2, ch, p2, type);
		for(endPtr = p1 + total; p1 < endPtr; )
			*p2++ = lut[*p1++];
	}



}
