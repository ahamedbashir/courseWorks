// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_errDiffusion:
//
// Apply error diffusion algorithm to image I1.
//
// This procedure produces a black-and-white dithered version of I1.
// Each pixel is visited and if it + any error that has been diffused to it
// is greater than the threshold, the output pixel is white, otherwise it is black.
// The difference between this new value of the pixel from what it used to be
// (somewhere in between black and white) is diffused to the surrounding pixel
// intensities using different weighting systems.
//
// Use Floyd-Steinberg     weights if method=0.
// Use Jarvis-Judice-Ninke weights if method=1.
//
// Use raster scan (left-to-right) if serpentine=0.
// Use serpentine order (alternating left-to-right and right-to-left) if serpentine=1.
// Serpentine scan prevents errors from always being diffused in the same direction.
//
// A circular buffer is used to pad the edges of the image.
// Since a pixel + its error can exceed the 255 limit of uchar, shorts are used.
//
// Apply gamma correction to I1 prior to error diffusion.
// Output is saved in I2.
//

// function for gamma correction
void gammaCorrect(ImagePtr I1, double gamma, ImagePtr I2);

// function to copy row pixels into a buffered array
void bufferedCopy(ChannelPtr<uchar> P, short* buf, int kernelSize, int width);

void
HW_errDiffusion(ImagePtr I1, int method, bool serpentine, double gamma, ImagePtr I2)
{
	ImagePtr I1_temp;
	IP_copyImageHeader(I1, I1_temp);
	IP_copyImageHeader(I1, I2);

	// gamma corrected image copied into I1_temp
	gammaCorrect(I1, gamma, I1_temp);

	int w = I1->width();
    int h = I1->height();

    int type;
    ChannelPtr<uchar> p1, p2, endPtr;


    int kernelSize = 3;
    // threshold is
    int th = MXGRAY/2;

    // Floyd-Steinberg method

    if ( method == 0) {
    	short* input1;
    	short* input2;

    	short err;

    	int bufSize  = w + 2;

    	// top row buffer
    	short* buf0 = new short[bufSize];
    	// bottom row buffer
    	short* buf1 = new short[bufSize];

    	for(int ch = 0; IP_getChannel(I1_temp, ch, p1, type); ch++) {
    		IP_getChannel(I2, ch, p2, type);

    		// copy 1st row to buffer
    		bufferedCopy(p1, buf0, kernelSize, w);

    		p1 += w;

    		// iterate over all the rows y from 2nd row ( y =1 )
    		for(int  y = 1; y < h; y++) {
    			// with serpentine scan

    			if(serpentine) {



    			}

    			// with raster scan
    			else {


    			}
    		}
    	}

    }


    // Jarvis-Judice-Ninke method

    else if (method == 1) {

    	int err;
    	int bufSize  = w + 4;
    	kernelSize = 5;

    	short** input = new short*[3];
    	short** buf = new short*[3];
    	for(int i = 0; i < 3; i++)
    		buf[i] = new short[bufSize];

    	for(int ch = 0; IP_getChannel(I1_temp, ch, p1, type); ch++) {
    		IP_getChannel(I2, ch, p2, type);

    		// copy top two rows into the buffered array
    		bufferedCopy(p1, buf[0], kernelSize, w);
    		bufferedCopy(p1, buf[1], kernelSize, w);
    		p1 += w;

    		// iterate over all the remaining rows
    		for(int y = 2; y < h; y++) {
    			if (y % 3 == 0)
    				bufferedCopy(p1, buf[0], kernelSize, w);
                else if (y % 3 == 1)
                	bufferedCopy(p1, buf[1], kernelSize, w);
                else if (y % 3 == 2)
                	bufferedCopy(p1, buf[2], kernelSize, w);
                
                p1 = p1 + w;

                // with serpentine scan
                if(serpentine) {

                }

                // with raster scan
                else {

                }

    		}
    	}
    }
    // without serpentine or raster scan
    else {
    	for(int ch = 0; IP_getChannel(I1_temp, ch, p1, type); ch++) {
            IP_getChannel(I2, ch, p2, type);
            for(endPtr = p1 + total; p1 < endPtr; )
            	*p2++ = *p1++;
        }
    }
}


// function to copy a row pixels into a buffered array

void bufferedCopy(ChannelPtr<uchar> P, short* buf, int kernelSize, int width) {
	int i = 0, bufSize = kernelSize + width - 1;
	// copying the row pixels
	for( ; i < kernelSize / 2; i++)
		buf[i] = *P;
	for( ; i < kernelSize/2+w -1; i++)
		buf[i] = *P++;
	for( ; i < bufSize; i ++)
		buf[i] = *P;
}


// gamma correction function from HW1_gamma.cpp
void gammaCorrect(ImagePtr I1, double gamma, ImagePtr I2)
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

