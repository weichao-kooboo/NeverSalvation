#pragma once
#ifndef NS_ACTOR
#define NS_ACTOR

#include "BaseActor.h"

class LOGIC_API Actor : public BaseActor {
public:
	Actor() {
#ifdef NS_DEBUG
		cout << "Actor\r\n" << endl;
#endif // NS_DEBUG
		Armor = 0;
		Health = 0;
	}
	unsigned short Armor;
	unsigned short Health;
	virtual ~Actor() {
#ifdef NS_DEBUG
		cout << "Actor delete\r\n" << endl;
#endif // NS_DEBUG
	};
};
#endif // !NS_ACTOR