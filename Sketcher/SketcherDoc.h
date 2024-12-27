// SketcherDoc.h: CSketcherDoc 클래스의 인터페이스

#pragma once
#include "Elements.h"

class CSketcherDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CSketcherDoc() noexcept;
	DECLARE_DYNCREATE(CSketcherDoc)

	// 특성입니다.
public:

protected:
	COLORREF m_Color; // 현재 드로잉 색깔
	WORD m_Element;	  // 현재 요소 형식
	int m_PenWidth;
	CSize m_DocSize;

	CTypedPtrList<CObList, CElement*> m_ElementList; // 요소 리스트

	// 작업입니다.
public:
	WORD GetElementType() const
	{
		return m_Element; // 요소 형식을 얻는다.
	}

	COLORREF GetElementColor() const
	{
		return m_Color;  // 요소 색깔을 얻는다.

	}

	int GetPenWidth() const {
		return m_PenWidth;
	}

	void AddElement(CElement* pElement) {
		m_ElementList.AddTail(pElement); // 요소를 리스트에 추가한다.
	}

	void DeleteElement(CElement* pElement); // 요소를 삭제한다.

	void CSketcherDoc::SendToBack(CElement* pElement);

	POSITION GetListHeadPosition() const {
		return m_ElementList.GetHeadPosition();
	}

	CElement* GetNext(POSITION& aPos) const {
		return m_ElementList.GetNext(aPos); // 현재 요소 포인터를 리턴한다.
	}

	POSITION GetListTailPosition() const {
		return m_ElementList.GetTailPosition();	// 리스트 끝의 POSITION 값을 리턴
	}

	CElement* GetPrev(POSITION& aPos) const {
		return m_ElementList.GetPrev(aPos);	// 현재 요소 포인터를 리턴한다.
	}
	CSize GetDocSize() const {
		return m_DocSize;
	}

	// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// 구현입니다.
public:
	virtual ~CSketcherDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	// 생성된 메시지 맵 함수
protected:
	//{{AFX_MSG(CSketcherDoc)
	afx_msg void OnColorBlack();
	afx_msg void OnColorBlue();
	afx_msg void OnColorGreen();
	afx_msg void OnColorRed();
	afx_msg void OnElementCircle();
	afx_msg void OnElementCurve();
	afx_msg void OnElementLine();
	afx_msg void OnElementRectangle();
	afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementCurve(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementRectangle(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnPenwidth();
	afx_msg void OnElementText();
	afx_msg void OnUpdateElementText(CCmdUI *pCmdUI);
};
