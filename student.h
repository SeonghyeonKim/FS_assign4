#pragma once

#ifndef STUDENT
#define STUDENT
#include <iostream>
class Student {
public:
	char Id[11]; char Name[11]; char Address[16];
	char DateEnroll[16]; char temp[16]; int NumberCredit;

	Student();
	friend std::istream& operator >> (std::istream& stream, Student& s);
	friend std::ostream& operator << (std::ostream& stream, Student& s);
};

Student::Student() {
	Id[0] = 0; Name[0] = 0; Address[0] = 0;
	DateEnroll[0] = 0; temp[0] = 0; NumberCredit = 0;
}

#endif

