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

#include "modules/cuda/test/ModuleCudaCorrelatorTest.h"
#include "modules/cuda/oskar_modules_cuda_correlator_lm.h"
#include <cmath>
#include <cstdlib>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

#define C_0 299792458

// Register the test class.
CPPUNIT_TEST_SUITE_REGISTRATION(ModuleCudaCorrelatorTest);

/**
 * @details
 * Sets up the context before running each test method.
 */
void ModuleCudaCorrelatorTest::setUp()
{
}

/**
 * @details
 * Clean up routine called after each test is run.
 */
void ModuleCudaCorrelatorTest::tearDown()
{
}

/**
 * @details
 * Tests vector addition using CUDA.
 */
void ModuleCudaCorrelatorTest::test_method()
{
    int ns = 10;
    int na = 5;
    double ra0 = 0.0;
    double dec0 = M_PI / 2.0;
    double lst0 = 0.0;
    int nsdt = 10;
    double sdt = 0.1;
    double freq = 400e6;
    double k = 2 * M_PI * freq / C_0;

    std::vector<double> l(ns, 0.0), m(ns, 0.0);
    std::vector<double> ax(na, 0.0), ay(na, 0.0), az(na, 0.0);
    std::vector<double> bsqrt(ns, 0.0);
    std::vector<double> e(ns * na * 2, 0.0);
    std::vector<double> vis(na * na * 2, 0.0);
    std::vector<double> u(na, 0.0), v(na, 0.0), w(na, 0.0);
    oskar_modules_cudad_correlator_lm(na, &ax[0], &ay[0], &az[0],
            ns, &l[0], &m[0], &bsqrt[0], &e[0], ra0, dec0, lst0, nsdt, sdt, k,
            &vis[0], &u[0], &v[0], &w[0]);
}