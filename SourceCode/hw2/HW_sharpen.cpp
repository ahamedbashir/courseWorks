// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_sharpen:
//
// Sharpen image I1. Output is in I2.
//

//  Written by :  BASHIR AHAMED
//                SHOFIQUR RAHMAN
//                UCHA SAMADASHVILI
//
//  Semester   :  FALL 2018

// how to call HW_blur ????
// fixed it... using extern
extern void row_Blur(ChannelPtr<uchar> p1, ChannelPtr<uchar> p2, int length, int width, int jump);

extern void HW_blur(ImagePtr I1, int filterW, int filterH, ImagePtr I2);

void
HW_sharpen(ImagePtr I1, int size, double factor, ImagePtr I2)
{
	int w = I1->width();
	int h = I1->height();
	int total = w * h;


	IP_copyImageHeader(I1, I2);
	ChannelPtr<uchar> p1, p2, endPtr;
	int type;

	// no need to process if filter size is 1
	if(size == 1) {
		for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
			IP_getChannel(I2, ch, p2, type);
			for(endPtr = p1 + total; p1 < endPtr; )
				*p2++ = *p1++;
		}
	}

	else {
		// blur the image
		// ? Why not call the HW_blur function... nice
		// multiply with factor with the blurred diff and add with original value
		HW_blur(I1, size, size, I2);
		for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
			IP_getChannel(I2, ch, p2, type);
			for(endPtr = p1 + total; p1 < endPtr; p1++)
				*p2++ = CLIP( (factor * ( *p1 - *p2) + *p1), 0, MaxGray);
		}
	}
}
