/*
 * Copyright (c) 2011, The University of Oxford
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

#ifndef OSKAR_ANGULAR_DISTANCE_H_
#define OSKAR_ANGULAR_DISTANCE_H_

/**
 * @file oskar_angular_distance.h
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @details
 * Return the angular distance between two points on a sphere.
 * This is implemented using the Haversin formula:
 *
 * \f{equation}{
 *     2\arcsin\left(\sqrt{\sin^2\left(\frac{\Delta\phi}{2}\right)
 *     +\cos{\phi_s}\cos{\phi_f}\sin^2\left(\frac{\Delta\lambda}{2}\right)}\right)
 * \f}
 *
 * @param[in] l1 Longitude of the first point, in radians.
 * @param[in] l2 Longitude of the second point, in radians.
 * @param[in] b1 Latitude of the first point, in radians.
 * @param[in] b2 Latitude of the second point, in radians.
 *
 * @return The angular distance in radians.
 */
double oskar_angular_distance(double l1, double l2, double b1, double b2);

#ifdef __cplusplus
}
#endif

#endif /* OSKAR_ANGULAR_DISTANCE_H_ */
