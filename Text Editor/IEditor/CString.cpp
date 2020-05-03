#include<iostream>
#include"CString.h"
using namespace std;

CString::CString()
{
	size = 0;
	data = nullptr;
}

CString::CString(char c)
{
	size = 2;
	data = new char[size];
	data[0] = c;
	data[1] = '\0';
}

int CString::getLength() const
{
	if (data != 0)
	{
		int i = 0, count = 0;
		while (data[i] != '\0')
		{
			count = count + 1;
			i = i + 1;
		}
		return count;
	}
	else
	{
		return 0;
	}
}

int CString::getLength(const char*c)const
{
	int i = 0, count = 0;
	while (c[i] != '\0')
	{
		count = count + 1;
		i = i + 1;
	}
	return count;
}

int CString::getSize()const
{
	return size;
}

CString::CString(const char*c)
{
	size = getLength(c) + 1;
	data = new char[size];
	int i = 0;
	while (c[i] != '\0')
	{
		data[i] = c[i];
		i = i + 1;
	}
	data[i] = '\0';
}

CString::CString(const CString & r)
{
	if (r.data == nullptr)
	{
		data = nullptr;
		size = 0;
		return;
	}
	size = r.size;
	data = new char[size];
	int len = r.getLength();
	int i;
	for (i = 0; i < len; i = i + 1)
	{
		data[i] = r.data[i];
	}
	data[i] = '\0';
}

CString::CString(CString && ref)
{
	size = ref.size;
	data = new char[size];
	if (!ref.data)
	{
		data = nullptr;
		return;
	}
	int len = ref.getLength();
	int i;
	for (i = 0; i < len; i = i + 1)
	{
		data[i] = ref.data[i];
	}
	data[i] = '\0';
}

CString & CString::operator = (const CString & ref)
{
	if (this == &ref)  //if self assignment is occured
	{
		return *this;
	}
	this->~CString();
	if (!ref)
	{
		return*this;
	}
	size = ref.size;
	data = new char[size];
	int len = ref.getLength();
	int i;
	for (i = 0; i < len; i = i + 1)
	{
		data[i] = ref.data[i];
	}
	data[i] = '\0';
	return *this;
}

CString & CString::operator=(CString && ref)
{
	//cout << "\nCTORRRRR";
	if (this == &ref)
	{
		return *this;
	}
	this->~CString();
	data = ref.data;
	size = ref.size;
	ref.data = nullptr;
	ref.size = 0;
	return *this;
}

CString::~CString()
{
	if (data)
		delete[]data;
	data = nullptr;
	size = 0;
}

const char* CString::getData()
{
	return data;
}

