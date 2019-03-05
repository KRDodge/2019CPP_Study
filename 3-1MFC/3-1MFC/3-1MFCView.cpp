
// 3-1MFCView.cpp: CMy31MFCView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "3-1MFC.h"
#endif

#include "3-1MFCDoc.h"
#include "3-1MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy31MFCView

IMPLEMENT_DYNCREATE(CMy31MFCView, CView)

BEGIN_MESSAGE_MAP(CMy31MFCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy31MFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMy31MFCView 생성/소멸

CMy31MFCView::CMy31MFCView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy31MFCView::~CMy31MFCView()
{
}

BOOL CMy31MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy31MFCView 그리기

void CMy31MFCView::OnDraw(CDC* pDC)
{
	CMy31MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC->TextOut(10, 10, m_strWindowSize);
	CRect rect;
	GetClientRect(&rect);
	pDC->DrawText(m_strOutput, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	
	pDC->TextOut(m_ptMouseMove.x, m_ptMouseMove.y, m_strPointText);

}


// CMy31MFCView 인쇄


void CMy31MFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy31MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy31MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy31MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMy31MFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy31MFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy31MFCView 진단

#ifdef _DEBUG
void CMy31MFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMy31MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy31MFCDoc* CMy31MFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy31MFCDoc)));
	return (CMy31MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy31MFCView 메시지 처리기


void CMy31MFCView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_strWindowSize.Format(_T("윈도우 크기는 넓이 %d, 높이 %d입니다."), cx, cy);
	Invalidate(); //화면 갱신

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMy31MFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDrag = true;
	m_strOutput = _T("왼쪽 마우스 버튼을 눌렀습니다.");
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


void CMy31MFCView::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_strOutput = _T("오른쪽 마우스 버튼을 눌렀습니다.");
	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}


void CMy31MFCView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	m_strOutput = _T("키보드가 눌렸습니다.");
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMy31MFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bDrag == true)
	{
		m_strOutput = _T("마우스를 드래그하고 있습니다.");
	}
	else
	{
		m_strOutput = _T("마우스를 이동 중 입니다.");
	}

	m_ptMouseMove = point;
	CView::OnSize(nFlags, point.x, point.y);
	m_strPointText.Format(_T("X:%d Y:%d"), point.x, point.y);

	Invalidate();
	CView::OnMouseMove(nFlags, point);
}


void CMy31MFCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDrag = false;
	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}
