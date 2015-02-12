#include <math.h>
#include "detectionsystem.h"
#include "tdc.h"
using namespace std;
namespace DumpGenerate {
DetectionSystem::DetectionSystem(numtype trigger_number):trigger(trigger_number),elements(){}
DetectionSystem::~DetectionSystem(){}
DetectionSystem& DetectionSystem::operator<<(shared_ptr<IDetector> element){
	elements.push_back(element);
}
shared_ptr< Queue > DetectionSystem::getEvent(numtype event_id){
	auto packet=make_shared<SubQueue>(event_id,trigger);
	for(auto element:elements){
		auto data=element->getEvent();
		if(data)
			packet<<data;
	}
	return make_shared<Queue>()<<packet;
}




}