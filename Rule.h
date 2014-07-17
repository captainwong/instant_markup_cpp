// Rule.h: interface for the CRule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULE_H__A43BBCAB_07B1_4953_B5D8_3FC886AF1D1F__INCLUDED_)
#define AFX_RULE_H__A43BBCAB_07B1_4953_B5D8_3FC886AF1D1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHandler;
class CRule  
{
public:
	virtual bool condition(const string& block) = 0;
	virtual bool action(const string& block, CHandler* handler);
	CRule();
	virtual ~CRule();
protected:
	string m_type;
};

class CHeadingRule : public CRule
{
public:
	CHeadingRule() {	m_type = "heading";	}
	virtual ~CHeadingRule(){}
	virtual bool condition(const string& block){
		do{
			if(block.find('\n') != string::npos)
				break;
			if(block.length() > 70)
				break;
			if(block[block.size() - 1] == ':')
				break;
			return true;
		}while(0);
		return false;
	}
};

class CTitleRule : public CHeadingRule
{
public:
	CTitleRule() : m_bFirst(true) { m_type = "title"; }
	virtual ~CTitleRule(){}
	virtual bool condition(const string& block){
		if(!m_bFirst)
			return false;
		m_bFirst = true;
		return CHeadingRule::condition(block);
	}
private:
	bool m_bFirst;
};

class CListItemRule : public CRule
{
public: 
	CListItemRule() { m_type = "listitem"; }
	virtual ~CListItemRule(){}
	virtual bool condition(const string& block){
		return block[0] == '-';
	}
	virtual bool action(const string& block, CHandler* handler);
};

class CListRule : public CListItemRule
{
public:
	CListRule() : m_bInside(false) { m_type = "list"; }
	virtual ~CListRule(){}
	virtual bool condition(const string& block){
		return true;
	}
	virtual bool action(const string& block, CHandler* handler);
private:
	bool m_bInside;
};

class CParagraphRule : public CRule
{
public:
	CParagraphRule() { m_type = "paragraph"; }
	virtual ~CParagraphRule(){}
	virtual bool condition(const string& blcok){
		return true;
	}
};

#endif // !defined(AFX_RULE_H__A43BBCAB_07B1_4953_B5D8_3FC886AF1D1F__INCLUDED_)
