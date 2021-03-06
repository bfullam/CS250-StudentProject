#include "Student.h"

//Default constructor   
Student::Student()
{
	studentID = 0;
	numberOfCourses = 0;
	tuitionWasPaid = false;
}

//setStudentInfo
void Student::setStudentInfo(const string& firstName, const string& lastName, int id, bool tuitionPaid, vector <Course> courses)
{
	setName(firstName, lastName);
	studentID = id;
	numberOfCourses = static_cast<int>(courses.size());
	tuitionWasPaid = tuitionPaid;
	coursesEnrolled = courses;

}

//getID
int Student::getID() const
{
	return studentID;
}

//getNumberOfCourses
int Student::getNumberOfCourses() const
{
	return numberOfCourses;
}

//getCreditsEnrolled
int Student::getCreditsEnrolled() const
{
	int credits = 0;
	for (int i = 0; i < numberOfCourses; i++)
	{
		credits += coursesEnrolled[i].getCourseCredits();
	}
	return credits;
}

//isTuitionPaid
bool Student::isTuitionPaid() const
{
	return tuitionWasPaid;
}

//isEnrolledInCourse
bool Student::isEnrolledInCourse(const string& courseNo) const
{
	if (numberOfCourses == 0)
		return false;
	else
	{
		for (int i = 0; i < numberOfCourses; i++)
		{
			if (coursesEnrolled[i].getCourseNumber() == courseNo)
				return true;
		}
	}
	return false;
}

//getGpa
double Student::getGpa() const
{
	double qualityPoints = 0;
	for (int i = 0; i < numberOfCourses; i++)
	{
		switch (coursesEnrolled[i].getCourseGrade())
		{
		case ('A') :
			qualityPoints += (4 * coursesEnrolled[i].getCourseCredits());
			break;
		case ('B') :
			qualityPoints += (3 * coursesEnrolled[i].getCourseCredits());
			break;
		case ('C') :
			qualityPoints += (2 * coursesEnrolled[i].getCourseCredits());
			break;
		case ('D') :
			qualityPoints += (1 * coursesEnrolled[i].getCourseCredits());
			break;
		case ('F') :
			qualityPoints += 0;
			break;
		}
	}
	return qualityPoints / getCreditsEnrolled();
}

//billingAmount
double Student::billingAmount(double tuitionRate)const
{
	return getCreditsEnrolled() * tuitionRate;
}

//printStudentInfo
void Student::printStudentInfo() const
{
	cout << studentID << " - ";
	printName();
}

//printStudentInfo
void Student::printStudentInfo(double tuitionRate) const
{
	cout << "Student Name: "; printName(); cout << endl;

	cout << "Student ID: " << studentID << endl
		<< "Number of courses enrolled: " << numberOfCourses << endl;

	cout << "\nCourse No  Course Name  Credits  Grade" << endl;
	
	for (int i = 0; i < numberOfCourses; i++)
	{
		coursesEnrolled[i].printCourseInfo(tuitionWasPaid);
	}

	cout << "Total number of credit hours: " << getCreditsEnrolled() << endl;

	if (tuitionWasPaid)
		cout << "Current Term GPA: " << getGpa() << endl;
	else
	{
		cout << "*** Grades are being held for not paying the tuition. ***" << endl
			<< "Amount Due: " << billingAmount(tuitionRate) << endl;
	}

	cout << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n" << endl;
}

//getCoursesEnrolled
vector <Course> Student::getCoursesEnrolled() const
{
	return coursesEnrolled;
}

void Student::printStudentInfoToFile(ofstream& out, double tuitionRate) const
{
    	string fName, lName;
    	getName(fName, lName);
    
    	out << "Student Name: ";
    	out << lName << ", " << fName << endl;
    	out << endl;
    
    	out << "Student ID: " << studentID << endl
    	<< "Number of courses enrolled: " << numberOfCourses << endl;
    
    	out << "\nCourse No  Course Name  Credits  Grade" << endl;
    
    	for (int i = 0; i < numberOfCourses; i++)
    	{
        	out << left << setw(8) << coursesEnrolled[i].getCourseNumber() << "   " << 	setw(15) << coursesEnrolled[i].getCourseName();
        	out.unsetf(ios::left);
        	out << setw(3) << coursesEnrolled[i].getCourseCredits() << "   ";
        	if (isTuitionPaid())
            	out << setw(4) << coursesEnrolled[i].getCourseGrade() << endl;
        	else 
				out << setw(4) << "***" << endl;
    	}
    
    	out << "Total number of credit hours: " << getCreditsEnrolled() << endl;
    
    	if (tuitionWasPaid)
        out << "Current Term GPA: " << fixed << setprecision(2) << getGpa() << endl;
    	else
    	{
        	out << "*** Grades are being held for not paying the tuition. ***" << endl
        	<< "Amount Due: " << billingAmount(tuitionRate) << endl;
    	}
    
    	out << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n" << endl;
}

//Destructor
Student::~Student(){}