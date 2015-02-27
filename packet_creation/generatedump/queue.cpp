#include "queue.h"
using namespace std;
namespace DumpGenerate {
AbstractDataStructure::~AbstractDataStructure() {}
DumpWrapper &operator <<(DumpWrapper &output, AbstractDataStructure* data) {
    data->outputData(output);
    return output;
}
DumpWrapper &operator <<(DumpWrapper &output, shared_ptr<AbstractDataStructure> data) {
    return output<<data.get();
}

DataContainer::DataContainer():m_data() {}
DataContainer::~DataContainer() {}
DataContainer &DataContainer::operator<<(shared_ptr<AbstractDataStructure> item) {
    m_data.push_back(item);
    return *this;
}
DataContainer& DataContainer::operator<<(AbstractDataStructure* item) {
    return operator<<(shared_ptr<AbstractDataStructure>(item));
}
unsigned int DataContainer::SubItemCount() {
    return m_data.size();
}
void DataContainer::outputData(DumpWrapper &output) {
    for(auto item: m_data) {
        item->outputData(output);
    }
}
numtype DataContainer::size() {
    numtype res=0;
    for(auto item: m_data) {
        res+=item->size();
    }
    return res;
}
FieldSet::FieldSet():fields() {
    sizepos=-1;
    sizesize=0;
	sizeoffset=0;
}
FieldSet::~FieldSet() {}
FieldSet& FieldSet::setSizePositionAndSize(int pos, unsigned char sz) {
    if(pos<0)throw;
    if(0==sz)throw;
    sizepos=pos;
    sizesize=sz;
	return *this;
}
FieldSet& FieldSet::SetSizeOffset(numtype val){
	sizeoffset=val;
	return *this;
}

numtype FieldSet::size() {
    numtype res=0;
    for(auto field:fields)res+=field.second;
    if(sizepos>=0)res+=sizesize;
    return res;
}
FieldSet& FieldSet::AddField(numtype value,unsigned char sz) {
    if(0==sz)throw;
    fields.push_back(make_pair(value,sz));
    return *this;
}
void FieldSet::outputData(DumpWrapper& output) {
    int index=0;
    for(auto field:fields) {
		if(sizepos==index)output<<make_pair(size()-sizeoffset,sizesize);
        output<<field;
        index++;
    }
    if(sizepos==index)output<<make_pair(size(),sizesize);
}
Queue::Queue():FieldSet(),DataContainer() {
    setSizePositionAndSize(0);
    AddField(0x00030062);//this is another field!!! actually it is ignored
}
Queue::~Queue() {}
numtype Queue::size() {
    return FieldSet::size()+DataContainer::size();
}
void Queue::outputData(DumpWrapper& output) {
    FieldSet::outputData(output);
    DataContainer::outputData(output);
	output|0;
}
SubQueue::SubQueue(numtype EventID, numtype TriggerNumber):FieldSet(),DataContainer() {
    setSizePositionAndSize(0).SetSizeOffset(4);
	AddField(0x00020001);//actually is ignored
	AddField(EventID).AddField(TriggerNumber);
}
SubQueue::~SubQueue() {}
numtype SubQueue::size() {
    return FieldSet::size()+DataContainer::size();
}
void SubQueue::outputData(DumpWrapper& output) {
    FieldSet::outputData(output);
    DataContainer::outputData(output);
}
DataItem::DataItem(numtype deviceID):FieldSet() {
	AddField(deviceID,WordLength-DataItemCountSize);
    count=0;
}
DataItem::~DataItem() {}
DataItem& DataItem::operator<<(numtype word) {
    AddField(word);
    count++;
    return *this;
}
DataItem& DataItem::operator<<(numpair words){
	*this<<words.first;
	return *this<<words.second;
}
DataItem& DataItem::operator<<(numlist words){
	for(auto word:words)*this<<word;
	return *this;
}
DataItem& DataItem::operator<<(numvect words){
	for(auto word:words)*this<<word;
	return *this;
}
numtype DataItem::size() {
    return FieldSet::size()+DataItemCountSize;
}
void DataItem::outputData(DumpWrapper& output) {
	output<<make_pair(count,DataItemCountSize);
    FieldSet::outputData(output);
}
};
