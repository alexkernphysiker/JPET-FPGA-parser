// this file is distributed under 
// GPL v 3.0 license
#ifndef WZYFLIUESLUXCADJ
#define WZYFLIUESLUXCADJ
#include <list>
#include "queue.h"
#include "detectionsystem.h"
namespace DumpGenerate {
	using namespace std;
	class TDCChannel;
	class TDCTime;
	class TDC:public virtual IDetector{
	public:
		TDC(numtype id,numtype null_channel=0);
		virtual ~TDC();
		TDC &operator<<(shared_ptr<TDCChannel> channel);
		TDC &operator<<(numtype channel_id);
		const shared_ptr<TDCChannel> operator[](numtype channel_id);
		numtype ID();
	protected:
		virtual shared_ptr<DataItem> getEvent()override;
	private:
		numtype m_id;
		numtype n_ch;
		vector<shared_ptr<TDCChannel>> pluged_channels;
	};
	class TDCChannel{
		friend class TDC;
	public:
		TDCChannel(numtype id);
		virtual ~TDCChannel();
		virtual TDCChannel &operator<<(TDCTime time);
		numtype ID();
	protected:
		list<pair<numtype,numtype>> &get_queue();
	private:
		numtype m_id;
		list<pair<numtype,numtype>> signal_queue;
	};
	class TDCTime{
		friend class TDCChannel;
		friend class TDC;
	public:
		TDCTime();
		TDCTime(const TDCTime &source);
		TDCTime(numtype e, numtype c, numtype f, bool r);
		~TDCTime(){}
		numtype Epoch();
		numtype Coasser();
		numtype FineTime();
		bool RisingEdge();
	protected:
		pair<numtype,numtype> returnDataWord(numtype ch_id);
	private:
		numtype epoch,coasser,finetime;
		bool risingedge;
	};
	inline TDCTime NulTime(){return TDCTime(0,0,0,false);}
};
#endif
