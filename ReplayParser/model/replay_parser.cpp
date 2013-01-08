/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#include "replay_parser.h"
#include "Replay.h"

Replay::Shared ReplayParser::LoadFromFile( const std::string& filename )
{
	fstream fs;
	fs.open(filename, fstream::in | fstream::binary);

	if (fs.is_open())
	{
		fs.seekg (0, ios::end);
		fstream::pos_type length = fs.tellg();
		fs.seekg (0, ios::beg);

		// allocate memory:
		char* buffer = new char [(int)length];

		// read data as a block:
		fs.read (buffer,length);
		fs.close();

		io::stream_buffer<io::basic_array_source<char> > buf(buffer, length);
		std::istream memory_stream(&buf);

		io::filtering_streambuf<io::input> in;
		in.push(io::gzip_decompressor());
		in.push(memory_stream);

		io::filtering_istream stream(in);

		Replay::Shared result = Replay::ReadFromStream(stream);
		
		result->PrintInfo();


		return result;

	}
	
	throw new exception("something went wrong");
}

void ReplayParser::SaveToFile(const Replay& replay, const std::string& filename)
{
	ofstream file(filename, ios_base::out | ios_base::binary);
	io::filtering_streambuf<io::output> in;
	in.push(io::gzip_compressor());
	in.push(file);
	
	io::filtering_ostream output_filtering_stream(in);
	replay.WriteToStream(output_filtering_stream);
}