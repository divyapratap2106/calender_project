#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>

using namespace std;

struct Date {
    int dd;
    int mm;
    int yy;
};
Date date;

struct Remainder {
    int dd;
    int mm;
    char note[50];
};
Remainder R;

COORD xy = {0, 0};

void gotoxy(int x, int y) {
    xy.X = x; xy.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

// Sets the foreground color for printing in a console window.
void SetColor(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void ClearColor() {
    SetColor(15);
}

void ClearConsoleToColors(int ForgC, int BackC) {
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    SetConsoleTextAttribute(hStdOut, wColor);
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        SetConsoleCursorPosition(hStdOut, coord);
    }
}

void SetColorAndBackground(int ForgC, int BackC) {
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

int check_leapYear(int year) {
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        return 1;
    return 0;
}

void increase_month(int *mm, int *yy) {
    ++*mm;
    if (*mm > 12) {
        ++*yy;
        *mm = *mm - 12;
    }
}

void decrease_month(int *mm, int *yy) {
    --*mm;
    if (*mm < 1) {
        --*yy;
        if (*yy < 1600) {
            cout << "No record available";
            return;
        }
        *mm = *mm + 12;
    }
}

int getNumberOfDays(int month, int year) {
    switch (month) {
        case 1: return 31;
        case 2: return (check_leapYear(year) == 1) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return -1;
    }
}

const char* getName(int day) {
    switch (day) {
        case 0: return "Sunday";
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        default: return "Error in getName() module. Invalid argument passed";
    }
}

void print_date(int mm, int yy) {
    cout << "---------------------------\n";
    gotoxy(25, 6);
    switch (mm) {
        case 1: cout << "January"; break;
        case 2: cout << "February"; break;
        case 3: cout << "March"; break;
        case 4: cout << "April"; break;
        case 5: cout << "May"; break;
        case 6: cout << "June"; break;
        case 7: cout << "July"; break;
        case 8: cout << "August"; break;
        case 9: cout << "September"; break;
        case 10: cout << "October"; break;
        case 11: cout << "November"; break;
        case 12: cout << "December"; break;
    }
    cout << " , " << yy;
    gotoxy(20, 7);
    cout << "---------------------------";
}

int getDayNumber(int day, int mon, int year) {
    int res = 0, t1, t2, y = year;
    year = year - 1600;
    while (year >= 100) {
        res = res + 5;
        year = year - 100;
    }
    res = (res % 7);
    t1 = ((year - 1) / 4);
    t2 = (year - 1) - t1;
    t1 = (t1 * 2) + t2;
    t1 = (t1 % 7);
    res = res + t1;
    res = res % 7;
    t2 = 0;
    for (t1 = 1; t1 < mon; t1++) {
        t2 += getNumberOfDays(t1, y);
    }
    t2 = t2 + day;
    t2 = t2 % 7;
    res = res + t2;
    res = res % 7;
    if (y > 2000)
        res = res + 1;
    res = res % 7;
    return res;
}

const char* getDay(int dd, int mm, int yy) {
    int day;
    if (!(mm >= 1 && mm <= 12)) {
        return "Invalid month value";
    }
    if (!(dd >= 1 && dd <= getNumberOfDays(mm, yy))) {
        return "Invalid date";
    }
    if (yy >= 1600) {
        day = getDayNumber(dd, mm, yy);
        day = day % 7;
        return getName(day);
    } else {
        return "Please give year more than 1600";
    }
}

int checkNote(int dd, int mm) {
    ifstream fp("note.dat", ios::binary);
    if (!fp) {
        cout << "Error in Opening the file";
        return 0;
    }
    while (fp.read((char*)&R, sizeof(R))) {
        if (R.dd == dd && R.mm == mm) {
            fp.close();
            return 1;
        }
    }
    fp.close();
    return 0;
}

void printMonth(int mon, int year, int x, int y) {
    int nod, day, cnt, d = 1, x1 = x, y1 = y, isNote = 0;
    if (!(mon >= 1 && mon <= 12)) {
        cout << "INVALID MONTH";
        _getch();
        return;
    }
    if (!(year >= 1600)) {
        cout << "INVALID YEAR";
        _getch();
        return;
    }
    gotoxy(20, y);
    print_date(mon, year);
    y += 3;
    gotoxy(x, y);
    cout << "S   M   T   W   T   F   S   ";
    y++;
    nod = getNumberOfDays(mon, year);
    day = getDayNumber(d, mon, year);
    switch (day) {
        case 0: x = x; cnt = 1; break;
        case 1: x = x + 4; cnt = 2; break;
        case 2: x = x + 8; cnt = 3; break;
        case 3: x = x + 12; cnt = 4; break;
        case 4: x = x + 16; cnt = 5; break;
        case 5: x = x + 20; cnt = 6; break;
        case 6: x = x + 24; cnt = 7; break;
        default: cout << "INVALID DATA"; return;
    }
    gotoxy(x, y);
    if (cnt == 1) {
        SetColor(12);
    }
    if (checkNote(d, mon) == 1) {
        SetColorAndBackground(15, 12);
    }
    cout << d;
    ClearColor();
    for (d = 2; d <= nod; d++) {
        if (cnt % 7 == 0) {
            y++;
            cnt = 0;
            x = x1 - 4;
        }
        x = x + 4;
        cnt++;
        gotoxy(x, y);
        if (cnt == 1) {
            SetColor(12);
        } else {
            ClearColor();
        }
        if (checkNote(d, mon) == 1) {
            SetColorAndBackground(15, 12);
        }
        cout << d;
        ClearColor();
    }
    gotoxy(8, y + 2);
    SetColor(14);
    cout << "Press any key to continue...........";
    ClearColor();
    _getch();
}

void AddNote() {
    ofstream fp("note.dat", ios::app | ios::binary);
    if (!fp) {
        cout << "Error in Opening the file";
        return;
    }
    cout << "Enter the date(DD/MM): ";
    cin >> R.dd >> R.mm;
    cout << "Enter the Note(50 character max): ";
    cin.ignore();
    cin.getline(R.note, 50);
    fp.write((char*)&R, sizeof(R));
    cout << "Note is saved successfully";
    fp.close();
    _getch();
}

void showNote(int mm) {
    ifstream fp("note.dat", ios::binary);
    if (!fp) {
        cout << "Error in Opening the file";
        return;
    }
    cout << "Notes List:\n";
    while (fp.read((char*)&R, sizeof(R))) {
        if (R.mm == mm) {
            cout << "Date: " << R.dd << "/" << R.mm << ", Note: " << R.note << endl;
        }
    }
    fp.close();
    _getch();
}

int main() {
    ClearConsoleToColors(15, 1);
    SetConsoleTitle("Calender Project - Programming-technique.blogspot.com");
    int choice;
    while (true) {
        system("cls");
        cout << "-------------------------\n";
        cout << "1. Find Out the Day\n";
        cout << "2. Print all the day of month\n";
        cout << "3. Add Note\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls");
        switch (choice) {
            case 1:
                cout << "Enter date (DD/MM/YYYY): ";
                cin >> date.dd >> date.mm >> date.yy;
                cout << "Day is: " << getDay(date.dd, date.mm, date.yy);
                cout << endl;
                _getch();
                break;
            case 2:
                cout << "Enter month and year (MM YYYY): ";
                cin >> date.mm >> date.yy;
                printMonth(date.mm, date.yy, 20, 5);
                break;
            case 3:
                AddNote();
                break;
            case 4:
                exit(0);
                break;
            default:
                cout << "Invalid choice";
                break;
        }
    }
    return 0;
}
