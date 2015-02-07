#include "tdc.h"
#include <math.h>
using namespace std;
namespace DumpGenerate {
#include "../../math_h/bit_opr.cc"//define bit operations
numtype TDCHeader(bool error) {
    numtype errorcode=0;
    numtype somecode=0x77;//it's ignored
    if(error)
        errorcode=0xffff;
    return occupy_bits<15,0>(errorcode)|occupy_bits<23,16>(somecode)|bit<29>::set;
}
numpair TDCTime(numtype channel, numtype epoch, numtype coasser, numtype finetime,bool rizingedge) {
    numtype rize=0;
    if(rizingedge)rize=bit<11>::set;
    return make_pair(bits_in<30,29>::set|occupy_bits<27,0>(epoch),
                     bit<31>::set|occupy_bits<28,22>(channel)|occupy_bits<21,12>(finetime)|rize|occupy_bits<10,0>(coasser)
                    );
}
}
