#ifndef COURSE_H_
#define COURSE_H_

#include <iostream>

class Course{
public:
	Course(int, int, std::string);
	int getCode() const;
	int getCredits() const;
	std::string getGrade() const;
	void print(std::ostream &os) const;
private:
	int code, credits;
	std::string grade;
};
inline std::ostream &operator <<(std::ostream &os, const Course &course) {course.print(os); return os;}
inline void Course::print(std::ostream &os) const {os << '\t' << this->code << " " << "(" << this->credits << " credits)" << ": " << this->grade << std::endl;}
inline Course::Course(int code, int credits, std::string grade) {this->code = code; this->credits = credits; this->grade = grade;}
inline int Course::getCode() const {return this->code;}
inline int Course::getCredits() const {return this->credits;}
inline std::string Course::getGrade() const {return this->grade;}
#endif
