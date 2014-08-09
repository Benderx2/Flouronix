/*

   Copyright 2009 Pierre KRIEGER

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
*/
#include <klib/kmath.h>
double ceil(double x) {
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x400; controlWord &= ~0x800;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyintl(x);
}

float ceilf(float x) {
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x400; controlWord &= ~0x800;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyintl(x);
}

long double ceill(long double x) {
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x400; controlWord &= ~0x800;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyintl(x);
}

double floor(double x) {
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x800; controlWord &= ~0x400;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyint(x);
}

float floorf(float x) {
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x800; controlWord &= ~0x400;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyintf(x);
}

long double floorl(long double x) {
        // first we have to modify the CR field in the x87 control register
        uint_least16_t controlWord;
        asm volatile("fstcw %0" : : "m"(controlWord) : "memory");
        controlWord |= 0x800; controlWord &= ~0x400;
        asm volatile("fldcw %0" : : "m"(controlWord));
        return nearbyintl(x);
}

double nearbyint(double x) {
        asm("frndint" : "+t"(x));
        return x;
}

float nearbyintf(float x) {
        asm("frndint" : "+t"(x));
        return x;
}

long double nearbyintl(long double x) {
        asm("frndint" : "+t"(x));
        return x;
}
double remainer(double x, double y) {
        double result;
        asm("fld %2 ; fld %1 ; fprem ; fxch ; fincstp" : "=t"(result) : "m"(x), "m"(y));
        return result;
}

float remainerf(float x, float y) {
        float result;
        asm("fld %2 ; fld %1 ; fprem ; fxch ; fincstp" : "=t"(result) : "m"(x), "m"(y));
        return result;
}

long double remainerl(long double x, long double y) {
        long double result;
        asm("fld %2 ; fld %1 ; fprem ; fxch ; fincstp" : "=t"(result) : "m"(x), "m"(y));
        return result;
}

double remquo(double x, double y, int* quo) {
        *quo = (int)x / (int)y;
        return remainer(x, y);
}

float remquof(float x, float y, int* quo) {
        *quo = (int)x / (int)y;
        return remainerf(x, y);
}

long double remquol(long double x, long double y, int* quo) {
        *quo = (int)x / (int)y;
        return remainerl(x, y);
}

double copysign(double x, double y) {
        double magnitude = fabs(x);
        return signbit(y) ? -magnitude : magnitude;
}

float copysignf(float x, float y) {
        double magnitude = fabsf(x);
        return signbit(y) ? -magnitude : magnitude;
}

long double copysignl(long double x, long double y) {
        double magnitude = fabsl(x);
        return signbit(y) ? -magnitude : magnitude;
}
double fdim(double x, double y) {
        return (x > y) ? (x - y) : 0;
}

float fdimf(float x, float y) {
        return (x > y) ? (x - y) : 0;
}

long double fdiml(long double x, long double y) {
        return (x > y) ? (x - y) : 0;
}

double fmax(double x, double y) {
        return (x > y) ? x : y;
}

float fmaxf(float x, float y) {
        return (x > y) ? x : y;
}

long double fmaxl(long double x, long double y) {
        return (x > y) ? x : y;
}

double fmin(double x, double y) {
        return (x < y) ? x : y;
}

float fminf(float x, float y) {
        return (x < y) ? x : y;
}

long double fminl(long double x, long double y) {
        return (x < y) ? x : y;
}

double fma(double x, double y, double z) {
        return x * y + z;
}

float fmaf(float x, float y, float z) {
        return x * y + z;
}

long double fmal(long double x, long double y, long double z) {
        return x * y + z;
}
double exp(double x) {
        asm("fldl2e ; fmulp ; f2xm1" : "+t"(x));
        return x + 1;
}

float expf(float x) {
        asm("fldl2e ; fmulp ; f2xm1" : "+t"(x));
        return x + 1;
}

long double expl(long double x) {
        asm("fldl2e ; fmulp ; f2xm1" : "+t"(x));
        return x + 1;
}

double exp2(double x) {
        asm("f2xm1" : "+t"(x));
        return x + 1;
}

float exp2f(float x) {
        asm("f2xm1" : "+t"(x));
        return x + 1;
}

long double exp2l(long double x) {
        asm("f2xm1" : "+t"(x));
        return x + 1;
}

double expm1(double x) {
        return exp(x) - 1;
}

float expm1f(float x) {
        return expf(x) - 1;
}

long double expm1l(long double x) {
        return expl(x) - 1;
}
double ldexp(double x, int exp) {
        return x * (1 << exp);
}

float ldexpf(float x, int exp) {
        return x * (1 << exp);
}

long double ldexpl(long double x, int exp) {
        return x * (1 << exp);
}

double log(double x) {
        double ln2;
        asm("fldln2" : "=t"(ln2));
        return ln2 * log2(x);
}

float logf(float x) {
        float ln2;
        asm("fldln2" : "=t"(ln2));
        return ln2 * log2f(x);
}

long double logl(long double x) {
        long double ln2;
        asm("fldln2" : "=t"(ln2));
        return ln2 * log2l(x);
}

double log10(double x) {
        double log10_2;
        asm("fldlg2" : "=t"(log10_2));
        return log10_2 * log2(x);
}

float log10f(float x) {
        double log10_2;
        asm("fldlg2" : "=t"(log10_2));
        return log10_2 * log2f(x);
}

long double log10l(long double x) {
        double log10_2;
        asm("fldlg2" : "=t"(log10_2));
        return log10_2 * log2l(x);
}

