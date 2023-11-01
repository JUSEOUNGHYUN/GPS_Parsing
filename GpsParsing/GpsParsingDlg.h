
// GpsParsingDlg.h: 헤더 파일
//

#pragma once
#pragma warning(disable:4996)

#include <iostream>
#include <cstdio>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <list>
#include "stdafx.h"
#include "pch.h"
#include "explorerview.h"
#include "CHtmlViewDlg.h";

#define GPS_TIMER		100

// CGpsParsingDlg 대화 상자
class CGpsParsingDlg : public CDialogEx
{
// 생성입니다.
public:
	CGpsParsingDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CString m_strPathName;
	std::string m_strPath;
	FILE* m_fp;
	int m_cur_filePointer;
	int m_nCnt = 0;
	int m_map_api_select;

	int m_FileSize;
	std::string m_strGGALat;	// 위도 = 가로
	std::string m_strGGALon;	// 경도 = 세로

	CString m_total;

	explorerview* m_map_html_view;
	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GPSPARSING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFileOpen();
	std::string AddColon(std::string strTemp);
	std::string Date(std::string str);
	std::list<std::string>m_listNMEADataSateNum;
	std::list<std::string> m_listNMEADataGGALat;
	std::list<std::string> m_listNMEADataGGALon;

	afx_msg LRESULT SetGpsTimer(WPARAM wParam, LPARAM lParam);	
	afx_msg LRESULT SetLatLon(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT SetHTML(WPARAM wParam, LPARAM lParam);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedStart();

	afx_msg void OnBnClickedGoogleRadio();
	afx_msg void OnBnClickedDaumRadio();
	
	void ParsingNMEAData();
	void Google_Map();
	void Daum_Map();
	void SetViewHtml();

	std::string strDotSubstr(std::string strTemp);
	std::string kNotsDecimalPoint(std::string str, float kNots);
	std::string strFileFormatDotSubstr(std::string strTemp);
	std::string SubstrAsteriscus(std::string strTemp);
	std::string MovePeriod(std::string strTemp);
	std::string SubstrFileName(std::string str);
	std::string FileName(std::string str);

	CStatic m_staticSateNum1;
	CStatic m_staticSateNum2;
	CStatic m_staticSateNum3;
	CStatic m_staticSateNum4;
	CStatic m_staticSateNum5;
	CStatic m_staticSateNum6;
	CStatic m_staticSateNum7;
	CStatic m_staticSateNum8;
	CStatic m_staticSateNum9;
	CStatic m_staticSateNum10;
	CStatic m_staticSateNum11;
	CStatic m_staticSateNum12;

	CStatic m_staticSNR1;
	CStatic m_staticSNR2;
	CStatic m_staticSNR3;
	CStatic m_staticSNR4;
	CStatic m_staticSNR5;
	CStatic m_staticSNR6;
	CStatic m_staticSNR7;
	CStatic m_staticSNR8;
	CStatic m_staticSNR9;
	CStatic m_staticSNR10;
	CStatic m_staticSNR11;
	CStatic m_staticSNR12;

	CProgressCtrl m_progressSNR1;
	CProgressCtrl m_progressSNR2;
	CProgressCtrl m_progressSNR3;
	CProgressCtrl m_progressSNR4;
	CProgressCtrl m_progressSNR5;
	CProgressCtrl m_progressSNR6;
	CProgressCtrl m_progressSNR7;
	CProgressCtrl m_progressSNR8;
	CProgressCtrl m_progressSNR9;
	CProgressCtrl m_progressSNR10;
	CProgressCtrl m_progressSNR11;
	CProgressCtrl m_progressSNR12;

	CHtmlViewDlg m_htmlView;
};
