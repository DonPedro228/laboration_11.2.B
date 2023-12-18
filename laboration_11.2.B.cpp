#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <fstream>

using namespace std;

enum Specialnost { Computer_Science, Informatics, Mathematics_And_Economics, Physics_And_Informatics, Labor_Education };
string specStr[] = { "Computer_Science", "Informatics", "Mathematics_And_Economics", "Physics_And_Informatics", "Labor_Education"};

union Grade {
    double programmingGrade;
    double numericalMethodsGrade;
    double pedagogyGrade;
};

struct Student {
    int studentNumber;
    char prizv[60];
    int course;
    Specialnost spec;
    double physicsGrade;
    double mathGrade;
    Grade thirdGrade;
};

void Create(string filename);
void Print(string filename);
int Count5(string filename);
int Count4(string filename);
int Count3(string filename);
void Students_With_Grade_5_In_Physics_And_Math(string filename);

int main() {
    int N;
    string filename;
    cout << "Input name of file: ";
    cin >> filename;
    int grade3Count;
    int grade4Count;
    int grade5Count;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Select an action: " << endl << endl;
        cout << " [1] - entering data from the keyboard " << endl;
        cout << " [2] - cout data in display" << endl;
        cout << " [3] - count grade of 3 from math" << endl;
        cout << " [4] - count grade of 4 from math" << endl;
        cout << " [5] - count grade of 5 from math" << endl;
        cout << " [6] - print students who got 5 from physics and math" << endl;
        cout << " [0] - Exit" << endl << endl;
        cout << "Input value: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            Create(filename);
            break;
        case 2:
            Print(filename);
            break;
        case 3:
            grade3Count = Count3(filename);
            cout << " Count grade of 3 from math: " << grade3Count << endl;
            break;
        case 4:
            grade4Count = Count4(filename);
            cout << " Count grade of 4 from math: " << grade4Count << endl;
            break;
        case 5:
            grade5Count = Count5(filename);
            cout << " Count grade of 5 from math: " << grade5Count << endl;
            break;
        case 6:
            cout << " Students who got 5 from physics and math: " << endl;
            Students_With_Grade_5_In_Physics_And_Math(filename);
            break;
        case 0:
            break;
        default:
            cout << "You choose fake value! " << endl;
        }
    } while (menuItem != 0);

    return 0;
}

void Create(string filename) {
    ofstream f(filename, ios::binary);
    Student s;
    char ch;
    int spec, i = 0;



    do {
        i++;
        cin.get();

        cout << "Student #" << i << ":" << endl;
        cout << "LastName: "; cin.getline(s.prizv, 60);
        cout << "Course: "; cin >> s.course;

        

        cout << "Specialnost (0 - Computer_Science, 1 - Informatics, 2 - Mathematics_And_Economics, 3 - Physics_And_Informatics, 4 - Labor_Education): ";
        cin >> spec;
        s.spec = (Specialnost)spec;

        cout << "Math_Grade: "; cin >> s.mathGrade;
        cout << "Phisics_Grade: "; cin >> s.physicsGrade;


        switch (s.spec) {
        case Computer_Science:
            cout << "Programming_Grade: ";
            cin >> s.thirdGrade.programmingGrade;
            break;
        case Informatics:
            cout << "Numerical_Methods Grade: ";
            cin >> s.thirdGrade.numericalMethodsGrade;
            break;
        case Mathematics_And_Economics:
        case Physics_And_Informatics:
        case Labor_Education:
            cout << "Pedagogy_Grade: ";
            cin >> s.thirdGrade.pedagogyGrade;
            break;
        }
        cin.get();

        f.write((char*)&s, sizeof(Student));

        cout << "Continue? (Y/N): "; cin >> ch; cout << endl;

    } while (ch == 'Y' || ch == 'y');
    f.close();
    cout << endl;
}

void Print(string filename) {
    ifstream f(filename, ios::binary);
    Student s;
    int i = 0;


    cout << "=========================================================================================================================="
        << endl;
    cout << "| # | Last Name | Course | Specialnist        | Physics | Math | Programming | Num. Meth.  | Pedagogy |"
        << endl;

    while (f.read((char*)&s, sizeof(Student))) {
        i++;
        cout << "| " << i << " | " << setw(10) << left << s.prizv
            << " | " << setw(4) << left << s.course
            << " | " << setw(13) << left << specStr[s.spec];
        cout << " | " << setw(10) << left << s.mathGrade
            << " | " << setw(6) << left << s.physicsGrade;

        switch (s.spec) {
        case Computer_Science:
            cout << " | " << setw(13) << left << s.thirdGrade.programmingGrade <<
                " | " << setw(10) << left << "" <<
                " | " << setw(15) << left << "" << " |";
            break;
        case Informatics:
            cout << " | " << setw(13) << left << "" <<
                " | " << setw(10) << left << "" <<
                " | " << setw(15) << left << s.thirdGrade.numericalMethodsGrade << " |";
            break;
        default:
            cout << " | " << setw(13) << left << "" <<
                " | " << setw(10) << left << s.thirdGrade.pedagogyGrade <<
                " | " << setw(15) << left << "" << " |";
            break;
        }
        cout << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    }
    cout << "==============================================================================================================" << endl;

    f.close();
        
}

int Count5(string filename) {
    ifstream f(filename, ios_base::binary);
    Student s;
    int totalStudents = 0, grade5Count = 0;
    while (f.read((char*)&s, sizeof(Student))) {
        totalStudents++;
        if (s.mathGrade == 5) {
            grade5Count++;
        }
    }
    f.close();

    if (totalStudents == 0)
        return 0.0;

    return grade5Count;
}

int Count4(string filename) {
    ifstream f(filename, ios_base::binary);
    Student s;
    int totalStudents2 = 0, grade4Count = 0;
    while (f.read((char*)&s, sizeof(Student))) {
        totalStudents2++;
        if (s.mathGrade == 4) {
            grade4Count++;
        }
    }
    f.close();
    if (totalStudents2 == 0)
        return 0.0;

    return grade4Count;
}

int Count3(string filename) {
    ifstream f(filename, ios_base::binary);
    Student s;
    int totalStudents3 = 0, grade3Count = 0;
    while (f.read((char*)&s, sizeof(Student))) {
        totalStudents3++;
        if (s.mathGrade == 3) {
            grade3Count++;
        }
    }
    f.close();
    if (totalStudents3 == 0)
        return 0.0;

    return grade3Count;
}

void Students_With_Grade_5_In_Physics_And_Math(string filename) {
    ifstream f(filename, ios_base::binary);
    Student s;
    cout << "Name of students who got 5 from physics and math: " << endl;
    while (f.read((char*)&s, sizeof(Student))) {
        if (s.physicsGrade == 5 && s.mathGrade == 5) {
            cout << s.prizv << endl;
        }
    }
    f.close();
}

