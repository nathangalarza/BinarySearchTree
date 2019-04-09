#include <iostream>

using namespace std;
#include "BinarySearchTree.h"
#include "StudentTestScore.h"
#include <string>
int Menu();

void visit(StudentTestScores &entry);
//void createUserWithData(BinarySearchTree<StudentTestScores> &tree);
int main() {




	BinarySearchTree<StudentTestScores>* students = new BinarySearchTree<StudentTestScores>();// = new BinarySearchTree<StudentTestScores>();
	StudentTestScores newStudent[10];
	string Name;
	string Name2;
	int index;
	double Score;
	int option = 0;
	int ii = 0;
	int option2;
	int MAX;
	StudentTestScores newUser;
	StudentTestScores* Modify;
	do
	{
		option = Menu();
		switch (option)
		{
		case 1:
			//createUserWithData(students);//StudentTestScores newStudent();
			//string studentname;
		//	double testscore;
			//int index;
			cout << "Cuantos estudiantes deseas añadir \n";
			cin >> MAX;
			for (int j = 0; j < MAX; j++) {
				cout << "Escriba el nombre del estudiante: ";
				cin >> Name;
				cout << "Escriba el numero de examenes del estudiante: " << endl;
				cin >> index;
				newStudent[j].createTestScoresArray(index);
				newStudent[j].setStudentName(Name);

				for (int i = 0; i < index; i++)
				{
					cout << "Escriba Score del examen: " << "no." << i + 1 << endl << "enter:";
					cin >> Score;
					newStudent[j].setTestScore(Score, i);
				}

				//tree.add(newUser);

				//students->setRootData(newStudent[1]);
				//students->setRootData(newStudent[j]);
				students->add(newStudent[j]);

				cout << "student added!";
				ii++;

			}
			break;
		case 2:

			cout << "Entre el nombre del estudiante que desea remover: ";
			cin >> Name;

			newUser.setStudentName(Name);
			students->remove(newUser);
			cout << "removido";

			break;
		case 3:


			cout << "Seleccione el Record: " << endl;
			cin >> Name;
			newUser.setStudentName(Name);
			if (students->isEmpty()) {
				cout << "no hay records del estudiante \n";


			}
			else cout << students->getEntry(newUser);

			break;
		case 4:

			students->inorderTraverse(visit);
			cout << "cual deseas modificar?";
			cin >> Name;
			newUser.setStudentName(Name);
			//	newStudent->getNumTestScores();
			cout << "que deseas cambiar? \n(1)Nombre\n(2)Scores\n";
			cin >> option2;
			if (option2 == 1) {

				cout << "Enter new Name:";
				cin >> Name;
				newUser.setStudentName(Name);
				cout << "\nmodified";
			}
			else if (option2 == 2) {
				students->remove(newUser);
				for (int i = 0; i < newUser.getNumTestScores(); i++) {
					cout << "enter new Scores for no." << i + 1 << endl;
					cin >> Score;
					newUser.createTestScoresArray(newUser.getNumTestScores());
					newUser.setTestScore(Score, newUser.getNumTestScores());
					cout << "\nmodified";
				}

			}
			else cout << "wrong";

			break;

		}
	} while (option != 5);



	//const StudentTestScores tree(newStudent());
//	newStudent() = tree;
	//BinaryNode<StudentTestScores> subtree();

	//BinarySearchTree<StudentTestScores>;


	//students->add(tree());
		//	students(newStudent);
		//	BinarySearchTree<StudentTestScores>*students1 = new BinarySearchTree<StudentTestScores>(newUser);
			//students1->add(Name, index, NULL);
			//students->add(students1);

			/*double Score;
			double average;
			int index;
			int option = 0;
			int ii;
			do
			{
				option = Menu();
				switch (option)
				{
				case 1:
					createUserWithData(students);

					break;
				case 2:

					break;
				case 3:

					break;
				case 4:
					break;

				}
			} while (option != 4);


		*/











}

//void createUserWithData(BinarySearchTree<StudentTestScores> &tree) {
//
//
//	string Name;
//	int index;
//	double Score;
//	StudentTestScores newStudent();
//	cout << "enter students name:";
//	cin >> Name;
//
//	cout << "enter students exams:";
//	cin >> index;
//	StudentTestScores newUser(Name, index,NULL);
//	for (int i = 0; i < index; i++) {
//
//		double input;
//		cout << "enter student score for exam no." << i << endl; cout << "enter: ";
//		cin >> input;
//		Score = input;
//		newUser.setTestScore(input, index);
//
//	}
//
//	//tree.add(newUser);
//	//	cout << newUser.getNumTestScores();
//
//}
int Menu()
{
	int option;
	cout << "Welcome to Talaveras Test Scores during fall trimester" << endl;
	cout << "******************************************************" << endl;
	cout << "(1)Add Students***************************************" << endl;
	cout << "(2)Remove a student***********************************" << endl;
	cout << "(3)Display Student************************************" << endl;
	cout << "(4)Modify Student*************************************" << endl;
	cout << "(5)Exit***********************************************" << endl;
	cout << "Enter Choice:";

	cin >> option;
	return option;
}

void printTree(BinarySearchTree<StudentTestScores>& tree)
{
	if (tree.isEmpty()) {

		cout << "empty";

	}
	tree.inorderTraverse(visit);

}
void visit(StudentTestScores &entry) {


	cout << entry << endl;


}