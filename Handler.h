// Handler.h: interface for the CHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HANDLER_H__34541A43_717C_4364_A442_73AEA7D9B715__INCLUDED_)
#define AFX_HANDLER_H__34541A43_717C_4364_A442_73AEA7D9B715__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define pfunc (CHandler::*)


class CHandler  
{
public:
	typedef void (CHandler::*pFunc)();
	typedef string (CHandler::*pFuncSub)();
	virtual string sub(const string& sub_name);
	virtual void feed(const string& block);
	virtual void end(const string& func_name);
	virtual void start(const string& func_name);
	CHandler();
	virtual ~CHandler();
	static map<string, pFunc> m_funcmap;
	static map<string, pFuncSub> m_funcsubmap;
	typedef map<string, pFunc>::iterator funcmap_iter;
	typedef map<string, pFuncSub>::iterator funcsubmap_iter;
protected:
	string callback_sub(const string& str);
	void callback(const string& str);
};

#define STR(str) #str
#define ASSIGN_FUNC(func_name) \
	CHandler::m_funcmap[STR(func_name)] = (CHandler::pFunc)&func_name;
#define ASSIGN_FUNC_SUB(func_name) \
	CHandler::m_funcsubmap[STR(func_name)] = (CHandler::pFuncSub)&func_name;

#endif // !defined(AFX_HANDLER_H__34541A43_717C_4364_A442_73AEA7D9B715__INCLUDED_)
