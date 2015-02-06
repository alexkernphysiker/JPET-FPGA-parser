#include "tdc.h"
#include <math.h>
using namespace std;
namespace DumpGenerate {
TDCHeader::TDCHeader(bool error){
	if(error)
		errorcode=0xffff&rand();
	else
		errorcode=0;
	randomcode=0x1ff&rand();
}
TDCHeader::~TDCHeader(){}
list<numtype> TDCHeader::out(){
	list<numtype> res;
	res.push_back(errorcode|((randomcode|(0x1<<(8+5)))<<16));
	return res;
}


}