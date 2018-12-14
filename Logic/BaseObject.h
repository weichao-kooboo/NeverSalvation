#pragma once
#ifndef NS_BASEOBJECT
#define NS_BASEOBJECT

#include "Core.h"

class LOGIC_API BaseObject {
public:
	 BaseObject() {
		 Name = "";
		 Describe = "";
#ifdef NS_DEBUG
		 cout << "BaseObject:Name:" << Name << "Describe:" << Describe << "\r\n" << endl;
#endif // NS_DEBUG

	 };
	 BaseObject(const string name,const string des) {
		 Name = name;
		 Describe = des;
#ifdef NS_DEBUG
		 cout << "BaseObject:Name:" << Name << "Describe:" << Describe << "\r\n" << endl;
#endif // NS_DEBUG
	 };
	 BaseObject(const BaseObject& rhs) {
		 Name = rhs.Name;
		 Describe = rhs.Describe;
#ifdef NS_DEBUG
		 cout << "BaseObject:Name:" << Name << "Describe:" << Describe << "\r\n" << endl;
#endif // NS_DEBUG
	 };
	 BaseObject& operator=(const BaseObject& rhs) {
		 Name = rhs.Name;
		 Describe = rhs.Describe;
		 return *this;
	 };
	 bool operator==(const BaseObject& rhs) {
		 return Name == rhs.Name;
	 };
	 bool operator!=(const BaseObject& rhs) {
		 return Name != rhs.Name;
	 };
	 virtual ~BaseObject() {
#ifdef NS_DEBUG
		 cout << "BaseObject delete\r\n" << endl;
#endif // NS_DEBUG
	 };
//protected:
	 string Name;
	 string Describe;
};

#endif // !NS_BASEOBJECT