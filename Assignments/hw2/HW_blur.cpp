// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_blur:
//
// Blur image I1 with a box filter (unweighted averaging).
// The filter has width filterW and height filterH.
// We force the kernel dimensions to be odd.
// Output is in I2.
//
void
HW_blur(ImagePtr I1, int filterW, int filterH, ImagePtr I2)
{
	ImagePtr I1_temp;
	IP_copyImageHeader(I1, I1_temp);
	IP_copyImageHeader(I1, I2);

	int w = I1->width();
	int h = I1->height();
	int total = w * h;

	ChannelPtr<uchar> p1, p1_temp, p2, endPtr;

	for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++ ) {
		IP_getChannel(I1_temp, ch, p1_temp, type);
		IP_getChannel(I2, ch, p2, type);

		if(filterW == 1) {
			for(endPtr = p1 + total; p1 < endPtr; )
				*p1_temp++ = *p1++;
		}

		if( filterW > 1) {
			// blur rows y = 0 to y = h
			// should I create a function for this
		}

		// blurr the temp image and output to I2
		if( filterH == 1) {
			for(endPtr = p1_temp + total; p1_temp < endPtr; )
				*p2++ = *p1_temp++;
		}

		if(filterH > 1) {
			// copy all the blurred rows
			// should I create a function for this
		}
	}
}
