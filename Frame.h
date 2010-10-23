#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <string>
using std::deque;
using std::string;

class FrameSetter
{
public:
	bool operator==(FrameSetter& other)
	{
		return (other.mode == mode);
	}

	FrameSetter(int arg)
	{
		mode = arg;
	}
	int mode;
	//0 - clear 1 - print 2 - flush 3 - pause
};

class Frame
{
public:
	Frame(void);
	~Frame(void);
	void setLoggedinuser(string in);
	string getLoggedinuser();
	void printHeader();
	void printBufferC();
	void printBuffer();
	void pauseFrame();
	Frame& operator<<(string in);
	Frame& operator<<(FrameSetter in);
	static FrameSetter clr;
	static FrameSetter print;
	static FrameSetter pause;
	static FrameSetter flush;
private:
	deque<string> buffer;
	static string loggedinuser;
};

class buffFull {};
