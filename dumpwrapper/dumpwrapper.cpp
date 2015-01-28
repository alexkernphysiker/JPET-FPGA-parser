#include <QString>
#include "dumpwrapper.h"
DumpWrapper::DumpWrapper(QTextStream *output, uchar items_per_column, uchar columns_number){
	out=output;per_column=items_per_column;colunms=columns_number;
}
DumpWrapper::~DumpWrapper(){}
DumpWrapper &DumpWrapper::operator <<(uchar value){
	if(0==cnt%(per_column*colunms)){*out<<QString("\n%1").arg(cnt,4,16,QChar('0'));}
	if(0==cnt%(per_column))*out<<" ";
	*out<<QString(" %1").arg(value,2,16,QChar('0'));cnt++;
}
