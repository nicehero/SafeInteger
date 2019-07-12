#ifndef ___NICE___SAFE__INTEGER___
#define ___NICE___SAFE__INTEGER___
#include <stdint.h>
#include <utility>

using oper_uint_base = uint32_t;
using store_uint_base = uint64_t;
const store_uint_base oper_uint_base_max = store_uint_base(UINT32_MAX);

class OperUInt;
class StoreUInt
{
	friend class OperUInt;
public:
	StoreUInt() {
		impl = store_uint_base(0);
	}
	StoreUInt(store_uint_base impl_) {
		impl = store_uint_base(impl_);
	}
	bool operator>=(const store_uint_base& other) const {
		return impl >= other;
	}
	bool operator<=(const store_uint_base& other) const {
		return impl <= other;
	}
	bool operator>(const store_uint_base& other) const {
		return impl > other;
	}
	bool operator<(const store_uint_base& other) const {
		return impl < other;
	}
	bool operator==(const store_uint_base& other) const {
		return impl == other;
	}
	bool operator!=(const store_uint_base& other) const {
		return impl != other;
	}
	operator store_uint_base() const {
		return impl;
	}
	bool add(const store_uint_base& other) {
		store_uint_base ret = impl + other;
		if (ret < impl || ret < other) {
			return false;
		}
		impl = ret;
		return true;
	}
	bool add(oper_uint_base other) {
		store_uint_base o(other);
		return add(o);
	}
	bool add(OperUInt other);
	bool minus(const store_uint_base& other) {
		if (other > impl) {
			return false;
		}
		impl -= other;
		return true;
	}
	bool minus(oper_uint_base other) {
		store_uint_base o(other);
		return minus(o);
	}
	bool minus(OperUInt other);
	std::pair<bool, OperUInt> toOper();
	store_uint_base impl;
};

class OperUInt
{
	friend class StoreUInt;
public:
	OperUInt() {
		impl = oper_uint_base(0);
	}
	OperUInt(oper_uint_base impl_) {
		impl = impl_;
	}
	StoreUInt operator+(const OperUInt& right)const {
		return StoreUInt(store_uint_base(impl) + store_uint_base(right.impl));
	}
	StoreUInt operator*(const OperUInt& right)const {
		return StoreUInt(store_uint_base(impl) * (store_uint_base(right.impl)));
	}
	StoreUInt operator/(const OperUInt& right)const {
		return StoreUInt(store_uint_base(impl) / store_uint_base(right.impl));
	}
	StoreUInt operator%(const OperUInt& right)const {
		return StoreUInt(store_uint_base(impl) % (store_uint_base(right.impl)));
	}
	oper_uint_base impl;
};
inline bool StoreUInt::add(OperUInt other) {
	return add(other.impl);
}
inline bool StoreUInt::minus(OperUInt other) {
	return minus(other.impl);
}
inline std::pair<bool, OperUInt> StoreUInt::toOper()
{
	if (impl > oper_uint_base_max)
	{
		return std::make_pair(false, OperUInt(oper_uint_base(impl)));
	}
	return std::make_pair(true, OperUInt(oper_uint_base(impl)));
}

#endif
