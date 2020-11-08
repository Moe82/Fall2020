#ifndef STUDENT_H_
#define STUDENT_H_
#include <vector> 
#include <iostream>

#include "course.h"

class Student{
public:
	Student(std::string name, int id, std::vector<Course> courses);
	int getId() const;
	std::string getName() const;
	double getGPA() const;
	void print(std::ostream &os) const;
	std::vector<Course> courses;
private:
	int id;
	std::string name;
};
inline std::ostream &operator <<(std::ostream &os, const Student &student) {student.print(os); return os;}
#endif