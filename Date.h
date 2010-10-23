#ifndef DATE_H_
#define DATE_H_

// Tudo isto: necessario? Se sim, nao podemos copiar
// de algum lado (acho que tem nos slides) e dar o
// devido credito?

class InvalidDate {};
class InvalidDay : public InvalidDate {};
class InvalidMonth : public InvalidDate {};

class Date {
	int year;
	int month;
	int day;
public:
	Date (int year, int month, int day);
	Date () {}
	void SetDate ();
	void SetMonth (int month);
	void SetDay (int day);
	void SetYear (int year);
	int GetMonth ();
	int GetDay ();
	int GetYear();
};

#endif
