// refererence code: fft1d.c by Professor George Wolberg, CCNY

//      Semester   :    FALL 2018
// ************************************************************

//  ***********************
// to compile : g++ fft1D.cpp
// input size must by power of 2 ( 2^n )

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
void fft1d(complexP q1, int dir, complexP q2);

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
        fft1d(q1, dir, q2);

        ferr = file_out(q2, out);
        if(ferr > 0)
            printf("%s\n", "File write success");
        else
            printf("%s\n", "File write failed");

        fclose(in);
        fclose(out);
    }

    return 0;
}


void fft1d(complexP q1, int dir, complexP q2)
{
    int i, N, N2;
    float *r1, *i1, *r2, *i2, *ra, *ia, *rb, *ib;
    float FCTR, fctr, a, b, c, s, num[2];
    complexP qa, qb;

    N = q1->len;
    r1 = (float*) q1->real;
    i1 = (float*) q1->imag;
    r2 = (float*) q2->real;
    i2 = (float*) q2->imag;

    if (N == 2) {
        a = r1[0] + r1[1];  // F(0)=f(0)+f(1);F(1)=f(0)-f(1)
        b = i1[0] + i1[1];  // a,b needed when r1=r2
        r2[1] = r1[0] - r1[1];
        i2[1] = i1[0] - i1[1];
        r2[0] = a;
        i2[0] = b;

    } else {
        N2 = N / 2;
        qa = (complexP) malloc(sizeof(complexS));
        qa->len = N2;
        qa->real = (float*) malloc(sizeof(float)*qa->len);
        qa->imag = (float*) malloc(sizeof(float)*qa->len);

        qb = (complexP) malloc(sizeof(complexS));
        qb-> len = N2;
        qb-> real = (float*) malloc(sizeof(float)*qb->len);
        qb-> imag = (float*) malloc(sizeof(float)*qb->len);

        ra = (float*) qa->real;
        ia = (float*) qa->imag;
        rb = (float*) qb->real;
        ib = (float*) qb->imag;

        // split list into 2 halves; even and odd
        for (i = 0; i < N2; i++) {
                ra[i] = *r1++;
                ia[i] = *i1++;
                rb[i] = *r1++;
                ib[i] = *i1++;
        }

        // compute fft on both lists
        fft1d(qa, dir, qa);
        fft1d(qb, dir, qb);

        // build up coefficients
        if (!dir)   // forward
            FCTR = -2 * PI / N;
        else
            FCTR =  2 * PI / N;

        for (fctr = i = 0; i < N2; i++, fctr += FCTR) {
            c = cos(fctr);
            s = sin(fctr);
            a = c * rb[i] - s * ib[i];
            r2[i] = ra[i] + a;
            r2[i + N2] = ra[i] - a;

            a = s * rb[i] + c * ib[i];
            i2[i] = ia[i] + a;
            i2[i + N2] = ia[i] - a;
        }

        free(qa);
        free(qb);
    }

    if (!dir) { // inverse : divide by logN
        for (i = 0; i < N; i++) {
            q2->real[i] = q2->real[i] / 2;
            q2->imag[i] = q2->imag[i] / 2;
        }
    }
}
