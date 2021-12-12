
#include "Course.h"


Course::Course()
{

}

Course::~Course()
{

}

Course::Course(const Course & courseToCopy)
{
	courseId = courseToCopy.courseId;
	courseCredit = courseToCopy.courseCredit;
	courseGrade = courseToCopy.courseGrade;
}

Course::Course(int cy, int cc, string cg)
{
	courseId = cy;
	courseCredit = cc;
	courseGrade = cg;
}

void Course::operator=(const Course & right)
{
	courseCredit = right.courseCredit;
	courseGrade = right.courseGrade;
	courseId = right.courseId;
}

int Course::getCourseId()
{
	return courseId;
}

int Course::getCourseCredit()
{
	return courseCredit;
}

string Course::getCourseGrade()
{
	return courseGrade;
}

 void Course:: setCourseCredit(int courseC){
        courseCredit = courseC;
    }

     void Course:: setCourseId(int courseI){
        courseId = courseI;
     }

    void Course:: setCourseGrade(string courseGr){
        courseGrade = courseGr;

    }
/*
#include "Course.h"

using namespace std;

Course:: Course(){

}

Course::~Course()
{

}

Course::Course(const Course & courseToCopy)
{
	courseId = courseToCopy.courseId;
	courseCredit = courseToCopy.courseCredit;
	courseGrade = courseToCopy.courseGrade;
}

void Course::operator=(const Course & right)
{
	courseCredit = right.courseCredit;
	courseGrade = right.courseGrade;
	courseId = right.courseId;
}


    int Course:: getCourseId(){
        return courseId;
    }

    int Course:: getCourseCredit(){
        return courseCredit;
    }

    string Course:: getCourseGrade(){
        return courseGrade;
    }

    void Course:: setCourseCredit(int courseC){
        courseCredit = courseC;
    }

     void Course:: setCourseId(int courseI){
        courseId = courseI;
     }

    void Course:: setCourseGrade(string courseGr){
        courseGrade = courseGr;
    }*/
