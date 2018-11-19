// refererence code: dft1d.c by Professor George Wolberg, CCNY


//	***********************
//	to compile : gcc dft1D.c -lm

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// constant number PI
#define PI 3.1415927

// struct data type to represent complex number
typedef struct {
	float* real;
	float* imag;
	int len;	
}complexNum, *complexPtr;

// function to compute dft
// 3) dft1D in dir out
void dft1D(FILE* in, int dir, FILE* out);
// function to write the dft into a text file
int file_out(complexNum in, FILE* out) {
	int ferr = fprintf(out, "%d %d\n", 2, in.len);
	if(ferr < 0)
		return ferr;

	for(int i = 0; i < in.len; i++) {
		ferr = fprintf(out, "%f %f\n", in.real[i], in.imag[i]);
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

		dft1D(in, dir, out);

		fclose(in);
		fclose(out);
	}

	return 0;
}

void dft1D(FILE* in, int dir, FILE* out) {
	int N, w, h;
	fscanf(in, "%d %d", &w, &h);

	int ferr;
	float s, c, real, imag;
	complexNum F, f;
	N = h;
	f.real = malloc(sizeof(float) * N);
    f.imag = malloc(sizeof(float) * N);
    f.len = h;

	F.real = malloc(sizeof(float) * N);
    F.imag = malloc(sizeof(float) * N);
    F.len = h;


    if(dir == 0) {
    	for(int i = 0; i < N; i++)
    		fscanf(in, "%f %f", &f.real[i], &f.imag[i]);

    	// spectrum calculation using Forward Fourier Transform
    	for(int n = 0; n < N; n++) {
    		real = imag = 0;

    		for(int k = 0; k < N; k++) {
    			c =  cos(2.* PI * n * k / N);
    			s = -sin(2.* PI * n * k / N);
    			real += (f.real[k]*c - f.imag[k]*s);
    			imag += (f.real[k]*s + f.imag[k]*c);
    		}
    		F.real[n] = real / N;
    		F.imag[n] = imag / N;
    	}

    	ferr = file_out(F, out);
    	if(ferr > 0)
    		printf("%s\n", "File write success");
    	else
    		printf("%s\n", "File write failed");
    }

    else if( dir == 1) {
    	for(int i = 0; i < N; i++)
    		fscanf(in, "%f %f", &F.real[i], &F.imag[i]);

    	// spectrum calculation using Forward Fourier Transform
    	for(int n = 0; n < N; n++) {
    		real = imag = 0;

    		for(int k = 0; k < N; k++) {
    			c =  cos(2.* PI * n * k / N);
    			s =  sin(2.* PI * n * k / N);
    			real += (F.real[k]*c - F.imag[k]*s);
    			imag += (F.real[k]*s + F.imag[k]*c);
    		}
    		f.real[n] = real;
    		f.imag[n] = imag;
    	}

    	ferr = file_out(f, out);
    	if(ferr > 0)
    		printf("%s\n", "File write success");
    	else
    		printf("%s\n", "File write failed");

    }

    else {
    	printf("%s\n", "Invalid option");
    }

    free(f.real);
    free(f.imag);
    free(F.real);
    free(F.imag);

    return;
}