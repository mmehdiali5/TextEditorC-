#ifndef IEDITOR_H
#define IEDITOR_H
#include"DNode.h"
#include"CString.h"

enum EditorCommands { LIST_ALL, UP,UP1,DOWN,DOWN1, OPEN, SAVE, EXIT, APPEND, REMOVE, MODIFY, NO_COMMAND };

class IEditor
{
	DNode<CString>*head=nullptr;
	int linesCount=0;
	int currentLineNumber=1;
	DNode<CString>*currentLineRef=nullptr;
	CString fileName = "Test.txt";
	void addElement(const CString&);
	int getCommand(const CString&)const;
	void listAll();
	void up();
	void down();
	void append();
	void modify();
	void up1(CString&);
	void down1(CString&);
	void remove();
	void exit();
public:
	void start();
	void setFileName(const CString&fn);
	CString getFileName();
	void create();
	void open();
	~IEditor();
};

#endif
