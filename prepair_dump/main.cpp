#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
const uchar items_per_column=8;
const uchar colunms_number=2;
uint n=50;
uchar dump[] ={
	0,1,2,3,4,5,6,7,8,9,
	0,1,2,3,4,5,6,7,8,9,
	0,1,2,3,4,5,6,7,8,9,
	0,1,2,3,4,5,6,7,8,9,
	0,1,2,3,4,5,6,7,8,9
};
int main(int arg_cnt,char**arg){
		if(arg_cnt<=1){
				printf("Required parameters:\n");
				return -1;
		}
		QFile output(arg[1]);
		output.open(QIODevice::WriteOnly);
		if(output.isOpen()){
				QTextStream out(&output);
				uint cnt=0;
				while(cnt<n){
					if(0==cnt%(items_per_column*colunms_number)){out<<QString("\n%1").arg(cnt,4,16,QChar('0'));}
					if(0==cnt%(items_per_column))out<<" ";
					out<<QString(" %1").arg(dump[cnt],2,16,QChar('0'));cnt++;
				}
				output.close();
				printf("done.\n");
		}else {
				printf("Cannot open output file\n");
				return -1;
		}
		return 0;
}
