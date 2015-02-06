//NOTE: numtype should be defined before including this file
// a is always the index of the greatest bit
// b is always the index of the smallest bit
template<int b>
struct bit{enum{set=numtype(1)<<b,unset = !set};};
template<int a, int b>
struct bits{enum{set=(numtype(1)<<a)|bits<a-1,b>::set,unset = !set};};
template<int b>
struct bits<b,b>{enum{set=bit<b>::set,unset = !set};};
template<int a, int b>
numtype occupy_bits(numtype small_value){
	numtype moved=small_value<<b;
	numtype cut=moved&bits<a,b>::set;
	if(cut!=moved)throw;
	return cut;
}
