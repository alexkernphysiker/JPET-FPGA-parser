#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <list>
#include <memory>
#include <utility>
#include "dumpwrap/dumpwrapper.h"
class AbstractDataStructure{
public:
	virtual ~AbstractDataStructure();
	virtual numtype size()=0;
	virtual void outputData(DumpWrapper &output)=0;
};
DumpWrapper &operator <<(DumpWrapper &output, std::shared_ptr<AbstractDataStructure> data);
class DataContainer:public virtual AbstractDataStructure{
public:
	DataContainer();
	virtual ~DataContainer();
	virtual numtype size()override;
	virtual void outputData(DumpWrapper &output)override;
	DataContainer &operator<<(std::shared_ptr<AbstractDataStructure> item);
	unsigned int SubItemCount();
private:
	std::list<std::shared_ptr<AbstractDataStructure>> m_data;
};
std::shared_ptr<DataContainer> operator<<(std::shared_ptr<DataContainer> output,std::shared_ptr<AbstractDataStructure> item);
class FieldSet:public virtual AbstractDataStructure{
public:
	FieldSet();
	virtual ~FieldSet();
	virtual numtype size()override;
	virtual void outputData(DumpWrapper &output)override;
	FieldSet &setSizePositionAndSize(int pos, unsigned char sz);
	FieldSet &AddField(unsigned char sz, numtype value);
private:
	std::list<std::pair<unsigned char,numtype>> fields;
	int sizepos;unsigned char sizesize;
};
const unsigned char WordLength=4;
class Queue:protected virtual FieldSet, public virtual DataContainer{
public:
    Queue();
    virtual ~Queue();
    virtual numtype size()override;
    virtual void outputData(DumpWrapper &output)override;
};
class SubQueue:protected virtual FieldSet, public virtual DataContainer{
public:
    SubQueue(numtype EventID,numtype TriggerNumber);
    virtual ~SubQueue();
    virtual numtype size()override;
    virtual void outputData(DumpWrapper &output)override;
};
const unsigned char DataItemCountSize=2;
class DataItem:public virtual FieldSet{
public:
    DataItem(numtype deviceID);
    virtual ~DataItem();
    virtual numtype size()override;
    virtual void outputData(DumpWrapper &output)override;
    DataItem &operator<<(numtype word);
private:
	numtype count;
};
std::shared_ptr<DataItem> operator<<(std::shared_ptr<DataItem> output,numtype word);
#endif //__QUEUE_H__