#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
using namespace std;

// ---------------------- Base Class ----------------------
class Expense {
protected:
    float amount;
    string date;
    string description;

public:
    Expense(float amt, string dt, string desc)
        : amount(amt), date(dt), description(desc) {}

    virtual ~Expense() {}

    float getAmount() const { return amount; }

    virtual string getDetails() const {
        return "Amount: " + to_string(amount) + " | Date: " + date + " | Description: " + description;
    }

    // Serialize data for saving
    virtual string serialize() const {
        return to_string(amount) + "," + date + "," + description;
    }
};

// ---------------------- Derived Class: FoodExpense ----------------------
class FoodExpense : public Expense {
    string foodType;

public:
    FoodExpense(float amt, string dt, string desc, string fType)
        : Expense(amt, dt, desc), foodType(fType) {}

    string getDetails() const override {
        return "[Food] " + Expense::getDetails() + " | Food Type: " + foodType;
    }

    string serialize() const override {
        return "Food," + Expense::serialize() + "," + foodType;
    }
};

// ---------------------- Derived Class: TravelExpense ----------------------
class TravelExpense : public Expense {
    string destination;

public:
    TravelExpense(float amt, string dt, string desc, string dest)
        : Expense(amt, dt, desc), destination(dest) {}

    string getDetails() const override {
        return "[Travel] " + Expense::getDetails() + " | Destination: " + destination;
    }

    string serialize() const override {
        return "Travel," + Expense::serialize() + "," + destination;
    }
};

// ---------------------- ExpenseManager ----------------------
class ExpenseManager {
    vector<shared_ptr<Expense>> expenses;

public:
    void addExpense(shared_ptr<Expense> expense) {
        expenses.push_back(expense);
    }

    float getTotalExpenses() const {
        float total = 0;
        for (const auto &e : expenses)
            total += e->getAmount();
        return total;
    }

    void listAllExpenses() const {
        cout << "\n--- All Expenses ---\n";
        for (const auto &e : expenses) {
            cout << e->getDetails() << endl;
        }
    }

    void saveData(const string &filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error opening file for writing!" << endl;
            return;
        }
        for (const auto &e : expenses)
            outFile << e->serialize() << endl;
        outFile.close();
    }

    void loadData(const string &filename) {
        ifstream inFile(filename);
        if (!inFile) return;

        expenses.clear();
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string type, amtStr, date, desc, extra;
            getline(ss, type, ',');
            getline(ss, amtStr, ',');
            getline(ss, date, ',');
            getline(ss, desc, ',');
            getline(ss, extra, ',');

            float amt = stof(amtStr);
            if (type == "Food")
                addExpense(make_shared<FoodExpense>(amt, date, desc, extra));
            else if (type == "Travel")
                addExpense(make_shared<TravelExpense>(amt, date, desc, extra));
        }
        inFile.close();
    }
};

// ---------------------- BudgetAdvisor ----------------------
class BudgetAdvisor {
public:
    void analyze(float totalExpenses) {
        cout << "\n--- Budget Analysis ---\n";
        if (totalExpenses > 10000)
            cout << "Warning: You are overspending! Try to save more.\n";
        else
            cout << "Good job! Your spending is under control.\n";
    }
};

// ---------------------- User Interface ----------------------
class UserUI {
    ExpenseManager manager;
    BudgetAdvisor advisor;
    string dataFile = "expenses.txt";

public:
    UserUI() {
        manager.loadData(dataFile);
    }

    void displayMenu() {
        int choice;
        do {
            cout << "\n==== Smart Expense Tracker ====\n";
            cout << "1. Add Food Expense\n";
            cout << "2. Add Travel Expense\n";
            cout << "3. View All Expenses\n";
            cout << "4. View Total Expenses\n";
            cout << "5. Get Budget Advice\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addFoodExpense(); break;
                case 2: addTravelExpense(); break;
                case 3: manager.listAllExpenses(); break;
                case 4: cout << "Total Expenses: " << manager.getTotalExpenses() << endl; break;
                case 5: advisor.analyze(manager.getTotalExpenses()); break;
                case 0: manager.saveData(dataFile); cout << "Data saved. Goodbye!\n"; break;
                default: cout << "Invalid choice! Try again.\n";
            }
        } while (choice != 0);
    }

private:
    void addFoodExpense() {
        float amt; string dt, desc, type;
        cout << "Enter amount: "; cin >> amt;
        cout << "Enter date (DD/MM): "; cin >> dt;
        cout << "Enter description: "; cin.ignore(); getline(cin, desc);
        cout << "Enter food type: "; getline(cin, type);
        manager.addExpense(make_shared<FoodExpense>(amt, dt, desc, type));
    }

    void addTravelExpense() {
        float amt; string dt, desc, dest;
        cout << "Enter amount: "; cin >> amt;
        cout << "Enter date (DD/MM): "; cin >> dt;
        cout << "Enter description: "; cin.ignore(); getline(cin, desc);
        cout << "Enter destination: "; getline(cin, dest);
        manager.addExpense(make_shared<TravelExpense>(amt, dt, desc, dest));
    }
};

// ---------------------- Main ----------------------
int main() {
    UserUI ui;
    ui.displayMenu();
    return 0;
}
