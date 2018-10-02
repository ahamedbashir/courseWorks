
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

	else {
		// extra credit

		IP_copyImageHeader(I1, I2);
		int w = I1->width();
		int h = I1->height();

		int total = w * h;

		// use IP_embedRange fto scale the range
		IP_embedRange(I1, 0.0, (double)MaxGray, I2);

		// initialize I2 dimension and buffer

		int targetW = targetHisto->width();
		int lut[targetW];


		// evaluate remapping
		


		// visit all input pixel and update the output
		

	}

}

void
histoMatchApprox(ImagePtr I1, ImagePtr targetHisto, ImagePtr I2)
{
	IP_copyImageHeader(I1, I2);

	// computer normalize histogram of I1
	int w = I1->width();
	int h = I1->height();
	
	int total = w * h;
	int H[MXGRAY];
	double avgH[MXGRAY];

	for(int i = 0; i < MXGRAY; ++i)
		H[i] = 0;

	ChannelPtr<uchar> p1, p2, endPtr;
	int type;
	for( int ch = 0 ; IP_getChannel(I1, ch, p1, type); ch++) {
		for(endPtr = p1 + total; p1 < endPtr; p1++)
			H[*p1]++;
	}

	// normalize 
	for(int i = 0; i < MXGRAY; ++i)
		avgH[i] = H[i] /(double)total; 
	
	// for debugging only
	int totalP = 0;
	for ( int i : H){
		std::cout << i << " ";
		totalP += i;
	}
	std::cout << "\ntotal in H = "<<totalP << '\n';
	std::cout << "total int I =  "  << total << '\n';

	// compute the running sum avg  of normalized histogram
	
	double avgC[MXGRAY];
	avgC[0] = avgH[0];

	for(int i = 1; i < MXGRAY; ++i)
		avgC[i] = avgC[i-1] + avgH[i];

	// compute running sum avg of targetHisto
	IP_copyImageHeader(I1, targetHisto);
	int refH[MXGRAY]; 
	double avgRefH[MXGRAY];

	int refTotal = targetHisto->width() * targetHisto->height();


        for(int i = 0; i < MXGRAY; ++i)
                refH[i] = 0;


        for( int ch = 0 ; IP_getChannel(targetHisto, ch, p1, type); ch++) {
                for(endPtr = p1 + total; p1 < endPtr; p1++)
                        refH[*p1]++;
        }

	// normalize 
        for(int i = 0; i < MXGRAY; ++i)
                avgRefH[i] = refH[i] /(double)refTotal; 
    
        // for debugging only
        totalP = 0;
        for ( int i : refH){ 
                std::cout << i << " ";
                totalP += i;
        }
        std::cout << "\ntotal in H = "<<totalP << '\n';
        std::cout << "total int I =  "  << refTotal << '\n';

	std:: cout << refTotal << '\n';

	// runing sum avg of targetHisto
	
	double avgRefC[MXGRAY];
	avgRefC[0] = avgRefH[0];
	for(int i = 1; i < MXGRAY; ++i)
		avgRefC[i] = avgRefC[i-1] + avgRefH[i];


	// create look up table
	
	int lut[MXGRAY];

	for (int i = 0; i < MXGRAY; ++i) {

		int l = MaxGray;

		do {
			lut[i] = l;
			l--;
		} while(l >= 0 && avgRefC[l] >= avgC[i]);
	}
	


	// update the output image pixel using lut
	

}
