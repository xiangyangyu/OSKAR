/*
 * Copyright (c) 2016, The University of Oxford
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

#include "telescope/oskar_TelescopeLoadAbstract.h"
#include "utility/oskar_dir.h"

using std::map;
using std::string;

void oskar_TelescopeLoadAbstract::load(oskar_Telescope* telescope,
        const string& cwd, int num_subdirs, map<string, string>& filemap,
        int* status)
{
    (void) telescope;
    (void) cwd;
    (void) num_subdirs;
    (void) filemap;
    (void) status;
}

void oskar_TelescopeLoadAbstract::load(oskar_Station* station,
        const string& cwd, int num_subdirs, int depth,
        map<string, string>& filemap, int* status)
{
    (void) station;
    (void) cwd;
    (void) num_subdirs;
    (void) depth;
    (void) filemap;
    (void) status;
}

string oskar_TelescopeLoadAbstract::get_path(const string& dir,
        const string& item)
{
    char* path = oskar_dir_get_path(dir.c_str(), item.c_str());
    string s = string(path);
    free(path);
    return s;
}
