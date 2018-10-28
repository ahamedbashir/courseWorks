// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_blur:
//
// Blur image I1 with a box filter (unweighted averaging).
// The filter has width filterW and height filterH.
// We force the kernel dimensions to be odd.
// Output is in I2.
//

void row_Blur(ChannelPtr<uchar> p1, ChannelPtr<uchar> p2, int length, int width, int jump) {
	// make the row odd
	if(width % 2 == 0)
		width++;

	// num of pixel on either side
	int numOfNeighbors = width / 2;
	int bufSize = length + width - 1;

	short* buf = new short[bufSize];
	int idx = 0;
	unsigned int sum = 0;

	// buffered copy for padding
	for(int i = 0; i < numOfNeighbors; i++)
		buf[i] = *p1;

	// copy pixels
	for( int i = numOfNeighbors; i < numOfNeighbors + length; i++) {
		buf[i] = p1[idx];
		idx += jump;
	}

	for(int i = numOfNeighbors + length; i < bufSize; i++) {
		buf[i] = p1[idx - jump];
	}

	for(int i = 0; i < width; i++)
		sum += buf[i];

	// blurred individual pixel
	for(int i = 0; i < length; i++) {
		int pos = i*jump;
		p2[pos] = sum / width;
		sum += (buf[width + i] - buf[i]);
	}
	delete[] buf;
}


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
	int type;

	for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++ ) {
		IP_getChannel(I1_temp, ch, p1_temp, type);
		IP_getChannel(I2, ch, p2, type);

		if(filterW == 1) {
			for(endPtr = p1 + total; p1 < endPtr; )
				*p1_temp++ = *p1++;
		}

		else if( filterW > 1) {
			// blur rows y = 0 to y = h
			// should I create a function for this
			for(int y = 0; y < h; y++) {
				row_Blur(p1, p1_temp, w, filterW, 1);
				p1 += w;
				p1_temp += w;
			}
		}

		p1_temp = p1_temp - total;

		// blurr the temp image and output to I2
		if( filterH == 1) {
			for(endPtr = p1_temp + total; p1_temp < endPtr; )
				*p2++ = *p1_temp++;
		}

		else if(filterH > 1) {
			// blurr columns
			// should I create a function for this
			for(int x  = 0; x < w; x++) {
				row_Blur(p1_temp, p2, h, filterH, w);
				p1_temp += 1;
				p2 += 1;
			}
		}
	}
}
