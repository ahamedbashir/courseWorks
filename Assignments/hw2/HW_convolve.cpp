// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_convolve:
//
// Convolve I1 with filter kernel in Ikernel.
// Output is in I2.
//

// function to copy row pixels into a buffer

void
HW_convolve(ImagePtr I1, ImagePtr Ikernel, ImagePtr I2)
{
	int w = I1->width();
	int h = I1->height();
	int total = w * h;

	IP_copyImageHeader(I1, I2);
	ChannnelPtr<uchar> p1, p2, endPtr;
	int type;

	if(Ikernel->width() > 1) {
		int kernelWidth = Ikernel->width();
		short* buf[kernelWidth];
		int length = kernelWidth + w - 1;

		for(int i = 0; i < kernelWidth; i++)
			buf[i] = new short[length];

 		ChannnelPtr<double> kernelPtr;
 		IP_getChannel(Ikernel, ch, kernelPtr, type);

 		for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
 			endPtr = p1 + total;

 			IP_getChannel(I2, ch, p2, type);

 			// copy and pad top row

 			// iterate over all the rows


 			// process each row using the kernelPtr

 			// update the buffered rows

 			// copy row

 		}

	}
	else {
		for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
 			IP_getChannel(I2, ch, p2, type);
 			for(endPtr = p1 + total; p1 < endPtr; )
 				*p2++ = *p1++;
 		}
	}
}
