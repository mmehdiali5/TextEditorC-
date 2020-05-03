#ifndef CSTRING_H
#define CSTRING_H
#include<iostream>
#include<ostream>
#include<istream>
using namespace std;
class CString
{
private:
	char*data;
	int size;
	int getLength(const char*) const;
	bool isValidIndex(int index) const;
	void swap(char*a, char*b);
	bool isValidCount(int count);
	int getIntegerLength() const;
	int getFloatLength()const;
	friend ostream & operator << (ostream & r, const CString & c);
	friend istream & operator >> (istream & r, CString & c);
public:
	CString();
	CString(char c);
	CString(const char*);
	CString(const CString &);
	CString(CString &&);
	CString & operator = (const CString &);
	CString & operator = (CString &&);
	~CString();
	int getLength() const;
	int getSize()const;
	const char*getData();
	char& operator [](int index);
	const char & operator [](int index) const;
	bool operator !() const;
	void display() const;
	int find(const CString & substr, int start = 0) const;
	void insert(int index, const CString & subStr);
	void reSize(int s);
	void remove(int index, int count = 1);
	int replace(const CString & old, const CString & newSubStr);
	void trimLeft();
	void trimRight();
	void trim();
	void makeUpper();
	void makeLower();
	void reverse();
	int operator ==(const CString & s2) const;
	void input();
	void shrink();
	CString left(int count);
	CString right(int count);
	//int toInteger() const;
	explicit operator long long int()const;
	//float toFloat()const;
	explicit operator float()const;
	CString operator +(const CString & s2) const;
	void operator +=(const CString & s2);
	CString tokenize(const CString & delim);
	CString operator()(const CString & delim);
	friend void operator++(const CString &);
	friend void operator++(const CString &, int);
	void operator++();
};

ostream & operator << (ostream & r, const CString & c);
istream & operator >> (istream & r, CString & c);

#endif


