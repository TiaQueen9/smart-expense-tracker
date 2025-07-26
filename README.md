# **Smart Expense Tracker**

## **Project Overview**
The **Smart Expense Tracker** is a simple yet powerful console-based application designed to help users manage their daily expenses and receive budget recommendations. It is built entirely using **Object-Oriented Programming (OOP)** principles and demonstrates **clean architecture** with reusable, maintainable code.

---

## **Problem Statement**
Tracking expenses manually can be tedious and prone to errors. This project solves that by:
- **Automatically categorizing expenses** (Food, Travel, etc.).
- **Providing total expense reports** and detailed breakdowns.
- **Offering budget suggestions** using basic financial rules.
- **Persisting expense data** between sessions using file storage.

---

## **Key Features**
- Add categorized expenses (e.g., food, travel).
- View all recorded expenses with details.
- Calculate total and category-wise spending.
- Get budget advice based on total expenditure.
- Save and load expenses using a simple file-based database.

---

## **OOP Concepts Implemented**
1. **Abstraction** – Separate classes for expense management, budget analysis, and UI.
2. **Encapsulation** – Attributes like `amount`, `date`, and `description` are protected/private.
3. **Inheritance** – `FoodExpense` and `TravelExpense` extend the base `Expense` class.
4. **Polymorphism** – Overridden `getDetails()` and `serialize()` methods for different expense types.
5. **Design Principle** –  
   - *Single Responsibility Principle*: Each class (UI, Manager, Advisor) has one job.
   - *Open-Closed Principle*: Easily extendable to add new expense categories.

---

## **Tech Stack**
- **Language**: C++
- **File Handling**: Text/CSV file for saving and loading data
- **Memory Management**: Smart pointers (`shared_ptr`) to manage dynamic objects

---

## **Sample Program Output**
```text
==== Smart Expense Tracker ====
1. Add Food Expense
2. Add Travel Expense
3. View All Expenses
4. View Total Expenses
5. Get Budget Advice
0. Exit

> User adds FoodExpense: 200 Rs (Pizza)
> User adds TravelExpense: 1500 Rs (Goa Trip)
> Total Expenses: 1700 Rs
> Budget Advice: Good job! Your spending is under control.
