# 📛 GPS_Parsing

📍 프로젝트 기간 : 2023.07.10 ~ 2023.10.01 (3개월)

# 📌 개요
 - c++ fopen, fread를 공부를 하던 도중 NMEA 데이터를 byte별로 쪼개서 fread를 하면 제대로 공부가 될것을 예상해 이 프로그램을 기획하게 되었습니다.
- NMEA 데이터를 fread하고, 데이터(GGA, GSA, RMC, GSV etc)를 Parsing후 각각 경도,위도를 추출했습니다.
- html에 그 데이터를 주입하여 html에 마크업이 되는 기능을 구현했습니다.

# 🛠️ 기술 및 도구
<img src="https://img.shields.io/badge/C++-00599C?style=flat-square&logo=C Sharp&logoColor=white"/> <img src="https://img.shields.io/badge/MFC-239120?style=flat-square&logo=MFC&logoColor=white"/> <img src="https://img.shields.io/badge/html-E34F26?style=flat-square&logo=HTML5&logoColor=white"/> <img src="https://img.shields.io/badge/NMEA-000000?style=flat-square&logo=NMEA&logoColor=white"/>

# 🎏 기능 구현
- GPS Data(NEMA) Parsing
- Load in Google Map, Kakao Map
- Set View html
- File Read (fopen, fseek, fread, fgets)

### 0. 기본 화면

![Basic Screen](https://github.com/JUSEOUNGHYUN/GPS_Parsing/assets/80812790/28a46cf0-2751-485e-8bc2-5f2e6b627b9f)

### 1. GPS 데이터(NMEA) Parsing후 html 파일 생성
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
     
             // for문 = html에 위도, 경도 데이터 주입
    	for (int i = 0; i < GGALatCount; i++)
    	{
    		CString inf;
    		CString GGALat = CA2CT(strGroupGGALat[i].c_str()); // 위도 
    		CString GGALon = CA2CT(strGroupGGALon[i].c_str()); // 경도
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

#### 1.1 파일 생성

![화면 캡처 2023-11-02 013915](https://github.com/JUSEOUNGHYUN/GPS_Parsing/assets/80812790/2350b7c3-4ab2-4b7c-8ad8-af03c4b41cb3)

#### 1.2 html에 위치 데이터 마크업
    var positions = [
    	{
    		title: '1',
    		latlng: new kakao.maps.LatLng(33.30344, 126.29545)
    	},
    	...........
    	{
    		title: '40',
    		latlng: new kakao.maps.LatLng(33.28140, 126.31317)
    	},
    ];

### 2. SetViewHtml()
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

### 3. GPS 위치 데이터 마크업 html (카카오 지도)

![화면 캡처 2023-11-02 014037](https://github.com/JUSEOUNGHYUN/GPS_Parsing/assets/80812790/9876dff4-4e88-4efe-bb61-6d8b180b95ef)

### 4. GPS 위치 데이터 마크업 html (구글 지도)

![google map](https://github.com/JUSEOUNGHYUN/GPS_Parsing/assets/80812790/55166722-d56a-4804-af77-f214eeb619df)

### 5. 컴파일

![gps_1](https://github.com/JUSEOUNGHYUN/GPS_Parsing/assets/80812790/3012a40e-aecb-44d7-9187-b9ddee384879)
