
#include "SimpleStudent.h"

Student::Student(const int sid, const string sname)
{
	studentId = sid;
	studentName = sname;
	courses = new Course[0];
	courseNo = 0;
}

Student::~Student()
{   //çalýþtýrýnca hata fýrlatýyo
	//delete[] courses;

}

Student::Student(const Student & studentToCopy)
{
	studentId = studentToCopy.studentId;
	studentName = studentToCopy.studentName;
	courses = new Course[studentToCopy.courseNo];
	courseNo = studentToCopy.courseNo;
	courses = studentToCopy.courses;
}

void Student::operator=(const Student & right)
{
	studentId = right.studentId;
	studentName = right.studentName;
	courses = right.courses;
	courseNo = right.courseNo;
}

int Student::getStudentId()
{
	return studentId;
}

string Student::getStudentName()
{
	return studentName;
}

double Student::calculateStudentCurrentGPA()
{
	double gpa=0;
	double totalcredit=0;
	for(int i=0;i<courseNo;i++)
    {
		if(courses[i].getCourseGrade()=="A")
	      gpa += 4.0*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "A+")
			gpa += 4.0*courses[i].getCourseCredit();

		if(courses[i].getCourseGrade() == "A-")
			gpa += 3.7*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "B+")
			gpa += 3.3*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "B")
			gpa += 3.0*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "B-")
			gpa += 2.7*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "C+")
			gpa += 2.3*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "C")
			gpa += 2.0*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "C-")
			gpa += 1.7*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "D+")
			gpa += 1.3*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "D")
			gpa += 1.0*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "F")
			gpa += 0.0*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "FX")
			gpa += 0.0*courses[i].getCourseCredit();

		if (courses[i].getCourseGrade() == "FZ")
			gpa += 0.0*courses[i].getCourseCredit();


    }
	for(int i=0;i<courseNo;i++)
	{
		totalcredit += courses[i].getCourseCredit();
	}
	gpa = gpa / totalcredit;
	return gpa;
}

int Student::getCourseNo()
{
	return courseNo;
}

void Student::setCourseNo(int x)
{
	courseNo = x;
}

Course* Student::getCourses()
{
	return courses;
}

void Student::setCourses(Course * x)
{
	courses = x;
}





/*
#include <iostream>
#include "SimpleStudent.h"
#include <string>

//#include "Course.h"

using namespace std;

    //default constructor
    Student::Student(const int sid , const string sname){
        studentId = sid;
        studentName = sname;
        courses = new Course[0];
        courseCount = 0;
    }

    Student::~Student(){

    }

    //ADD copy constructor for studentToCopy
   Student::Student(const Student &studentToCopy){
        studentId = studentToCopy.studentId;
        studentName = studentToCopy.studentName;
        courses = new Course[studentToCopy.courseCount];
        courseCount = studentToCopy.courseCount;
        courses = studentToCopy.courses;
}


    void Student:: operator=(const Student &right){
     	studentId = right.studentId;
        studentName = right.studentName;
        courses = right.courses;
        courseCount = right.courseCount;
    }

    double Student:: calculateStudentCurrentGPA(){
        double totalPoint = 0;
        double totalCredit = 0;
        double multiplier = 0;
        for(int i = 0; i < courseCount; i++){
            if((courses[i].getCourseGrade()) == "+A" ){
                multiplier = 4.0;
            }else if((courses[i].getCourseGrade()) == "A" ){
                multiplier = 4.0;
            }else if((courses[i].getCourseGrade()) == "A-" ){
                multiplier = 3.7;
            }else if((courses[i].getCourseGrade()) == "B+" ){
                multiplier = 3.3;
            }else if((courses[i].getCourseGrade()) == "B" ){
                multiplier = 3.0;
            }else if((courses[i].getCourseGrade()) == "B-" ){
                multiplier = 2.7;
            }else if((courses[i].getCourseGrade()) == "C+" ){
                multiplier = 2.3;
            }else if((courses[i].getCourseGrade()) == "C" ){
                multiplier = 2.0;
            }else if((courses[i].getCourseGrade()) == "C-" ){
                multiplier = 1.7;
            }else if((courses[i].getCourseGrade()) == "D+" ){
                multiplier = 1.3;
            }else if((courses[i].getCourseGrade()) == "D" ){
                multiplier = 1.0;
            }else if((courses[i].getCourseGrade()) == "F" ){
                multiplier = 0.0;
            }else if((courses[i].getCourseGrade()) == "FX" ){
                multiplier = 0.0;
            }else if((courses[i].getCourseGrade()) == "FZ" ){
                multiplier = 0.0;
            }else{
                multiplier = 0.0;
            }

            totalPoint = totalPoint + (multiplier * courses[i].getCourseCredit());
            totalCredit+= courses[i].getCourseCredit();
        }

        return (totalPoint / totalCredit);

    }

//Get methods to be able to manipulate Student values
int Student::getStudentId(){
    return studentId;
}

string Student::getStudentName(){
    return studentName;
}

int Student:: getCourseCount(){
    return courseCount;
}

void Student:: setCourseCount(int courseCou){
    courseCount = courseCou;
}

Course* Student:: getCourses(){
    return courses;
}

void Student::setCourses(Course * newCourse)
{
	courses = newCourse;
}


*/
