#ifndef DUMPWRAPPER_H
#define DUMPWRAPPER_H
#include <fstream>
#include <utility>
#include <list>
#include <vector>
namespace DumpGenerate {
typedef unsigned long numtype;//only unsigned types are supported
typedef std::list<numtype> numlist;
typedef std::vector<numtype> numvect;
typedef std::pair<numtype,numtype> numpair;
typedef std::pair<numtype,unsigned char> numwithsize;
const unsigned char maxtablesize=sizeof(numtype);
enum Endian {LittleEndian,BigEndian};
class DumpWrapper {
protected:
    DumpWrapper(Endian endian);
public:
    virtual ~DumpWrapper();
    //Set the size of unsigned numbers wrapped into the stream
    DumpWrapper &operator |(unsigned char number_size);
    //Sends an unsigned number to be wrapped into the stream (the size should be set before)
    DumpWrapper &operator <<(numtype value);
	DumpWrapper &operator <<(numlist values);
	DumpWrapper &operator <<(numvect values);
	DumpWrapper &operator <<(numwithsize field);
protected:
    virtual DumpWrapper &write(unsigned char value)=0;
private:
    Endian m_endian;
    unsigned char nsize;
    unsigned char ntable[maxtablesize];
};
class DumpWrapperToText:public virtual DumpWrapper {
public:
    DumpWrapperToText(std::ofstream* output, Endian endian, unsigned char items_per_column = 8, unsigned char columns_number = 2);
    virtual ~DumpWrapperToText();
protected:
    virtual DumpWrapper &write(unsigned char value)override;
private:
    unsigned char per_column;
    unsigned char colunms;
    std::ofstream *out;
    numtype cnt;
};
class TestDump:public virtual DumpWrapper{
public:
    TestDump(Endian endian);
    virtual ~TestDump();
protected:
	virtual DumpWrapper &write(unsigned char value)override;
public:
	unsigned char operator[](int index);
private:
	std::vector<unsigned char> m_dump;
};
};
#endif // DUMPWRAPPER_H
