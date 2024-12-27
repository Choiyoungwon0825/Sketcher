#pragma once

#include "SketcherDoc.h"
#include "Elements.h"

class CSketcherView : public CScrollView
{
protected:
	CSketcherView() noexcept;
	DECLARE_DYNCREATE(CSketcherView)

	// 멤버 변수
	CPoint m_FirstPoint;   // 첫 번째 점
	CPoint m_SecondPoint;  // 두 번째 점
	CElement* m_pTempElement; // 임시 요소 포인터
	CElement* m_pSelected;		// 현재 선택된 요소
	BOOL m_MoveMode;			// 요소 플래그 이동
	CPoint m_CursorPos;			// 커서 위치
	CPoint m_FirstPos;			// move 작업에서의 원래 위치
	int m_Scale; // 현재 view Scale

// 특성입니다.
public:
	CSketcherDoc* GetDocument() const;

	// 작업입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 그리기 함수

protected:
	CElement* CreateElement();     //새로운 요소를 힙 위에 생성한다.
	CElement* SelectElement(CPoint aPoint);		// 요소를 선택한다.
	void MoveElement(CClientDC& aDC, const CPoint& point);	//요소를 이동시킨다.

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 구현입니다.
public:
	virtual ~CSketcherView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual void OnInitialUpdate();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSendtoBack();
	void OnViewScale();
	afx_msg void OnMove();
	afx_msg void OnDelete();
	void ResetScrollSizes();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
};

#ifndef _DEBUG  // SketcherView.cpp의 디버그 버전
inline CSketcherDoc* CSketcherView::GetDocument() const
{
	return reinterpret_cast<CSketcherDoc*>(m_pDocument);
}
#endif