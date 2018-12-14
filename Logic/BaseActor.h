#pragma once
#ifndef NS_BASEACTOR
#define NS_BASEACTOR

#include "BaseObject.h"

class LOGIC_API BaseActor :public BaseObject {
public:
	BaseActor() {

#ifdef NS_DEBUG
		cout << "BaseActor\r\n" << endl;
#endif // NS_DEBUG
	};
	virtual void Death() = 0;
	virtual void Initlize() = 0;
	virtual void Release() = 0;
	virtual ~BaseActor() {
#ifdef NS_DEBUG
		cout << "BaseActor delete\r\n" << endl;
#endif // NS_DEBUG
	};
};
#endif // !NS_BASEACTOR