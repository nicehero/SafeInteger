
#include <iostream>
#include "SafeInteger.hpp"


const static oper_uint_base price = 10;
class User {
public:
	bool buySomeThing(OperUInt num) {
		if (money.minus(num * price)) {
			someThing.add(num);
		}
		return true;
	}

	StoreUInt money = 10;
	StoreUInt someThing = 0;
};

int main()
{
	User user1;
	user1.buySomeThing(6554);
	std::cout << "user1.something:" << user1.someThing << "\n";

	return 0;
}
