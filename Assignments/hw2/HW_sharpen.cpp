// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_sharpen:
//
// Sharpen image I1. Output is in I2.
//
void
HW_sharpen(ImagePtr I1, int size, double factor, ImagePtr I2)
{
	int w = I1->width();
	int h = I1->height();
	int total = w * h;


	IP_copyImageHeader(I1, I2);
	ChannelPtr<uchar> p1, p2, endPtr;
	int type;

	// no need to process if size is 1
	if(size == 1) {
	}

	else {
		// blur the image
		// multiply with factor with the blurred diff and add with original value
	}
}
