#include "dumpwrapper.h"
#include <iomanip>
using namespace std;
DumpWrapper::DumpWrapper(ofstream *output, Endian endian, unsigned char items_per_column, unsigned char columns_number){
	out=output;per_column=items_per_column;
	colunms=columns_number;cnt=0;
	m_endian=endian;nsize=1;
}
DumpWrapper::~DumpWrapper(){}
DumpWrapper &DumpWrapper::write(unsigned char value){
	ios state(nullptr);
	if(0==cnt%(per_column*colunms)){
		if(cnt>0)*out<<"\n";
		*out<<hex<<uppercase<<setw(8)<<setfill('0')<<cnt; 
	}
	if(0==cnt%(per_column))*out<<" ";
	*out<<" "<<hex<<uppercase<<setw(2)<<setfill('0')<<int(value);
	cnt++;
	return *this;
}
DumpWrapper &DumpWrapper::operator |(unsigned char number_size){
	if(0==number_size) throw;
	if(number_size>maxtablesize)throw;
	nsize=number_size;
	return *this;
}
DumpWrapper &DumpWrapper::operator <<(numtype value){
	numtype tmp=value;
	for(unsigned char i=0;i<nsize;i++){
		ntable[i]=tmp%256;
		tmp/=256;
	}
	switch(m_endian){
		case LittleEndian:
			for(unsigned char i=0; i<nsize;i++)write(ntable[i]);
			break;
		case BigEndian:
			for(unsigned char i=0; i<nsize;i++)write(ntable[nsize-1-i]);
			break;
		default:
			throw;
	};
	return *this;
}
DumpWrapper &DumpWrapper::operator <<(std::pair<unsigned char,numtype> field){
	unsigned char tmp=nsize;
	operator|(field.first)<<field.second|tmp;
}

