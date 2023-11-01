// explorerview.cpp : implementation file
//

#include "stdafx.h"
#include "GpsParsingDlg.h"
#include "explorerview.h"
//#include "MapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// explorerview

IMPLEMENT_DYNCREATE(explorerview, CHtmlView)

explorerview::explorerview()
{
	//{{AFX_DATA_INIT(explorerview)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

explorerview::~explorerview()
{

}

void explorerview::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(explorerview)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(explorerview, CHtmlView)
	//{{AFX_MSG_MAP(explorerview)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// explorerview diagnostics

#ifdef _DEBUG
void explorerview::AssertValid() const
{
	CHtmlView::AssertValid();
}

void explorerview::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// explorerview message handlers

void explorerview::OnInitialUpdate() 
{
	CGpsParsingDlg* pDlg = (CGpsParsingDlg*)AfxGetMainWnd();

	Navigate2(pDlg->m_total, NULL, NULL);
}

void explorerview::OnDocumentComplete(LPCTSTR lpszURL) 
{
	CHtmlView::OnDocumentComplete(lpszURL);
}

void explorerview::OnDestroy() 
{
	CHtmlView::OnDestroy();
}
