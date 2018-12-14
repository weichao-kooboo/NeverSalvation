#pragma once
#ifndef NS_DYNAMICACTOR
#define NS_DYNAMICACTOR

#include "Actor.h"

class LOGIC_API DynamicActor :public Actor {
public:
	DynamicActor() {

#ifdef NS_DEBUG
		cout << "DynamicActor\r\n" << endl;
#endif // NS_DEBUG
		Attack = 0;
	};
	unsigned short Attack;
	virtual ~DynamicActor() {
#ifdef NS_DEBUG
		cout << "DynamicActor delete\r\n" << endl;
#endif // NS_DEBUG
	};
};
#endif // !NS_DYNAMICACTOR