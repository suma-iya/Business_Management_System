#include <bits/stdc++.h>

using namespace std;

// Worker class
class Worker{
private:
    string name;
    string shift;
    int worker_id;

public:
    string type;
    double salary;
    Worker(string type, string name, string shift, int worker_id, double salary) {
        this->type = type;
        this->name = name;
        this->shift = shift;
        this->worker_id = worker_id;
        this->salary = salary;
    }

    virtual void displayDetails() {
        cout << "Name: " << name << endl;
        cout << "Shift: " << shift << endl;
        cout << "Worker ID: " << worker_id << endl;
        cout << "Salary: " << salary << "tk" << endl;
    }

    string tag(){
        return type;
    }

    string wname(){
        return name;
    }

    string wshift(){
        return shift;
    }

    int wworker_id(){
        return worker_id;
    }

    double wsalary(){
        return salary;
    }

    // To Calculate Total Salary
    friend Worker operator+(double total, Worker &ob1){
        total = total + ob1.salary;
    }
};

// Supervisor class inheriting from Worker
class Supervisor : public Worker {

    public:
        double sbonus;
        Supervisor(string type, string name, string shift, int worker_id, double salary)
            : Worker(type, name, shift, worker_id, salary) {
            sbonus = 200;
        }

        void displayDetails() {
            cout << "Supervisor Details" << endl;
            Worker::displayDetails();
            cout << "Bonus: " << sbonus << "tk" << endl;
        }

        double sup_bonus(){
            return sbonus;
        }
};

// Manager class inheriting from Worker
class Manager : public Worker {
   
    public:
        double mbonus;
        Manager(string type,string name, string shift, int worker_id, double salary)
            : Worker(type, name, shift, worker_id, salary) {
            mbonus = 500;
        }

        void displayDetails() {
            cout << "Manager Details" << endl;
            Worker::displayDetails();
            cout << "Bonus: " << mbonus << "tk" << endl;
        }
        double man_bonus(){
            return mbonus;
        }
};

void show_details(const vector<Worker*>& All_Workers){
    ofstream outFile("output.txt");
    if (!outFile)
    {
        cerr << "Error creating output file." << endl;
    }else{
        for (const auto& worker : All_Workers)
        {
            outFile << worker->tag() << ": " << endl;
            outFile << "Name: " << worker->wname() << endl;
            outFile << "Shift: " << worker->wshift() << endl;  
            outFile << "Worker-id: " << worker->wworker_id() << endl;
            outFile << "Salary: " << worker->wsalary() << "tk" << endl; 
            if (typeid(*worker) == typeid(Manager))
            {
                Manager* manager = dynamic_cast<Manager*>(worker);
                outFile << "Bonus: " << manager->man_bonus() << endl;
            }
            if (typeid(*worker) == typeid(Supervisor)){
                Supervisor* supervisor = dynamic_cast<Supervisor*>(worker);
                outFile << "Bonus: " << supervisor->sup_bonus() << endl;
            }
            outFile << endl;
        }
    } 
    double total_salary = 0;

    for (const auto& worker : All_Workers)
    {
        total_salary = total_salary + worker->salary;
    }

    outFile << "Total Salary: " << total_salary << endl;
}


int main() {

    int button;
    vector<Worker*> All_Workers;
    do{
        cout << "1. Worker" << endl;
        cout << "2. Supervisor" << endl;
        cout << "3. Manager" << endl;
        cout << "4. Exit" << endl;
        cin >> button;
        if(button == 1 || button ==2 || button == 3){

            string tag, name, shift;
            int worker_id;
            double salary, bonus;

            cout << "Enter tag: ";
            cin >> tag;

            cout << "Enter name: ";
            cin >> name;

            cout << "Enter shift: ";
            cin >> shift;

            cout << "Worker id: ";
            cin >> worker_id;
            
            cout << "Salary: ";
            cin >> salary;

            if(button == 1){
                All_Workers.push_back(new Worker(tag, name, shift, worker_id, salary));
            }else if(button == 2){
                All_Workers.push_back(new Supervisor(tag, name, shift, worker_id, salary));
            }else if(button ==3){
                All_Workers.push_back(new Manager(tag, name, shift, worker_id, salary));
            }else if(button!=4){
                cout << "Invalid Option" << endl;
            }
        }
    }while(button!=4);
  
    show_details(All_Workers);
    for (const auto& worker : All_Workers)
    {
        delete worker;
    }
}
