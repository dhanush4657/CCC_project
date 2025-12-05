#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h> // for _getch() password masking (Windows/CodeBlocks/VS etc.)

using namespace std;

// ------------ STRUCTS ------------

struct User
{
    string username;
    string password;
    string role; // admin, staff, student, parent, accountant
};

struct Student
{
    string regno;
    string name;
    int mark1;
    int mark2;
    int mark3;
};

// ------------ FUNCTION DECLARATIONS ------------

// password masking
string getPasswordMasked(const string &prompt);

// auth
bool authenticate(User &loggedInUser);

// menus
void adminMenu(User &loggedInUser);
void staffMenu(User &loggedInUser);
void studentMenu(User &loggedInUser);
void parentMenu(User &loggedInUser);
void accountantMenu(User &loggedInUser);

// student operations
void addStudent();
void viewAllStudents();
void updateStudent();
void deleteStudent();
void viewStudentByRegNo(const string &regno);
void searchStudent(); // ✅ NEW

// file helpers
vector<Student> loadStudentsFromFile();
void saveStudentsToFile(const vector<Student> &students);

// password change
void changePassword(User &loggedInUser);

// ------------ PASSWORD MASKING ------------

string getPasswordMasked(const string &prompt)
{
    cout << prompt;
    string password;
    char ch;

    while (true)
    {
        ch = _getch(); // if compiler error, try `ch = getch();`

        // Enter key
        if (ch == '\r')
        {
            cout << endl;
            break;
        }
        // Backspace
        else if (ch == '\b')
        {
            if (!password.empty())
            {
                password.pop_back();
                cout << "\b \b"; // remove last '*'
            }
        }
        // Arrow keys / function keys (skip extra code)
        else if (ch == 0 || ch == -32)
        {
            _getch();
            continue;
        }
        // Normal character
        else
        {
            password.push_back(ch);
            cout << '*';
        }
    }
    return password;
}

// ------------ MAIN ------------

int main()
{
    while (true)
    {
        cout << "=============================\n";
        cout << "  STUDENT RECORD SYSTEM\n";
        cout << "=============================\n";

        User loggedInUser;

        bool ok = authenticate(loggedInUser);
        if (!ok)
        {
            cout << "Login failed! Try again.\n\n";
            continue;
        }

        if (loggedInUser.role == "admin")
        {
            adminMenu(loggedInUser);
        }
        else if (loggedInUser.role == "staff")
        {
            staffMenu(loggedInUser);
        }
        else if (loggedInUser.role == "student")
        {
            studentMenu(loggedInUser);
        }
        else if (loggedInUser.role == "parent")
        {
            parentMenu(loggedInUser);
        }
        else if (loggedInUser.role == "accountant")
        {
            accountantMenu(loggedInUser);
        }
        else
        {
            cout << "Unknown role. Exiting.\n";
            break;
        }
    }

    return 0;
}

// ------------ AUTHENTICATION ------------

bool authenticate(User &loggedInUser)
{
    string inputUser, inputPass, inputRole;
    cout << "\n----- SIGN IN -----\n";
    cout << "Username: ";
    cin >> inputUser;

    inputPass = getPasswordMasked("Password: ");

    cout << "Role (admin/staff/student/parent/accountant): ";
    cin >> inputRole;

    ifstream fin("credentials.txt");
    if (!fin)
    {
        cout << "Error: credentials.txt not found!\n";
        return false;
    }

    string u, p, r;
    while (fin >> u >> p >> r)
    {
        if (u == inputUser && p == inputPass && r == inputRole)
        {
            loggedInUser.username = u;
            loggedInUser.password = p;
            loggedInUser.role = r;
            cout << "Login successful as " << r << "!\n\n";
            return true;
        }
    }

    return false;
}

// ------------ MENUS ------------

void adminMenu(User &loggedInUser)
{
    int choice;
    do
    {
        cout << "===== ADMIN MENU =====\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Search Student\n"; // ✅ NEW
        cout << "6. Change My Password\n";
        cout << "7. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            viewAllStudents();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            searchStudent(); // ✅ NEW
            break;
        case 6:
            changePassword(loggedInUser);
            break;
        case 7:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
        cout << endl;
    } while (choice != 7);
}

void staffMenu(User &loggedInUser)
{
    int choice;
    do
    {
        cout << "===== STAFF MENU =====\n";
        cout << "1. View All Students\n";
        cout << "2. Update Student (marks)\n";
        cout << "3. Change My Password\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewAllStudents();
            break;
        case 2:
            updateStudent();
            break;
        case 3:
            changePassword(loggedInUser);
            break;
        case 4:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
        cout << endl;
    } while (choice != 4);
}

