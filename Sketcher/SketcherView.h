#pragma once

#include "SketcherDoc.h"
#include "Elements.h"

class CSketcherView : public CView
{
protected:
	CSketcherView() noexcept;
	DECLARE_DYNCREATE(CSketcherView)

	// 멤버 변수
	CPoint m_FirstPoint;   // 첫 번째 점
	CPoint m_SecondPoint;  // 두 번째 점
	CElement* m_pTempElement; // 임시 요소 포인터

// 특성입니다.
public:
	CSketcherDoc* GetDocument() const;

	// 작업입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 그리기 함수
	CElement* CreateElement();     // 요소 생성 함수

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
	afx_msg void OnColorBlack();
	afx_msg void OnColorBlue();
	afx_msg void OnColorGreen();
	afx_msg void OnColorRed();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SketcherView.cpp의 디버그 버전
inline CSketcherDoc* CSketcherView::GetDocument() const
{
	return reinterpret_cast<CSketcherDoc*>(m_pDocument);
}
#endif
