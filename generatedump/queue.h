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
DumpWrapper &operator <<(DumpWrapper &output, AbstractDataStructure &data);
class AbstractDataContainer:public virtual AbstractDataStructure{
public:
	virtual ~AbstractDataContainer();
	virtual numtype size()override;
	virtual void outputData(DumpWrapper &output)override;
	AbstractDataContainer &AddData(std::shared_ptr<AbstractDataStructure> item);
private:
	std::list<std::shared_ptr<AbstractDataStructure>> m_data;
};
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
#endif //__QUEUE_H__