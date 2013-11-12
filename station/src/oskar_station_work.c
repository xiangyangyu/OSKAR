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

#include <oskar_station_work.h>
#include <private_station_work.h>

#ifdef __cplusplus
extern "C" {
#endif

oskar_StationWork* oskar_station_work_create(int type,
        int location, int* status)
{
    int i, complex_matrix;
    oskar_StationWork* work = 0;

    /* Check all inputs. */
    if (!status)
    {
        oskar_set_invalid_argument(status);
        return 0;
    }

    /* Allocate memory for the structure. */
    work = (oskar_StationWork*) malloc(sizeof(oskar_StationWork));

    /* Check the base type is correct. */
    if (type != OSKAR_SINGLE && type != OSKAR_DOUBLE)
        *status = OSKAR_ERR_BAD_DATA_TYPE;

    /* Set complex matrix type. */
    complex_matrix = OSKAR_COMPLEX | OSKAR_MATRIX;

    /* Initialise arrays. */
    oskar_mem_init(&work->horizon_mask, OSKAR_INT, location, 0, 1, status);
    oskar_mem_init(&work->theta_modified, type, location, 0, 1, status);
    oskar_mem_init(&work->phi_modified, type, location, 0, 1, status);
    oskar_mem_init(&work->enu_direction_x, type, location, 0, 1, status);
    oskar_mem_init(&work->enu_direction_y, type, location, 0, 1, status);
    oskar_mem_init(&work->enu_direction_z, type, location, 0, 1, status);
    oskar_mem_init(&work->relative_direction_l, type, location, 0, 1, status);
    oskar_mem_init(&work->relative_direction_m, type, location, 0, 1, status);
    oskar_mem_init(&work->relative_direction_n, type, location, 0, 1, status);
    oskar_mem_init(&work->ra, type, location, 0, 1, status);
    oskar_mem_init(&work->dec, type, location, 0, 1, status);
    oskar_mem_init(&work->radius, type, location, 0, 1, status);

    oskar_mem_init(&work->weights, (type | OSKAR_COMPLEX),
            location, 0, 1, status);
    oskar_mem_init(&work->weights_error, (type | OSKAR_COMPLEX),
            location, 0, 1, status);
    oskar_mem_init(&work->array_pattern, (type | OSKAR_COMPLEX),
            location, 0, 1, status);
    oskar_mem_init(&work->element_pattern_matrix, (type | complex_matrix),
            location, 0, 1, status);
    oskar_mem_init(&work->element_pattern_scalar, (type | OSKAR_COMPLEX),
            location, 0, 1, status);

    for (i = 0; i < OSKAR_MAX_STATION_DEPTH; ++i)
    {
        oskar_mem_init(&work->hierarchy_work_matrix[i], (type | complex_matrix),
                location, 0, 1, status);
        oskar_mem_init(&work->hierarchy_work_scalar[i], (type | OSKAR_COMPLEX),
                location, 0, 1, status);
    }

    return work;
}

void oskar_station_work_free(oskar_StationWork* work, int* status)
{
    int i;

    /* Check all inputs. */
    if (!work || !status)
    {
        oskar_set_invalid_argument(status);
        return;
    }

    oskar_mem_free(&work->horizon_mask, status);
    oskar_mem_free(&work->theta_modified, status);
    oskar_mem_free(&work->phi_modified, status);
    oskar_mem_free(&work->enu_direction_x, status);
    oskar_mem_free(&work->enu_direction_y, status);
    oskar_mem_free(&work->enu_direction_z, status);
    oskar_mem_free(&work->relative_direction_l, status);
    oskar_mem_free(&work->relative_direction_m, status);
    oskar_mem_free(&work->relative_direction_n, status);
    oskar_mem_free(&work->ra, status);
    oskar_mem_free(&work->dec, status);
    oskar_mem_free(&work->radius, status);
    oskar_mem_free(&work->weights, status);
    oskar_mem_free(&work->weights_error, status);
    oskar_mem_free(&work->array_pattern, status);
    oskar_mem_free(&work->element_pattern_matrix, status);
    oskar_mem_free(&work->element_pattern_scalar, status);

    for (i = 0; i < OSKAR_MAX_STATION_DEPTH; ++i)
    {
        oskar_mem_free(&work->hierarchy_work_matrix[i], status);
        oskar_mem_free(&work->hierarchy_work_scalar[i], status);
    }

    /* Free the structure. */
    free(work);
}

oskar_Mem* oskar_station_work_horizon_mask(oskar_StationWork* work)
{
    return &work->horizon_mask;
}

const oskar_Mem* oskar_station_work_horizon_mask_const(
        const oskar_StationWork* work)
{
    return &work->horizon_mask;
}

oskar_Mem* oskar_station_work_enu_direction_x(oskar_StationWork* work)
{
    return &work->enu_direction_x;
}

const oskar_Mem* oskar_station_work_enu_direction_x_const(
        const oskar_StationWork* work)
{
    return &work->enu_direction_x;
}

oskar_Mem* oskar_station_work_enu_direction_y(oskar_StationWork* work)
{
    return &work->enu_direction_y;
}

const oskar_Mem* oskar_station_work_enu_direction_y_const(
        const oskar_StationWork* work)
{
    return &work->enu_direction_y;
}

oskar_Mem* oskar_station_work_enu_direction_z(oskar_StationWork* work)
{
    return &work->enu_direction_z;
}

const oskar_Mem* oskar_station_work_enu_direction_z_const(
        const oskar_StationWork* work)
{
    return &work->enu_direction_z;
}

oskar_Mem* oskar_station_work_relative_direction_l(oskar_StationWork* work)
{
    return &work->relative_direction_l;
}

const oskar_Mem* oskar_station_work_relative_direction_l_const(
        const oskar_StationWork* work)
{
    return &work->relative_direction_l;
}

oskar_Mem* oskar_station_work_relative_direction_m(oskar_StationWork* work)
{
    return &work->relative_direction_m;
}

const oskar_Mem* oskar_station_work_relative_direction_m_const(
        const oskar_StationWork* work)
{
    return &work->relative_direction_m;
}

oskar_Mem* oskar_station_work_relative_direction_n(oskar_StationWork* work)
{
    return &work->relative_direction_n;
}

const oskar_Mem* oskar_station_work_relative_direction_n_const(
        const oskar_StationWork* work)
{
    return &work->relative_direction_n;
}

oskar_Mem* oskar_station_work_ra(oskar_StationWork* work)
{
    return &work->ra;
}

const oskar_Mem* oskar_station_work_ra_const(const oskar_StationWork* work)
{
    return &work->ra;
}

oskar_Mem* oskar_station_work_dec(oskar_StationWork* work)
{
    return &work->dec;
}

const oskar_Mem* oskar_station_work_dec_const(const oskar_StationWork* work)
{
    return &work->dec;
}

oskar_Mem* oskar_station_work_radius(oskar_StationWork* work)
{
    return &work->radius;
}

const oskar_Mem* oskar_station_radius_const(
        const oskar_StationWork* work)
{
    return &work->radius;
}

#ifdef __cplusplus
}
#endif
