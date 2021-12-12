// Bilkent.cpp: Konsol uygulaması için giriş noktasını tanımlar.
//

#include <iostream>
#include "SRS.h"
#include "SimpleStudent.h"

using namespace std;
void displayAllStudents(SRS S) {
	Student *allStudents;
	int studentNo = S.getStudents(allStudents);
	cout << "No of students: " << studentNo << endl;
	for (int i = 0; i < studentNo; i++) {
		cout << allStudents[i].getStudentName() << " (";
		cout << allStudents[i].getStudentId() << ")" << endl;
	}
	//if (allStudents != NULL)    //burdan hata alıyorum*********************************************
		//delete[] allStudents;
}
void displayStatistics(SRS S) {
	Student *allStudents;

	int studentNo = S.getStudents(allStudents);
	int noUnsatisfactory = 0;
	int noProbation = 0;
	int noSatisfactory = 0;
	int noHonor = 0;
	int noHighHonor = 0;
	for (int i = 0; i < studentNo; i++) {
		double gpa = allStudents[i].calculateStudentCurrentGPA();
		if (gpa < 1.80)
			noUnsatisfactory++;
		else if (gpa < 2.00)
			noProbation++;

		else {
			noSatisfactory++;
			if (gpa >= 3.00 && gpa < 3.50)
				noHonor++;
			if (gpa >= 3.50)
				noHighHonor++;
		}
	}
	cout << "Number of high honor: " << noHighHonor << endl;
	cout << "Number of honor: " << noHonor << endl;
	cout << "Number of satisfactory: " << noSatisfactory << endl;
	cout << "Number of probation: " << noProbation << endl;
	cout << "Number of unsatisfactory: " << noUnsatisfactory << endl;
	//if (allStudents != NULL)   //burdan hata alıyorum**************************************
		//delete[] allStudents;
}
int main() {
	SRS S;

	S.addStudent(1234, "Cigdem Gunduz");

	S.addStudent(5678, "Ercument Cicek");

	S.addStudent(7890, "Cigdem Gunduz");


	S.addStudent(7890, "Serhan Yilmaz");

	for (int i = 0; i < 1000; i++) {
		S.addStudent(i, "Gozde Gunesli");
		S.addCourse(i, 201, "B", 4);
		S.addCourse(i, 101, "C", 3);
		S.addCourse(i, 102, "A+", 4);
		S.addCourse(i, 103, "F", 3);
		S.addCourse(i, 204, "D", 2);
		S.addCourse(i, 503, "C", 3);
	}

	S.addCourse(1234, 201, "B", 4);
	S.addCourse(5678, 202, "B", 1);
	S.addCourse(5678, 201, "C-", 4);
	S.addCourse(7890, 410, "D+", 4);
	S.addCourse(7890, 201, "W", 4);
	S.addStudent(3782, "Onur Karakaslar");
	S.addCourse(3782, 201, "A", 2);
	S.addStudent(3782, "Cigdem Demir");
	S.addCourse(3782, 201, "F", 1);
	S.removeCourse(5678, 202);
	S.removeCourse(5678, 210);
	for (int i = 1500; i > 0; i--)
		S.removeStudent(i);
	displayAllStudents(S);

	displayStatistics(S);
	cout << "Course GPA for 201 is " << S.calculateCourseGPA(201) << endl;
	return 0;
}
