
#include "SRS.h"
#include <iostream>
using namespace std;


SRS::SRS()
{
	studentNo = 0;
}


SRS::~SRS()
{  //çalýþtýrýnca hata fýrlatýyo
	//delete[] students;

}

SRS::SRS(const SRS & srsToCopy)
{
	students = srsToCopy.students;
	studentNo = srsToCopy.studentNo;
}

void SRS::operator=(const SRS & right)
{
	studentNo = right.studentNo;
	students = new Student[studentNo];
	for(int i=0;i<studentNo;i++)
	{
		students[i]=right.students[i];
	}
}

bool SRS::addStudent(const int studentId, const string studentName)
{
	for(int i=0;i<studentNo;i++)
	{
      if(studentId==students[i].getStudentId())
	  {
		  return false;
	  }
	}
	Student *temp = students;
	students = new Student[studentNo + 1];
	for(int i=0;i<studentNo;i++)
	{
		students[i] = temp[i];
	}
	Student tempSu(studentId, studentName);
	studentNo++;
	students[studentNo - 1] = tempSu;
	delete [] temp;
	return true;
}

bool SRS::removeStudent(const int studentId)
{

	if(studentNo!=0)
	{
		for (int i = 0; i<studentNo; i++)
		{
			if (studentId == students[i].getStudentId())
			{
				Student *temp = students;
				students = new Student[studentNo - 1];

				for (int a = 0,b=0; a<studentNo - 1;b++)
				{
					if (temp[b].getStudentId() != studentId)
					{
						students[a] = temp[b];
						a++;
					}

				}


				studentNo--;
				delete [] temp;
				return true;
			}
		}

	}

	return false;


}

int SRS::getStudents(Student *& allStudents)
{
	allStudents=students;
	return studentNo;
}

bool SRS::addCourse(const int studentId, const int courseId, const string courseGrade, const int courseCredit)
{
	Course* tempa;
	for(int i=0;i<studentNo;i++)
        {
		   tempa = students[i].getCourses();
	       if(students[i].getStudentId()==studentId)
		   {
			  for(int j=0;j<students[i].getCourseNo();j++)
			  {
			      if(tempa[j].getCourseId()==courseId)
				  {
					  return false;
				  }
			  }
			  Course *temp;
			  temp = students[i].getCourses();
			  Course * temp2;
			  temp2= new Course[students[i].getCourseNo() + 1]; //
			  students[i].setCourses(temp2);

			  for(int a=0;a<students[i].getCourseNo();a++)
			  {
				  temp2[a] = temp[a];
			  }
			 Course tempC(courseId,courseCredit,courseGrade);

			  temp2[students[i].getCourseNo()] = tempC;

			  students[i].setCourses(temp2);

			  students[i].setCourseNo(students[i].getCourseNo() + 1);
			  delete[] temp;
			  delete[] tempa;
			  return true;
			 }

        }
	return false;
}

bool SRS::removeCourse(const int studentId, const int courseId)
{
	Course* temp;
	for(int i=0;i<studentNo;i++)
	{
		temp = students[i].getCourses();
	  if(students[i].getStudentId()==studentId)
	  {
	      for(int a=0;a<students[i].getCourseNo();a++)
		  {
		       if(temp[i].getCourseId()==courseId)
			   {
				   Course *tempA = temp;
				   temp=new Course[students[i].getCourseNo() - 1];

				   for (int a = 0, b = 0; a<students[i].getCourseNo() - 1; b++)
				   {
					   if (tempA[b].getCourseId() != courseId)
					   {
						   temp[a] = tempA[b];
						   a++;
					   }

				   }


				   students[i].setCourses(temp);
				   students[i].setCourseNo(students[i].getCourseNo()-1);
				   delete[] temp;
				   return true;

			   }
		  }
		  return false;

	  }
	}
	return false;
}

