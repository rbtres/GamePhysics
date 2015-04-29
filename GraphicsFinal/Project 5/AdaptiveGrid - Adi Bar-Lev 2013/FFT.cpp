//------------------------------------------------------------------------------
//
// The FFT code was written originally by Paul Bourke: 
// http://paulbourke.net/miscellaneous/dft/
//
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <math.h>
#include "FFT.h"
/*
//------------------------------------------------------------------------------
void COceanFFTTexture::GenerateNoise(float *_Height,int _Size)

{
	const static int q = 15;
	const static float c1 = (1 << q) - 1;
	const static float c2 = ((int)(c1 / 3)) + 1;
	const static float c3 = 1.f / c1;
	float random = 0.f;

	for (int i = 0; i < _Size*_Size; i++)
	{
		random = ((float)rand() / (float)(RAND_MAX + 1));
		float noise = (2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * c3;
		_Height[i] = noise*0.5f+0.5f;
	}
}
//------------------------------------------------------------------------------
float COcean::Noise(int x, int y, int random)
{

	int n = x + y * 57 + random * 131;

	n = (n<<13) ^ n;

	return (1.0f - ( (n * (n * n * 15731 + 789221) +

		1376312589)&0x7fffffff)* 0.000000000931322574615478515625f);

}
*/
//------------------------------------------------------------------------------
bool Powerof2( int num, int* power_two, int* outcome )
{
	*outcome = 1;
	*power_two = 0;
	while (num > 1)
	{
		num = num >> 1;
		(*power_two)++;
		*outcome = *outcome << 1;
	}
	return (num == *outcome) ? true : false;
}
/*-------------------------------------------------------------------------
 // Perform a 2D FFT inplace given a complex 2D array.
// - The direction dir, 1 for forward, -1 for reverse.
// - The size of the array (nx,ny)
// - Return false if there are memory problems or the dimensions are not powers of 2

This computes an in-place complex-to-complex FFT
   x and y are the real and imaginary arrays of 2^m points.
   dir =  1 gives forward transform
   dir = -1 gives reverse transform
     Formula: forward
                  N-1
                  ---
              1   \          - j k 2 pi n / N
      X(n) = ---   >   x(k) e                    = forward transform
              N   /                                n=0..N-1
                  ---
                  k=0
      Formula: reverse
                  N-1
                  ---
                  \          j k 2 pi n / N
      X(n) =       >   x(k) e                    = forward transform
                  /                                n=0..N-1
                  ---
                  k=0
*/
//------------------------------------------------------------------------------
int FFT(int dir,int m,double *x,double *y)
{
   long nn,i,i1,j,k,i2,l,l1,l2;
   double c1,c2,tx,ty,t1,t2,u1,u2,z;
   /* Calculate the number of points */
   nn = 1;
   for (i=0;i<m;i++)
      nn *= 2;
   /* Do the bit reversal */
   i2 = nn >> 1;
   j = 0;
   for (i=0;i<nn-1;i++) {
      if (i < j) {
         tx = x[i];
         ty = y[i];
         x[i] = x[j];
         y[i] = y[j];
         x[j] = tx;
         y[j] = ty;
      }
      k = i2;
      while (k <= j) {
         j -= k;
         k >>= 1;
      }
      j += k;
   }
   /* Compute the FFT */
   c1 = -1.0;
   c2 = 0.0;
   l2 = 1;
   for (l=0;l<m;l++) {
      l1 = l2;
      l2 <<= 1;
      u1 = 1.0;
      u2 = 0.0;
      for (j=0;j<l1;j++) {
         for (i=j;i<nn;i+=l2) {
            i1 = i + l1;
            t1 = u1 * x[i1] - u2 * y[i1];
            t2 = u1 * y[i1] + u2 * x[i1];
            x[i1] = x[i] - t1;
            y[i1] = y[i] - t2;
            x[i] += t1;
            y[i] += t2;
         }
         z =  u1 * c1 - u2 * c2;
         u2 = u1 * c2 + u2 * c1;
         u1 = z;
      }
      c2 = sqrt((1.0 - c1) / 2.0);
      if (dir == 1)
         c2 = -c2;
      c1 = sqrt((1.0 + c1) / 2.0);
   }
   /* Scaling for forward transform */
   if (dir == 1) {
      for (i=0;i<nn;i++) {
         x[i] /= (double)nn;
         y[i] /= (double)nn;
      }
   }
   return(true);
}
//------------------------------------------------------------------------------
int FFT2D(COMPLEX **c,int nx,int ny,int dir)
{
	int i,j;
	int m,twopm;
	double *real,*imag;
	/* Transform the rows */
	real = (double *)malloc(nx * sizeof(double));
	imag = (double *)malloc(nx * sizeof(double));
	if (real == NULL || imag == NULL)
		return(false);
	if (!Powerof2(nx,&m,&twopm))
		return false;
	for (j=0;j<ny;j++) {
		for (i=0;i<nx;i++) {
			real[i] = c[i][j].real;
			imag[i] = c[i][j].imag;
		}
		FFT(dir,m,real,imag);
		for (i=0;i<nx;i++) {
			c[i][j].real = real[i];
			c[i][j].imag = imag[i];
		}
	}
	free(real);
	free(imag);
	/* Transform the columns */
	real = (double *)malloc(ny * sizeof(double));
	imag = (double *)malloc(ny * sizeof(double));
	if (real == NULL || imag == NULL)
		return(false);
//	if (!Powerof2(ny,&m,&twopm) || twopm != ny)
//		return(false);
	for (i=0;i<nx;i++) {
		for (j=0;j<ny;j++) {
			real[j] = c[i][j].real;
			imag[j] = c[i][j].imag;
		}
		FFT(dir,m,real,imag);
		for (j=0;j<ny;j++) {
			c[i][j].real = real[j];
			c[i][j].imag = imag[j];
		}
	}
	free(real);
	free(imag);
	return(true);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/* This generate the ocean spectre from a horizontal vector 
float WATERFFT_philippe(Vector2 *k, Vector2 *wind , float Pow_factor , float Wind_factor)
{
    float k2 ,v2,ret;
	float WC;
	k2 = (float)(k->X * k->X + k->Y * k->Y);
	k2 = (float)sqrt(k2);
    if (k2 == 0.0f) return 0.0f;
    v2 = wind->X * wind->X + wind->Y * wind->Y;
	v2 = (float)sqrt(v2);

	WC = 0.5f + 0.5f * (k->X*wind->X + k->Y*wind->Y) / (k2*v2);
	WC = (float)pow(WC , Wind_factor);

    ret = (float)(WC / pow(k2 , Pow_factor));
    return ret;
}
//------------------------------------------------------------------------------
*/
