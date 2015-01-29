#include <QString>
#include "dumpwrapper.h"
DumpWrapper::DumpWrapper(QTextStream *output, Endian endian, uchar items_per_column, uchar columns_number){
    out=output;per_column=items_per_column;
    colunms=columns_number;cnt=0;
    m_endian=endian;nsize=1;
}
DumpWrapper::~DumpWrapper(){
}
DumpWrapper &DumpWrapper::write(uchar value){
    if(0==cnt%(per_column*colunms)){
        if(cnt>0)*out<<"\n";
        *out<<QString("%1").arg(cnt,4,16,QChar('0'));
    }
	if(0==cnt%(per_column))*out<<" ";
	*out<<QString(" %1").arg(value,2,16,QChar('0'));cnt++;
    return *this;
}
DumpWrapper &DumpWrapper::operator |(uchar number_size){
    if(0==number_size) throw;
    if(number_size>maxtablesize)throw;
    nsize=number_size;
    return *this;
}
DumpWrapper &DumpWrapper::operator <<(numtype value){
    numtype tmp=value;
    for(uchar i=0;i<nsize;i++){
        ntable[i]=uchar(tmp%256);
        tmp/=256;
    }
    switch(m_endian){
    case LittleEndian:
        for(uchar i=0; i<nsize;i++)write(ntable[i]);
        break;
    case BigEndian:
        for(uchar i=0; i<nsize;i++)write(ntable[nsize-1-i]);
        break;
    default:
        throw;
    };
    return *this;
}
