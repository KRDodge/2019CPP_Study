﻿
// 3-1MFC_2View.h: CMy31MFC2View 클래스의 인터페이스
//

#pragma once


class CMy31MFC2View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy31MFC2View() noexcept;
	DECLARE_DYNCREATE(CMy31MFC2View)

// 특성입니다.
public:
	CMy31MFC2Doc* GetDocument() const;

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
	virtual ~CMy31MFC2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool m_bTimerRun;
	bool m_bTimerType;
	CString m_strTimer;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // 3-1MFC_2View.cpp의 디버그 버전
inline CMy31MFC2Doc* CMy31MFC2View::GetDocument() const
   { return reinterpret_cast<CMy31MFC2Doc*>(m_pDocument); }
#endif

