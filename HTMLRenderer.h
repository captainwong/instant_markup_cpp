// HTMLRenderer.h: interface for the CHTMLRenderer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLRENDERER_H__8B02E39C_638E_41DB_9BB1_472043E20F16__INCLUDED_)
#define AFX_HTMLRENDERER_H__8B02E39C_638E_41DB_9BB1_472043E20F16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Handler.h"

class CHTMLRenderer : public CHandler  
{
public:
	string sub_mail();
	string sub_url();
	string sub_emphasis();
	void end_title();
	void start_title();
	void end_listitem();
	void start_listitem();
	void end_list();
	void start_list();
	void end_heading();
	void start_heading();
	void end_paragraph();
	void start_paragraph();
	void end_document();
	void start_document();
	CHTMLRenderer();
	virtual ~CHTMLRenderer();

};

#endif // !defined(AFX_HTMLRENDERER_H__8B02E39C_638E_41DB_9BB1_472043E20F16__INCLUDED_)
