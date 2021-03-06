/*
 * Copyright (c) 2012-2013, The University of Oxford
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

#include "math/oskar_rotate.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

void oskar_rotate_sph_f(int num_points, float* x, float* y, float*z,
        float lon, float lat)
{
    int i;
    float cosLon, sinLon, cosLat, sinLat, x_, y_, z_;
    cosLon = cosf(lon);
    sinLon = sinf(lon);
    cosLat = cosf(lat);
    sinLat = sinf(lat);
    for (i = 0; i < num_points; ++i)
    {
        x_ = x[i];
        y_ = y[i];
        z_ = z[i];
        x[i] = x_ * cosLon * cosLat - y_ * sinLon - z_ * cosLon*sinLat;
        y[i] = x_ * cosLat * sinLon + y_ * cosLon - z_ * sinLon*sinLat;
        z[i] = x_ * sinLat + z_ * cosLat;
    }
}

void oskar_rotate_sph_d(int num_points, double* x, double* y, double*z,
        double lon, double lat)
{
    int i;
    double cosLon, sinLon, cosLat, sinLat, x_, y_, z_;
    cosLon = cos(lon);
    sinLon = sin(lon);
    cosLat = cos(lat);
    sinLat = sin(lat);
    for (i = 0; i < num_points; ++i)
    {
        x_ = x[i];
        y_ = y[i];
        z_ = z[i];
        x[i] = x_ * cosLon * cosLat - y_ * sinLon - z_ * cosLon*sinLat;
        y[i] = x_ * cosLat * sinLon + y_ * cosLon - z_ * sinLon*sinLat;
        z[i] = x_ * sinLat + z_ * cosLat;
    }
}

void oskar_rotate_x_f(int num_points, float* y, float* z, float angle)
{
    int i;
    float cosAng, sinAng, y_, z_;
    cosAng = cosf(angle);
    sinAng = sinf(angle);
    for (i = 0; i < num_points; ++i)
    {
        y_ = y[i];
        z_ = z[i];
        y[i] = y_ * cosAng - z_ * sinAng;
        z[i] = y_ * sinAng + z_ * cosAng;
    }
}

void oskar_rotate_y_f(int num_points, float* x, float* z, float angle)
{
    int i;
    float cosAng, sinAng, x_, z_;
    cosAng = cosf(angle);
    sinAng = sinf(angle);
    for (i = 0; i < num_points; ++i)
    {
        x_ = x[i];
        z_ = z[i];
        x[i] =  x_ * cosAng + z_ * sinAng;
        z[i] = -x_ * sinAng + z_ * cosAng;
    }
}

void oskar_rotate_z_f(int num_points, float* x, float* y, float angle)
{
    int i;
    float cosAng, sinAng, x_, y_;
    cosAng = cosf(angle);
    sinAng = sinf(angle);
    for (i = 0; i < num_points; ++i)
    {
        x_ = x[i];
        y_ = y[i];
        x[i] = x_ * cosAng - y_ * sinAng;
        y[i] = x_ * sinAng + y_ * cosAng;
    }
}

void oskar_rotate_x_d(int num_points, double* y, double* z, double angle)
{
    int i;
    double cosAng, sinAng, y_, z_;
    cosAng = cos(angle);
    sinAng = sin(angle);
    for (i = 0; i < num_points; ++i)
    {
        y_ = y[i];
        z_ = z[i];
        y[i] = y_ * cosAng - z_ * sinAng;
        z[i] = y_ * sinAng + z_ * cosAng;
    }
}

void oskar_rotate_y_d(int num_points, double* x, double* z, double angle)
{
    int i;
    double cosAng, sinAng, x_, z_;
    cosAng = cos(angle);
    sinAng = sin(angle);
    for (i = 0; i < num_points; ++i)
    {
        x_ = x[i];
        z_ = z[i];
        x[i] =  x_ * cosAng + z_ * sinAng;
        z[i] = -x_ * sinAng + z_ * cosAng;
    }
}

void oskar_rotate_z_d(int num_points, double* x, double* y, double angle)
{
    int i;
    double cosAng, sinAng, x_, y_;
    cosAng = cos(angle);
    sinAng = sin(angle);
    for (i = 0; i < num_points; ++i)
    {
        x_ = x[i];
        y_ = y[i];
        x[i] = x_ * cosAng - y_ * sinAng;
        y[i] = x_ * sinAng + y_ * cosAng;
    }
}

#ifdef __cplusplus
}
#endif
