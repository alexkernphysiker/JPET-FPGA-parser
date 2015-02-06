#include "tdc.h"
#include <math.h>
namespace DumpGenerate {
TDCHeader::TDCHeader(bool error){
	if(error)
		errorcode=0xffff&rand();
	else
		errorcode=0;
	randomcode=0x1ff&rand();
}
TDCHeader::~TDCHeader(){}
numtype TDCHeader::out(){
	return errorcode|(randomcode<<16)|(0x1<<(16+5));
}


}