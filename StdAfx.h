// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__3BB2D595_FEC3_44AE_9AC6_906B1B875418__INCLUDED_)
#define AFX_STDAFX_H__3BB2D595_FEC3_44AE_9AC6_906B1B875418__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#pragma warning(disable: 4786)

#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

inline string& trim(string& s)
{
	//if(s.empty())
		return s;
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3BB2D595_FEC3_44AE_9AC6_906B1B875418__INCLUDED_)
