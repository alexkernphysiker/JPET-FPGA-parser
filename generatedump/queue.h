#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <list>
#include <memory>
#include <utility>
#include "dumpwrap/dumpwrapper.h"
namespace DumpGenerate {
class AbstractDataStructure {
public:
    virtual ~AbstractDataStructure();
    virtual numtype size()=0;
    virtual void outputData(DumpWrapper &output)=0;
};
DumpWrapper &operator <<(DumpWrapper &output, AbstractDataStructure *data);
DumpWrapper &operator <<(DumpWrapper &output, std::shared_ptr<AbstractDataStructure> data);
class DataContainer:public virtual AbstractDataStructure {
public:
    DataContainer();
    virtual ~DataContainer();
    virtual numtype size()override;
    virtual void outputData(DumpWrapper &output)override;
    DataContainer &operator<<(std::shared_ptr<AbstractDataStructure> item);
    DataContainer &operator<<(AbstractDataStructure *item);
    unsigned int SubItemCount();
private:
    std::list<std::shared_ptr<AbstractDataStructure>> m_data;
};
class FieldSet:public virtual AbstractDataStructure {
public:
    FieldSet();
    virtual ~FieldSet();
    virtual numtype size()override;
    virtual void outputData(DumpWrapper &output)override;
    FieldSet &setSizePositionAndSize(int pos, unsigned char sz);
    FieldSet &AddField(unsigned char sz, numtype value);
private:
    std::list<numwithsize> fields;
    int sizepos;
    unsigned char sizesize;
};
const unsigned char WordLength=4;
class Queue:protected virtual FieldSet, public virtual DataContainer {
public:
    Queue();
    virtual ~Queue();
    virtual numtype size()override;
    virtual void outputData(DumpWrapper &output)override;
};
class SubQueue:protected virtual FieldSet, public virtual DataContainer {
public:
    SubQueue(numtype EventID,numtype TriggerNumber);
    virtual ~SubQueue();
    virtual numtype size()override;
    virtual void outputData(DumpWrapper &output)override;
};
const unsigned char DataItemCountSize=2;
class DataSubItem {
public:
	virtual ~DataSubItem();
	virtual numlist out()=0;
};
class DataItem:public virtual FieldSet {
public:
    DataItem(numtype deviceID);
    virtual ~DataItem();
    virtual numtype size()override;
    virtual void outputData(DumpWrapper &output)override;
    DataItem &operator<<(numtype word);
    DataItem &operator<<(DataSubItem *item);
    DataItem &operator<<(std::shared_ptr<DataSubItem> item);
private:
    numtype count;
};
template<class outputtype,class datatype>std::shared_ptr<outputtype>
operator<<(std::shared_ptr<outputtype> output,datatype data) {
    *output << data;
    return output;
}
template<int b>
struct bit{enum{set=numtype(1)<<b,unset = !set};};
template<int a, int b>
struct bits{enum{set=(numtype(1)<<a)|bits<a-1,b>::set,unset = !set};};
template<int b>
struct bits<b,b>{enum{set=bit<b>::set,unset = !set};};

};
#endif //__QUEUE_H__
