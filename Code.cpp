#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

// Structure to represent a department
struct Department
{
    int dept_id;
    string dept_name;
    string dept_head;
    string dept_email;
};

// Vector to store department records
vector<Department> departments;

// File to store data
const string DATA_FILE = "university_setting.txt";

// Function Declarations
void loadDepartments();
void storeDepartments();
void displayDepartments(const vector<Department> &data);
void createDepartment(int id, string name, string head, string email);
void updateDepartment(int id, string newName = "", string newHead = "", string newEmail = "");
void deleteDepartment(int id);
void retrieveDepartments();
void merge(vector<Department> &arr, int left, int mid, int right, string key);
void mergeSort(vector<Department> &arr, int left, int right, string key);
int binarySearch(const vector<Department> &arr, const string &target, string key);

// Function Definitions
void storeDepartments()
{
    ofstream file(DATA_FILE);
    for (const auto &dept : departments)
    {
        file << dept.dept_id << "," << dept.dept_name << ","
             << dept.dept_head << "," << dept.dept_email << endl;
    }
    file.close();
}

void loadDepartments()
{
    ifstream file(DATA_FILE);
    string line;

    while (getline(file, line))
    {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);

        int id = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string head = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string email = line.substr(pos3 + 1);

        departments.push_back({id, name, head, email});
    }
    file.close();
}

void createDepartment(int id, string name, string head, string email)
{
    Department dept = {id, name, head, email};
    departments.push_back(dept);
    storeDepartments();
}

void updateDepartment(int id, string newName, string newHead, string newEmail)
{
    for (auto &dept : departments)
    {
        if (dept.dept_id == id)
        {
            if (!newName.empty())
                dept.dept_name = newName;
            if (!newHead.empty())
                dept.dept_head = newHead;
            if (!newEmail.empty())
                dept.dept_email = newEmail;
            storeDepartments();
            return;
        }
    }
    cout << "Department ID not found!" << endl;
}

void deleteDepartment(int id)
{
    departments.erase(remove_if(departments.begin(), departments.end(),
                                [id](Department &dept)
                                { return dept.dept_id == id; }),
                      departments.end());
    storeDepartments();
}

void retrieveDepartments()
{
    displayDepartments(departments);
}

void merge(vector<Department> &arr, int left, int mid, int right, string key)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Department> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if ((key == "dept_id" && L[i].dept_id <= R[j].dept_id) ||
            (key == "dept_name" && L[i].dept_name <= R[j].dept_name) ||
            (key == "dept_email" && L[i].dept_email <= R[j].dept_email))
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(vector<Department> &arr, int left, int right, string key)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, key);
        mergeSort(arr, mid + 1, right, key);
        merge(arr, left, mid, right, key);
    }
}

int binarySearch(const vector<Department> &arr, const string &target, string key)
{
    int low = 0, high = arr.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if ((key == "dept_name" && arr[mid].dept_name == target) ||
            (key == "dept_email" && arr[mid].dept_email == target))
        {
            return mid;
        }
        else if ((key == "dept_name" && arr[mid].dept_name < target) ||
                 (key == "dept_email" && arr[mid].dept_email < target))
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

void displayDepartments(const vector<Department> &data)
{
    for (const auto &dept : data)
    {
        cout << "ID: " << dept.dept_id << ", Name: " << dept.dept_name
             << ", Head: " << dept.dept_head << ", Email: " << dept.dept_email << endl;
    }
}

int main()
{
    // Load existing data from file
    loadDepartments();

    int choice;
    do
    {
        cout << "\n=== University Department Management System ===\n";
        cout << "1. Add a Department\n";
        cout << "2. Update a Department\n";
        cout << "3. Delete a Department\n";
        cout << "4. Display All Departments\n";
        cout << "5. Search for a Department\n";
        cout << "6. Sort Departments\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int id;
            string name, head, email;
            cout << "Enter Department ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Department Name: ";
            getline(cin, name);
            cout << "Enter Department Head: ";
            getline(cin, head);
            cout << "Enter Department Email: ";
            getline(cin, email);
            createDepartment(id, name, head, email);
            break;
        }
        case 2:
        {
            int id;
            string newName, newHead, newEmail;
            cout << "Enter Department ID to Update: ";
            cin >> id;
            cin.ignore();
            cout << "Enter New Name (leave blank to skip): ";
            getline(cin, newName);
            cout << "Enter New Head (leave blank to skip): ";
            getline(cin, newHead);
            cout << "Enter New Email (leave blank to skip): ";
            getline(cin, newEmail);
            updateDepartment(id, newName, newHead, newEmail);
            break;
        }
        case 3:
        {
            int id;
            cout << "Enter Department ID to Delete: ";
            cin >> id;
            deleteDepartment(id);
            break;
        }
        case 4:
            retrieveDepartments();
            break;
        case 5:
        {
            string key, target;
            cout << "Search by (dept_name/dept_email): ";
            cin >> key;
            cin.ignore();
            cout << "Enter Search Value: ";
            getline(cin, target);

            mergeSort(departments, 0, departments.size() - 1, key);
            int index = binarySearch(departments, target, key);
            if (index != -1)
            {
                cout << "\nSearch Result:\n";
                displayDepartments({departments[index]});
            }
            else
            {
                cout << "\nDepartment not found!" << endl;
            }
            break;
        }
        case 6:
        {
            string key;
            cout << "Sort by (dept_id/dept_name/dept_email): ";
            cin >> key;
            mergeSort(departments, 0, departments.size() - 1, key);
            cout << "\nDepartments After Sorting:\n";
            retrieveDepartments();
            break;
        }
        case 0:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}