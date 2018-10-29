#include <algorithm>
#include <vector>
using std::vector;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW_median:
//
// Apply median filter of size sz x sz to I1.
// Clamp sz to 9.
// Output is in I2.
//


// need a function to get the median of  of the neighbor

// need a function to copy each row seperately

void
HW_median(ImagePtr I1, int sz, ImagePtr I2)
{
    int w = I1->width();
    int h = I1->height();
    int total = w * h;

    IP_copyImageHeader(I1, I2);
    int numOfNeighbors = 0;

    ChannelPtr<uchar> p1, p2, endPtr;
    int type;

	// make the row odd as usual
	if(sz % 2 == 0)
		sz++;

	if(sz == 1) {
		// just copy like I did on sharpening.. hah hah
	}

	else {
		// do the processing.... concentrate
		// for each row, copy and process
		
	}
}
