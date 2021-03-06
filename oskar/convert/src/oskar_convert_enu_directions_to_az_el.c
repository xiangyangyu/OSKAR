/*
 * Copyright (c) 2013-2014, The University of Oxford
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

#include "convert/oskar_convert_enu_directions_to_az_el.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

OSKAR_EXPORT
void oskar_convert_enu_directions_to_az_el_f(int n, const float* x,
        const float* y, const float* z, float* az, float* el)
{
    int i = 0;
    float x_, y_, z_, a;
    for (i = 0; i < n; ++i)
    {
        x_ = x[i];
        y_ = y[i];
        z_ = z[i];
        a = atan2f(x_, y_); /* Azimuth */
        x_ = sqrtf(x_*x_ + y_*y_);
        y_ = atan2f(z_, x_); /* Elevation. */
        az[i] = a;
        el[i] = y_;
    }
}

OSKAR_EXPORT
void oskar_convert_enu_directions_to_az_el_d(int n, const double* x,
        const double* y, const double* z, double* az, double* el)
{
    int i = 0;
    double x_, y_, z_, a;
    for (i = 0; i < n; ++i)
    {
        x_ = x[i];
        y_ = y[i];
        z_ = z[i];
        a = atan2(x_, y_); /* Azimuth */
        x_ = sqrt(x_*x_ + y_*y_);
        y_ = atan2(z_, x_); /* Elevation. */
        az[i] = a;
        el[i] = y_;
    }
}


#ifdef __cplusplus
}
#endif