double log1p(double x) {
        log(1 + x);
}

float log1pf(float x) {
        logf(1 + x);
}

long double log1pl(long double x) {
        logl(1 + x);
}

double log2(double x) {
        asm("fld1 ; fxch ; fyl2x" : "+t"(x));
        return x;
}

float log2f(float x) {
        asm("fld1 ; fxch ; fyl2x" : "+t"(x));
        return x;
}

long double log2l(long double x) {
        asm("fld1 ; fxch ; fyl2x" : "+t"(x));
        return x;
}

double cbrt(double x) {
        return pow(x, 1. / 3.);
}

float cbrtf(float x) {
        return powf(x, 1. / 3.);
}

long double cbrtl(long double x) {
        return powl(x, 1. / 3.);
}

double fabs(double x) {
        asm("fabs" : "+t"(x));
        return x;
}

float fabsf(float x) {
        asm("fabs" : "+t"(x));
        return x;
}

long double fabsl(long double x) {
        asm("fabs" : "+t"(x));
        return x;
}

double hypot(double x, double y) {
        return sqrt(x*x + y*y);
}

float hypotf(float x, float y) {
        return sqrt(x*x + y*y);
}

long double hypotl(long double x, long double y) {
        return sqrt(x*x + y*y);
}

double pow(double x, double y) {
        return exp(y * log(x));
}

float powf(float x, float y) {
        return exp(y * log(x));
}

long double powl(long double x, long double y) {
        return exp(y * log(x));
}

double sqrt(double x) {
        asm("fsqrt" : "+t"(x));
        return x;
}

float sqrtf(float x) {
        asm("fsqrt" : "+t"(x));
        return x;
}

long double sqrtl(long double x) {
        asm("fsqrt" : "+t"(x));
        return x;
}
double acos(double x) {
        double pi;
        asm("fldpi" : "=t"(pi));
        return (pi / 2) - asin(x);
}

float acosf(float x) {
        float pi;
        asm("fldpi" : "=t"(pi));
        return (pi / 2) - asinf(x);
}

long double acosl(long double x) {
        long double pi;
        asm("fldpi" : "=t"(pi));
        return (pi / 2) - asinl(x);
}

double asin(double x) {
        return 2. * atan(x / (1. + sqrt(1. - x * x)));
}

float asinf(float x) {
        return 2. * atanf(x / (1. + sqrtf(1. - x * x)));
}

long double asinl(long double x) {
        return 2. * atanl(x / (1. + sqrtl(1. - x * x)));
}

double atan(double x) {
        return atan2(x, 1.);
}

float atanf(float x) {
        return atan2(x, 1.);
}

long double atanl(long double x) {
        return atan2(x, 1.);
}

double atan2(double y, double x) {
        double result;
        asm("fld %1 ; fld %2 ; fpatan" : "=t"(result) : "m"(y), "m"(x));
        return result;
}

float atan2f(float y, float x) {
        float result;
        asm("fld %1 ; fld %2 ; fpatan" : "=t"(result) : "m"(y), "m"(x));
        return result;
}

long double atan2l(long double y, long double x) {
        long double result;
        asm("fld %1 ; fld %2 ; fpatan" : "=t"(result) : "m"(y), "m"(x));
        return result;
}

double cos(double x) {
        asm("fcos" : "+t"(x));
        return x;
}

float cosf(float x) {
        asm("fcos" : "+t"(x));
        return x;
}

long double cosl(long double x) {
        asm("fcos" : "+t"(x));
        return x;
}

double sin(double x) {
        asm("fsin" : "+t"(x));
        return x;
}

float sinf(float x) {
        asm("fsin" : "+t"(x));
        return x;
}

long double sinl(long double x) {
        asm("fsin" : "+t"(x));
        return x;
}

double tan(double x) {
        return sin(x) / cos(x);
}

float tanf(float x) {
        return sinf(x) / cosf(x);
}

long double tanl(long double x) {
        return sinl(x) / cosl(x);
}

double acosh(double x) {
        return log(x + sqrt(x * x - 1));
}

float acoshf(float x) {
        return logf(x + sqrtf(x * x - 1));
}

long double acoshl(long double x) {
        return logl(x + sqrtl(x * x - 1));
}

double asinh(double x) {
        return log(x + sqrt(x * x + 1));
}

float asinhf(float x) {
        return logf(x + sqrtf(x * x + 1));
}

long double asinhl(long double x) {
        return logl(x + sqrtl(x * x + 1));
}

double atanh(double x) {
        return 0.5 * log((1. + x) / (1. - x));
}

float atanhf(float x) {
        return 0.5 * logf((1. + x) / (1. - x));
}

long double atanhl(long double x) {
        return 0.5 * logl((1. + x) / (1. - x));
}

double cosh(double x) {
        return (exp(x) + exp(-x)) * 0.5;
}

float coshf(float x) {
        return (exp(x) + exp(-x)) * 0.5;
}

long double coshl(long double x) {
        return (exp(x) + exp(-x)) * 0.5;
}

double sinh(double x) {
        return (exp(x) - exp(-x)) * 0.5;
}

float sinhf(float x) {
        return (exp(x) - exp(-x)) * 0.5;
}

long double sinhl(long double x) {
        return (exp(x) - exp(-x)) * 0.5;
}

double tanh(double x) {
        return sinh(x) / cosh(x);
}

float tanhf(float x) {
        return sinhf(x) / coshf(x);
}

long double tanhl(long double x) {
        return sinhl(x) / coshl(x);
}

