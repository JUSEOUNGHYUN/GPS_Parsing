
// GpsParsingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GpsParsing.h"
#include "GpsParsingDlg.h"
#include "afxdialogex.h"
#include "Wininet.h"
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_SET_GPS_TIME			WM_USER + 20
#define WM_SET_GGA_LATLON		WM_USER + 21
#define WM_HTML_VIEW			WM_USER + 22
#define UM_CUSTROM1			(WM_USER+25)	// 정의

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CGpsParsingDlg 대화 상자

CGpsParsingDlg::CGpsParsingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GPSPARSING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_map_api_select = 0;
}

void CGpsParsingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SATE_NUMBER1, m_staticSateNum1);
	DDX_Control(pDX, IDC_SATE_NUMBER2, m_staticSateNum2);
	DDX_Control(pDX, IDC_SATE_NUMBER3, m_staticSateNum3);
	DDX_Control(pDX, IDC_SATE_NUMBER4, m_staticSateNum4);
	DDX_Control(pDX, IDC_SATE_NUMBER5, m_staticSateNum5);
	DDX_Control(pDX, IDC_SATE_NUMBER6, m_staticSateNum6);
	DDX_Control(pDX, IDC_SATE_NUMBER7, m_staticSateNum7);
	DDX_Control(pDX, IDC_SATE_NUMBER8, m_staticSateNum8);
	DDX_Control(pDX, IDC_SATE_NUMBER9, m_staticSateNum9);
	DDX_Control(pDX, IDC_SATE_NUMBER10, m_staticSateNum10);
	DDX_Control(pDX, IDC_SATE_NUMBER11, m_staticSateNum11);
	DDX_Control(pDX, IDC_SATE_NUMBER12, m_staticSateNum12);

	DDX_Control(pDX, IDC_SNR1, m_staticSNR1);
	DDX_Control(pDX, IDC_SNR2, m_staticSNR2);
	DDX_Control(pDX, IDC_SNR3, m_staticSNR3);
	DDX_Control(pDX, IDC_SNR4, m_staticSNR4);
	DDX_Control(pDX, IDC_SNR5, m_staticSNR5);
	DDX_Control(pDX, IDC_SNR6, m_staticSNR6);
	DDX_Control(pDX, IDC_SNR7, m_staticSNR7);
	DDX_Control(pDX, IDC_SNR8, m_staticSNR8);
	DDX_Control(pDX, IDC_SNR9, m_staticSNR9);
	DDX_Control(pDX, IDC_SNR10, m_staticSNR10);
	DDX_Control(pDX, IDC_SNR11, m_staticSNR11);
	DDX_Control(pDX, IDC_SNR12, m_staticSNR12);

	DDX_Control(pDX, IDC_PROGRESS1, m_progressSNR1);
	DDX_Control(pDX, IDC_PROGRESS2, m_progressSNR2);
	DDX_Control(pDX, IDC_PROGRESS3, m_progressSNR3);
	DDX_Control(pDX, IDC_PROGRESS4, m_progressSNR4);
	DDX_Control(pDX, IDC_PROGRESS5, m_progressSNR5);
	DDX_Control(pDX, IDC_PROGRESS6, m_progressSNR6);
	DDX_Control(pDX, IDC_PROGRESS7, m_progressSNR7);
	DDX_Control(pDX, IDC_PROGRESS8, m_progressSNR8);
	DDX_Control(pDX, IDC_PROGRESS9, m_progressSNR9);
	DDX_Control(pDX, IDC_PROGRESS10, m_progressSNR10);
	DDX_Control(pDX, IDC_PROGRESS11, m_progressSNR11);
	DDX_Control(pDX, IDC_PROGRESS12, m_progressSNR12);
}

