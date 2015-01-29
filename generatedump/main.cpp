#include <iostream>
#include <fstream>
#include "dumpwrap/dumpwrapper.h"
using namespace std;
int main(int arg_cnt,char**arg){
	if(arg_cnt<=1){
		printf("Required parameters:\n");
		return -1;
	}
	ofstream output;
	output.open(arg[1]);
	if(output.is_open()){
		DumpWrapper wrap(&output);
		wrap|2;
		for(unsigned int i=0; i<512; i++)wrap<<i;
		output.close();
		printf("done.\n");
	}else{
		printf("Could not open the file!\n");
	}
	return 0;
}
