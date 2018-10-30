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
void bufferedCopy(ChannelPtr<uchar> P, short* buf, int kernelSize, int width);

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

    if(sz > 9)
    	sz  = 9;
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

// function to copy a row pixels into a buffered array

void bufferedCopy(ChannelPtr<uchar> P, short* buf, int kernelSize, int width) {
	int i = 0, bufSize = kernelSize + width - 1;
	// copying the row pixels
	for( ; i < kernelSize / 2; i++)
		buf[i] = *P;
	for( ; i < kernelSize/2+width -1; i++)
		buf[i] = *P++;
	for( ; i < bufSize; i ++)
		buf[i] = *P;
}

int medianOfKNeighbors(std::vector<int> elements, int numOfNeighbors) {
	int total = elements.size();
	if(total == 1)
		return elements[0];
	else {
		std::sort(elements.begin(), elements.end());
		int mid = total / 2;
		if(numOfNeighbors == 0)
			return elements[mid];
		else {
			short sum = elements[mid];
			int i;
			for(i = 1; i <= numOfNeighbors; i++)
				sum = (sum + elements[mid-i] + elements[mid+i]);

			return sum/(2*i + 1);
		}

	}
}