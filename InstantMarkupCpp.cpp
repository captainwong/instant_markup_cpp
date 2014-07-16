// InstantMarkupCpp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Handler.h"
#include "Rule.h"
#include "D:/global/deelx.h"
#include "HTMLRenderer.h"
#include "stdio.h"



class CParser
{
public:
	CParser(){}
	CParser(CHandler* handler){
		m_handler = handler;
	}
	~CParser(){
		for(iter_filter iter = m_filters.begin(); iter != m_filters.end(); iter++){
			pFilter p = *iter;
			delete p;
			p = NULL;
		}
		for(rule_iter riter = m_rules.begin(); riter != m_rules.end(); riter++){
			CRule *rule = *riter;
			delete rule;
			rule = NULL;
		}
	}
	void add_filter(const string& pattern, const string& name){
		pFilter p = new filter(pattern, name);
		m_filters.push_back(p);
	}
	void add_rule(CRule* rule){
		m_rules.push_back(rule);
	}
	void parse(istream& in){
		m_handler->start("document");
		std::string line;
		std::string block;
		typedef vector<string> _BLOCK;
		typedef vector<string>::iterator block_iter;
		_BLOCK blocks;
		while(std::getline(in, line)){
			//line = trim(line);
			if(!line.empty())
				block += line + '\n';
			else if(!block.empty()){
				blocks.push_back(block);
				block = "";
			}
		}

		for(block_iter biter = blocks.begin(); biter != blocks.end(); biter++){
			block = *biter;
			for(iter_filter fiter = m_filters.begin(); fiter != m_filters.end(); fiter++){
				pFilter p = *fiter;
				filtering(block, p->_pattern, p->_name, m_handler);
			}
			for(rule_iter riter = m_rules.begin(); riter != m_rules.end(); riter++){
				CRule *rule = *riter;
				if(rule->condition(block))
					if(rule->action(block, m_handler))
						break;
			}
		}
		m_handler->end("document");
	}
protected:
	string filtering(const string& block, const string& pattern,
				const string& sub_name, CHandler* handler){
		static CRegexpT <char> regexp(pattern.c_str());
		MatchResult result = regexp.MatchExact(block.c_str());
		if(result.IsMatched()){
			char* content = regexp.Replace(block.c_str(),
				handler->sub(sub_name).c_str());
			string new_block(content);
			delete content;
			return new_block;
		}
		return block;
	}
protected:
	//
	CHandler* m_handler;
	vector<CRule*> m_rules;
	typedef vector<CRule*>::iterator rule_iter;
	typedef struct _filter
	{
		string _pattern;
		string _name;
		_filter(const string& pattern, const string& name){
			_pattern = pattern;
			_name = name;
		}
	}filter, *pFilter;
	vector<pFilter> m_filters;
	typedef vector<pFilter>::iterator iter_filter;
};

class CBasicTextParser : public CParser
{
public:
	CBasicTextParser(CHandler* handler){
		m_handler = handler;
		add_rule(new CListRule());
		add_rule(new CListItemRule());
		add_rule(new CTitleRule());
		add_rule(new CHeadingRule());
		add_rule(new CParagraphRule());

		add_filter("\\*(.+?)\\*", "emphasis");
		add_filter("(http://[\\.a-zA-Z/]+)", "url");
		add_filter("([\\.a-zA-Z]+@[\\.a-zA-Z]+[a-zA-Z]+)", "mail");
	}
	virtual ~CBasicTextParser(){}
private:
	CBasicTextParser(){}
};

int main(int argc, char** argv)
{
	CHTMLRenderer handler;
	
	/*for(CHandler::funcmap_iter iter = CHandler::m_funcmap.begin(); 
		iter != CHandler::m_funcmap.end(); iter++)
	{
		cout << "key: " << iter->first << " value: " << iter->second << endl;
	}
	*/
	CBasicTextParser parser(&handler);
	parser.parse(cin);
	return 0;
}


