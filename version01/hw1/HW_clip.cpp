// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_clip:
//
// Clip intensities of image I1 to [t1,t2] range. Output is in I2.
// If    input<t1: output = t1;
// If t1<input<t2: output = input;
// If      val>t2: output = t2;
//
//
void
HW_clip(ImagePtr I1, int t1, int t2, ImagePtr I2)
{
	// copy the image header of the input image I1 (width, height) into the output image I2
	
	IP_copyImageHeader(I1, I2);
	
	int w = I1->width();
	int h = I1->height();
	int total = w*h;

	int i, lut[MXGRAY];

	// create the look up table
	//
	// assign t1 to lut for all i <=t1	
	for( i = 0; i < t1; ++i)
		lut[i] = t1;

	// assing i to lut for all values > t1 but <t2
	for( ; i < t2; ++i)
		lut[i] = i;

	// assign t2 to lut for all i >= t2
	for(i = t2; i <MXGRAY; ++i)
		lut[i] = t2;

	ChannelPtr<uchar> p1, p2, endPtr;
	int type;

	// update the values of output image based of the lut
	for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
		IP_getChannel(I2, ch, p2, type);
		for(endPtr = p1 + total; p1 < endPtr; )
			*p2++ = lut[*p1++];
	}

}
