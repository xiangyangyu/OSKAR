/*
 * Copyright (c) 2013, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <oskar_convert_relative_direction_cosines_to_apparent_ra_dec.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Single precision. */
void oskar_convert_relative_direction_cosines_to_apparent_ra_dec_f(int np,
        float ra0, float dec0, const float* l, const float* m, float* ra,
        float* dec)
{
    int i;
    float sinDec0, cosDec0;
    sinDec0 = sinf(dec0);
    cosDec0 = cosf(dec0);

    /* Loop over positions and evaluate the longitude and latitude values. */
    for (i = 0; i < np; ++i)
    {
        float l_, m_, n_;
        l_ = l[i];
        m_ = m[i];
        n_ = sqrtf(1.0 - l_*l_ - m_*m_);
        dec[i] = asinf(n_ * sinDec0 + m_ * cosDec0);
        ra[i] = ra0 + atan2f(l_, cosDec0 * n_ - m_ * sinDec0);
    }
}

/* Double precision. */
void oskar_convert_relative_direction_cosines_to_apparent_ra_dec_d(int np,
        double ra0, double dec0, const double* l, const double* m, double* ra,
        double* dec)
{
    int i;
    double sinLat0, cosLat0;
    sinLat0 = sin(dec0);
    cosLat0 = cos(dec0);

    /* Loop over l, m positions and evaluate the longitude and latitude values. */
    for (i = 0; i < np; ++i)
    {
        double l_, m_, n_;
        l_ = l[i];
        m_ = m[i];
        n_ = sqrt(1.0 - l_*l_ - m_*m_);
        dec[i] = asin(n_ * sinLat0 + m_ * cosLat0);
        ra[i] = ra0 + atan2(l_, cosLat0 * n_ - m_ * sinLat0);
    }
}

#ifdef __cplusplus
}
#endif
