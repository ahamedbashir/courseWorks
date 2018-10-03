
void histoMatchApprox(ImagePtr, ImagePtr, ImagePtr);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_histoMatch:
//
// Apply histogram matching to I1. Output is in I2.
//
void
HW_histoMatch(ImagePtr I1, ImagePtr targetHisto, bool approxAlg, ImagePtr I2)
{
	std::cout << approxAlg << '\n';
	if(approxAlg) {
		// this is required

		histoMatchApprox(I1, targetHisto, I2);
		return;
	}

/*	else {
		// extra credit

		IP_copyImageHeader(I1, I2);
		int w = I1->width();
		int h = I1->height();

		int total = w * h;

		// use IP_embedRange fto scale the range
		IP_embedRange(I1, 0.0, (double)MaxGray, I2);

		// initialize I2 dimension and buffer

		int targetW = targetHisto->width();
		int *lut = new int[targetW];

		int H1[MXGRAY], lim[MXGRAY], *H2,  R, typeLut  = 0, type = 0;
		double minH, maxH;
		int left[MXGRAY], right[MXGRAY], index[MXGRAY];
		ChannelPtr<uchar> p, lutPtr, endPtr;

		for(int ch = 0; IP_getChannel(I2, ch, p, type); ++ch) {
			IP_getChannel(targetHisto, ch, lutPtr, typeLut);
			H2 = (int *) &lutPtr[0];

			// scaling H2 values with the dimension of input image

			int sumH = 0;
			for(int i = 0; i <MXGRAY; ++i)
				sumH += H2[i];

			double scale = (double)total/sumH;

			if( scale != 1) {
				sumH = 0;
				for ( int i = 0; i < MXGRAY; ++i) {
					H2[i] = round(H2[i] * scale);
					sumH  += H2[i];
					if ( sumH > totol) {
						H2[i] -= (sumH - total);
					for(: i < MXGRAY; ++i)
						H2[i] = 0;
					}
				}
			}

		// evaluage left, right, lim and 
			IP_histogram(I2, ch, H1, MXGRAY, minH, maxH);
			R = 0;
			sumH = 0;
			for(int i = 0; 

		// evaluate remapping
		


		// visit all input pixel and update the output
		

	}
*/
}

void
histoMatchApprox(ImagePtr I1, ImagePtr targetHisto, ImagePtr I2)
{
	IP_copyImageHeader(I1, I2);

	// computer histogram of I1
	int w = I1->width();
	int h = I1->height();
	
	int total = w * h;
	int H[MXGRAY];
	double avgH[MXGRAY];

	for(int i = 0; i < MXGRAY; ++i)
		H[i] = 0;

	ChannelPtr<uchar> p1, p2,p3, endPtr;
	int type;
	for( int ch = 0 ; IP_getChannel(I1, ch, p1, type); ch++) {
		for(int i = 0; i < total; ++i)
		{
			H[*p1++]++;
		}
	}

	// normalize histogram of I1
	double p = 0.0;
	for(int i = 0; i < MXGRAY; ++i) {
		avgH[i] = H[i] /(double)total; 
		p += avgH[i];
		std::cout << p << " ";
	}
	std::cout << " I1 total prabability = " << p << '\n';

	
	// compute  CDF of I1
	double CDF[MXGRAY];
	CDF[0] = avgH[0];

	for(int i = 1; i < MXGRAY; ++i)
		CDF[i] = CDF[i-1] + avgH[i];

	// compute Histogram of targetHisto

	int refH[MXGRAY]; 
	double avgRefH[MXGRAY];
	int refTotal = targetHisto->width() * targetHisto->height();

        for(int i = 0; i < MXGRAY; ++i)
                refH[i] = 0;

        for( int ch = 0 ; IP_getChannel(targetHisto, ch, p2, type); ch++) {
                for(int i = 0; i < MXGRAY; ++i){
                        refH[*p1++]++;
		}
        }

	// normalize targetHisto
        
	for(int i = 0; i < MXGRAY; ++i){
                avgRefH[i] = refH[i] /(double)refTotal; 
	}
  
	// compute CDF of targetHisto
	double refCDF[MXGRAY];
	refCDF[0] = refH[0];
	for(int i = 1; i < MXGRAY; ++i)
		refCDF[i] = refCDF[i-1] + avgRefH[i];


	// create look up table
	
	int lut[MXGRAY];

	for (int i = 0; i < MXGRAY; ++i) {
		int l = MaxGray;

		do {
			lut[i] = l;
			l--;
		} while(l >= 0 && refC[l] > C[i]);
		
	}
	
	//
	// debug lut 
	std:: cout << "lut values :\n";
	for(int i : lut)
		std::cout << i << " ";

	// update the output image pixel using lut
		
	for(int ch = 0; IP_getChannel(I1, ch, p1, type); ++ch) {
		IP_getChannel(I2, ch, p2, type);
		for(endPtr = p1 + total; p1 < endPtr; )
			*p2++ = lut[*p1++];
	}		

}
