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
#include <map>

#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#pragma warning( disable : 4244)
#include <boost/iostreams/filter/gzip.hpp>
#pragma warning( default : 4244)
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>

#define foreach(a, b) BOOST_FOREACH(a, b)

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
		return (r > 0.0f) ? floor(r + 0.5f) : ceil(r - 0.5f);
	}

}

#include "model/BinaryStreamUtil.h"
#include "model/format_constants.h"

#endif // pch_h__
