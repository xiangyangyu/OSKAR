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

#include <oskar_global.h>
#include <imaging/oskar_Image.h>
#include <imaging/oskar_ImageStats.h>
#include <imaging/oskar_image_get_stats.h>
#include <imaging/oskar_image_read.h>
#include <utility/oskar_get_error_string.h>
#include <apps/lib/oskar_OptionParser.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <cfloat>
#include <vector>
#include <iomanip>

using namespace std;

// ----------------------------------------------------------------------------
void set_options(oskar_OptionParser& opt);
bool check_options(oskar_OptionParser& opt, int argc, char** argv);
void print_error(int status, const char* message);
// ----------------------------------------------------------------------------

int main(int argc, char** argv)
{
    // Register options =======================================================
    oskar_OptionParser opt("oskar_image_stats");
    set_options(opt);
    if (!check_options(opt, argc, argv))
        return OSKAR_FAIL;

    // Retrieve options =======================================================
    int channel, pol, time;
    opt.get("-c")->getInt(channel);
    opt.get("-p")->getInt(pol);
    opt.get("-t")->getInt(time);
    bool verbose = opt.isSet("-v") ? true : false;
    vector<string> files = opt.getInputFiles(1);

    if (verbose) {
        cout << "#"<< endl;
        cout << "# Statistics for the following images:" << endl;
        for (int i = 0; i < (int)files.size(); ++i) {
            cout << "#  [" << setw(2) << i << "] " << files[i] << endl;
        }
        cout << "#" << endl;
        cout << "# Data index:" << endl;
        cout << "#   Channel .... = " << channel << endl;
        cout << "#   Polarisation = " << pol << endl;
        cout << "#   Time ....... = " << time << endl;
        cout << "#" << endl;
    }

    // Generate the statistics ================================================
    int status = OSKAR_SUCCESS;
    FILE* out = stdout;
    string sformat = "% -6.3e";
    string sep = ", ";

    if (verbose) {
        fprintf(out, "#\n");
        fprintf(out, "# file index, minimum, maximum, mean, variance, standard deviation, RMS\n");
        fprintf(out, "#\n");
    }
    for (int i = 0; i < (int)files.size(); ++i)
    {
        oskar_Image image;
        oskar_image_read(&image, files[i].c_str(), 0, &status);
        if (status != OSKAR_SUCCESS) {
            string msg = "Failed to read image file " + files[i];
            print_error(status, msg.c_str());
            return status;
        }
        oskar_ImageStats stats;
        oskar_image_get_stats(&stats, &image, pol, time, channel, &status);
        if (status != OSKAR_SUCCESS) {
            string msg = "Failed to evaluate image statistics for: " + files[i];
            print_error(status, msg.c_str());
            return status;
        }
        fprintf(out, "%3i", i);
        fprintf(out, "%s", sep.c_str());
        fprintf(out, sformat.c_str(), stats.min);
        fprintf(out, "%s", sep.c_str());
        fprintf(out, sformat.c_str(), stats.max);
        fprintf(out, "%s", sep.c_str());
        fprintf(out, sformat.c_str(), stats.mean);
        fprintf(out, "%s", sep.c_str());
        fprintf(out, sformat.c_str(), stats.var);
        fprintf(out, "%s", sep.c_str());
        fprintf(out, sformat.c_str(), stats.std);
        fprintf(out, "%s", sep.c_str());
        fprintf(out, sformat.c_str(), stats.rms);
        fprintf(out, "\n");
    }

    return status;
}


void set_options(oskar_OptionParser& opt)
{
    opt.setDescription("Application to evaluate OSKAR binary image file "
            "statistics (min., max., mean, variance, standard deviation, and "
            "RMS).");
    opt.addRequired("Image file(s)...", "OSKAR image files to analyse.");
    opt.addFlag("-v", "Verbose");
    opt.addFlag("-c", "Channel index", 1, "0");
    opt.addFlag("-p", "Polarisation index", 1, "0");
    opt.addFlag("-t", "Time index", 1, "0");
    opt.addExample("oskar_image_stats file.img");
    opt.addExample("oskar_image_stats -t 2 *.img");
    opt.addExample("oskar_image_stats *.img -c 1 -t 2 -p 3");
}


bool check_options(oskar_OptionParser& opt, int argc, char** argv)
{
    if (!opt.check_options(argc, argv)) return false;
    int num_req = 1; // Number of image files required;
    bool visFirst = ((int)opt.firstArgs.size() >= (num_req+1)) &&
            ((int)opt.lastArgs.size() == 0);
    bool visEnd = ((int)opt.firstArgs.size() == 1) &&
            ((int)opt.lastArgs.size() >= num_req);
    if (!visFirst && !visEnd) {
        cerr << "\nERROR: Please provide 1 or more image files.\n\n";
        opt.printUsage();
        return false;
    }
    return true;
}


void print_error(int status, const char* message)
{
    cerr << "ERROR[" << status << "] " << message << endl;
    cerr << "REASON = " << oskar_get_error_string(status) << endl;
}