BEGIN_MESSAGE_MAP(CGpsParsingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILE_OPEN, &CGpsParsingDlg::OnBnClickedFileOpen)
	ON_MESSAGE(WM_SET_GPS_TIME, &CGpsParsingDlg::SetGpsTimer)
	ON_MESSAGE(WM_SET_GGA_LATLON, &CGpsParsingDlg::SetLatLon)
	ON_MESSAGE(WM_HTML_VIEW, &CGpsParsingDlg::SetHTML)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_START, &CGpsParsingDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_GOOGLE_RADIO, &CGpsParsingDlg::OnBnClickedGoogleRadio)
	ON_BN_CLICKED(IDC_DAUM_RADIO, &CGpsParsingDlg::OnBnClickedDaumRadio)
END_MESSAGE_MAP()


// CGpsParsingDlg 메시지 처리기

BOOL CGpsParsingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	this->SetWindowText(_T("Mini GPS"));

	m_cur_filePointer = 0;

	// progress Control 범위 지정
	m_progressSNR1.SetRange(0, 100);
	m_progressSNR2.SetRange(0, 100);
	m_progressSNR3.SetRange(0, 100);
	m_progressSNR4.SetRange(0, 100);
	m_progressSNR5.SetRange(0, 100);
	m_progressSNR6.SetRange(0, 100);
	m_progressSNR7.SetRange(0, 100);
	m_progressSNR8.SetRange(0, 100);
	m_progressSNR9.SetRange(0, 100);
	m_progressSNR10.SetRange(0, 100);
	m_progressSNR11.SetRange(0, 100);
	m_progressSNR12.SetRange(0, 100);

	/*
	CHtmlViewDlg* pHtmlDlg = (CHtmlViewDlg*)AfxGetMainWnd();
	pHtmlDlg->Create(IDD_HTML_VIEW_DIALOG1, CWnd::GetDesktopWindow());
	
	m_pHtmlDlg = new CHtmlViewDlg(this);
	m_pHtmlDlg->setter(this);
	m_pHtmlDlg->Create(IDD_HTML_VIEW_DIALOG1, CWnd::GetDesktopWindow());
	*/

	// pHtmlDlg->setter(pHtmlDlg->m_dlg2_hWnd->GetSafeHwnd());

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGpsParsingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGpsParsingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGpsParsingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

std::string CGpsParsingDlg::AddColon(std::string strTemp)
{
	// TODO: 여기에 구현 코드 추가.
	strTemp.insert(2, ":");
	strTemp.insert(5, ":");

	return strTemp;
}

std::string CGpsParsingDlg::Date(std::string str)
{
	// TODO: 여기에 구현 코드 추가.
	std::string strTemp = "20";
	strTemp += str;

	strTemp.insert(4, "/");
	strTemp.insert(7, "/");

	return strTemp;
}

std::string CGpsParsingDlg::strDotSubstr(std::string strTemp)
{
	// TODO: 여기에 구현 코드 추가.
	int pos;

	pos = strTemp.rfind('.');
	std::string first = strTemp.substr(0, pos);

	return first;
}

std::string CGpsParsingDlg::kNotsDecimalPoint(std::string str, float kNots)
{
	// TODO: 여기에 구현 코드 추가.
	float fSpd = stof(str);
	fSpd *= kNots;

	std::string strTemp = std::to_string(fSpd);

	int pos;

	pos = strTemp.find('.');
	std::string first = strTemp.substr(0, pos + 1);
	std::string second = strTemp.substr(pos + 1);

	second.erase(second.begin() + 1, second.end());
	std::string stre = first + second;

	return stre;
}

std::string CGpsParsingDlg::strFileFormatDotSubstr(std::string strTemp)
{
	// TODO: 여기에 구현 코드 추가.
	int pos;

	pos = strTemp.rfind(',');
	std::string first = strTemp.substr(pos + 1);
	return  first;
}

std::string CGpsParsingDlg::SubstrAsteriscus(std::string strTemp)
{
	// TODO: 여기에 구현 코드 추가.
	std::string first = strFileFormatDotSubstr(strTemp);

	int pos = first.find('*');
	std::string data = first.substr(0, pos);

	return data;
}

std::string CGpsParsingDlg::MovePeriod(std::string strTemp)
{
	std::string str2;

	int len = strTemp.length();
	int pos = strTemp.find('.');

	std::string first = strTemp.substr(0, pos);
	first.insert(first.end() - 2, 1, '.');
	std::string second = strTemp.substr(pos + 1);

	str2 = first + second;

	return str2;
}

