// ADayToRemember.cpp: определ€ет точку входа дл€ консольного приложени€.

// ¬ыполнила ћаньшина јлла 

/* 10. —оздать класс Date дл€ работы с датами в формате Угод.мес€ц.деньФ. ƒата
представл€етс€ структурой с трем€ пол€ми типа unsigned int: дл€ года мес€ца и дн€.
 ласс должен включать не менее трех функций инициализации: числами, строкой вида
Угод.мес€ц.деньФ (например, У2016.04.07Ф ) и датой. ќб€зательно должны быть
реализованы: вычисление даты чeрез заданное количество дней, вычитание заданного
количества дней из даты, определение високосности года, присвоение и получение
отдельных частей (год, мес€ц, день), сравнение дат (до, после, равно), вычисление
количества дней между датами.*/


#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;


class Date{

public:
	//конструктор (Init) числами
	//по умолчанию датой 1.01.1970
	Date(unsigned int d = 1, unsigned int m = 1, unsigned int y = 1970) {
		this->day = (d >= 1 && d <= 31) ? d : 0;
		this->month = (m >= 1 && m <= 12) ? m : 0;
		this->year = (y >= 1970 && y < 3000) ? y : 0;
	}

	//конструктор (Init) строкой вида Угод.мес€ц.деньФ(например, У2016.04.07Ф)
	Date(char *str) {
		string a;
		int n = 0, date[3];
		int len = strlen(str);
		for (int i = 0; i < len + 1; i++) {
			if (str[i] != '.' && str[i] != '\0') {
				a += str[i];
			}
			else {
				date[n] = atoi(a.c_str());
				n++;
				a = "";
			}
		}
		this->year = date[0];
		this->month = date[1];
		this->day = date[2];
	}

	/*Date::Date(const Date &d) {
		this->year = d.year;
		this->month = d.month;
		this->day = d.day;
	}*/

	//геттеры и сеттеры
	void SetDay(unsigned int d)
	{
		this->day = (d >= 1 && d <= 31) ? d : 0;
	}
	void SetMonth(unsigned int m)
	{
		this->month = (m >= 1 && m <= 12) ? m : 0;
	}
	void SetYear(unsigned int y)
	{
		this->year = (y >= 1970 && y < 3000) ? y : 0;
	}
	unsigned int GetDay() const
	{
		return this->day;
	}
	unsigned int GetMonth() const
	{
		return this->month;
	}
	unsigned int GetYear() const
	{
		return this->year;
	}

	//преобразование в строку
	string toString()
	{
		return to_string(year) + string(".") + to_string(month) + string(".") + to_string(day);
	}

	//вывод на экран
	void Display()
	{
		cout << "Date in format YYYY.MM.DD.: " << this->toString() << endl;
	}

	// проверка на високосный год
	static bool IsLeapYear(const unsigned int year) {
		return (year % 4 == 0 || (year % 100 == 0 && year % 400 != 0));
	}
	
	//проверка на существование даты
	static bool IsValid(const unsigned int day, const unsigned int month, const unsigned int year)
	{
		if (day > 31 || month > 12 || day <= 0 || month <= 0 || year < 0)
		{
			cout << "Invalid date " << endl;
			return false;
		}
		else
		{
			if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
			{
				cout << year << "." << month << "." << day << ": " << "It is a solar month of 30 days" << endl;
				return false;
			}
			else
			{
				if ((month == 2))
				{
					if (day > 29)
					{
						return false;
					}
					else
					{
						if ((!IsLeapYear(year)) && (day == 29))
						{
							cout << month << "." << day << "." << year << ": " << "It is not a LeapYear!!" << endl;
							return false;
						}
						else
						{
							return true;
						}
					}

				}
				else
				{
					return true;
				}
			}
		}
	}

