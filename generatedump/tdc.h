#ifndef ____TDC____
#define ____TDC____
#include "queue.h"
namespace DumpGenerate{
	class TDCHeader:public virtual DataSubItem{
	public:
		TDCHeader(bool error=false);
		virtual ~TDCHeader();
		virtual numtype out()override;
	private:
		numtype randomcode;
		numtype errorcode;
	};
};
#endif //____TDC____