#ifndef __KMATH_H
#define __KMATH_H
#include <stdint.h>
#ifdef __GNUC__
#define                 fpclassify(x)                   __builtin_fpclassify(x)
#define                 isfinite(x)                             __builtin_isfinite(x)
#define                 isinf(x)                                __builtin_isinf(x)
#define                 isnan(x)                                __builtin_isnan(x)
#define                 isnormal(x)                             __builtin_isnormal(x)
#define                 signbit(x)                              (isnan(x) ? 0 : ((x) < 0))
#else
// note: still to be tested
#define                 isinf(x)                                (((x) != 0) && (2 * (x) == (x)))
#define                 isnan(x)                                ((x) != (x))
#define                 isfinite(x)                             (!isinf(x))
#define                 isnormal(x)                             (!isnan(x) && isfinite(x) && ((x) != 0))
#define                 signbit(x)                              (isnan(x) ? 0 : ((x) < 0))
#define                 fpclassify(x)                   (((x) == 0) ? 2 : (isinf(x) ? 3 : (isnan(x) ? 4 : 1)))
#endif

double exp(double x);
float expf(float x);
long double expl(long double x);
double exp2(double x);
float exp2f(float x);
long double exp2l(long double x);
double expm1(double x);
float expm1f(float x);
long double expm1l(long double x);
double ldexp(double x, int exp) ;
float ldexpf(float x, int exp) ;
long double ldexpl(long double x, int exp);
double log(double x);
float logf(float x);
long double logl(long double x);
double log10(double x);
float log10f(float x);
long double log10l(long double x);
double log1p(double x);
float log1pf(float x);
long double log1pl(long double x);
double log2(double x);
float log2f(float x);
long double log2l(long double x);
double cbrt(double x);
float cbrtf(float x);
long double cbrtl(long double x);
double fabs(double x);
float fabsf(float x);
long double fabsl(long double x);
double hypot(double x, double y);
float hypotf(float x, float y);
long double hypotl(long double x, long double y);
double pow(double x, double y);
float powf(float x, float y);
long double powl(long double x, long double y);
double sqrt(double x);
float sqrtf(float x);
long double sqrtl(long double x);
double acos(double x);
float acosf(float x);
long double acosl(long double x);
double asin(double x);
float asinf(float x);
long double asinl(long double x);
double atan(double x);
float atanf(float x);
long double atanl(long double x);
double atan2(double y, double x);
float atan2f(float y, float x) ;
long double atan2l(long double y, long double x);
double cos(double x);
float cosf(float x);
long double cosl(long double x);
double sin(double x);
float sinf(float x);
long double sinl(long double x);
double tan(double x);
float tanf(float x);
long double tanl(long double x);
double acosh(double x);
float acoshf(float x);
long double acoshl(long double x);
double asinh(double x);
float asinhf(float x);
long double asinhl(long double x);
double atanh(double x);
float atanhf(float x);
long double atanhl(long double x);
double cosh(double x);
float coshf(float x);
long double coshl(long double x);
double sinh(double x);
float sinhf(float x);
long double sinhl(long double x);
double tanh(double x);
float tanhf(float x);
long double tanhl(long double x);
double ceil(double x) ;
float ceilf(float x);
long double ceill(long double x);
double floor(double x);
float floorf(float x);
long double floorl(long double x);
double nearbyint(double x);
float nearbyintf(float x);
long double nearbyintl(long double x);
double remainer(double x, double y);
float remainerf(float x, float y);
long double remainerl(long double x, long double y);
double remquo(double x, double y, int* quo);
float remquof(float x, float y, int* quo);
long double remquol(long double x, long double y, int* quo);
double copysign(double x, double y);
float copysignf(float x, float y);
long double copysignl(long double x, long double y);
double fdim(double x, double y);
float fdimf(float x, float y);
long double fdiml(long double x, long double y);
double fmax(double x, double y);
float fmaxf(float x, float y);
long double fmaxl(long double x, long double y);
double fmin(double x, double y);
float fminf(float x, float y);
long double fminl(long double x, long double y);
double fma(double x, double y, double z);
float fmaf(float x, float y, float z);
long double fmal(long double x, long double y, long double z);
#endif