	int Date::cmp(const Date& lval, const Date& rval) {
		if (lval.GetYear() != rval.GetYear())
			return lval.GetYear() - rval.GetYear();
		if (lval.GetMonth() != rval.GetMonth())
			return lval.GetMonth() - rval.GetMonth();
		if (lval.GetDay() != rval.GetDay())
			return lval.GetDay() - rval.GetDay();
		return 0;
	}

	bool Date::operator < (const Date& oper1) {
		return cmp(*this, oper1) < 0;
	}

	bool Date::operator > (const Date& oper1) {
		return cmp(*this, oper1) > 0;
	}

	bool Date::operator == (const Date& oper1) {
		return cmp(*this, oper1) == 0;
	}

	unsigned int KeyDaysInMonth[12] =
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int daysInYear[12] = { 31,59,90,120,151,181,212,243,273,304,334,365 };

	void CheckMonth(unsigned int &month, unsigned int &year) const
	{
		if (month > 12) {
			month = 1;
			year += 1;
		}
		else {
			if (month < 1) {
				month = 12;
				year -= 1;
			}
		}
	}

	void CheckDay(unsigned int maxday, unsigned int &day, unsigned int &month) const
	{
		if (day > maxday)
		{
			month += 1;
			day -= maxday;
		}
		if (day < 1) {
			month -= 1;
			day = maxday;
		}
	}
	
	unsigned int Date::LastDayInMonth(const int& month, const int& year) const
	{
		if (month == 2) return IsLeapYear(year) ? 29 : 28;
		else return  KeyDaysInMonth[month-1];
	}

	//вычисление даты через заданное количество дней
	Date operator+ (unsigned int days) const
	{
		unsigned int nMaxDays = LastDayInMonth(this->month, this->year);
		unsigned int nYear = this->year;
		unsigned int nMonth = this->month;
		unsigned int nDays = this->day + days;
		while (nDays > nMaxDays) {
			nDays -= nMaxDays;
			++nMonth;
			if (nMonth > 12) {
				nMonth = 1;
				++nYear;
			}
			nMaxDays = LastDayInMonth(nMonth, nYear);
		}
		return Date(nDays, nMonth, nYear);
	}

	//вычитание заданного количества дней из даты
	Date operator- (unsigned int days) const
	{
		if (0 > (this->day - days)) {
			return Date(this->year, this->month, this->day - days);
		}
		unsigned int nYear = this->year;
		int nDays = days;
		nDays -= this->day;
		unsigned int nMonth = this->month - 1;
		if (nMonth < 1) {
			nMonth = 12;
			--nYear;
		}
		unsigned int nDaysInMonth = LastDayInMonth(nMonth, nYear);
		while (nDays >= 0) {
			nDays -= nDaysInMonth;
			if (nDays > 0) {
				--nMonth;
				if (nMonth < 1) {
					nMonth = 12;
					--nYear;
				}
			}
			nDaysInMonth = LastDayInMonth(nMonth, nYear);
		}
		return Date((0 < nDays ? nDays : -nDays), nMonth, nYear);
	}

	//считает количество високосных годов
	int Date::countLeapYears() {
		size_t years = this->year;
		if (this->GetMonth() <= 2)
			years--;
		return years / 4 - years / 100 + years / 400;
	}

	long Date::sum(Date dt) {
		unsigned int x;
		long int tmp = dt.GetYear() * 365 + dt.GetDay(); 
		if (dt.GetMonth() != 1) {
			tmp += dt.daysInYear[dt.GetMonth() - 2];
		}
		return tmp += dt.countLeapYears();
	}
	
	static int Date::different(Date first, Date second) {
		long int n1 = first.sum(first);
		long int n2 = second.sum(second);
		return abs((n2 - n1));
	}

private:
	unsigned int day, month, year;
};

unsigned int InputNum()
{
	unsigned int n = 0;
	while (n <= 0)
	{
		try {
			cin >> n;
		}
		catch (unsigned int) {
			exception("Input error. Repeat input.\n");
		}
	}
	return n;
}

