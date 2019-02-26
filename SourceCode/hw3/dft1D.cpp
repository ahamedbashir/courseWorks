// ** refererence code: fft1d.c by Professor George Wolberg, CCNY **


// ************************************************************
//      Written by :    BASHIR AHAMED
//
//      https://github.com/ahamedbashir/imageProcessing
//
//      Semester   :    FALL 2018
// ************************************************************


//  ***********************
// to compile : g++ dft1D.cpp

#include<iostream>
#include<cstdlib>
#include<cmath>

// constant number PI
#define PI 3.1415927

// struct data type to represent complex number
typedef struct {
    float* real;
    float* imag;
    int len;    
} complexS, *complexP;

// fft1D from professors sample code
void dft1d(complexP q1, int dir, complexP q2);

// function to write the dft into a text file
int file_out(complexP q2, FILE* out) {
    int ferr = fprintf(out, "%d %d\n", 2, q2->len);
    if(ferr < 0)
        return ferr;

    for(int i = 0; i < q2->len; i++) {
        ferr = fprintf(out, "%f %f\n", q2->real[i], q2->imag[i]);
        if(ferr < 0)
            return ferr;
    }
    return 1;
}


int main(int argc, char *argv[])
{
    /* code */
    FILE *in, *out;

    if(argc != 4) {
        printf("Invalid argument parameter");
        printf("params: in : inpute file \ndir : 0 for forward, 1 for reverse DFT\nout : output file");
    }

    else if (argc == 4) {
        char* inputFile = argv[1];
        int dir = atoi(argv[2]);
        char* outputFile = argv[3];

        // open files
        in = fopen(inputFile, "r");
        out = fopen(outputFile, "w");

        int N, w, h;
        fscanf(in, "%d %d", &w, &h);
        int ferr;
        float s, c, real, imag;
        N = h;

        complexP q1 = (complexP) malloc(sizeof(complexS));
        complexP q2 = (complexP) malloc(sizeof(complexS));

        q1->len = N;
        q1->real = (float*)malloc(sizeof(float)*q1->len);
        q1->imag = (float*)malloc(sizeof(float)*q1->len);
        
        q2->len = N;
        q2->real = (float*)malloc(sizeof(float)*q2->len);
        q2->imag = (float*)malloc(sizeof(float)*q2->len);
        

        for(int i = 0; i < N; i++)
            fscanf(in, "%f %f", &q1->real[i], &q1->imag[i]);

        // run the fft1d
        dft1d(q1, dir, q2);

        ferr = file_out(q2, out);
        if(ferr > 0)
            printf("%s\n", "File write success");
        else
            printf("%s\n", "File write failed");

        free(q1);
        free(q1);

        fclose(in);
        fclose(out);
    }

    return 0;
}


void dft1d(complexP q1, int dir, complexP q2) {
	float s, c, real, imag;
    int N = q1->len;

    if(dir == 0) {
    	// spectrum calculation using Forward Fourier Transform
    	for(int n = 0; n < N; n++) {
    		real = imag = 0;

    		for(int k = 0; k < N; k++) {
    			c =  cos(2.* PI * n * k / N);
    			s = -sin(2.* PI * n * k / N);
    			real += (q1->real[k]*c - q1->imag[k]*s);
    			imag += (q1->real[k]*s + q1->imag[k]*c);
    		}
    		q2->real[n] = real / N;
    		q2->imag[n] = imag / N;
    	}
    }

    else if( dir == 1) {
    	// spectrum calculation using Forward Fourier Transform
    	for(int n = 0; n < N; n++) {
    		real = imag = 0;

    		for(int k = 0; k < N; k++) {
    			c =  cos(2.* PI * n * k / N);
    			s =  sin(2.* PI * n * k / N);
    			real += (q1->real[k]*c - q1->imag[k]*s);
    			imag += (q1->real[k]*s + q1->imag[k]*c);
    		}
    		q2->real[n] = real;
    		q2->imag[n] = imag;
    	}

    }
}