std::string CGpsParsingDlg::SubstrFileName(std::string str)
{
	int pos = str.rfind('\\');
	std::string second = str.substr(pos + 1);

	return second;
}

std::string CGpsParsingDlg::FileName(std::string str)
{
	int pos = str.rfind('.');

	std::string first = str.substr(0, pos + 1);

	return first;
}

void CGpsParsingDlg::OnBnClickedFileOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR fileFilter[] = _T("nmea(*.nmea)|*.nmea|");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT, fileFilter);

	if (dlg.DoModal() == IDOK)
	{
		m_strPathName = dlg.GetPathName(); // MFC 파일열기 대화상자(CFileDialog) 선택한 파일의 전체 경로 반환.
		m_strPath = std::string(CT2CA(m_strPathName));
		
	}
}

void CGpsParsingDlg::OnBnClickedStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetTimer(GPS_TIMER, 100, NULL);// 

	m_htmlView.DoModal();
}


void CGpsParsingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{

	case GPS_TIMER:

		::PostMessage(this->m_hWnd, WM_SET_GPS_TIME, 0, 0);
		break;

	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CGpsParsingDlg::SetHTML(WPARAM wParam, LPARAM lParam) {

	SetViewHtml();

	return 0;
}

LRESULT CGpsParsingDlg::SetGpsTimer(WPARAM wParam, LPARAM lParam) {

	ParsingNMEAData();

	return 0;
}

LRESULT CGpsParsingDlg::SetLatLon(WPARAM wParam, LPARAM lParam)
{
	if (m_map_api_select == 0)
	{
		Google_Map();
	}
	else
	{
		Daum_Map();
	}

	return 0;
}

// 1 move file pointer from previous fp position
// - 이전 fp 위치에서 파일 포인터를 이동합니다.
// 
// 2 read text line from nmea file
// - nmea 파일에서 텍스트 줄을 읽습니다.
// 
// 3 check time read line text and previous read line data
// - 라인 텍스트를 읽은 시간과 이전에 읽은 라인 데이터를 확인합니다.
// 
// 4 if time data is diffrent then save fp, update ui and quit function
// - 시간 데이터가 다른 경우 fp를 저장하고 ui를 업데이트하고 기능을 종료합니다.

void CGpsParsingDlg::ParsingNMEAData()
{
	// TODO: 여기에 구현 코드 추가.
	char data[100]{};
	m_fp = fopen(m_strPath.c_str(), "rb");

	fseek(m_fp, 0, SEEK_END);
	m_FileSize = ftell(m_fp);

	fseek(m_fp, m_cur_filePointer, SEEK_SET);

	std::string strGGATime;
	std::string strRMCTime;
	std::string timeData = "0";
	std::string initSateNum = "0";
	std::string initSNR = "0";
	int nCnt = 0;

	if (m_fp == NULL)
	{
		AfxMessageBox(_T("File not Found\n"));
	}

	std::string strGSVSNR[12]{};
	std::string strGSASate[12]{};
	int GSVcount = 0;

	while (fgets(data, sizeof(data), m_fp) != NULL)
	{
		std::string strTemp(data);
		SetDlgItemTextW(IDC_GPS_DATA, CA2CT(strTemp.c_str()));

		std::list<std::string> gpsList;

		std::string strGroup[20]{};
		std::string separator = ",";
		std::string result;
		int cur_position = 0;
		int count = 0;
		int position;

		while ((position = strTemp.find(separator, cur_position)) != std::string::npos) {

			int len = position - cur_position;
			result = strTemp.substr(cur_position, len);
			gpsList.push_back(result);
			cur_position = position + 1;
		}

		gpsList.push_back(SubstrAsteriscus(strTemp));

		int listSize = gpsList.size();

		for (int i = 0; i < listSize; i++)
		{
			strGroup[i] = gpsList.front();
			gpsList.pop_front();
		}

		// GGA
		if (strTemp[3] == 'G' && strTemp[4] == 'G' && strTemp[5] == 'A')
		{
			strGGATime = AddColon(strGroup[1]);

			std::string strDotGGATime = strDotSubstr(strGGATime);
			// timeData = strDotSubstr(strGGATime);

			if (timeData == "0" || timeData == strDotGGATime)
			{
				SetDlgItemTextW(IDC_EDIT_TIME, CA2CT(strGGATime.c_str()));
				m_strGGALat = MovePeriod(strGroup[2]);
				SetDlgItemTextW(IDC_EDIT_LAT, CA2CT(m_strGGALat.c_str()));
				m_strGGALon = MovePeriod(strGroup[4]);


				m_listNMEADataGGALat.push_back(m_strGGALat);
				m_listNMEADataGGALon.push_back(m_strGGALon);
				::PostMessage(this->m_hWnd, WM_SET_GGA_LATLON, 0, 0);

				SetDlgItemTextW(IDC_EDIT_LON, CA2CT(m_strGGALon.c_str()));
				std::string strGGAFixType = strGroup[6];
				SetDlgItemTextW(IDC_EDIT_FIXTYPE, CA2CT(strGGAFixType.c_str()));
				std::string strGGAAlt = strGroup[9] + " m";
				SetDlgItemTextW(IDC_EDIT_ALT, CA2CT(strGGAAlt.c_str()));
			}
			else
			{
				break;
			}
		}

		// GSA
		else if (strTemp[3] == 'G' && strTemp[4] == 'S' && strTemp[5] == 'A')
		{
			for (int i = 0; i < 12; i++)
			{
				strGSASate[i] = strGroup[i + 3];
				if (strGSASate[i] == "")
				{
					strGSASate[i] = "0";
				}
			}

			m_staticSateNum1.SetWindowTextW(CA2CT(strGSASate[0].c_str()));
			m_staticSateNum2.SetWindowTextW(CA2CT(strGSASate[1].c_str()));
			m_staticSateNum3.SetWindowTextW(CA2CT(strGSASate[2].c_str()));
			m_staticSateNum4.SetWindowTextW(CA2CT(strGSASate[3].c_str()));
			m_staticSateNum5.SetWindowTextW(CA2CT(strGSASate[4].c_str()));
			m_staticSateNum6.SetWindowTextW(CA2CT(strGSASate[5].c_str()));
			m_staticSateNum7.SetWindowTextW(CA2CT(strGSASate[6].c_str()));
			m_staticSateNum8.SetWindowTextW(CA2CT(strGSASate[7].c_str()));
			m_staticSateNum9.SetWindowTextW(CA2CT(strGSASate[8].c_str()));
			m_staticSateNum10.SetWindowTextW(CA2CT(strGSASate[9].c_str()));
			m_staticSateNum11.SetWindowTextW(CA2CT(strGSASate[10].c_str()));
			m_staticSateNum12.SetWindowTextW(CA2CT(strGSASate[11].c_str()));

			std::string strGSA_HDOP = strGroup[15];
			SetDlgItemTextW(IDC_EDIT_HDOP, CA2CT(strGSA_HDOP.c_str()));
		}

		// RMC
		else if (strTemp[3] == 'R' && strTemp[4] == 'M' && strTemp[5] == 'C')
		{
			strRMCTime = AddColon(strGroup[1]);

			std::string strDotRMCTime = strDotSubstr(strRMCTime);
			timeData = strDotSubstr(strRMCTime);

			if (timeData == "0" || timeData == strDotRMCTime)
			{
				std::string strRMCSpd = strGroup[7];
				float kNots = 1.852;
				std::string num_str = kNotsDecimalPoint(strRMCSpd, kNots);
				SetDlgItemTextW(IDC_EDIT_SPD, CA2CT(num_str.c_str()));
				std::string strRMCDate = Date(strGroup[9]);
				SetDlgItemTextW(IDC_EDIT_DATE, CA2CT(strRMCDate.c_str()));
			}
			else
			{
				break;
			}
		}

		// GSV
		else if (strTemp[3] == 'G' && strTemp[4] == 'S' && strTemp[5] == 'V')
		{

			std::string countGSV = strGroup[1];
			int oneTextLen = strTemp.size();
			count = stoi(countGSV);

			if (strGSVSNR->empty())
			{
				for (int i = 0; i < oneTextLen / ((i + 1) * 4); i++)
				{
					if (strGSASate[i] == strGroup[(i + 1) * 4])
					{
						strGSVSNR[i] = strGroup[((i + 1) * 4) + 3];
						GSVcount++;
					}
					else
					{
						break;
					}
					//std::cout << strGSVSNR[i] << " ";
				}
			}
			else
			{
				for (int i = 0; i < oneTextLen / ((i + 1) * 4); i++)
				{
					if (strGSASate[i + GSVcount] == strGroup[(i + 1) * 4])
					{
						strGSVSNR[i + GSVcount] = strGroup[((i + 1) * 4) + 3];

					}
					else
					{
						break;
					}
					//std::cout << strGSVSNR[i] << " ";
				}
			}

			nCnt++;

			if (nCnt > 0 && count > 0 && nCnt == count)
			{
				for (int i = 0; i < 12; i++)
				{
					if (strGSVSNR[i] == "")
					{
						strGSVSNR[i] = "0";
					}
				}

				int SNR1 = stoi(strGSVSNR[0]);
				m_staticSNR1.SetWindowTextW(CA2CT(strGSVSNR[0].c_str()));
				m_progressSNR1.SetPos(SNR1);

				int SNR2 = stoi(strGSVSNR[1]);
				m_staticSNR2.SetWindowTextW(CA2CT(strGSVSNR[1].c_str()));
				m_progressSNR2.SetPos(SNR2);

				int SNR3 = stoi(strGSVSNR[2]);
				m_staticSNR3.SetWindowTextW(CA2CT(strGSVSNR[2].c_str()));
				m_progressSNR3.SetPos(SNR3);

				int SNR4 = stoi(strGSVSNR[3]);
				m_staticSNR4.SetWindowTextW(CA2CT(strGSVSNR[3].c_str()));
				m_progressSNR4.SetPos(SNR4);

				int SNR5 = stoi(strGSVSNR[4]);
				m_staticSNR5.SetWindowTextW(CA2CT(strGSVSNR[4].c_str()));
				m_progressSNR5.SetPos(SNR5);

				int SNR6 = stoi(strGSVSNR[5]);
				m_staticSNR6.SetWindowTextW(CA2CT(strGSVSNR[5].c_str()));
				m_progressSNR6.SetPos(SNR6);

				int SNR7 = stoi(strGSVSNR[6]);
				m_staticSNR7.SetWindowTextW(CA2CT(strGSVSNR[6].c_str()));
				m_progressSNR7.SetPos(SNR7);

				int SNR8 = stoi(strGSVSNR[7]);
				m_staticSNR8.SetWindowTextW(CA2CT(strGSVSNR[7].c_str()));
				m_progressSNR8.SetPos(SNR8);

				int SNR9 = stoi(strGSVSNR[8]);
				m_staticSNR9.SetWindowTextW(CA2CT(strGSVSNR[8].c_str()));
				m_progressSNR9.SetPos(SNR9);

				int SNR10 = stoi(strGSVSNR[9]);
				m_staticSNR10.SetWindowTextW(CA2CT(strGSVSNR[9].c_str()));
				m_progressSNR10.SetPos(SNR10);

				int SNR11 = stoi(strGSVSNR[10]);
				m_staticSNR11.SetWindowTextW(CA2CT(strGSVSNR[10].c_str()));
				m_progressSNR11.SetPos(SNR11);

				int SNR12 = stoi(strGSVSNR[11]);
				m_staticSNR12.SetWindowTextW(CA2CT(strGSVSNR[11].c_str()));
				m_progressSNR12.SetPos(SNR12);
			} // if (nCnt >0 &&  count > 0 && nCnt==count)
		}

		m_cur_filePointer = ftell(m_fp);
	} // while (fgets(data, sizeof(data), m_fp) != NULL)

	fclose(m_fp);
}

void CGpsParsingDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	KillTimer(GPS_TIMER);
}

