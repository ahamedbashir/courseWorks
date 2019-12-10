// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_convolve:
//
// Convolve I1 with filter kernel in Ikernel.
// Output is in I2.
//
//
//  Semester   :  FALL 2018

// function to copy row pixels into a buffer
extern void bufferedRowCopy(ChannelPtr<uchar> P, short* buf, int kernelSize, int width);
void
HW_convolve(ImagePtr I1, ImagePtr Ikernel, ImagePtr I2)
{
	int w = I1->width();
	int h = I1->height();
	int total = w * h;

	ChannelPtr<uchar> p1, p2, endPtr;
	ChannelPtr<float> kernelPtr;
	int type;
	IP_copyImageHeader(I1, I2);
	IP_getChannel(Ikernel, 0, kernelPtr, type);
	
	int kernelSize = Ikernel->width();
	short* buf[kernelSize];
	int length = kernelSize + w - 1;
	for(int i = 0; i < kernelSize; i++)
		buf[i] = new short[length];

 	for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
 		endPtr = p1 + total;
 		IP_getChannel(I2, ch, p2, type);
 		
 		// copy and pad top row
 		int px;
 		for( px = 0; px < kernelSize/2; px++)
 			bufferedRowCopy(p1, buf[px], kernelSize, w);
 		// iterate over all the rows
 		for( ; px < kernelSize; px++) {
 			bufferedRowCopy(p1, buf[px], kernelSize, w);
 			if(p1 < endPtr - w)
 				p1 += w;
 		}

 		// process each row using the kernelPtr
 		for(int y = 0; y < h; y++) {
 			for(int x = 0; x < w; x++) {
				double sum = 0.0; // double integration (summation)
 				for(int i = 0; i < kernelSize; i++) {
 					for(int j = 0; j < kernelSize; j++) {
 						sum += (*kernelPtr) * buf[i][x+j];
 						kernelPtr++;
 					}
  				}
  				sum = std::floor(sum);
  				*p2++ = CLIP(int(sum), 0, MaxGray);
  				kernelPtr = (kernelPtr - kernelSize * kernelSize);
 			}

	 		// cicularly update the buffer
	 		for(int i = 0; i < kernelSize - 1; i++) {
	 			for(int j = 0; j < length; j++)
					buf[i][j] = buf[i+1][j];
	  		}
	 		// copy row h - 1;
	 		bufferedRowCopy(p1, buf[kernelSize-1], kernelSize, w);
	 		if(p1 < endPtr - w)
	 			p1 += w;
	 	}
 	}
 	for(int i = 0; i < kernelSize; i++)
		delete[] buf[i];
}