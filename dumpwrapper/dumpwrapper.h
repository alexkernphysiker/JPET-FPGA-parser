#ifndef DUMPWRAPPER_H
#define DUMPWRAPPER_H
#include <QTextStream>
typedef ulong numtype;//only unsigned types are supported
const uchar maxtablesize=sizeof(numtype);
enum Endian{LittleEndian,BigEndian};
class DumpWrapper{
public:
    DumpWrapper(QTextStream *output,Endian endian=LittleEndian, uchar items_per_column=8, uchar columns_number=2);
	virtual ~DumpWrapper();
    //Set the size of unsigned numbers wrapped into the stream
    DumpWrapper &operator |(uchar number_size);
    //Sends an unsigned number to be wrapped into the stream (the size should be set before)
    DumpWrapper &operator <<(numtype value);
protected:
    virtual DumpWrapper &write(uchar value);
private:
	uint cnt;
	uchar per_column;
	uchar colunms;
	QTextStream *out;
    Endian m_endian;
    uchar nsize;
    uchar ntable[maxtablesize];
};

#endif // DUMPWRAPPER_H