void CGpsParsingDlg::OnBnClickedGoogleRadio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_map_api_select = 0;

	//m_pHtmlDlg->DoModal();
}

void CGpsParsingDlg::OnBnClickedDaumRadio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_map_api_select = 1;
	//m_pHtmlDlg->DoModal();
}

void CGpsParsingDlg::Google_Map()
{
	CStdioFile file;
	int cnt = 0;
	int cnt2 = 0;

	float sumLat = 0;
	float sumLon = 0;
	float avgLat = 0;
	float avgLon = 0;
	float Lat = 0;
	float Lon = 0;

	int GGALatCount = m_listNMEADataGGALat.size();
	int GGALonCount = m_listNMEADataGGALon.size();

	CString CGGALatCount;
	CGGALatCount.Format(_T("%d"), GGALatCount);

	std::string* strGroupGGALat = new std::string[GGALatCount];
	std::string* strGroupGGALon = new std::string[GGALonCount];

	std::list<std::string>::iterator iterLat = m_listNMEADataGGALat.begin();
	std::list<std::string>::iterator iterLon = m_listNMEADataGGALon.begin();

	int i;
	for (i = 0; i < GGALatCount; iterLat++, i++)
	{
		strGroupGGALat[i] = (*iterLat);

		//m_listNMEADataGGALat.pop_front();

		Lat = stof(strGroupGGALat[i]);
		sumLat += Lat;
	}

	avgLat = sumLat / GGALatCount;
	CString CavgLat;
	CavgLat.Format(_T("%f"), avgLat);

	int j;
	for (j = 0; j < GGALatCount; iterLon++, j++)
	{
		strGroupGGALon[j] = (*iterLon);
		//m_listNMEADataGGALon.pop_front();

		Lon = stof(strGroupGGALon[j]);
		sumLon += Lon;
	}

	avgLon = sumLon / GGALonCount;
	CString CavgLon;
	CavgLon.Format(_T("%f"), avgLon);

	TCHAR chFilePath[256]{};
	GetModuleFileName(NULL, chFilePath, 256);

	CString strFolderPath(chFilePath);
	strFolderPath = strFolderPath.Left(strFolderPath.ReverseFind('\\'));
	std::string strTmp = FileName(SubstrFileName(std::string(CT2CA(m_strPathName)))) + "html";
	CString strPure = (CA2CT(strTmp.c_str()));
	m_total = strFolderPath + "\\" + strPure;

	DeleteFile(m_total);
	file.Open(m_total, CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite | CStdioFile::typeText);

	file.WriteString(_T("<!DOCTYPE html>\n"));
	file.WriteString(_T("<html>\n"));
	file.WriteString(_T("<head>\n"));
	file.WriteString(_T("\t<title>Google Maps</title>\n"));
	file.WriteString(_T("\t<style type='text/css'>\n"));
	file.WriteString(_T("\t#map {\n"));
	file.WriteString(_T("\t\theight: 400px;\n"));
	file.WriteString(_T("\t\twidth: 100%;\n"));
	file.WriteString(_T("\t}\n"));
	file.WriteString(_T("</style>\n"));
	file.WriteString(_T("<script>\n"));
	file.WriteString(_T("\tfunction initMap() {\n"));

	file.WriteString(_T("\t\tconst map = new google.maps.Map(document.getElementById('map'), {\n"));
	file.WriteString(_T("\t\t zoom: 14,\n"));
	file.WriteString(_T("\t\tcenter: { lat: ") + CavgLat + _T(", lng: ") + CavgLon + _T("},\n"));
	file.WriteString(_T("})\n"));
	file.WriteString(_T("for (var i = 0; i < locations.length; i++) {\n"));
	file.WriteString(_T("var marker = new google.maps.Marker({\n"));
	file.WriteString(_T("\tmap: map,\n"));
	file.WriteString(_T("\tlabel: locations[i].place,\n"));
	file.WriteString(_T("\tposition: new google.maps.LatLng(locations[i].lat, locations[i].lng),\n"));
	file.WriteString(_T("});\n"));
	file.WriteString(_T("}\n"));
	file.WriteString(_T("}\n"));
	file.WriteString(_T("const locations = [\n"));

	for (int i = 0; i < GGALatCount; i++)
	{
		CString inf;
		inf.Format(_T("%d"), i + 1);
		file.WriteString(_T("{ place: '") + inf + _T("', lat: ") + CA2CT(strGroupGGALat[i].c_str()) + _T(", lng: ") + CA2CT(strGroupGGALon[i].c_str()) + _T("},\n"));
	}

	file.WriteString(_T("];\n"));
	file.WriteString(_T("</script>\n"));
	file.WriteString(_T("</head>\n"));
	file.WriteString(_T("<body>\n"));
	file.WriteString(_T("<h3>구글 맵</h3>\n"));
	file.WriteString(_T("<div id='map'></div>\n"));
	file.WriteString(_T("<script\n"));
	file.WriteString(_T("\tsrc=\"https://maps.googleapis.com/maps/api/js?key=AIzaSyA4hsvZYX9o06po2yHuroa_P0l0_d9aceo&callback=initMap&libraries=&v=weekly\"\n"));
	file.WriteString(_T("\tasync></script>\n"));
	file.WriteString(_T("</body>\n"));
	file.WriteString(_T("\n"));
	file.WriteString(_T("</html>\n"));

	::PostMessage(this->m_hWnd, WM_HTML_VIEW, 0, 0);

	delete[] strGroupGGALat;
	delete[] strGroupGGALon;
	file.Close();
}