double SRS::calculateCourseGPA(const int courseId)
{  // burda bi yerde bir hata var.... çözemedim hatayý  belkide tüm iþlem hatalýdýr....
	Course* temp;
	double gpa= 0.0;
	double st = 0.0;
	  for(int i=0;i<studentNo;i++)
	  {
		  temp=students[i].getCourses();
		  for (int j = 0; j < students[i].getCourseNo(); j++)
		  {
			  if(temp[j].getCourseId()==courseId)
			  {
				  if (temp[j].getCourseGrade() == "A+")
					  gpa += 4.0;
				  if (temp[j].getCourseGrade() == "A")
					  gpa += 4.0;
				  if (temp[j].getCourseGrade() == "A-")
					  gpa += 3.7;
				  if (temp[j].getCourseGrade() == "B+")
					  gpa += 3.3;
				  if (temp[j].getCourseGrade() == "B")
					  gpa += 3.0;
				  if (temp[j].getCourseGrade() == "B-")
					  gpa += 2.7;
				  if (temp[j].getCourseGrade() == "C+")
					  gpa += 2.3;
				  if (temp[j].getCourseGrade() == "C")
					  gpa += 2.0;
				  if (temp[j].getCourseGrade() == "C-")
					  gpa += 1.7;
				  if (temp[j].getCourseGrade() == "D+")
					  gpa += 1.3;
				  if (temp[j].getCourseGrade() == "D")
					  gpa += 1.0;
				  if (temp[j].getCourseGrade() == "F")
					  gpa += 0.0;
				  if (temp[j].getCourseGrade() == "FX")
					  gpa += 0.0;
				  if (temp[j].getCourseGrade() == "FZ")
					  gpa += 0.0;

				  st=st+1.0;
			  }
		  }
	  }


	  gpa = gpa / st;

	  return gpa;
}



