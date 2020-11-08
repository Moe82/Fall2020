#include <iostream>

#include "student.h"

using namespace std;

Student::Student(string name, int id, vector<Course> courses){
	this->name = name;
	this->id = id;
	this->courses = courses;
}

int Student::getId() const{
	return this->id;
}

string Student::getName() const{
	return this->name;
}

double Student::getGPA() const{
	double value = 0.0, totalCredits = 0.0, grade = 0.0;
	for(int i=0; i < courses.size(); i++){
   
   			if (courses[i].getGrade() == "A")
        		grade = 4.0;
	        else if (courses[i].getGrade() == "B")
	        	grade = 3.0;
	        else if (courses[i].getGrade() == "C")
	        	grade = 2.0;
	        else if (courses[i].getGrade() == "D")
	        	grade = 1.0;	        	    
   		value += grade * courses[i].getCredits();
   		totalCredits += courses[i].getCredits();
   	}
   	return (value / totalCredits);
}

void Student::print(std::ostream &os) const{
	os << this->id << " " << this->name << ": " << this->getGPA() << endl;
		for(int i=0; i < courses.size(); i++)
			os << courses[i];
}