//NOTE: numtype should be defined before including this file
template<int b>
struct bit{enum{set=numtype(1)<<b,unset = !set};};
template<int a, int b>
struct bits{enum{set=(numtype(1)<<a)|bits<a-1,b>::set,unset = !set};};
template<int b>
struct bits<b,b>{enum{set=bit<b>::set,unset = !set};};
