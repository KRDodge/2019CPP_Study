
// 3-1MFC_3View.h: CMy31MFC3View 클래스의 인터페이스
//

#pragma once


class CMy31MFC3View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy31MFC3View() noexcept;
	DECLARE_DYNCREATE(CMy31MFC3View)

// 특성입니다.
public:
	CMy31MFC3Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy31MFC3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_strOutput;
	CPoint m_ptLocation;
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CPoint m_ptClientSize;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 3-1MFC_3View.cpp의 디버그 버전
inline CMy31MFC3Doc* CMy31MFC3View::GetDocument() const
   { return reinterpret_cast<CMy31MFC3Doc*>(m_pDocument); }
#endif

