#include <iostream>
#include <vector>
#include <iomanip> // for setting precision

using namespace std;

// Function to calculate GPA for a semester
double calculateGPA(const vector<int>& credits, const vector<double>& grades) {
    double totalGradePoints = 0.0;
    int totalCredits = 0;

    for (size_t i = 0; i < credits.size(); ++i) {
        totalGradePoints += credits[i] * grades[i];
        totalCredits += credits[i];
    }

    return totalCredits > 0 ? totalGradePoints / totalCredits : 0.0;
}

// Function to calculate CGPA
double calculateCGPA(const vector<int>& totalCreditsPerSemester, const vector<double>& gpasPerSemester) {
    double totalGradePoints = 0.0;
    int totalCredits = 0;

    for (size_t i = 0; i < totalCreditsPerSemester.size(); ++i) {
        totalGradePoints += totalCreditsPerSemester[i] * gpasPerSemester[i];
        totalCredits += totalCreditsPerSemester[i];
    }

    return totalCredits > 0 ? totalGradePoints / totalCredits : 0.0;
}

int main() {
    int numSemesters;
    cout << "Enter the number of semesters: ";
    cin >> numSemesters;

    vector<int> totalCreditsPerSemester(numSemesters);
    vector<double> gpasPerSemester(numSemesters);

    for (int i = 0; i < numSemesters; ++i) {
        int numCourses;
        cout << "Enter the number of courses for semester " << i + 1 << ": ";
        cin >> numCourses;

        vector<int> credits(numCourses);
        vector<double> grades(numCourses);

        int totalCredits = 0;
        double totalGradePoints = 0.0;

        for (int j = 0; j < numCourses; ++j) {
            cout << "Enter the credit hours for course " << j + 1 << ": ";
            cin >> credits[j];
            cout << "Enter the grade points earned for course " << j + 1 << ": ";
            cin >> grades[j];

            totalCredits += credits[j];
            totalGradePoints += credits[j] * grades[j];
        }

        double gpa = calculateGPA(credits, grades);
        totalCreditsPerSemester[i] = totalCredits;
        gpasPerSemester[i] = gpa;

        cout << "GPA for semester " << i + 1 << ": " << fixed << setprecision(2) << gpa << endl;
    }

    double cgpa = calculateCGPA(totalCreditsPerSemester, gpasPerSemester);
    cout << "Overall CGPA: " << fixed << setprecision(2) << cgpa << endl;

    return 0;
}
