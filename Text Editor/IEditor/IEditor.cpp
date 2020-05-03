#include<iostream>
#include<fstream>
using namespace std;
#include"IEditor.h"

void IEditor::start()
{
	bool stop = false;
	while (!stop)
	{
		CString in;
		cout << currentLineNumber << "> ";
		in.input();
		int command = getCommand(in);
		if (command == LIST_ALL)
		{
			listAll();
		}
		else if (command == EXIT)
		{
			exit();
			stop = true;
		}
		else if (command == UP)
		{
			up();
		}
		else if (command == DOWN)
		{
			down();
		}
		else if (command == APPEND)
		{
			append();
		}
		else if (command == MODIFY)
		{
			modify();
		}
		else if (command == UP1)
		{
			up1(in);
		}
		else if (command == DOWN1)
		{
			down1(in);
		}
		else if (command == REMOVE)
		{
			remove();
		}
		if (command == NO_COMMAND)
		{
			addElement(in);
		}
	}
}

int IEditor::getCommand(const CString& in)const
{
	int len = in.getLength();
	if (len < 2)
	{
		return NO_COMMAND;
	}
	else if (in[0] != '_')
	{
		return NO_COMMAND;
	}
	else if ((in[1] != 'L') && (in[1] != 'U') && (in[1] != 'D') && (in[1] != 'M') && (in[1] != 'R') && (in[1] != 'E') &&(in[1]!='A'))
	{
		return NO_COMMAND;
	}
	if (in[1]=='L' && len==2)
	{
		return LIST_ALL;
	}
	else if (in[1] == 'U')
	{
		if (len == 2)
		{
			return UP;
		}
		if (len == 3)
		{
			if (in[2] == ' ')
			{
				return UP;
			}
			else
			{
				return NO_COMMAND;
			}
		}
		else
		{
			if (in[2] == ' ')
			{
				return UP1;
			}
			else
			{
				return NO_COMMAND;
			}
		}
	}
	else if (in[1] == 'D')
	{
		if (len == 2)
		{
			return DOWN;
		}
		if (len == 3)
		{
			if (in[2] == ' ')
			{
				return DOWN;
			}
			else
			{
				return NO_COMMAND;
			}
		}
		else
		{
			if (in[2] == ' ')
			{
				return DOWN1;
			}
			else
			{
				return NO_COMMAND;
			}
		}
	}
	else if (in[1] == 'E' && len==2)
	{
		return EXIT;
	}
	else if (in[1] == 'A' && len==2)
	{
		return APPEND;
	}
	else if (in[1] =='R' && len==2)
	{
		return REMOVE;
	}
	else if (in[1] == 'M' && len==2)
	{
		return MODIFY;
	}
}

void IEditor::listAll()
{
	DNode<CString>*p = head;
	int j = 1;
	while (p != nullptr)
	{
		cout << j << "> " << p->info << "\n";
		currentLineRef = p;
		p = p->next;
		j++;
	}
	currentLineNumber = linesCount + 1;
}

void IEditor::setFileName(const CString&fn)
{
	fileName = fn;
}

void IEditor::create()
{
	ofstream ofs(fileName.getData());
}

void IEditor::open()
{
	ifstream ifs(fileName.getData());
	CString in;
	while (!ifs.eof())
	{
		ifs >> in;
		if (!ifs.eof() || (ifs.eof() && !in==false))
		{
			addElement(in);
		}
	}
}

CString IEditor::getFileName()
{
	return fileName;
}

void IEditor::up()
{
	if (currentLineNumber != 1)
	{
		currentLineNumber--;
		currentLineRef = currentLineRef->prev;
	}
}

void IEditor::down()
{
	if (currentLineNumber + 1 <= linesCount)
	{
		currentLineNumber++;
		currentLineRef = currentLineRef->next;
	}
}

void IEditor::append()
{
	if (currentLineNumber == 1 && head != nullptr)
	{
		cout << currentLineNumber << "> ";
		CString in2;
		in2.input();
		(head->info) += in2;
		currentLineNumber++;
		currentLineRef = head->next;
	}
	else if (currentLineRef != nullptr && currentLineRef->next != nullptr)
	{
		cout << currentLineNumber << "> ";
		CString in2;
		in2.input();
		(currentLineRef->next->info) += in2;
		currentLineNumber++;
		currentLineRef = currentLineRef->next;
	}
}

