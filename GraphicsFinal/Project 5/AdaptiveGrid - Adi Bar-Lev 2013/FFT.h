//------------------------------------------------------------------------------
//
// The FFT code was written originally by Paul Bourke: 
// http://paulbourke.net/miscellaneous/dft/
//
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <math.h>
//------------------------------------------------------------------------------
struct Vector2
{	
	float X,Y;
};
//------------------------------------------------------------------------------
struct COMPLEX
{
	double		real;
	double		imag;
};
//------------------------------------------------------------------------------
//void COceanFFTTexture::GenerateNoise(float *_Height,int _Size);
bool Powerof2( int num, int* power_two, int* outcome );
int FFT(int dir,int m,double *x,double *y);
int FFT2D(COMPLEX **c,int nx,int ny,int dir);
float WATERFFT_philippe(Vector2 *k, Vector2 *wind , float Pow_factor , float Wind_factor);
//------------------------------------------------------------------------------
