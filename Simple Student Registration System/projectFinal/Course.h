#ifndef __COURSE_H
#define __COURSE_H
#include <string>
using namespace std;
class Course {
public:
	Course();
	~Course();
	Course(const Course &courseToCopy);
	Course(int cy, int cc, string cg);
	void operator=(const Course &right);
	int getCourseId();
	int getCourseCredit();
	string getCourseGrade();

private:
	int courseId;
	int courseCredit;
	string courseGrade;

};
#endif