void studentMenu(User &loggedInUser)
{
    int choice;
    do
    {
        cout << "===== STUDENT MENU =====\n";
        cout << "1. View My Record\n";
        cout << "2. Change My Password\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // assuming student username == regno in credentials.txt
            viewStudentByRegNo(loggedInUser.username);
            break;
        case 2:
            changePassword(loggedInUser);
            break;
        case 3:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
        cout << endl;
    } while (choice != 3);
}

void parentMenu(User &loggedInUser)
{
    int choice;
    do
    {
        cout << "===== PARENT MENU =====\n";
        cout << "1. View My Child Record (by regno)\n";
        cout << "2. Change My Password\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string reg;
            cout << "Enter your child's registration number: ";
            cin >> reg;
            viewStudentByRegNo(reg);
            break;
        }
        case 2:
            changePassword(loggedInUser);
            break;
        case 3:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
        cout << endl;
    } while (choice != 3);
}

void accountantMenu(User &loggedInUser)
{
    int choice;
    do
    {
        cout << "===== ACCOUNTANT MENU =====\n";
        cout << "1. View All Student Records\n";
        cout << "2. Change My Password\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewAllStudents();
            break;
        case 2:
            changePassword(loggedInUser);
            break;
        case 3:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
        cout << endl;
    } while (choice != 3);
}

// ------------ STUDENT FILE OPERATIONS ------------

vector<Student> loadStudentsFromFile()
{
    vector<Student> v;
    ifstream fin("students.txt");
    if (!fin)
    {
        // file may not exist initially
        return v;
    }
    Student s;
    while (fin >> s.regno >> s.name >> s.mark1 >> s.mark2 >> s.mark3)
    {
        v.push_back(s);
    }
    return v;
}

void saveStudentsToFile(const vector<Student> &students)
{
    ofstream fout("students.txt");
    if (!fout)
    {
        cout << "Error: cannot open students.txt for writing\n";
        return;
    }
    for (const auto &s : students)
    {
        fout << s.regno << " " << s.name << " "
             << s.mark1 << " " << s.mark2 << " " << s.mark3 << "\n";
    }
}

void addStudent()
{
    Student s;
    cout << "Enter regno: ";
    cin >> s.regno;
    cout << "Enter name: ";
    cin >> s.name;
    cout << "Enter mark1 mark2 mark3: ";
    cin >> s.mark1 >> s.mark2 >> s.mark3;

    // Append student to students.txt
    ofstream fout("students.txt", ios::app);
    if (!fout)
    {
        cout << "Error: cannot open students.txt\n";
        return;
    }
    fout << s.regno << " " << s.name << " "
         << s.mark1 << " " << s.mark2 << " " << s.mark3 << "\n";
    fout.close();

    // Create login credentials for the new student
    string defaultPassword = s.regno + string("@123"); // default pattern

    ofstream cred("credentials.txt", ios::app);
    if (!cred)
    {
        cout << "Error: cannot open credentials.txt\n";
        return;
    }
    cred << s.regno << " " << defaultPassword << " " << "student" << "\n";
    cred.close();

    cout << "\nStudent added successfully!\n";
    cout << "Login credentials created:\n";
    cout << "Username: " << s.regno << "\n";
    cout << "Password: " << defaultPassword << "\n";
}

void viewAllStudents()
{
    vector<Student> v = loadStudentsFromFile();
    if (v.empty())
    {
        cout << "No students found.\n";
        return;
    }
    cout << "RegNo\tName\tM1\tM2\tM3\n";
    for (const auto &s : v)
    {
        cout << s.regno << "\t" << s.name << "\t"
             << s.mark1 << "\t" << s.mark2 << "\t" << s.mark3 << "\n";
    }
}

void updateStudent()
{
    string targetReg;
    cout << "Enter regno of student to update: ";
    cin >> targetReg;

    vector<Student> v = loadStudentsFromFile();
    bool found = false;
    for (auto &s : v)
    {
        if (s.regno == targetReg)
        {
            found = true;
            cout << "Current details: " << s.regno << " " << s.name << " "
                 << s.mark1 << " " << s.mark2 << " " << s.mark3 << "\n";

            cout << "Enter new name: ";
            cin >> s.name;
            cout << "Enter new mark1 mark2 mark3: ";
            cin >> s.mark1 >> s.mark2 >> s.mark3;
            break;
        }
    }

    if (!found)
    {
        cout << "Student not found.\n";
        return;
    }

    saveStudentsToFile(v);
    cout << "Student updated successfully.\n";
}

