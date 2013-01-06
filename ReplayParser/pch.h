/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef pch_h__
#define pch_h__

#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <stdio.h>
#include <streambuf>
#include <stdint.h>
#include <iostream>
#include <math.h>

#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/shared_ptr.hpp>

namespace io = boost::iostreams;
using namespace std;

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

namespace
{
	float round(float r) 
	{
		return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
	}

}

#include "model/BinaryStreamUtil.h"
#include "model/format_constants.h"

#endif // pch_h__
