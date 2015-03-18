#ifndef WZYFLIUESLUXCADJ
#define WZYFLIUESLUXCADJ
#include <list>
#include "queue.h"
#include "detectionsystem.h"
namespace DumpGenerate {
	class TDCChannel;
	class TDCTime;
	class TDC:public virtual IDetector{
	public:
		TDC(numtype id,numtype null_channel=0);
		virtual ~TDC();
		TDC &operator<<(std::shared_ptr<TDCChannel> channel);
		TDC &operator<<(numtype channel_id);
		const std::shared_ptr<TDCChannel> operator[](numtype channel_id);
		numtype ID();
	protected:
		virtual std::shared_ptr<DataItem> getEvent()override;
	private:
		numtype m_id;
		numtype n_ch;
		std::vector<std::shared_ptr<TDCChannel>> pluged_channels;
	};
	class TDCChannel{
		friend class TDC;
	public:
		TDCChannel(numtype id);
		virtual ~TDCChannel();
		virtual TDCChannel &operator<<(TDCTime time);
		numtype ID();
	protected:
		std::list<std::pair<numtype,numtype>> &get_queue();
	private:
		numtype m_id;
		std::list<std::pair<numtype,numtype>> signal_queue;
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
		std::pair<numtype,numtype> returnDataWord(numtype ch_id);
	private:
		numtype epoch,coasser,finetime;
		bool risingedge;
	};
	inline TDCTime NulTime(){return TDCTime(0,0,0,false);}
};
#endif
