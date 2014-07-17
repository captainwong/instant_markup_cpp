// Rule.cpp: implementation of the CRule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Rule.h"
#include "Handler.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRule::CRule()
{

}

CRule::~CRule()
{

}

bool CRule::action(const string &block, CHandler *handler)
{
	if(handler){
		handler->start(m_type);
		handler->feed(block);
		handler->end(m_type);
		return true;
	}
	return false;
}

bool CListItemRule::action(const string& block, CHandler* handler)
{
	handler->start(m_type);
	handler->feed(block.substr(1, block.size() - 1));
	handler->end(m_type);
	return true;
}

bool CListRule::action(const string& block, CHandler* handler)
{
	if(!m_bInside && CListItemRule::condition(block)){
		handler->start(m_type);
		m_bInside = true;
	}else if(m_bInside && !CListItemRule::condition(block)){
		handler->end(m_type);
		m_bInside = false;
	}
	return false;
}
