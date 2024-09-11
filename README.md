# calender_project

This is a simple console-based calendar application written in C++. The application allows users to perform various calendar-related operations such as finding the day of a specific date, printing all days of a given month, and adding notes for specific dates.

Features
Find Out the Day: Determine the day of the week for any given date.
Print Days of the Month: Display all days of a specified month and year in a calendar format.
Add Notes: Users can add reminders or notes for specific dates.
View Notes: Display all notes for a selected month.
How It Works
->Console Navigation: The user interacts with the program through a menu-based console interface.
->Date Calculation: Uses custom functions to calculate the day of the week and other date-related functionalities.
->Note Management: Stores notes in a binary file (note.dat), allowing users to save and retrieve reminders.
Getting Started
Prerequisites
Windows OS: This program uses Windows-specific libraries (windows.h and conio.h) for console manipulation.
C++ Compiler: Make sure you have a C++ compiler installed (such as g++).
Installation
Clone this repository:


Copy code
->git clone https://github.com/yourusername/your-repo-name.git
->cd your-repo-name
->Compile the code:


->g++ -o CalendarApplication CalendarApplication.cpp
->Run the executable:

Usage

Option 1: Enter a date (DD/MM/YYYY) to find out which day of the week it falls on.
Option 2: Enter a month and year (MM YYYY) to print the entire month's calendar.
Option 3: Add a note for a specific date.
Option 4: Exit the application.

Code Overview
Date Handling: Functions such as getDayNumber, check_leapYear, and getNumberOfDays are used to handle date calculations.
Console Manipulation: Functions like gotoxy, SetColor, and ClearConsoleToColors are used for managing text and colors in the console output.
File Handling: Notes are managed using file operations (ifstream and ofstream) to read from and write to a binary file.
