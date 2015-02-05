#include "queue.h"
AbstractDataStructure::~AbstractDataStructure(){}
DumpWrapper &operator <<(DumpWrapper &output, AbstractDataStructure &data){
	data.outputData(output);
	return output;
}
AbstractDataContainer::~AbstractDataContainer(){}
AbstractDataContainer &AbstractDataContainer::AddData(std::shared_ptr<AbstractDataStructure> item){
	m_data.push_back(item);
}
void AbstractDataContainer::outputData(DumpWrapper &output){
	for(auto item: m_data){
		item->outputData(output);
	}
}
numtype AbstractDataContainer::size(){
	numtype res=0;
	for(auto item: m_data){
		res+=item->size();
	}
	return res;
}
FieldSet::FieldSet(){
	sizepos=-1;
	sizesize=0;
}
FieldSet::~FieldSet(){}
FieldSet& FieldSet::setSizePositionAndSize(int pos, unsigned char sz){
	if(pos<0)throw;
	if(0==sz)throw;
	sizepos=pos;
	sizesize=sz;
}
numtype FieldSet::size(){
	numtype res=0;
	for(auto field:fields)res+=field.first;
	if(sizepos>=0)res+=sizesize;
	return res;
}
FieldSet& FieldSet::AddField(unsigned char sz, numtype value){
	if(0==sz)throw;
	fields.push_back(std::make_pair(sz,value));
}
void FieldSet::outputData(DumpWrapper& output){
	int index=0;
	for(auto field:fields){
		if(sizepos==index)output<<std::make_pair(sizesize,size());
		output<<field;
		index++;
	}
	if(sizepos==index)output<<std::make_pair(sizesize,size());
}



