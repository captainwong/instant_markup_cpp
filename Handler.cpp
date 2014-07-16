// Handler.cpp: implementation of the CHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Handler.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
map<string, CHandler::pFunc> CHandler::m_funcmap;
map<string, CHandler::pFuncSub> CHandler::m_funcsubmap;


CHandler::CHandler()
{

}

CHandler::~CHandler()
{

}

void CHandler::callback(const string &str)
{
	/*if(m_funcmap.count(str))
		(this->*(m_funcmap[str]))();
	else
		cout << "invalid function name." << endl;
	*/

	funcmap_iter iter = m_funcmap.find(str);
	if(iter != m_funcmap.end())
		(this->*(iter->second))();
	else
		cout << "invalid function name : " << str << endl;
}

void CHandler::start(const string &func_name)
{
	callback(string("CHTMLRenderer::start_") + func_name);
}

void CHandler::end(const string &func_name)
{
	callback(string("CHTMLRenderer::end_") + func_name);
}

void CHandler::feed(const string &block)
{
	cout << block << endl;
}

string CHandler::sub(const string &sub_name)
{
	return callback_sub(string("CHTMLRenderer::sub_") + sub_name);
}

string CHandler::callback_sub(const string &str)
{
	funcsubmap_iter iter = m_funcsubmap.find(str);
	if(iter != m_funcsubmap.end())
		return (this->*(iter->second))();
	else
		cout << "invalid sub name : " << str << endl;
	return "$001";
}