/*/
#include <iostream>
#include <string>
#include "SRS.h"
#include "SimpleStudent.h"
#include "Course.h"

using namespace std;

SRS::SRS(){
    students = new Student[1];
    studentCount = 0;
}


SRS::~SRS(){
    if(students != NULL) {
            cout << "students have been deleted" << endl;
            delete[] students;
        }
}

//arrange them later
SRS::SRS(const SRS & srsToCopy)
{
    //cout << "test for operator1" << endl;
	studentCount = srsToCopy.studentCount;
	students = srsToCopy.students;

}

void SRS::operator=(const SRS & right)
{
	studentCount = right.studentCount;
	students = new Student[studentCount];

	for(int i = 0; i < studentCount ;i++)
	{
	    //cout << "test for operator" << endl;
		students[i]=right.students[i];
	}
}

bool SRS:: addStudent(const int studentId, const string studentName) {
        bool isOk = true;

        if(!studentCount){
            Student st1(studentId, studentName);
            students[0] = st1;
            //test for the question is students[0] filled?
           // cout << "Name students[0]:" << students[0].getStudentName() <<"\nId students[0]: " << students[0].getStudentId() <<endl <<endl;
            studentCount++;

        }
        else{

        for (int i = 0; i < studentCount; i++) {
            if (students[i].getStudentId() == studentId) {
                isOk = false;
            }
        }
        if (isOk) { //if this is true then, we will add student to the students array

            Student *tempStudent = new Student[studentCount + 1];

            for(int i = 0; i < studentCount; i++){
               tempStudent[i] = students[i];
            }

            Student st1(studentId, studentName);
            tempStudent[studentCount] = st1;

            delete students;

            students = new Student[studentCount + 1];

            for(int  i = 0; i <= studentCount; i++){
                students[i] = tempStudent[i];
            }

            delete [] tempStudent;

            studentCount++; //studentCount has increased
        }
    }

        return isOk;
    }

  bool SRS::removeStudent(const int studentId) {
        bool deleteIt = false;
        int deleteIndices = 0;
        for (int i = 0; i < studentCount; i++) {
                  //cout << "Id is: " << students[i].getStudentId() <<"and given studentId is: "<< studentId << endl;
            if (students[i].getStudentId() == studentId) {//id exist on the system then deleteIt = true
                deleteIt = true;
                deleteIndices = i;
            }
        }

        if (deleteIt && (studentCount >= 1) ) { //if this is true we need to delete user from the system


           Student *tempStudent = new Student[studentCount - 1];

            for (int i = 0; i < deleteIndices; ++i) {
                tempStudent[i] = students[i];
            }

            for (int j = deleteIndices; j < studentCount - 1; ++j) {
                tempStudent[j] = students[j + 1];
            }

            delete students;

            students = new Student[studentCount - 1];

            for(int i = 0; i < studentCount - 1; i++){
                students[i] = tempStudent[i];
            }

            //test print students
           for(int i = 0; i < studentCount - 1; i++){
                //cout << "Elements are:  " << i << " is: " <<students[i].getStudentId() << "    ";
             }
             //cout << endl << endl;
            //end of print students

            delete [] tempStudent;
             studentCount--;
        }
        return deleteIt;
    }


int SRS::getStudents(Student *& allStudents)
{
	allStudents=students;
	return studentCount;
}


bool SRS:: addCourse(const int studentId, const int courseId, const string courseGrade, const int courseCredit){
    cout << "Student Count is: " << studentCount << endl;
    bool isStudentFound = false;
    int studentIndice = 0;
    //cout << "Student Count is: " << studentCount << endl;
    for(int i = 0; i < studentCount; i ++){
        if(students[i].getStudentId() == studentId){ //is this studentId included in our studentArray
            isStudentFound = true;
            studentIndice = i;
        }
    }

   cout << "reaches to there "<< " isstudentFound is: "<< isStudentFound << endl;

    if(isStudentFound){

                Course *temp = students[studentIndice].getCourses();
               //cout << "temp is" << temp[0].getCourseId()<<"      "  <<students[studentIndice].getCourseCount() <<endl;
                for(int j = 0; j < students[studentIndice].getCourseCount(); j++){

                    if(temp[j].getCourseId() == courseId){ //this course id is exist for at least one studnedt as a courseId
                       // cout << "student id's are: " << temp[j].getCourseId() << endl;
                        isStudentFound = false; //student exist in the array and this courseId exist for this student
                    }
                }

                delete [] temp;

            }


    if(isStudentFound){

            Course *temp;
            temp = students[studentIndice].getCourses();

            Course *tempCourse = new Course[students[studentIndice].getCourseCount() + 1]; //empty Courses

            students[studentIndice].setCourses(tempCourse);

            for(int i = 0; i < students[studentIndice].getCourseCount() ; i++){
                tempCourse[i] = temp[i];
            }

                //Create Object
                Course cr1;
                //assign values
                cr1.setCourseId(courseId);
                cr1.setCourseCredit(courseCredit);
                cr1.setCourseGrade(courseGrade);
                //Object created

                tempCourse[students[studentIndice].getCourseCount()] = cr1;

                students[studentIndice].setCourses(tempCourse);

                int a = students[studentIndice].getCourseCount();
                a++;

                students[studentIndice].setCourseCount(a);

                delete [] tempCourse;
                delete [] temp;
    }
    return isStudentFound;

}


bool SRS:: removeCourse(const int studentId, const int courseId){
    bool deleteIt = false;
    int studentIndex = 0;
    int courseIndex = 0;

    for(int i = 0; i < studentCount; i++){ //is student exist in the system
       Course *temp = students[i].getCourses();
       for(int j = 0; j < students[i].getCourseCount(); j++){ // look for courses

       if(students[i].getStudentId() == studentId && temp[j].getCourseId() == courseId){
        deleteIt = true;
        studentIndex = i;
        courseIndex = j;
       }

    }
    delete [] temp;

    } //we found that will we delete or not

    if(deleteIt){

        Course *temp = students[studentIndex].getCourses();

        Course *tempCourses = new Course[students[studentIndex].getCourseCount() - 1];

        for(int i = 0; i < courseIndex; i++){
            tempCourses[i] = temp[i];
        }

        for (int j = courseIndex; j < students[studentIndex].getCourseCount() - 1; ++j) {
                tempCourses[j] = temp[j + 1];
            }

            students[studentIndex].setCourses(tempCourses); // = tempCourses;

            delete [] tempCourses;
            delete [] temp;

    }

    return true;
}


double SRS:: calculateCourseGPA(const int courseId){
    int numOfStudent = 0; //number of student that takes this lesson
    double totalPoint = 0;
    double multiplier = 0;
    for(int i = 0; i < studentCount; i++){
        for(int j = 0;  j < courseCount; j++){
            Course *temp = (students[i].getCourses()); //bu student için course arrayini attık

            if(temp[j].getCourseId() == courseId){

           // if(students[i].courses[j].getCourseGrade == "A+"){
            if(temp[j].getCourseGrade() == "A+"){
                multiplier = 4.0;
            }else if(temp[j].getCourseGrade() == "A"){
                multiplier = 4.0;
            }else if(temp[j].getCourseGrade() == "A-"){
                multiplier = 3.7;
            }else if(temp[j].getCourseGrade() == "B+"){
                multiplier = 3.3;
            }else if(temp[j].getCourseGrade() == "B"){
                multiplier = 3.0;
            }else if(temp[j].getCourseGrade() == "B-"){
                multiplier = 2.7;
            }else if(temp[j].getCourseGrade() == "C+"){
                multiplier = 2.3;
            }else if(temp[j].getCourseGrade() == "C"){
                multiplier = 2.0;
            }else if(temp[j].getCourseGrade() == "C-"){
                multiplier = 1.7;
            }else if(temp[j].getCourseGrade() == "D+"){
                multiplier = 1.3;
            }else if(temp[j].getCourseGrade() == "D"){
                multiplier = 1.0;
            }else {
                multiplier = 0.0;
            }
            //multiplier has arranged
                totalPoint = totalPoint +  multiplier;
                numOfStudent++;

            }
            delete [] temp;
        }
    }

    return (totalPoint / numOfStudent);

}

    int SRS:: getStudentCount(){
        return studentCount;
    }
*/
