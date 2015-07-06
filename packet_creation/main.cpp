// this file is distributed under 
// GPL v 3.0 license
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
		DetectionSystem alldetectors(0xff);
		shared_ptr<TDC> tdc1=make_shared<TDC>(0x7771,0);
		for(numtype i=1;i<=5;i++)tdc1<<i;
		shared_ptr<TDC> tdc2=make_shared<TDC>(0x7772,0);
		for(numtype i=1;i<=3;i++)tdc2<<i;
		alldetectors<<tdc1<<tdc2;
		TDCTime timeconst(0xff,0xff,0xff,true);
		for(numtype i=1;i<=5;i++)(*tdc1)[i]<<timeconst;
		for(numtype i=1;i<=3;i++)(*tdc2)[i]<<timeconst;
		wrap<<alldetectors.getEvent(0x1d1d00);
		wrap<<alldetectors.getEvent(0x1d1d01);
		TDCTime timeconst1(0x77,0x77,0x77,true);
		TDCTime timeconst2(0x77,0x77,0x78,false);
		for(numtype i=1;i<=3;i++)(*tdc2)[i]<<timeconst1;
		for(numtype i=1;i<=3;i++)(*tdc2)[i]<<timeconst2;
		wrap<<alldetectors.getEvent(0x1d1d02);
		for(numtype i=1;i<=5;i++)(*tdc1)[i]<<timeconst1;
		for(numtype i=1;i<=5;i++)(*tdc1)[i]<<timeconst2;
		wrap<<alldetectors.getEvent(0x1d1d03);
		output.close();
		printf("File saved.\n");
	} else {
		printf("Could not open the file!\n");
	}
	return 0;
}
