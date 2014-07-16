// HTMLRenderer.cpp: implementation of the CHTMLRenderer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HTMLRenderer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHTMLRenderer::CHTMLRenderer()
{
	ASSIGN_FUNC(CHTMLRenderer::start_document);
	ASSIGN_FUNC(CHTMLRenderer::end_document);
	ASSIGN_FUNC(CHTMLRenderer::start_paragraph);
	ASSIGN_FUNC(CHTMLRenderer::end_paragraph);
	ASSIGN_FUNC(CHTMLRenderer::start_heading);
	ASSIGN_FUNC(CHTMLRenderer::end_heading);
	ASSIGN_FUNC(CHTMLRenderer::start_list);
	ASSIGN_FUNC(CHTMLRenderer::end_list);
	ASSIGN_FUNC(CHTMLRenderer::start_listitem);
	ASSIGN_FUNC(CHTMLRenderer::end_listitem);
	ASSIGN_FUNC(CHTMLRenderer::start_title);
	ASSIGN_FUNC(CHTMLRenderer::end_title);
	ASSIGN_FUNC_SUB(CHTMLRenderer::sub_emphasis);
	ASSIGN_FUNC_SUB(CHTMLRenderer::sub_url);
	ASSIGN_FUNC_SUB(CHTMLRenderer::sub_mail);
}

CHTMLRenderer::~CHTMLRenderer()
{

}

void CHTMLRenderer::start_document()
{
	cout << "<html><head><title>instant_markup</title></head><body>" << endl;
}

void CHTMLRenderer::end_document()
{
	cout << "</body></html>" << endl;
}

void CHTMLRenderer::start_paragraph()
{
	cout << "<p>" << endl;
}

void CHTMLRenderer::end_paragraph()
{
	cout << "</p>" << endl;
}

void CHTMLRenderer::start_heading()
{
	cout << "<h2>" << endl;
}

void CHTMLRenderer::end_heading()
{
	cout << "</h2>" << endl;
}

void CHTMLRenderer::start_list()
{
	cout << "<ul>" << endl;
}

void CHTMLRenderer::end_list()
{
	cout << "</ul>" << endl;
}

void CHTMLRenderer::start_listitem()
{
	cout << "<li>" << endl;
}

void CHTMLRenderer::end_listitem()
{
	cout << "</li>" << endl;
}

void CHTMLRenderer::start_title()
{
	cout << "<h1>" << endl;
}

void CHTMLRenderer::end_title()
{
	cout << "</h1>" << endl;
}

string CHTMLRenderer::sub_emphasis(const string &content)
{
	return "<em>$001</em>\n";
}

string CHTMLRenderer::sub_url(const string &content)
{
	return "<a href=\"$001\">$001</a>\n";
}

string CHTMLRenderer::sub_mail(const string &content)
{
	return "<a href=\"mailto:$001\">$001</a>\n";
}

