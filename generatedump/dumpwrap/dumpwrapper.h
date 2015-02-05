#ifndef DUMPWRAPPER_H
#define DUMPWRAPPER_H
#include <fstream>
#include <utility>

typedef unsigned long numtype;//only unsigned types are supported
const unsigned char maxtablesize=sizeof(numtype);
enum Endian{LittleEndian,BigEndian};

class DumpWrapper{
public:
	DumpWrapper(std::ofstream *output,Endian endian=LittleEndian, unsigned char items_per_column=8, unsigned char columns_number=2);
	virtual ~DumpWrapper();
	//Set the size of unsigned numbers wrapped into the stream
	DumpWrapper &operator |(unsigned char number_size);
	//Sends an unsigned number to be wrapped into the stream (the size should be set before)
	DumpWrapper &operator <<(numtype value);
	DumpWrapper &operator <<(std::pair<unsigned char,numtype> field);
protected:
	virtual DumpWrapper &write(unsigned char value);
private:
	numtype cnt;
	unsigned char per_column;
	unsigned char colunms;
	std::ofstream *out;
	Endian m_endian;
	unsigned char nsize;
	unsigned char ntable[maxtablesize];
};
#endif // DUMPWRAPPER_H
