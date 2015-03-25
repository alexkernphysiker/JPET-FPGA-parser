#ifndef ZWQTARNYQHWQYKGM
#define ZWQTARNYQHWQYKGM
#include <fstream>
#include <utility>
#include <list>
#include <vector>
namespace DumpGenerate {
	using namespace std;
	typedef unsigned long numtype;//only unsigned types are supported
	typedef list<numtype> numlist;
	typedef vector<numtype> numvect;
	typedef pair<numtype,numtype> numpair;
	typedef pair<numtype,unsigned char> numwithsize;
	const unsigned char maxtablesize=sizeof(numtype);
	enum Endian {LittleEndian,BigEndian};
	class DumpWrapper {
	protected:
		DumpWrapper(Endian endian);
	public:
		virtual ~DumpWrapper();
		//Set the size of unsigned numbers wrapped into the stream; 0 - resets internal counter
		DumpWrapper &operator |(unsigned char number_size);
		//Sends an unsigned number to be wrapped into the stream (the size should be set before)
		DumpWrapper &operator <<(numtype value);
		DumpWrapper &operator <<(numlist values);
		DumpWrapper &operator <<(numvect values);
		DumpWrapper &operator <<(numwithsize field);
	protected:
		virtual DumpWrapper &write(unsigned char value)=0;
		virtual DumpWrapper &reset_counter()=0;
	private:
		Endian m_endian;
		unsigned char nsize;
		unsigned char ntable[maxtablesize];
	};
	class DumpWrapperToText:public virtual DumpWrapper {
	public:
		DumpWrapperToText(ofstream* output, Endian endian, unsigned char items_per_column = 8, unsigned char columns_number = 2);
		virtual ~DumpWrapperToText();
	protected:
		virtual DumpWrapper &write(unsigned char value)override;
		virtual DumpWrapper &reset_counter()override;
		numtype count();
	private:
		unsigned char per_column;
		unsigned char colunms;
		ofstream *out;
		numtype cnt;
	};
	const unsigned char last_bytes_repeat_cnt=32;
	class DumpWrapperToTextPacketDumps:public virtual DumpWrapperToText{
	public:
		DumpWrapperToTextPacketDumps(ofstream* output, Endian endian, unsigned char items_per_column = 8, unsigned char columns_number = 2);
		virtual ~DumpWrapperToTextPacketDumps();
	protected:
		virtual DumpWrapper &write(unsigned char value)override;
		virtual DumpWrapper &reset_counter()override;
	private:
		unsigned char torepeat[last_bytes_repeat_cnt];
	};
};
#endif
