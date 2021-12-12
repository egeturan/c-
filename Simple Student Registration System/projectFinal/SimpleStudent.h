
#ifndef __SIMPLE_STUDENT_H
#define __SIMPLE_STUDENT_H
#include <string>
#include "Course.h"
using namespace std;
class Student {
public:
	Student(const int sid = 0, const string sname = "");
	~Student();
	Student(const Student &studentToCopy);
	void operator=(const Student &right);
	int getStudentId();
	string getStudentName();
	double calculateStudentCurrentGPA();
	int getCourseNo();
	void setCourseNo(int x);
	Course* getCourses();
	void setCourses(Course* x);

private:
	Course *courses;
	int studentId;
	string studentName;
	int courseNo;
};
#endif




/*

#ifndef __SIMPLE_STUDENT_H
#define __SIMPLE_STUDENT_H
#include "Course.h"
#include <string>

using namespace std;

class Student {

public:
    Student(const int sid = 0, const string sname = "");
    ~Student();
    Student(const Student &studentToCopy);
    void operator=(const Student &right);

    double calculateStudentCurrentGPA();

    int getStudentId();
    string getStudentName();
    int getCourseCount();

    void setCourseCount(int courseCou);

    Course * getCourses();
    int getS

    void setCourses(Course * newCourse);

private:
    int studentId;
    string studentName;
    Course *courses;
    int courseNo;
    int courseCount;
};
#endif
*/
