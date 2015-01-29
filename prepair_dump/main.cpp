#include <QFile>
#include <QTextStream>
#include <dumpwrapper/dumpwrapper.h>
int main(int arg_cnt,char**arg){
		if(arg_cnt<=1){
				printf("Required parameters:\n");
				return -1;
		}
		QFile output(arg[1]);
		output.open(QIODevice::WriteOnly);
		if(output.isOpen()){
				QTextStream out(&output);
                DumpWrapper wrap(&out);
                wrap|2;
                for(uint i=0; i<512; i++)wrap<<i;
				output.close();
				printf("done.\n");
		}else {
				printf("Cannot open output file\n");
				return -1;
		}
		return 0;
}
