
// 3-1MFC_3View.cpp: CMy31MFC3View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "3-1MFC_3.h"
#endif

#include "3-1MFC_3Doc.h"
#include "3-1MFC_3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy31MFC3View

IMPLEMENT_DYNCREATE(CMy31MFC3View, CView)

BEGIN_MESSAGE_MAP(CMy31MFC3View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
//	ON_WM_NCRBUTTONDOWN()
ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMy31MFC3View 생성/소멸

CMy31MFC3View::CMy31MFC3View() noexcept : 
m_strOutput(_T("")), 
m_ptLocation(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy31MFC3View::~CMy31MFC3View()
{
}

BOOL CMy31MFC3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy31MFC3View 그리기

void CMy31MFC3View::OnDraw(CDC* pDC)
{
	CMy31MFC3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC->TextOut(m_ptLocation.x, m_ptLocation.y, m_strOutput);
}


// CMy31MFC3View 인쇄

BOOL CMy31MFC3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy31MFC3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy31MFC3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy31MFC3View 진단

#ifdef _DEBUG
void CMy31MFC3View::AssertValid() const
{
	CView::AssertValid();
}

void CMy31MFC3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy31MFC3Doc* CMy31MFC3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy31MFC3Doc)));
	return (CMy31MFC3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy31MFC3View 메시지 처리기


void CMy31MFC3View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int nCharIndex = m_strOutput.GetLength();

	if(nChar == VK_BACK)
	{
		m_strOutput.Delete(nCharIndex - 1, 1);
	}
	else
	{
		m_strOutput += (WCHAR)nChar;
	}
	Invalidate();

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CMy31MFC3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar)
	{
	case VK_LEFT:
		m_ptLocation.x--;
		break;

	case VK_RIGHT:
		m_ptLocation.x++;
		break;

	case VK_DOWN:
		m_ptLocation.y++;
		break;

	case VK_UP:
		m_ptLocation.y--;
		break;

	case VK_PRIOR:
		m_ptLocation.y -= 50;
		break;

	case VK_NEXT:
		m_ptLocation.y += 50;
		break;

	case VK_HOME:
		m_ptLocation = CPoint(0, 0);
		break;
	}

	if(m_ptLocation.x<0)
	{
		m_ptLocation.x = 0;
		AfxMessageBox(_T("Cannot Move Left"));
	}
	if(m_ptLocation.y<0)
	{
		m_ptLocation.y = 0;
		AfxMessageBox(_T("Cannot Move UP"));
	}
	if(m_ptLocation.x > m_ptClientSize.x)
	{
		m_ptLocation.x = m_ptClientSize.x;
		AfxMessageBox(_T("Cannot Move Right"));
	}
	if(m_ptLocation.y > m_ptClientSize.y)
	{
		m_ptLocation.y = m_ptClientSize.y;
		AfxMessageBox(_T("Cannot Move Down"));
	}


	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMy31MFC3View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_ptClientSize.x = cx;
	m_ptClientSize.y = cy;
	Invalidate();

}


void CMy31MFC3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ptLocation = point;
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


//void CMy31MFC3View::OnNcRButtonDown(UINT nHitTest, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CView::OnNcRButtonDown(nHitTest, point);
//}


void CMy31MFC3View::OnRButtonDown(UINT nFlags, CPoint point)
{
	if(m_strOutput.IsEmpty() == false )
	{
		if(AfxMessageBox(_T("DELETE ALL?"),MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			m_strOutput.Empty();
		}
	}
	else
	{
		AfxMessageBox(_T("INSERT TEXT"));
	}
	Invalidate();


	CView::OnRButtonDown(nFlags, point);
}
