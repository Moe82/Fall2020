#include <fstream>
#include <iterator>
#include <string>
#include <vector> 

#include "student.h"

using namespace std;

void load(string fname, vector<Student> &students);

int main() {
	try {
		vector<Student> students;
		load("student.data", students);
		cout << endl << students.size() << " records processed" << endl;
		return 0;
	} catch(string message) {
		cout << "*** Exception *** " << message << endl;
		exit(1);
	}
}

struct compareGrades{
	inline bool operator() (const Course& course1, const Course& course2){
        return (course1.getGrade() < course2.getGrade());
    }
};

struct compareStudents{
    inline bool operator() (const Student& student1, const Student& student2){
        return (student1.getGPA() > student2.getGPA());
    }
};

void load(string fname, vector<Student> &students) {
    ifstream file;
    file.open("student.data");
	istream_iterator<string> word_iter(file), word_iter_end;
	vector<string> tokens; 
	for ( ; word_iter != word_iter_end; ++ word_iter ) {
    	tokens.push_back(*word_iter);
	}
	vector<int> indicesOfNegative1;
	for(int i=0; i < tokens.size(); i++){
		if (tokens[i] == "-1")
			indicesOfNegative1.push_back(i);
	}
	vector<vector<string> > subVecters;
	int vBegin = 0, vEnd = 0;
	for(int i=0; i < indicesOfNegative1.size(); i++){
		vEnd = tokens.size() - indicesOfNegative1[i];
		vector<string> v(tokens.begin() + vBegin, tokens.end() - vEnd);
		vBegin = indicesOfNegative1[i]+1;
		subVecters.push_back(v);
	}
	for(int i=0; i < subVecters.size(); i++){
		vector<Course> courses;
		for (int x=2; x < subVecters[i].size(); x+=3){
			Course c(stoi(subVecters[i][x]), stoi(subVecters[i][x+1]), subVecters[i][x+2]);
			courses.push_back(c);
		}
		students.push_back(Student(subVecters[i][1], stoi(subVecters[i][0]), courses));
	}
	sort(students.begin(), students.end(), compareStudents());
	for(int i=0; i < students.size(); i++){
		sort(students[i].courses.begin(), students[i].courses.end(),compareGrades()); 
		cout << students[i]; 
	}
}