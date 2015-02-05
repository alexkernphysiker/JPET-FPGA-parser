#include <iostream>
#include <fstream>
#include "dumpwrap/dumpwrapper.h"
#include "queue.h"
using namespace std;
int main(int arg_cnt,char**arg){
	if(arg_cnt<=1){
		printf("Required parameters:\n");
		return -1;
	}
	ofstream output;
	output.open(arg[1]);
	if(output.is_open()){
		DumpWrapper wrap(&output,BigEndian);
		Queue queue;
		wrap<<queue;
		output.close();printf("File saved.\n");
	}else{
		printf("Could not open the file!\n");
	}
	return 0;
}
