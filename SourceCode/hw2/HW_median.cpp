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

//  Written by :  BASHIR AHAMED
//                SHOFIQUR RAHMAN
//                UCHA SAMADASHVILI
//
//  Semester   :  FALL 2018

// need a function to get the median of  of the neighbor

// need a function to copy each row seperately
void bufferedRowCopy(ChannelPtr<uchar> P, short* buf, int kernelSize, int width);
int medianOfNeighbors(std::vector<int> neighbors, int numOfNeighbors);

void
HW_median(ImagePtr I1, int sz, ImagePtr I2)
{
    int w = I1->width();
    int h = I1->height();
    int total = w * h;

    IP_copyImageHeader(I1, I2);
    int numOfNearestNeighbors = 0;

    ChannelPtr<uchar> p1, p2, endPtr;
    int type;

	// make the row odd as usual
	if(sz % 2 == 0)
		sz++;
	if(sz > 9)
		sz = 9;

	// do the processing.... concentrate
	short* buf[sz];
	int length = sz + w - 1;
	for(int i = 0; i < sz; i++)
		buf[i] = new short[length];

	for(int ch = 0; IP_getChannel(I1, ch, p1, type); ch++) {
		IP_getChannel(I2, ch, p2, type);
		endPtr = p1 + total;
		int px;
		for(px = 0; px < sz/2; px++)
			bufferedRowCopy(p1, buf[px], sz, w);
		for( ; px < sz; px++ ) {
			bufferedRowCopy(p1, buf[px], sz, w);
			p1  = p1 + w;
		}

		std::vector<int> neighbors(0);
		for(int y = 0; y < h; y++) {
			for(int j = 0; j < sz; j++) {
				for(int i = 0; i < sz; i++)
					neighbors.push_back(buf[i][j]);
			}

			for(int x = 0; x < w; x++) {
				*p2++ = medianOfNeighbors(neighbors, numOfNearestNeighbors);
				if( x < w - 1) {
					neighbors.erase(neighbors.begin(), neighbors.begin()+sz);
					for(int i = 0; i < sz; i++)
						neighbors.push_back(buf[i][sz+x]);
				}
			}
			neighbors.clear();
			bufferedRowCopy(p1, buf[(sz + y -1)%sz], sz, w);
			if(p1 < endPtr - w)
				p1 = p1 + w;

		}
	}
	for(int i = 0; i < sz; i++)
		delete[] buf[i];

}

// function to copy a row pixels into a buffered array
void bufferedRowCopy(ChannelPtr<uchar> P, short* buf, int kernelSize, int width) {
	int i = 0;
	// copying the row pixels
	for( ; i < kernelSize / 2; i++)
		buf[i] = *P;
	for( ; i < kernelSize/2+width -1; i++)
		buf[i] = *P++;
	for( ; i < kernelSize + width - 1; i ++)
		buf[i] = *P;
}

int medianOfNeighbors(std::vector<int> neighbors, int numOfNearestNeighbors) {
	int total = neighbors.size();
	if(total == 1)
		return neighbors[0];
	else {
		std::sort(neighbors.begin(), neighbors.end());
		int mid = total / 2;
		if(numOfNearestNeighbors == 0){
			if(total %2 != 0)
				return neighbors[mid];
			else
				return std::ceil((neighbors[mid] + neighbors[mid-1])/2);
		}

		else {
			short sum = neighbors[mid];
			int i = 0;
			for(i = 1; i <= numOfNearestNeighbors; i++)
				sum = (sum + neighbors[mid-i] + neighbors[mid+i]);

			return sum/(2*i + 1);
		}

	}
}
