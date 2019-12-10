// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_contrast:
//
// Apply contrast enhancement to I1. Output is in I2.
// Stretch intensity difference from reference value (128) by multiplying
// difference by "contrast" and adding it back to 128. Shift result by
// adding "brightness" value.
//


void
HW_contrast(ImagePtr I1, double brightness, double contrast, ImagePtr I2)
{
	IP_copyImageHeader(I1, I2);
	int w = I1->width();
	int h = I1->height();
	int total = w*h;

	int i, lut[MXGRAY];

	// update the lut using the brightness, add shift( 128 + brightness)
	// clip the values between 0 to 255
	for(i = 0; i <MXGRAY; ++i) 
		lut[i] = CLIP( round((i-128)*contrast + 128 + brightness), 0, MaxGray);

	ChannelPtr<uchar> p1, p2, endPtr;
	int type;

	// update the output values for each pixel based on the input image pixel
	// using the lut
	for( int ch = 0; IP_getChannel(I1, ch, p1, type); ++ch) {
		IP_getChannel(I2, ch, p2, type);
		for(endPtr = p1 + total; endPtr > p1; )
			*p2++ = lut[*p1++];
	}
}
