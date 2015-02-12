#ifndef ____DETECTION_SYSTEM_______
#define ____DETECTION_SYSTEM_______
#include <memory>
#include <vector>
#include "dumpwrap/dumpwrapper.h"
#include "queue.h"
namespace DumpGenerate{
class IDetector;
class DetectionSystem{
public:
	DetectionSystem(numtype trigger_number);
	virtual ~DetectionSystem();
	DetectionSystem &operator<<(std::shared_ptr<IDetector> element);
	virtual std::shared_ptr<Queue> getEvent(numtype event_id);
private:
	numtype trigger;
	std::vector<std::shared_ptr<IDetector>> elements;
};
	#include "../../math_h/bit_opr.cc"//define bit operations
class IDetector{
	friend class DetectionSystem;
public:
	virtual ~IDetector(){}
protected:
	virtual std::shared_ptr<DataItem> getEvent()=0;//null pointer in the result means no data available
};
};
#endif//____DETECTION_SYSTEM_______