#include "tdc.h"
#include <math.h>
using namespace std;
namespace DumpGenerate {
#include "bit_opr.cc"//define bit operations
numtype TDCHeader(bool error) {
    numtype errorcode=0;
	numtype somecode=0x77;//it's ignored
    if(error)
        errorcode=rand();
	return occupy_bits<15,0>(errorcode)|occupy_bits<23,16>(somecode)|(0b001<<29);
}
numpair TDCTime(numtype channel, numtype epoch, numtype coasser, numtype finetime,bool rizingedge){
	numtype rize=0;
	if(rizingedge)rize=bit<11>::set;
	return make_pair((0b011<<29)|occupy_bits<27,0>(epoch),
					 (0b1<<31)|occupy_bits<28,22>(channel)|occupy_bits<21,12>(finetime)|rize|occupy_bits<10,0>(coasser)
				);
}
}
