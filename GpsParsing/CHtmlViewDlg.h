#include "afxdialogex.h"
#pragma once

class CGpsParsingDlg;	// 
// CHtmlViewDlg 대화 상자

class CHtmlViewDlg : public CDialog
{
	DECLARE_DYNAMIC(CHtmlViewDlg)

public:
	CHtmlViewDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHtmlViewDlg();

	// 부모 클래스 setter 선언
	CGpsParsingDlg* m_pMainDlg;
	void setter(CGpsParsingDlg* dlg)
	{
		m_pMainDlg = dlg;
	}

	// 자식에게 사용자 지정 메시지 함수와 메시지 선언
	afx_msg LRESULT CHtmlViewDlg::OnUwmCustom1(WPARAM wParam, LPARAM lParam);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HTML_VIEW_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
