// this file is distributed under 
// GPL v 3.0 license
#include "dumpwrapper.h"
#include <iomanip>
using namespace std;
namespace DumpGenerate {
	DumpWrapper::DumpWrapper(Endian endian) {
		m_endian=endian;
		nsize=1;
	}
	DumpWrapper::~DumpWrapper() {}
	DumpWrapper &DumpWrapper::operator |(unsigned char number_size) {
		if(0==number_size){
			reset_counter();
			*this|1;
			return *this;
		}
		if(number_size>maxtablesize)throw;
		nsize=number_size;
		return *this;
	}
	DumpWrapper &DumpWrapper::operator <<(numtype value) {
		numtype tmp=value;
		for(unsigned char i=0; i<nsize; i++) {
			ntable[i]=tmp%256;
			tmp/=256;
		}
		switch(m_endian) {
			case LittleEndian:
				for(unsigned char i=0; i<nsize; i++)write(ntable[i]);
				break;
			case BigEndian:
				for(unsigned char i=0; i<nsize; i++)write(ntable[nsize-1-i]);
				break;
			default:
				throw;
		};
		return *this;
	}
	DumpWrapper& DumpWrapper::operator<<(numlist values) {
		for(numtype v:values)*this<<v;
		return *this;
	}
	DumpWrapper& DumpWrapper::operator<<(numvect values) {
		for(numtype v:values)*this<<v;
		return *this;
	}
	
	DumpWrapper &DumpWrapper::operator <<(numwithsize field) {
		unsigned char tmp=nsize;
		operator|(field.second)<<field.first|tmp;
		return *this;
	}
	DumpWrapperToText::DumpWrapperToText(ofstream* output, Endian endian, unsigned char items_per_column, unsigned char columns_number)
		:DumpWrapper(endian) {
		out=output;
		per_column=items_per_column;
		colunms=columns_number;
		cnt=0;
	}
	DumpWrapperToText::~DumpWrapperToText() {}
	DumpWrapper& DumpWrapperToText::write(unsigned char value) {
		ios state(nullptr);
		if(0==cnt%(per_column*colunms)) {
			if(cnt>0)*out<<"\n";
			*out<<hex<<uppercase<<setw(4)<<setfill('0')<<(cnt&0xffff);
		}
		if(0==cnt%(per_column))*out<<" ";
		*out<<" "<<hex<<uppercase<<setw(2)<<setfill('0')<<int(value);
		cnt++;
		return *this;
	}
	numtype DumpWrapperToText::count(){return cnt;}
	DumpWrapper& DumpWrapperToText::reset_counter(){
		*out<<"\n";
		cnt=0;
		return *this;
	}
	DumpWrapperToTextPacketDumps::DumpWrapperToTextPacketDumps(ofstream* output, Endian endian, unsigned char items_per_column, unsigned char columns_number)
		:DumpWrapperToText(output, endian, items_per_column, columns_number),DumpWrapper(endian){}
	DumpWrapperToTextPacketDumps::~DumpWrapperToTextPacketDumps(){}
	DumpWrapper& DumpWrapperToTextPacketDumps::write(unsigned char value){
		if(count()<last_bytes_repeat_cnt)
			torepeat[count()]=value;
		return DumpGenerate::DumpWrapperToText::write(value);
	}
	DumpWrapper& DumpWrapperToTextPacketDumps::reset_counter(){
		*this|1;
		unsigned char repeatcnt=count()<last_bytes_repeat_cnt?count():last_bytes_repeat_cnt;
		for(int i=0;i<repeatcnt;i++)
			*this<<torepeat[i];
		return DumpGenerate::DumpWrapperToText::reset_counter();
	}
};