void IEditor::modify()
{
	if (currentLineNumber == 1 && head != nullptr)
	{
		cout << currentLineNumber << "> ";
		CString in2;
		in2.input();
		head->info = move(in2);
		currentLineNumber++;
		currentLineRef = head;
	}
	else if (currentLineRef != nullptr && currentLineRef->next!=nullptr && currentLineNumber<=linesCount)
	{
		cout << currentLineNumber << "> ";
		CString in2;
		in2.input();
		currentLineRef->next->info = move(in2);
		currentLineNumber++;
		currentLineRef = currentLineRef->next;
	}
}

void IEditor::up1(CString&in)
{
	CString num(in.getData() + 3);
	int count = (long long int)num;
	if (currentLineNumber - count >= 1)
	{
		currentLineNumber = currentLineNumber - count;
		DNode<CString>*p = currentLineRef;
		while (count != 0)
		{
			currentLineRef = currentLineRef->prev;
			count--;
		}
	}
	else
	{
		currentLineNumber = 1;
		currentLineRef = nullptr;
	}
}

void IEditor::down1(CString & in)
{
	CString num(in.getData() + 3);
	int count = (long long int)num;
	if (currentLineNumber + count <= linesCount)
	{
		currentLineNumber = currentLineNumber + count;
		DNode<CString>*p = currentLineRef;
		while (count != 0)
		{
			currentLineRef = currentLineRef->next;
			count--;
		}
	}
	else
	{
		currentLineNumber = linesCount + 1;
		DNode<CString>*p = head;
		currentLineRef = nullptr;
		if (head->next != nullptr)
		{
			while (p != nullptr)
			{
				currentLineRef = p;
				p = p->next;
			}
		}
	}
}

void IEditor::remove()
{
	if (currentLineNumber == 1 && head != nullptr)
	{
		DNode<CString>*temp = head->next;
		delete head;
		head = temp;
		currentLineRef = head;
		linesCount = linesCount - 1;
	}
	else if (currentLineRef != nullptr && currentLineRef->next != nullptr)
	{
		DNode<CString>*temp = currentLineRef->next;
		currentLineRef->next = currentLineRef->next->next;
		if (currentLineRef->next != nullptr)
		{
			currentLineRef->next->prev = currentLineRef;
		}
		delete temp;
		linesCount = linesCount - 1;
	}
}

void IEditor::exit()
{
	ofstream ofs(fileName.getData());
	DNode<CString>*p = head;
	int i = 1;
	while (p != nullptr)
	{
		ofs << p->info;
		if (i != linesCount)
		{
			ofs << "\n";
		}
		p = p->next;
		i++;
	}
}

void IEditor::addElement(const CString& in)
{
	if (head == nullptr)
	{
		head = new DNode<CString>(in);
		currentLineRef = head;
	}
	else if (currentLineRef == nullptr)
	{
		DNode<CString>*x = new DNode<CString>(in);
		head->prev = x;
		x->next = head;
		head = x;
		currentLineRef = head;
	}
	else
	{
		DNode<CString>*x = new DNode<CString>(in);
		DNode<CString>*p = head;
		while (p != currentLineRef)
		{
			p = p->next;
		}
		x->next = p->next;
		p->next = x;
		x->prev = p;
		if (x->next != nullptr)
		{
			x->next->prev = x;
		}
		currentLineRef = x;
	}
	currentLineNumber++;
	linesCount++;
}

IEditor::~IEditor()
{
	if (head == nullptr)
	{
		return;
	}
	while (head != nullptr)
	{
		DNode<CString>*temp = head;
		if (head->next != nullptr)
		{
			head = head->next;
			head->prev = nullptr;
		}
		else
		{
			head = nullptr;
		}
		delete temp;
	}
	currentLineRef = nullptr;
	linesCount = 0;
	currentLineNumber = 1;
}