
// SketcherDoc.h: CSketcherDoc 클래스의 인터페이스
//


#pragma once


class CSketcherDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CSketcherDoc() noexcept;
	DECLARE_DYNCREATE(CSketcherDoc)

	// 특성입니다.
public:

protected:
	COLORREF m_Color;
	WORD m_Element;
	int m_PenWidth = 1;

	// 작업입니다.
public:
	WORD GetElementType() const
	{
		return m_Element;
	}

	COLORREF GetElementColor() const
	{
		return m_Color;
		
	}

	int GetPenWidth() const {
		return m_PenWidth;
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

};