void Splitter(char *str, unsigned int *dd, unsigned int *mm, unsigned int *yy) {
	string a;
	int n = 0, date[3];
	int len = strlen(str);
	for (int i = 0; i < len + 1; i++) {
		if (str[i] != '.' && str[i] != '\0') {
			a += str[i];
		}
		else {
			date[n] = atoi(a.c_str());
			n++;
			a = "";
		}
	}
	*yy = date[0];
	*mm = date[1];
	*dd = date[2];
}

Date InitDate() {
	int answer;
	unsigned int d = 0;
	unsigned int m = 0;
	unsigned int y = 0;
	cout << "In which format do you want enter date?" << endl;
	cout << "1. Numbers" << endl;
	cout << "2. String" << endl;
	cin >> answer;
	switch (answer) {
	case 1: 
	{
		do {
			cout << "Input date: " << endl;
			try {
				cout << "Input day: " << endl;
				cin >> d;
			}
			catch (unsigned int) {
				exception("Input error.\n");
				d = 0;
			}

			try {
				cout << "Input month: " << endl;
				cin >> m;
			}
			catch (unsigned int) {
				exception("Input error.\n");
				m = 0;
			}

			try {
				cout << "Input year: " << endl;
				cin >> y;
			}
			catch (unsigned int) {
				exception("Input error.\n");
				y = 0;
			} 
		} while (!Date::IsValid(d, m, y));
		Date obj(d, m, y);
		return obj;
		break;
	}

	case 2: {
		char str[80];
		do {
			cout << "Input date in format 'year.month.day'" << endl;
			cin >> str;
			Splitter(str, &d, &m, &y);
		} while (!Date::IsValid(d, m, y));
		Date obj(str);
		return obj;
		break;
	}
	default: {
		cout << "Invalid command." << endl;
	}
	}
}

// ћеню
void PrintMenu()
{
	cout << "---------------------------------------------------------------" << endl;
	cout << "[1] Ч Add days" << endl;
	cout << "[2] Ч Substract days" << endl;
	cout << "[3] Ч Is leap year?" << endl;
	cout << "[4] Ч Comparison of two dates" << endl;
	cout << "[5] Ч How much days between two dates" << endl;
	cout << "[0] Ч Exit" << endl;
	
};

int main()
{
	setlocale(LC_ALL, "Russian");

	int p;
	for (;;) {
		PrintMenu();
		cout << "Input a command: ";
		cin >> p;
		cout << endl;
		cin.clear();

		switch (p)
		{
		case 1: {
			Date firstDate = InitDate();
			cout << "Input a positive integer" << endl;
			unsigned int num = InputNum();
			Date result = firstDate + num;
			result.Display();
			break;
		}
		case 2: {
			Date firstDate = InitDate();
			cout << "Input a positive integer" << endl;
			unsigned int num = InputNum();
			Date result = firstDate - num;
			result.Display();
			break;
		}
		case 3: {
			cout << "Enter year" << endl;
			unsigned int year = InputNum();
			if (Date::IsLeapYear(year)) {
				cout << year << " is a leap year" << endl;
			}
			else {
				cout << year << " is NOT a leap year" << endl;
			}
			break;
		}
		case 4: {
			cout << "Enter 2 dates:" << endl;
			Date firstDate = InitDate();
			Date secondDate = InitDate();
			if (firstDate == secondDate) {
				cout << "Dates equal" << endl;
			}
			else {
				cout << "Dates not equal" << endl;
				if (firstDate < secondDate) {
					cout << "First < second" << endl;
				}
				else {
					cout << "First > second" << endl;
				}
			}
			break;
		}
		case 5: {
			cout << "Enter first date: " << endl;
			Date firstDate = InitDate();
			cout << "Enter second date: " << endl;
			Date secondDate = InitDate();
			int result = Date::different(firstDate, secondDate);
			cout << result << endl;
			break;
		}
		case 0: {
			cout << "The work is been finished \n";  
			exit(1);
			break;
		}
		default:
			cout << "Invalid command" << endl;
		}
	}
    return 0;
}

