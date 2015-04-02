#ifndef SFPRFPYSEVOIWSRN
#define SFPRFPYSEVOIWSRN
#include <memory>
#include <vector>
#include "dumpwrap/dumpwrapper.h"
#include "queue.h"
namespace DumpGenerate{
	using namespace std;
	class IDetector;
	class DetectionSystem{
	public:
		DetectionSystem(numtype trigger_number);
		virtual ~DetectionSystem();
		DetectionSystem &operator<<(shared_ptr<IDetector> element);
		virtual shared_ptr<Queue> getEvent(numtype event_id);
	private:
		numtype trigger;
		vector<shared_ptr<IDetector>> elements;
	};
	#include "math_h/bit_opr.cc"
	class IDetector{
		friend class DetectionSystem;
	public:
		virtual ~IDetector(){}
	protected:
		virtual shared_ptr<DataItem> getEvent()=0;//null pointer in the result means no data available
	};
};
#endif
