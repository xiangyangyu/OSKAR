/*
 * Copyright (c) 2012, The University of Oxford
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

#include "oskar_global.h"
#ifndef OSKAR_NO_FITS
#include "fits/oskar_fits_to_sky_model.h"
#endif
#include "sky/oskar_sky_model_save.h"
#include "utility/oskar_get_error_string.h"
#include "utility/oskar_log_error.h"
#include "apps/lib/oskar_OptionParser.h"
#include <cstdio>

int main(int argc, char** argv)
{
    // Check if built with FITS support.
#ifndef OSKAR_NO_FITS
    int error = OSKAR_SUCCESS;

    oskar_OptionParser opt("oskar_fits_to_sky_model");
    opt.setDescription("Converts a FITS image to an OSKAR sky model. A number "
            "of options are provided to control how much of the image is used "
            "to make the sky model.");
    opt.addRequired("FITS file", "The FITS image to convert.");
    opt.addRequired("sky model file", "The OSAKR sky model file name to convert to.");
    opt.addFlag("-s", "Spectral index", 1, "0.0");
    opt.addFlag("-f", "Minimum allowed fraction of image peak", 1, "0.0");
    opt.addFlag("-d", "Downsample factor", 1, "0");
    opt.addFlag("-n", "Noise floor", 1, "0.0");
    if (!opt.check_options(argc, argv))
        return OSKAR_FAIL;

    // Parse command line.
    double spectral_index = 0.0;
    double min_peak_fraction = 0.0;
    double noise_floor = 0.0;
    int downsample_factor = 0;
    opt.get("-d")->getInt(downsample_factor);
    opt.get("-f")->getDouble(min_peak_fraction);
    opt.get("-n")->getDouble(noise_floor);
    opt.get("-s")->getDouble(spectral_index);

//    printf("----\n");
//    printf("fits  = %s\n", opt.getArg(0));
//    printf("model = %s\n", opt.getArg(1));
//    printf("f     = %f\n", min_peak_fraction);
//    printf("n     = %f\n", noise_floor);
//    printf("----\n");
//    return 1;

    // Load the FITS file as a sky model.
    oskar_SkyModel sky;
    error = oskar_fits_to_sky_model(0, opt.getArg(0), &sky, spectral_index,
            min_peak_fraction, noise_floor, downsample_factor);
    if (error)
    {
        oskar_log_error(0, oskar_get_error_string(error));
        return error;
    }

    // Write out the sky model.
    oskar_sky_model_save(opt.getArg(1), &sky, &error);
    if (error)
    {
        oskar_log_error(0, oskar_get_error_string(error));
        return error;
    }
    return OSKAR_SUCCESS;

#else
    // No FITS support.
    oskar_log_error(0, "OSKAR was not compiled with FITS support.");
    return -1;
#endif
}
