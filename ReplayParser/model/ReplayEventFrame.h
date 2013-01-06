/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayEventFrame_h__
#define ReplayEventFrame_h__

class ReplayEventFrame
{
public:
	typedef boost::shared_ptr<ReplayEventFrame> Shared;

	ReplayEventFrame(u_long header, u_char eventTimeAdjustment, char* event_data)
		: header(header), eventTimeAdjustment(eventTimeAdjustment), event_data(event_data)
	{

	}

	void swap(ReplayEventFrame & other)
	{
		std::swap(header, other.header);
		std::swap(eventTimeAdjustment, other.eventTimeAdjustment);
		std::swap(event_data, other.event_data);
	}

	ReplayEventFrame & operator = (ReplayEventFrame other) 
	{
		swap(other);
		return *this;
	}

	ReplayEventFrame::ReplayEventFrame( const ReplayEventFrame& other ) :
		header( other.header ), eventTimeAdjustment( other.eventTimeAdjustment ), event_data(nullptr)
	{
		if (other.event_data != nullptr)
		{
			event_data = new char[GetEventSize(header)];
			memcpy(event_data, other.event_data, GetEventSize(header));
		}
	}

	~ReplayEventFrame()
	{
		if (event_data != nullptr) delete[] event_data;
	}

	static ReplayEventFrame::Shared ReadFromStream(istream& stream) 
	{
		u_long header = BinaryStreamUtil::ReadBinary<u_long>(stream);
		u_long size = GetEventSize(header);
		u_char eventTimeAdjustment = BinaryStreamUtil::ReadBinary<u_char>(stream, 1); // Unknown 
		char* data;
		if (size > 0)
		{
			data = BinaryStreamUtil::ReadArray<char>(stream, size);
		}
		else
		{
			data = nullptr;
		}

		return ReplayEventFrame::Shared(new ReplayEventFrame(header, eventTimeAdjustment, data));
	}

	void WriteToStream(std::ostream& stream) const
	{
		BinaryStreamUtil::WriteBinary<u_long>(header, stream);
		BinaryStreamUtil::WriteBinary<char>(eventTimeAdjustment, stream);
		BinaryStreamUtil::WriteArray<char>(event_data, GetSize(), stream);
	}

	u_long GetOwner() const { return GetEventOwner(header); }
	u_long GetSize() const { return GetEventSize(header); }
	u_long GetType() const { return GetEventType(header); }
	u_long GetGameSession() const { return GetEventSession(header); }
	EventFlags GetFlag() const { return GetEventFlag(header); }
	EventClass GetClass() const { return GetEventClass(header); }

	u_char GetEventTimeAdjustment() const { return eventTimeAdjustment; }
	char* GetEventData() const { return event_data; } 
protected:
	u_long header;
	u_char eventTimeAdjustment;
	char* event_data;
};
#endif // ReplayEventFrame_h__
