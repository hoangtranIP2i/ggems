// This file is part of GGEMS
//
// GGEMS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// GGEMS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GGEMS.  If not, see <http://www.gnu.org/licenses/>.
//
// GGEMS Copyright (C) 2013-2014 Julien Bert

#ifndef GLOBAL_CUH
#define GLOBAL_CUH

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cfloat>
#include <assert.h>
#include <math.h>

#include "constants.cuh"
#include "vector.cuh"

/////// TYPEDEF ////////////////////////////////////////////////

#ifndef SINGLE_PRECISION
    // Double precision
    typedef float f32;
    typedef float2 f32xy;
    typedef float3 f32xyz;
    typedef float4 f32xyzw;

    typedef double f64;
    typedef double2 f64xy;
    typedef double3 f64xyz;
    typedef double4 f64xyzw;

    typedef int i32;
    typedef int2 i32xy;
    typedef int3 i32xyz;
    typedef int4 i32xyzw;

    typedef short int i16;
    typedef char i8;

    typedef unsigned int ui32;
    typedef unsigned short int ui16;
    typedef unsigned char ui8;

    #define make_f32xy make_float2;
    #define make_f32xyz make_float3;
    #define make_f32xyzw make_float4;

    #define make_f64xy make_double2;
    #define make_f64xy make_double3;
    #define make_f64xy make_double4;

    #define make_i32xy make_int2;
    #define make_i32xyz make_int3;
    #define make_i32xyzw make_int4;

    #define F32_MAX FLT_MAX;
    #define F64_MAX DBL_MAX;

#else
    // Single precision
    typedef float f32;
    typedef float2 f32xy;
    typedef float3 f32xyz;
    typedef float4 f32xyzw;

    typedef float f64;
    typedef float2 f64xy;
    typedef float3 f64xyz;
    typedef float4 f64xyzw;

    typedef int i32;
    typedef int2 i32xy;
    typedef int3 i32xyz;
    typedef int4 i32xyzw;

    typedef short int i16;
    typedef char i8;

    typedef unsigned int ui32;
    typedef unsigned short int ui16;
    typedef char ui8;

    #define make_f32xy make_float2;
    #define make_f32xyz make_float3;
    #define make_f32xyzw make_float4;

    #define make_f64xy make_float2;
    #define make_f64xy make_float3;
    #define make_f64xy make_float4;

    #define make_i32xy make_int2;
    #define make_i32xyz make_int3;
    #define make_i32xyzw make_int4;

    #define F32_MAX FLT_MAX;
    #define F64_MAX FLT_MAX;
#endif

////////////////////////////////////////////////////////////////

//void set_gpu_device(int deviceChoice,float minversion=3.0);
//void reset_gpu_device();

void print_error(std::string msg);
void print_warning(std::string msg);

void exit_simulation();

// Operation on C-Array
void array_push_back(unsigned int **vector, unsigned int &dim, unsigned int val);
void array_push_back(f32 **vector, unsigned int &dim, f32 val);
void array_insert(unsigned int **vector, unsigned int &dim, unsigned int pos, unsigned int val);
void array_insert(f32 **vector, unsigned int &dim, unsigned int pos, f32 val);
void array_append_array(f32 **vector, unsigned int &dim, f32 **an_array, unsigned int a_dim);

// Global simulation parameters
struct GlobalSimulationParameters {
    char physics_list[NB_PROCESSES];
    char secondaries_list[NB_PARTICLES];
    char record_dose_flag;

    unsigned int nb_of_particles;
    unsigned int nb_iterations;

    f32 time;
    unsigned int seed;

    // To build cross sections table
    unsigned int cs_table_nbins;
    f32 cs_table_min_E;
    f32 cs_table_max_E;

};

// Struct that handle colors
struct Color {
    f32 r, g, b;
};
Color make_color(f32 r, f32 g, f32 b);

#endif
