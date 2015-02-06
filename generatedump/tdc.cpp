#include "tdc.h"
#include <math.h>
using namespace std;
namespace DumpGenerate {
TDCHeader::TDCHeader(bool error){
	if(error)
		errorcode=0xffff&rand();
	else
		errorcode=0;
	randomcode=0x1ff0000&rand();
}
TDCHeader::~TDCHeader(){}
const numtype tdc_header_signature=0x20000000;
list<numtype> TDCHeader::out(){
	list<numtype> res;
	res.push_back(errorcode|randomcode|tdc_header_signature);
	return res;
}


}