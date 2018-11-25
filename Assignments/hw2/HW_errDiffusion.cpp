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


//  Written by :  BASHIR AHAMED
//                SHOFIQUR RAHMAN
//                UCHA SAMADASHVILI
//
//  Semester   :  FALL 2018


// function for gamma correction
void gammaCorrect(ImagePtr I1, double gamma, ImagePtr I2);

// function to copy row pixels into a buffered array
void bufferedCopy(ChannelPtr<uchar> P, short* buf, int kernelSize, int width);

void
HW_errDiffusion(ImagePtr I1, int method, bool serpentine, double gamma, ImagePtr I2)
{
  // weights for floyed-steinberg method
    double fl_st[4];
    fl_st[0] = 7/16.0;
    fl_st[1] = 5/16.0;
    fl_st[2] = 3/16.0;
    fl_st[3] = 1/16.0;
// weights for Jarvis-Judice-Ninke method
    double jjn[4];
    jjn[0] = 7/48.0;
    jjn[1] = 5/48.0;
    jjn[2] = 3/48.0;
    jjn[3] = 1/48.0;

    ImagePtr I1_temp;
    IP_copyImageHeader(I1, I2);

    // gamma corrected image copied into I1_temp
    gammaCorrect(I1, gamma, I1_temp);

    int w = I1->width();
    int h = I1->height();
    int type;
    ChannelPtr<uchar> p1, p2, endPtr;
    // int kernelSize = 3;
    // threshold is
    int th = MXGRAY/2;
    uchar* p2_temp;

    // circular buffer
    short* buf[3];
    buf[0] = new short[w+4];
    buf[1] = new short[w+4];
    buf[2] = new short[w+4];
    // padding with two extra space for both side of the row
    short* rowBuf0 = buf[0] + 2;
    short* rowBuf1 = buf[1] + 2;
    short* rowBuf2 = buf[2] + 2;
    int err;
    
    for(int ch=0; IP_getChannel(I1_temp,ch,p1,type); ch++){
      IP_getChannel(I2,ch,p2,type);

      //floyd-Steinberg
      if(method == 0) { 
        // 
        for(int i = 0; i < w; i ++)
          rowBuf0[i] = *p1++;
        // copy 1st row
        for(int i = 0; i < w; i++)
          rowBuf1[i] = *p1++;

        // padding on both side of the rows
        rowBuf0[w] = rowBuf0[w-1];
        rowBuf0[-1] = rowBuf0[0];
        rowBuf1[w] = rowBuf1[w-1];
        rowBuf1[-1] = rowBuf1[0]; 

        // iterate over all the rows remaining
        for(int i = 0; i < h; i++) {
          p2_temp = (uchar *)&p2[0];
          // raster scan
          if( !serpentine || i%2 != 0 ) {
            for(int j = 0; j < w; j++){
              p2_temp[j] = (rowBuf0[j] < th)? 0: MaxGray;
              err = rowBuf0[j] - p2_temp[j];
              rowBuf0[j+1] += err * fl_st[0];
              rowBuf1[j-1] += err * fl_st[2];
              rowBuf1[j]   += err * fl_st[1];
              rowBuf1[j+1] += err * fl_st[3];
              }
            }
            // serpentine scan
            else if(serpentine){
              for(int j = w-1; j >= 0; j--){
                p2_temp[j] = (rowBuf0[j] < th)? 0: MaxGray;
                err = rowBuf0[j] - p2_temp[j];
                rowBuf1[j-1] += err * fl_st[0];
                rowBuf0[j+1] += err * fl_st[2];
                rowBuf1[j]   += err * fl_st[1];
                rowBuf1[j-1] += err * fl_st[3];
              }
            }
            // swap rows
          rowBuf0 = rowBuf1;
          rowBuf1 = buf[i%2] + 2;
          // update rows after swap
          if(i < h-2){
            for(int j = 0; j < w; j++)
              rowBuf1[j] = *p1++;
          }
          p2 += w;
      }
    }

    //Jarvis-Judice-Ninke
    if(method == 1) {
      // copy rows
      for(int i = 0; i < w; i++)
        rowBuf0[i] = *p1++;
      for(int i = 0; i < w; i++)
         rowBuf1[i] = *p1++;
      for(int i = 0; i < w; i++)
          rowBuf2[i] = *p1++;
      // padding rows on both side
      rowBuf0[-2] = rowBuf0[-1] = rowBuf0[0];
      rowBuf0[w+1] = rowBuf0[w] = rowBuf0[w-1];
      rowBuf1[-2] = rowBuf1[-1] = rowBuf1[0];
      rowBuf1[w+1] = rowBuf1[w] = rowBuf1[w-1];
      rowBuf2[-2] = rowBuf2[-1] = rowBuf2[0];
      rowBuf2[w+1] = rowBuf2[w] = rowBuf2[w-1];
          
      for(int i = 0; i < h; i++){
        p2_temp = (uchar *)&p2[0];
        // raster scan
        if(!serpentine || i%2 != 0){
          for(int j = 0; j < w; j++){
            p2_temp[j] = (rowBuf0[j] < th)? 0: MaxGray;
            err = rowBuf0[j] - p2_temp[j];
            rowBuf0[j+1] += err * jjn[0];
            rowBuf0[j+2] += err * jjn[1];
            rowBuf1[j-2] += err * jjn[2];
            rowBuf1[j-1] += err * jjn[1];
            rowBuf1[j]   += err * jjn[0];
            rowBuf1[j+1] += err * jjn[1];
            rowBuf1[j+2] += err * jjn[2];
            rowBuf2[j-2] += err * jjn[3];
            rowBuf2[j-1] += err * jjn[2];
            rowBuf2[j]   += err * jjn[1];
            rowBuf2[j+1] += err * jjn[2];
            rowBuf2[j+2] += err * jjn[3];
            }
          }

          // serpentine scan
          else{
            for(int j  = w-1; j >= 0; j--){
              p2_temp[j] = (rowBuf0[j] < th)? 0: MaxGray;
              
              err = rowBuf0[j] - p2_temp[j];
              rowBuf0[j-1] += err * jjn[0];
              rowBuf0[j-2] += err * jjn[1];
              rowBuf1[j+2] += err * jjn[2];
              rowBuf1[j+1] += err * jjn[1];
              rowBuf1[j]   += err * jjn[0];
              rowBuf1[j-1] += err * jjn[1];
              rowBuf1[j-2] += err * jjn[2];
              rowBuf2[j+2] += err * jjn[3];
              rowBuf2[j+1] += err * jjn[2];
              rowBuf2[j]   += err * jjn[1];
              rowBuf2[j-1] += err * jjn[2];
              rowBuf2[j-2] += err * jjn[3];
            }
          }

          // swap rows 
          rowBuf0 = rowBuf1;
          rowBuf1 = rowBuf2;
          rowBuf2 = buf[i%3] + 2;
          //update swapped rows
          if(i < h-3){
            for(int j = 0; j < w; j++){
               rowBuf2[j] = *p1++;
             }
          }
          p2 += w;
        }
      }
    }
    // clear buf
    for(int i=0; i<3; i++){
      delete[] buf[i];
    }
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
        lut[i] = CLIP(int(pow((double)i/MaxGray, expGamma ) * MaxGray), 0,MaxGray);

    ChannelPtr<uchar> p1, p2, endPtr;
    int type;
    // update the corresponding output pixel of the imput image pixel based on the lut values
    for(int ch = 0; IP_getChannel(I1, ch, p1, type); ++ch) {
        IP_getChannel(I2, ch, p2, type);
        for(endPtr = p1 + total; endPtr > p1; )
            *p2++ = lut[*p1++];
    }
}


