
// 3-1MFC_2View.cpp: CMy31MFC2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "3-1MFC_2.h"
#endif

#include "3-1MFC_2Doc.h"
#include "3-1MFC_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy31MFC2View

IMPLEMENT_DYNCREATE(CMy31MFC2View, CView)

BEGIN_MESSAGE_MAP(CMy31MFC2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMy31MFC2View 생성/소멸

CMy31MFC2View::CMy31MFC2View() noexcept : m_bTimerRun(false), m_bTimerType(true)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy31MFC2View::~CMy31MFC2View()
{
}

BOOL CMy31MFC2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy31MFC2View 그리기

void CMy31MFC2View::OnDraw(CDC* pDC)
{
	CMy31MFC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);
	pDC->DrawText(m_strTimer, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy31MFC2View 인쇄

BOOL CMy31MFC2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy31MFC2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy31MFC2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy31MFC2View 진단

#ifdef _DEBUG
void CMy31MFC2View::AssertValid() const
{
	CView::AssertValid();
}

void CMy31MFC2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy31MFC2Doc* CMy31MFC2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy31MFC2Doc)));
	return (CMy31MFC2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy31MFC2View 메시지 처리기


int CMy31MFC2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 1000, NULL);
	m_bTimerRun = true;

	return 0;
}




void CMy31MFC2View::OnTimer(UINT_PTR nIDEvent)
{
	int hour;
	CString str;
	CTime timer = CTime::GetCurrentTime();

	if(m_bTimerType)
	{
		m_strTimer.Format(_T("%d年 %d月 %d日 %d時 %d分 %d秒"), 
			timer.GetYear(), timer.GetMonth(), timer.GetDay(), 
			timer.GetHour(), timer.GetMinute(), timer.GetSecond());
	}
	else
	{
		hour = timer.GetHour();
		if(hour>=12)
		{
			str = _T("PM");
			if (hour >= 13)
			{
				hour -= 12;
			}
			else
			{
				str = _T("AM");
			}
		}
		m_strTimer.Format(_T("%s %d時 %d分 %d秒"), str, hour, timer.GetMinute(), timer.GetSecond());
	}

	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CMy31MFC2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bTimerType)
	{
		if(AfxMessageBox(_T("時分秒?"),MB_YESNO|MB_ICONQUESTION)==IDYES)
		{
			m_bTimerType = false;
		}
	}
	else
	{
		if(AfxMessageBox(_T("年月時分秒?"),MB_YESNO|MB_ICONQUESTION) ==IDYES)
		{
			m_bTimerType = true;
		}
	}
	

	CView::OnLButtonDown(nFlags, point);
}


void CMy31MFC2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	if(m_bTimerRun == false)
	{
		if(AfxMessageBox(_T("電自時械 作動?"),MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			SetTimer(1000,0,NULL);
			m_bTimerRun = true;
		}
	}
	else
	{
		if(AfxMessageBox(_T("電自時械 中止?"),MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			KillTimer(0);
			m_bTimerRun = false;
		}
	}

	CView::OnRButtonDown(nFlags, point);
}


void CMy31MFC2View::OnDestroy()
{
	CView::OnDestroy();

	if (m_bTimerRun)
		KillTimer(0);
}
