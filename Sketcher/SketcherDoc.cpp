
// SketcherDoc.cpp: CSketcherDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#endif

#include "SketcherDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSketcherDoc

IMPLEMENT_DYNCREATE(CSketcherDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketcherDoc, CDocument)
	ON_COMMAND(ID_COLOR_BLACK, &CSketcherDoc::OnColorBlack)
	ON_COMMAND(ID_COLOR_BLUE, &CSketcherDoc::OnColorBlue)
	ON_COMMAND(ID_COLOR_GREEN, &CSketcherDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_RED, &CSketcherDoc::OnColorRed)
	ON_COMMAND(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnElementCircle)
	ON_COMMAND(ID_ELEMENT_CURVE, &CSketcherDoc::OnElementCurve)
	ON_COMMAND(ID_ELEMENT_LINE, &CSketcherDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnElementRectangle)

	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CSketcherDoc::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CSketcherDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CSketcherDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CSketcherDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnUpdateElementCircle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CURVE, &CSketcherDoc::OnUpdateElementCurve)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CSketcherDoc::OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnUpdateElementRectangle)
END_MESSAGE_MAP()


// CSketcherDoc 생성/소멸

CSketcherDoc::CSketcherDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CSketcherDoc::~CSketcherDoc()
{
}

BOOL CSketcherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CSketcherDoc serialization

void CSketcherDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CSketcherDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CSketcherDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSketcherDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSketcherDoc 진단

#ifdef _DEBUG
void CSketcherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketcherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketcherDoc 명령

void CSketcherDoc::OnColorBlack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Color = BLACK; // 드로잉 색을 검은색으로 설정
}


void CSketcherDoc::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Color = BLUE;
}


void CSketcherDoc::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Color = GREEN;
}


void CSketcherDoc::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Color = RED;
}


void CSketcherDoc::OnElementCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Element = CIRCLE;
}


void CSketcherDoc::OnElementCurve()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Element = CURVE;
}


void CSketcherDoc::OnElementLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Element = LINE;
}


void CSketcherDoc::OnElementRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_Element = RECTANGLE;
}


void CSketcherDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_Color == BLACK);
}


void CSketcherDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_Color == BLUE);
}


void CSketcherDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_Color == GREEN);
}


void CSketcherDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_Color == RED);
}


void CSketcherDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_Element == CIRCLE);
}


void CSketcherDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_Element == CURVE);
}


void CSketcherDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_Element == LINE);
}


void CSketcherDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_Element == RECTANGLE);
}
