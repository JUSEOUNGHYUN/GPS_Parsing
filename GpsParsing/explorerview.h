#if !defined(AFX_EXPLORERVIEW_H__6F4A7396_7052_4704_A2A6_3339B5D09AEB__INCLUDED_)
#define AFX_EXPLORERVIEW_H__6F4A7396_7052_4704_A2A6_3339B5D09AEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// explorerview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// explorerview html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class explorerview : public CHtmlView
{
protected:
	DECLARE_DYNCREATE(explorerview)

// html Data
public:
	//{{AFX_DATA(explorerview)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(explorerview)
	public:
	virtual void OnInitialUpdate();
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	explorerview();
	virtual ~explorerview();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(explorerview)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLORERVIEW_H__6F4A7396_7052_4704_A2A6_3339B5D09AEB__INCLUDED_)
