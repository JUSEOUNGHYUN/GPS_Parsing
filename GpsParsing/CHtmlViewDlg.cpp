// CHtmlViewDlg.cpp: 구현 파일
//

//#include "afxdialogex.h"
#include "pch.h"
#include "GpsParsing.h"
#include "CHtmlViewDlg.h"
#include "GpsParsingDlg.h"

#define UM_CUSTROM1		(WM_USER+25)	// 정의

// CHtmlViewDlg 대화 상자

IMPLEMENT_DYNAMIC(CHtmlViewDlg, CDialog)

CHtmlViewDlg::CHtmlViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_HTML_VIEW_DIALOG1, pParent)
{

}

CHtmlViewDlg::~CHtmlViewDlg()
{
}

void CHtmlViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHtmlViewDlg, CDialog)
	ON_MESSAGE(UM_CUSTROM1, &CHtmlViewDlg::OnUwmCustom1)
END_MESSAGE_MAP()


LRESULT CHtmlViewDlg::OnUwmCustom1(WPARAM wParam, LPARAM lParam)
{
	MessageBox(_T("Recieve Message!"), 0, 0);
	return 0;
}

// CHtmlViewDlg 메시지 처리기


BOOL CHtmlViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
