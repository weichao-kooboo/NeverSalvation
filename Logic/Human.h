#pragma once
#ifndef NS_HUMAN
#define NS_HUMAN

#include "DynamicActor.h"
#include "Movement.h"

class LOGIC_API Human :public DynamicActor, public Movement {
public:
	Human() {

#ifdef NS_DEBUG
		cout << "Human\r\n" << endl;
#endif // NS_DEBUG
		Strength = 0;
		Agility = 0;
		Intelligence = 0;
		Endurance = 0;
	};
	unsigned short Strength;
	unsigned short Agility;
	unsigned short Intelligence;
	unsigned short Endurance;
	void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void Jump();
    void Death();
    void Initlize();
    void Release();
	virtual ~Human() {
#ifdef NS_DEBUG
		cout << "Human delete\r\n" << endl;
#endif // NS_DEBUG
	};
};
#endif // !NS_HUMAN