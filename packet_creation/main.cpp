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
		DumpWrapperToTextPacketDumps wrap(&output,BigEndian);
		DetectionSystem alldetectors(0);
		shared_ptr<TDC> tdc=make_shared<TDC>(0x7777,0);
		for(numtype i=1;i<=5;i++)tdc<<i;
		alldetectors<<tdc;
		TDCTime timeconst(0xff,0xff,0xff,true);
		for(numtype i=1;i<=5;i++)(*tdc)[i]<<timeconst;
		wrap<<alldetectors.getEvent(0x1d1d00);
		wrap<<alldetectors.getEvent(0x1d1d01);
		for(numtype i=1;i<=5;i++)(*tdc)[i]<<timeconst;
		wrap<<alldetectors.getEvent(0x1d1d02);
		output.close();
		printf("File saved.\n");
	} else {
		printf("Could not open the file!\n");
	}
	return 0;
}