void CGpsParsingDlg::Daum_Map()
{
	CStdioFile file;

	CString cGGALon = CA2CT(m_strGGALon.c_str());
	CString cGGALat = CA2CT(m_strGGALat.c_str());

	float sumLat = 0;
	float sumLon = 0;
	float avgLat = 0;
	float avgLon = 0;
	float Lat = 0;
	float Lon = 0;

	int GGALatCount = m_listNMEADataGGALat.size();
	int GGALonCount = m_listNMEADataGGALon.size();

	CString CGGALatCount;
	CGGALatCount.Format(_T("%d"), GGALatCount);

	std::string* strGroupGGALat = new std::string[GGALatCount];
	std::string* strGroupGGALon = new std::string[GGALonCount];

	std::list<std::string>::iterator iterLat = m_listNMEADataGGALat.begin();
	std::list<std::string>::iterator iterLon = m_listNMEADataGGALon.begin();


	int i;
	for (i = 0; i < GGALatCount; iterLat++, i++)
	{
		strGroupGGALat[i] = (*iterLat);

		//m_listNMEADataGGALat.pop_front();


		Lat = stof(strGroupGGALat[i]);
		sumLat += Lat;
	}

	avgLat = sumLat / GGALatCount;
	CString CavgLat;
	CavgLat.Format(_T("%f"), avgLat);

	int j;
	for (j = 0; j < GGALatCount; iterLon++, j++)
	{
		strGroupGGALon[j] = (*iterLon);
		//m_listNMEADataGGALon.pop_front();

		Lon = stof(strGroupGGALon[j]);
		sumLon += Lon;
	}

	avgLon = sumLon / GGALonCount;
	CString CavgLon;
	CavgLon.Format(_T("%f"), avgLon);

	TCHAR chFilePath[256]{};
	GetModuleFileName(NULL, chFilePath, 256);

	CString strFolderPath(chFilePath);
	strFolderPath = strFolderPath.Left(strFolderPath.ReverseFind('\\'));
	std::string strTmp = FileName(SubstrFileName(std::string(CT2CA(m_strPathName)))) + "html";
	CString strPure = (CA2CT(strTmp.c_str()));
	m_total = strFolderPath + "\\" + strPure;

	DeleteFile(m_total);

	file.Open(m_total, CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite | CStdioFile::typeText);
	file.WriteString(_T("<!DOCTYPE html>\n"));
	file.WriteString(_T("<html>\n"));
	file.WriteString(_T("<head>\n"));
	file.WriteString(_T("\t<meta charset='utf-8'>\n"));
	file.WriteString(_T("\t<title>Multi-Position Mark</title>\n"));
	file.WriteString(_T("</html>\n"));
	file.WriteString(_T("<body>\n"));
	file.WriteString(_T("<div id='map' style='width:100 %; height:350px;'></div>\n"));
	file.WriteString(_T("<script type='text/javascript' src='https://dapi.kakao.com/v2/maps/sdk.js?appkey=31b4550cf25c251d62cae2a593f6ac38'></script>\n"));
	file.WriteString(_T("<script>\n"));
	file.WriteString(_T("var mapContainer = document.getElementById('map'),\n"));
	file.WriteString(_T("\tmapOption = {\n"));
	file.WriteString(_T("\t\tcenter: new kakao.maps.LatLng(") + CavgLat + _T(", ") + CavgLon + _T("),\n"));
	file.WriteString(_T("\t\tlevel: 6\n"));
	file.WriteString(_T("\t};\n"));
	file.WriteString(_T("var map = new kakao.maps.Map(mapContainer, mapOption);\n"));
	file.WriteString(_T("var positions = [\n"));
	for (int i = 0; i < GGALatCount; i++)
	{
		CString inf;
		CString GGALat = CA2CT(strGroupGGALat[i].c_str());
		CString GGALon = CA2CT(strGroupGGALon[i].c_str());
		inf.Format(_T("%d"), i + 1);
		file.WriteString(_T("\t{\n"));
		file.WriteString(_T("\t\ttitle: '") + inf + _T("',\n"));
		file.WriteString(_T("\t\tlatlng: new kakao.maps.LatLng(") + GGALat + _T(", ") + GGALon + _T(")\n"));
		file.WriteString(_T("\t},\n"));
	}
	file.WriteString(_T("];\n"));
	file.WriteString(_T("var imageSrc = 'https://t1.daumcdn.net/localimg/localimages/07/mapapidoc/markerStar.png'; \n"));
	file.WriteString(_T("\n"));
	file.WriteString(_T("for (var i = 0; i < positions.length; i ++) {\n"));
	file.WriteString(_T("var imageSize = new kakao.maps.Size(24, 35);\n"));
	file.WriteString(_T("var markerImage = new kakao.maps.MarkerImage(imageSrc, imageSize);\n"));
	file.WriteString(_T("var marker = new kakao.maps.Marker({\n"));
	file.WriteString(_T("map: map,\n"));
	file.WriteString(_T("position: positions[i].latlng,\n"));
	file.WriteString(_T("title : positions[i].title,\n"));
	file.WriteString(_T("image : markerImage\n"));
	file.WriteString(_T("});\n"));
	file.WriteString(_T("}\n"));
	file.WriteString(_T("</script>\n"));
	file.WriteString(_T("</body>\n"));
	file.WriteString(_T("</html>\n"));

	::PostMessage(this->m_hWnd, WM_HTML_VIEW, 0, 0);

	delete[] strGroupGGALat;
	delete[] strGroupGGALon;
	file.Close();
}

void CGpsParsingDlg::SetViewHtml()
{
	DWORD m_NetConnectCheck = NULL;
	BOOL m_NetWork = NULL;

	if (InternetGetConnectedState(&m_NetConnectCheck, 0))
	{
		m_NetWork = TRUE;
		if ((m_NetConnectCheck & INTERNET_CONNECTION_OFFLINE) != 0)
		{
			m_NetWork = FALSE;
		}
	}
	else
	{
		m_NetWork = FALSE;
	}

	if (m_NetWork)
	{
		CRect m_map_rc;
		GetDlgItem(IDC_EXPLORER_HTML_VIEW)->GetWindowRect(m_map_rc);
		ScreenToClient(m_map_rc);

		m_map_html_view = new explorerview();
		m_map_html_view->Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, m_map_rc, this, 20008);
		m_map_html_view->OnInitialUpdate();
	}
	else
	{
		AfxMessageBox(_T("Not connecting Network. GPS Maps disable mode"));
	}
}