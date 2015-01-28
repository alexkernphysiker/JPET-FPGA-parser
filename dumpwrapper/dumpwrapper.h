#ifndef DUMPWRAPPER_H
#define DUMPWRAPPER_H
#include <QTextStream>
enum Endian{BigEndian, LittleEndian};
class DumpWrapper{
public:
	DumpWrapper(QTextStream *output, uchar items_per_column=8, uchar columns_number=2);
	virtual ~DumpWrapper();
	virtual DumpWrapper &operator <<(uchar value);
private:
	uint cnt;
	uchar per_column;
	uchar colunms;
	QTextStream *out;
};

#endif // DUMPWRAPPER_H