bool CString::isValidIndex(int index)const
{
	if (index >= 0 && index < size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const char & CString::operator [](int index) const
{
	if (isValidIndex(index))
	{
		return data[index];
	}
	exit(0);
}

char& CString::operator [](int index)
{
	if (isValidIndex(index))
	{
		return data[index];
	}
	exit(0);
}

bool CString::operator!() const
{
	if (!data || getLength() == 0)
		return true;
	return false;
}

void CString::display() const
{
	if (data)
	{
		cout << data;
	}
}

int CString::find(const CString & substr, int start) const
{
	int i = start;
	int len1 = getLength();
	int lenSubstr = substr.getLength();
	if (data != 0)
	{
		while (i < len1 + 1)
		{
			if (data[i] == substr.data[0])
			{
				int j = i + 1;
				int k = 1;
				bool check = true;
				while (check && j < len1 && k < lenSubstr)
				{
					if (data[j] != substr.data[k])
					{
						check = false;
					}
					k = k + 1;
					j = j + 1;
				}
				if (substr.getLength() != 0)
				{
					if (check && k == lenSubstr)
					{
						return i;
					}
				}
				else
				{
					if (check)
					{
						return i;
					}
				}
			}
			i = i + 1;
		}
		return -1;
	}
	return -1;
}

void CString::reSize(int s)
{
	if (s <= 0)
	{
		this->~CString();
		return;
	}
	char*p = new char[s];
	int n;
	if (size >= s)
	{
		n = s;
	}
	else
	{
		n = size;
	}
	for (int i = 0; i < n; i = i + 1)
	{
		p[i] = data[i];
	}
	this->~CString();
	data = p;
	size = s;
}

void CString::insert(int index, const CString & subStr)
{
	if (!data)
	{
		reSize(1);
		data[0] = '\0';
	}
	if (isValidIndex(index))
	{
		int len1 = getLength();
		int lenSubstr = subStr.getLength();
		if (subStr[0] == '\0')                     //If substr='\0'
		{
			lenSubstr = 1;
		}
		if (size < len1 + lenSubstr + 1)
		{
			reSize(len1 + lenSubstr + 1);
		}
		int tempSize = len1 - index + lenSubstr;
		char*temp = new char[tempSize];
		int i;
		for (i = 0; i < lenSubstr; i = i + 1)
		{
			temp[i] = subStr.data[i];
		}
		int j = index;
		while (i < tempSize)
		{
			temp[i] = data[j];
			j = j + 1;
			i = i + 1;
		}
		j = index;
		i = 0;
		while (j < len1 + lenSubstr)
		{
			data[j] = temp[i];
			i = i + 1;
			j = j + 1;
		}
		data[j] = '\0';
		delete[]temp;
		temp = nullptr;
	}
	else
	{
		exit(0);
	}
}

void CString::remove(int index, int count)
{
	int len = getLength();
	if (index >= 0 && index < getLength() - 1)
	{
		if (count > len - index)
		{
			count = len - index;
		}
		int i = index;
		while (data[i] != '\0')
		{
			data[i] = data[i + count];
			i = i + 1;
		}
	}
	else if (data != nullptr && len != 0) //It means if data=nullptr or string is empty then it remains unchanged otherwise exit(0)
	{
		exit(0);
	}
}

int CString::replace(const CString & old, const CString & newSubStr)
{
	int i = find(old);
	int len = old.getLength();
	int count = 0;
	while (i != -1)
	{
		count = count + 1;
		remove(i, len);
		insert(i, newSubStr);
		i = find(old);
	}
	return count;
}

void CString::trimLeft()
{
	if (data != nullptr)
	{
		int i = 0;
		int count = 0;
		while (data[i] == '\t' || data[i] == '\n' || data[i] == ' ')
		{
			count = count + 1;
			i = i + 1;
		}
		remove(0, count);
	}
}

void CString::trimRight()
{
	if (data != nullptr)
	{
		int j = getLength() - 1;
		while (data[j] == '\t' || data[j] == '\n' || data[j] == ' ')
		{
			j = j - 1;
		}
		data[j + 1] = '\0';
	}
}

void CString::trim()
{
	if (data != 0)
	{
		trimLeft();
		trimRight();
	}
}

void CString::makeUpper()
{
	if (data != nullptr && getLength() != 0)
	{
		int i = 0;
		while (data[i] != 0)
		{
			if (data[i] >= 'a'&&data[i] <= 'z')
			{
				data[i] = data[i] - 32;
			}
			i = i + 1;
		}
	}
}

void CString::makeLower()
{
	if (data != nullptr && getLength() != 0)
	{
		int i = 0;
		while (data[i] != 0)
		{
			if (data[i] >= 'A'&&data[i] <= 'Z')
			{
				data[i] = data[i] + 32;
			}
			i = i + 1;
		}
	}
}

void CString::swap(char*a, char*b)
{
	char temp = *b;
	*b = *a;
	*a = temp;
}

void CString::reverse()
{
	if (data != nullptr && getLength() != 0)
	{
		int i, j = getLength() - 1, n = getLength() / 2;
		for (i = 0; i < n; i = i + 1)
		{
			swap(&data[i], &data[j]);
			j = j - 1;
		}
	}
}

int CString::operator ==(const CString & s2) const
{
	int length1, length2;
	if (!data)
	{
		length1 = 0;
	}
	else
	{
		length1 = getLength();
	}
	if (!s2.data)
	{
		length2 = 0;
	}
	else
	{
		length2 = getLength(s2.data);
	}
	if (data != nullptr && length1 != 0 && s2.data != nullptr && length2 != 0)
	{
		if (length1 == length2)
		{
			for (int i = 0; i < length1; i = i + 1)
			{
				if (data[i] > s2.data[i])
				{
					return 1;
				}
				else if (data[i] < s2.data[i])
				{
					return -1;
				}
			}
			return 0;
		}
		else
		{
			int n;
			if (length1 < length2)
			{
				n = length1;
			}
			else
			{
				n = length2;
			}
			for (int i = 0; i < n; i = i + 1)
			{
				if (data[i] > s2.data[i])
				{
					return 1;
				}
				else if (data[i] < s2.data[i])
				{
					return -1;
				}
			}
			if (length1 > length2)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}
	}
	if (length1 == 0 && length2 == 0)
	{
		return 0;
	}
	else if (length1 != 0 && length2 == 0)
	{
		return 1;
	}
	else if (length1 == 0 && length2 != 0)
	{
		return -1;
	}
}

void CString::input()
{
	char c;
	bool stop = false;
	int i = 0;
	size = 2;
	data = new char[size];
	char check;
	cin.get(check);
	if (check != '\n')
	{
		data[i] = check;
		i = i + 1;
	}
	while (!stop)
	{
		cin.get(c);
		if (c != '\n')
		{
			data[i] = c;
		}
		else
		{
			stop = true;
		}

		i = i + 1;
		if (i >= size)
		{
			size = getLength() * 2 + 3;
			reSize(size);
		}
	}
	data[i - 1] = '\0';
	shrink();
}

void CString::shrink()
{
	int length = getLength() + 1;
	if (size > length)
	{
		reSize(length);
	}
}

bool CString::isValidCount(int count)
{
	return count > 0;
}

CString CString::left(int count)
{
	if (data && getLength() != 0)
	{
		CString a;
		int i;
		a.size = count + 1;
		a.data = new char[a.size];
		if (count > getLength())
		{
			count = getLength();
		}
		if (isValidCount(count))
		{
			for (i = 0; i < count; i = i + 1)
			{
				a.data[i] = data[i];
			}
			a.data[i] = '\0';
			remove(0, count);
			return a;
		}
	}
	else
	{
		return "";
	}
	exit(0); //If count<0
}

CString CString::right(int count)
{
	if (data && getLength() != 0)
	{
		CString a;
		int i;
		a.size = count + 1;
		a.data = new char[a.size];
		int j = getLength() - 1;
		if (count > getLength())
		{
			count = getLength();
		}
		if (isValidCount(count))
		{
			for (i = 0; i < count; i = i + 1)
			{
				a.data[i] = data[j];
				j = j - 1;
			}
			a.data[i] = '\0';
			a.reverse();
			remove((getLength() - count), count);
			return a;
		}
	}
	else
	{
		return "";
	}
	exit(0); //If count<0
}

int CString::getIntegerLength() const
{
	int i = 0;
	if (data[i] == '-')
	{
		i = i + 1;
	}
	while (data[i] != '\0' && data[i] >= '0' && data[i] <= '9')
	{
		i = i + 1;
	}
	return i;
}

/*int CString::toInteger() const
{
	if (data != 0 && getLength() != 0)
	{
		int i = 0;
		int integer = 0;
		int sign = 1;
		while (i < getIntegerLength())
		{
			if (data[0] == '-')
			{
				sign = -1;
				i = i + 1;
			}
			while (data[i] >= '1' && data[i] <= '9')
			{
				integer = integer * 10 + data[i] - '0';
				i = i + 1;
			}
		}
		return sign * integer;
	}
	else
	{
		return 0;
	}
}*/

int CString::getFloatLength()const
{
	int i = getIntegerLength();
	if (data[i] == '.')
	{
		i = i + 1;
		while (data[i] != '\0' && data[i] >= '0' && data[i] <= '9')
		{
			i = i + 1;
		}
		return i;
	}
	else
	{
		return i;
	}
}

/*float CString::toFloat()const
{
	if(data!=0 && getLength()!=0)
	{
	int i = 0,length = getFloatLength(),integer = 0,sign = 1,power = 0;
	int len = getFloatLength();
	float decimal = 0;
	bool isFloat = false;
		if (data[0] == '-')
		{
			sign = -1;
			i = i + 1;
			len = len - 1;
		}
		int j = i;
		while (j < len-1)
		{
			if (data[i] == '.')
			{
				integer = decimal;
				decimal = 0;
				power = length - i;
				i = i + 1;
				isFloat = 1;
			}
			decimal = decimal * 10 + (data[i] - '0');
			i = i + 1;
			j = j + 1;
		}
		if (isFloat == 1)
		{
			return sign * (integer + (decimal / pow(10, power - 1)));
		}
		else
		{
			return sign * decimal;
		}
	}
	else
	{
		return 0;
	}
}*/

CString CString::operator +(const CString & s2) const
{
	if (s2.data != nullptr && s2.getLength() != 0 && data != nullptr && getLength() != 0)
	{
		CString a;
		int len = getLength(), len2 = s2.getLength();
		a.size = len + len2 + 1;
		a.data = new char[a.size];
		a.insert(0, *this);
		a.insert(len, s2);
		a.data[len + len2] = '\0';
		return a;
	}
	else if (s2.getLength() == 0 && data != nullptr && getLength() != 0)
	{
		return *this;
	}
	else if (data == nullptr || getLength() == 0 || s2.getLength() != 0)
	{
		return s2;
	}
	else
	{
		return "";
	}
}

void CString::operator +=(const CString & s2)
{
	int len = getLength();
	int len2 = s2.getLength();
	if (data != nullptr && getLength() != 0)
	{
		int i = len;
		size = len + len2 + 1;
		reSize(size);
		for (int j = 0; j < len2; j = j + 1)
		{
			data[i] = s2.data[j];
			i = i + 1;
		}
		data[i] = '\0';
	}
	else
	{
		reSize(len2 + 1);
		int i;
		for (i = 0; i < len2; i = i + 1)
		{
			data[i] = s2.data[i];
		}
		data[i] = '\0';
	}
}

CString CString::tokenize(const CString & delim)
{
	CString a;
	int lenDelim = delim.getLength(), length = getLength();
	int i = 0;
	bool found = false;
	while (!found && i < length)
	{
		int j = 0;
		bool found2 = false;
		while (j < lenDelim && !found2)
		{
			if (data[i] == delim.data[j])
			{
				found2 = true;
				found = true;
			}
			j = j + 1;
		}
		i = i + 1;
	}
	int j;
	a.size = i + 1;
	a.data = new char[a.size];
	if (found)
	{
		for (j = 0; j < i - 1; j = j + 1)
		{
			a.data[j] = data[j];
		}
	}
	else
	{
		for (j = 0; j < i; j = j + 1)
		{
			a.data[j] = data[j];
		}
	}
	a.data[j] = '\0';
	remove(0, i);
	return a;
}

CString CString::operator()(const CString & delim)
{
	CString a;
	int lenDelim = delim.getLength(), length = getLength();
	int i = 0;
	bool found = false;
	while (!found && i < length)
	{
		int j = 0;
		bool found2 = false;
		while (j < lenDelim && !found2)
		{
			if (data[i] == delim.data[j])
			{
				found2 = true;
				found = true;
			}
			j = j + 1;
		}
		i = i + 1;
	}
	int j;
	a.size = i + 1;
	a.data = new char[a.size];
	if (found)
	{
		for (j = 0; j < i - 1; j = j + 1)
		{
			a.data[j] = data[j];
		}
	}
	else
	{
		for (j = 0; j < i; j = j + 1)
		{
			a.data[j] = data[j];
		}
	}
	a.data[j] = '\0';
	remove(0, i);
	return a;
}

CString::operator long long int()const
{
	if (data != 0 && getLength() != 0)
	{
		int i = 0;
		int integer = 0;
		int sign = 1;
		int len = getLength();
		if (data[0] == '-')
		{
			sign = -1;
			i = i + 1;
		}
		while (data[i] >= '0' && data[i] <= '9'&&i < len)
		{
			integer = integer * 10 + data[i] - '0';
			i = i + 1;
		}
		return sign * integer;
	}
	else
	{
		return 0;
	}
}

CString::operator float()const
{
	if (data != 0 && getLength() != 0)
	{
		int i = 0, length = getFloatLength(), integer = 0, sign = 1, power = 0;
		int len = getFloatLength();
		float decimal = 0;
		bool isFloat = false;
		if (data[0] == '-')
		{
			sign = -1;
			i = i + 1;
			len = len - 1;
		}
		int j = i;
		while (j < len - 1)
		{
			if (data[i] == '.')
			{
				integer = decimal;
				decimal = 0;
				power = length - i;
				i = i + 1;
				isFloat = 1;
			}
			decimal = decimal * 10 + (data[i] - '0');
			i = i + 1;
			j = j + 1;
		}
		if (isFloat == 1)
		{
			return sign * (integer + (decimal / pow(10, power - 1)));
		}
		else
		{
			return sign * decimal;
		}
	}
	else
	{
		return 0;
	}
}

ostream & operator <<(ostream & r, const CString & c)
{
	if (c.data)
	{
		r << c.data;
	}
	return r;
}

istream & operator >>(istream & in, CString & c)
{
	char ch;
	bool stop = false;
	int i = 0;
	c.size = 2;
	c.data = new char[c.size];
	while (!stop)
	{
		in.get(ch);
		if (ch != '\n' && !in.eof())
		{
			c.data[i] = ch;
		}
		else
		{
			stop = true;
		}

		i = i + 1;
		if (i >= c.size)
		{
			c.size = c.getLength() * 2 + 3;
			c.reSize(c.size);
		}
	}
	c.data[i - 1] = '\0';
	c.shrink();
	return in;
}

void  operator++(const CString & c)
{
	cout << "prefix\n";
}

void  CString::operator++()
{
	cout << "prefix\n";
}

void operator++(const CString & c, int)
{
	cout << "postfix\n";
}