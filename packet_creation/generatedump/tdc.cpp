#include "tdc.h"
using namespace std;
namespace DumpGenerate {
	TDC::TDC(numtype id, numtype null_channel):m_id(id),n_ch(null_channel){}
	TDC::~TDC(){}
	numtype TDC::ID(){return m_id;}
	TDC& TDC::operator<<(shared_ptr< TDCChannel > channel){
		for(auto ch:pluged_channels)
			if(channel->ID()==ch->ID())
				throw;
			pluged_channels.push_back(channel);
		return *this;
	}
	TDC& TDC::operator<<(numtype channel_id){return *this<<make_shared<TDCChannel>(channel_id);}
	const shared_ptr< TDCChannel > TDC::operator[](numtype channel_id){
		for(auto channel:pluged_channels)
			if(channel->ID()==channel_id)
				return channel;
			throw;
	}
	
	shared_ptr< DataItem > TDC::getEvent(){
		auto res=make_shared<DataItem>(m_id);
		{//header
			numtype errorcode=0;
			numtype somecode=0x00;//it's ignored
			res<<(occupy_bits<15,0>(errorcode)|occupy_bits<23,16>(somecode)|bit<29>::set);
		}
		res<<NulTime().returnDataWord(n_ch);
		for(auto channel:pluged_channels){
			for(auto data:channel->get_queue())
				res<<data;
			channel->get_queue().clear();
		}
		return res;
	}
	TDCChannel::TDCChannel(numtype id):m_id(id){}
	TDCChannel::~TDCChannel(){}
	numtype TDCChannel::ID(){return m_id;}
	list<pair<numtype,numtype>> &TDCChannel::get_queue(){return signal_queue;}
	TDCChannel& TDCChannel::operator<<(TDCTime time){
		signal_queue.push_back(time.returnDataWord(m_id));
	}
	TDCTime::TDCTime():TDCTime(0,0,0,false){}
	TDCTime::TDCTime(const TDCTime& source){
		risingedge=source.risingedge;
		epoch=source.epoch;
		coasser=source.coasser;
		finetime=source.finetime;
	}
	TDCTime::TDCTime(numtype e, numtype c, numtype f, bool r){
		if(e>bits_in<27,0>::set)throw;
		if(c>bits_in<10,0>::set)throw;
		if(f>bits_in<9,0>::set)throw;
		epoch=e;
		coasser=c;
		finetime=f;
		risingedge=r;
	}
	numtype TDCTime::Coasser(){return coasser;}
	numtype TDCTime::Epoch(){return epoch;}
	numtype TDCTime::FineTime(){return finetime;}
	bool TDCTime::RisingEdge(){return risingedge;}
	pair<numtype,numtype> TDCTime::returnDataWord(numtype ch_id){
		return make_pair(
			bits_in<30,29>::set|occupy_bits<27,0>(epoch),
						 bit<31>::set|occupy_bits<28,22>(ch_id)|occupy_bits<21,12>(finetime)|
						 (risingedge?bit<11>::set:0)|occupy_bits<10,0>(coasser)
		);
	}
}