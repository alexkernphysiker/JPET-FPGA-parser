#ifndef ____TDC____
#define ____TDC____
#include "queue.h"
namespace DumpGenerate{
	class TDCHeader:public virtual DataSubItem{
	public:
		TDCHeader(bool error=false);
		virtual ~TDCHeader();
		virtual numlist out()override;
	private:
		numtype m_error;
	};
};
#endif //____TDC____