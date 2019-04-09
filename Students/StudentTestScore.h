#pragma once
#include <string>
using namespace std;

const double DEFAULT_SCORE = 0.0;

class StudentTestScores
{
private:

	string studentName;
	double *testScores;
	int numTestScores;


public:

	void createTestScoresArray(int size)
	{
		numTestScores = size;
		testScores = new double[size];
		for (int i = 0; i < size; i++)
			testScores[i] = DEFAULT_SCORE;
	}

	StudentTestScores()
	{
		studentName = "";
		testScores = nullptr;
		numTestScores = 0;
	}

	StudentTestScores(string name, int numScores)
	{
		studentName = name;
		createTestScoresArray(numScores);
	}

	StudentTestScores(const StudentTestScores &obj)
	{

		studentName = obj.studentName;
		numTestScores = obj.numTestScores;
		testScores = new double[numTestScores];
		for (int i = 0; i < numTestScores; i++)
			testScores[i] = obj.testScores[i];
	}

	~StudentTestScores()
	{
		delete[] testScores;
	}

	void setTestScore(double score, int index)
	{
		testScores[index] = score;
	}

	void setStudentName(string name)
	{
		studentName = name;
	}

	string getStudentName() const
	{
		return studentName;
	}

	int getNumTestScores()
	{
		return numTestScores;
	}

	double getTestScore(int index) const
	{
		return testScores[index];
	}

	void operator=(const StudentTestScores & right)
	{
		delete[] testScores;
		studentName = right.studentName;
		numTestScores = right.numTestScores;
		testScores = new double[numTestScores];
		for (int i = 0; i < numTestScores; i++)
			testScores[i] = right.testScores[i];

	}

	bool operator > (const StudentTestScores& aStudentTestScores) const
	{
		return (this->studentName > aStudentTestScores.studentName);

	}

	bool operator == (const StudentTestScores& aStudentTestScores) const
	{
		return (this->studentName == aStudentTestScores.studentName);
	}

	friend ostream & operator <<(ostream & out, const StudentTestScores & aStudentTestScores)
	{
		char studentgrade = 'Z';
		int averagegrade = 0;
		out << "\n**************************";
		out << "\n  Student Report";
		out << "\n**************************";
		out << "\nStudent Name: " << aStudentTestScores.studentName;

		for (int i = 0; i < aStudentTestScores.numTestScores; i++)
		{
			out << "\n  Score #" << i + 1 << ": " << aStudentTestScores.testScores[i] << "%";
		}

		for (int i = 0; i < aStudentTestScores.numTestScores; i++)
		{
			averagegrade = averagegrade + aStudentTestScores.testScores[i];
		}

		averagegrade = averagegrade / aStudentTestScores.numTestScores;

		out << "\n Average grade of student is: " << averagegrade;

		if (averagegrade >= 90 && averagegrade <= 100)
		{
			studentgrade = 'A';
		}
		else if (averagegrade >= 80 && averagegrade <= 89)
		{
			studentgrade = 'B';
		}
		else if (averagegrade >= 70 && averagegrade <= 79)
		{
			studentgrade = 'C';
		}
		else if (averagegrade >= 60 && averagegrade <= 69)
		{
			studentgrade = 'D';
		}
		else
		{
			studentgrade = 'F';
		}

		out << "\n Student grade is :" << studentgrade;
		return out;
	}

};