void deleteStudent()
{
    string targetReg;
    cout << "Enter regno of student to delete: ";
    cin >> targetReg;

    vector<Student> v = loadStudentsFromFile();
    vector<Student> newList;
    bool found = false;

    for (const auto &s : v)
    {
        if (s.regno == targetReg)
        {
            found = true;
            continue; // skip this student
        }
        newList.push_back(s);
    }

    if (!found)
    {
        cout << "Student not found.\n";
        return;
    }

    saveStudentsToFile(newList);
    cout << "Student deleted successfully.\n";
}

void viewStudentByRegNo(const string &regno)
{
    vector<Student> v = loadStudentsFromFile();
    for (const auto &s : v)
    {
        if (s.regno == regno)
        {
            cout << "RegNo: " << s.regno << "\n";
            cout << "Name : " << s.name << "\n";
            cout << "Marks: " << s.mark1 << " " << s.mark2 << " " << s.mark3 << "\n";
            return;
        }
    }
    cout << "Record not found for regno: " << regno << "\n";
}

// ------------ SEARCH STUDENT (NEW) ------------

void searchStudent()
{
    cout << "\n----- SEARCH STUDENT -----\n";
    cout << "1. Search by Registration Number\n";
    cout << "2. Search by Name\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    vector<Student> v = loadStudentsFromFile();
    if (v.empty())
    {
        cout << "No students found.\n";
        return;
    }

    if (choice == 1)
    {
        string reg;
        cout << "Enter registration number: ";
        cin >> reg;

        bool found = false;
        for (const auto &s : v)
        {
            if (s.regno == reg)
            {
                cout << "\nStudent found:\n";
                cout << "RegNo: " << s.regno << "\n";
                cout << "Name : " << s.name << "\n";
                cout << "Marks: " << s.mark1 << " " << s.mark2 << " " << s.mark3 << "\n";
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "No student found with regno: " << reg << "\n";
        }
    }
    else if (choice == 2)
    {
        string name;
        cout << "Enter name: ";
        cin >> name; // single-word name (matches how it is stored)

        bool found = false;
        cout << "RegNo\tName\tM1\tM2\tM3\n";
        for (const auto &s : v)
        {
            if (s.name == name)
            {
                cout << s.regno << "\t" << s.name << "\t"
                     << s.mark1 << "\t" << s.mark2 << "\t" << s.mark3 << "\n";
                found = true;
            }
        }

        if (!found)
        {
            cout << "No student found with name: " << name << "\n";
        }
    }
    else
    {
        cout << "Invalid choice.\n";
    }
}

// ------------ CHANGE PASSWORD ------------

void changePassword(User &loggedInUser)
{
    cout << "\n----- CHANGE PASSWORD -----\n";

    string current = getPasswordMasked("Enter current password: ");

    if (current != loggedInUser.password)
    {
        cout << "Current password is incorrect.\n";
        return;
    }

    string newPass = getPasswordMasked("Enter new password: ");
    string confirm = getPasswordMasked("Confirm new password: ");

    if (newPass != confirm)
    {
        cout << "Passwords do not match.\n";
        return;
    }
    if (newPass.empty())
    {
        cout << "Password cannot be empty.\n";
        return;
    }

    // Load all users
    ifstream fin("credentials.txt");
    if (!fin)
    {
        cout << "Error: cannot open credentials.txt\n";
        return;
    }

    vector<User> users;
    string u, p, r;
    while (fin >> u >> p >> r)
    {
        users.push_back({u, p, r});
    }
    fin.close();

    // Find and update current user
    bool found = false;
    for (auto &user : users)
    {
        if (user.username == loggedInUser.username && user.role == loggedInUser.role)
        {
            user.password = newPass;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Error: current user not found in credentials file.\n";
        return;
    }

    // Write back to file
    ofstream fout("credentials.txt");
    if (!fout)
    {
        cout << "Error: cannot open credentials.txt for writing\n";
        return;
    }

    for (const auto &user : users)
    {
        fout << user.username << " " << user.password << " " << user.role << "\n";
    }
    fout.close();

    // Update in-memory user
    loggedInUser.password = newPass;

    cout << "Password changed successfully.\n";
}
