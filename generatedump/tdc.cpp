#include "tdc.h"
#include "bit_opr.h"
#include <math.h>
using namespace std;
namespace DumpGenerate {
TDCHeader::TDCHeader(bool error){
	if(error)
		m_error=(rand()&bits<15,0,numtype>::set);
	else
		m_error=0;
}
TDCHeader::~TDCHeader(){}
const numtype tdc_header_signature=0x20000000;
numlist TDCHeader::out(){
	numlist res;
	res.push_back(m_error|(rand()&bits<24,16,numtype>::set)|bit<29,numtype>::set);
	return res;
}


}