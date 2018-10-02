
void histoMatchApprox(ImagePtr, ImagePtr, ImagePtr);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_histoMatch:
//
// Apply histogram matching to I1. Output is in I2.
//
void
HW_histoMatch(ImagePtr I1, ImagePtr targetHisto, bool approxAlg, ImagePtr I2)
{
	if(approxAlg) {
		histoMatchApprox(I1, targetHisto, I2);
		return;
	}

	else {

		IP_copyImageHeader(I1, I2);
		int w = I1->width();
		int h = I1->height();

		int total = w * h;

		// use IP_embedRange fto scale the range
		IP_embedRange(I1, 0.0, (double)MaxGray, I2);

		// initialize I2 dimension and buffer

		int targetW = targetHiso->width();
		int lut[targetW];


	}

}

void
histoMatchApprox(ImagePtr I1, ImagePtr targetHisto, ImagePtr I2)
{
}
