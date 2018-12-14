#pragma once
#ifndef NS_MOVEMENT
#define NS_MOVEMENT

class LOGIC_API Movement {
public:
	Movement() {

#ifdef NS_DEBUG
		cout << "Movement\r\n" << endl;
#endif // NS_DEBUG
	};
	bool CanFly;
	bool CanClimb;
	unsigned short Speed;
	unsigned short JumpAbility;
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;
	virtual void MoveUp() = 0;
	virtual void MoveDown() = 0;
	virtual void Jump() = 0;
	virtual ~Movement() {

#ifdef NS_DEBUG
		cout << "Movement delete\r\n" << endl;
#endif // NS_DEBUG
	};
};
#endif // !NS_MOVEMENT