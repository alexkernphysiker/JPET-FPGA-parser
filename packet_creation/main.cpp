#include <iostream>
#include <fstream>
#include "generatedump/queue.h"
#include "generatedump/tdc.h"
using namespace std;
using namespace DumpGenerate;
int main(int arg_cnt,char**arg) {
    if(arg_cnt<=1) {
        printf("Required parameters:\n");
        return -1;
    }
    ofstream output;
    output.open(arg[1]);
    if(output.is_open()) {
        DumpWrapperToText wrap(&output,BigEndian);
        wrap<<(make_shared<Queue>()<<(
                   make_shared<SubQueue>(0x1d1d,0xd1d1)<<
                   (make_shared<DataItem>(0xffff)<<1<<make_pair(2,3))<<
                   (make_shared<DataItem>(0xffff)<<8)
               )<<(
                   make_shared<SubQueue>(0x1d1d,0xd1d1)<<
                   (make_shared<DataItem>(0x7777)<<TDCHeader()<<TDCTime(1,0xff,0xff,0xff,true))
               ));
        output.close();
        printf("File saved.\n");
    } else {
        printf("Could not open the file!\n");
    }
    return 0;
}
