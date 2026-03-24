#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct Course {
    string name;
    string grade;
    int credits;
    float points;
};

float getPoints(string g) {
    for (int i = 0; i < g.length(); i++) g[i] = toupper(g[i]);

    if (g == "A+" || g == "A") return 4.0;
    if (g == "A-") return 3.7;
    if (g == "B+") return 3.3;
    if (g == "B")  return 3.0;
    if (g == "B-") return 2.7;
    if (g == "C+") return 2.3;
    if (g == "C")  return 2.0;
    if (g == "C-") return 1.7;
    if (g == "D")  return 1.0;
    if (g == "F")  return 0.0;
    return -1.0;
}

int main() {
    string studentName;
    int n;
    Course list[20];
    float semWeight = 0;
    int semCredits = 0;
    float prevCGPA = 0;
    int prevCredits = 0;
    char hasHistory;

    cout << "***** Advanced GPA/CGPA Calculator *****" << endl;
    cout << "Student Name: ";
    getline(cin, studentName);

    cout << "Do you have a previous CGPA to include? (y/n): ";
    cin >> hasHistory;

    if (tolower(hasHistory) == 'y') {
        while (true) {
            cout << "Enter previous CGPA: ";
            if (cin >> prevCGPA && prevCGPA >= 0 && prevCGPA <= 4.0) break;
            cout << "Invalid CGPA. Enter 0.0 - 4.0." << endl;
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        while (true) {
            cout << "Enter total credits earned so far: ";
            if (cin >> prevCredits && prevCredits >= 0) break;
            cout << "Invalid credits." << endl;
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true) {
        cout << "\nHow many courses this semester? (1-20): ";
        if (cin >> n && n > 0 && n <= 20) break;
        cout << "Error: Enter 1-20." << endl;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    for (int i = 0; i < n; i++) {
        cout << "\nCourse " << i + 1 << " details:" << endl;
        cout << "Name: ";
        cin.ignore();
        getline(cin, list[i].name);

        while (true) {
            cout << "Grade: ";
            cin >> list[i].grade;
            list[i].points = getPoints(list[i].grade);
            if (list[i].points != -1.0) break;
            cout << "Invalid grade!" << endl;
        }

        while (true) {
            cout << "Credits: ";
            if (cin >> list[i].credits && list[i].credits > 0) break;
            cout << "Invalid credits." << endl;
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        semWeight += (list[i].points * list[i].credits);
        semCredits += list[i].credits;
    }

    float semGPA = semWeight / semCredits;
    float totalPoints = semWeight + (prevCGPA * prevCredits);
    int totalCredits = semCredits + prevCredits;
    float finalCGPA = totalPoints / totalCredits;

    cout << fixed << setprecision(2);
    cout << "\n***** RESULTS FOR " << studentName << " *****" << endl;
    cout << left << setw(20) << "Course" << setw(10) << "Grade" << "Credits" << endl;
    for (int i = 0; i < n; i++) {
        cout << left << setw(20) << list[i].name << setw(10) << list[i].grade << list[i].credits << endl;
    }
    cout << "****************************************" << endl;
    cout << "Semester GPA:  " << semGPA << endl;
    cout << "Total Credits: " << totalCredits << endl;
    cout << "Overall CGPA:  " << finalCGPA << endl;

    return 0;
}
