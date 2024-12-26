
// SketcherView.cpp: CSketcherView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#endif

#include "SketcherDoc.h"
#include "SketcherView.h"
#include "Elements.h"
#include "CScaleDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketcherView

IMPLEMENT_DYNCREATE(CSketcherView, CScrollView)

BEGIN_MESSAGE_MAP(CSketcherView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CSketcherView 생성/소멸

CSketcherView::CSketcherView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_FirstPoint = CPoint(0, 0); // 처음으로 기록된 점을 0,0으로 설정한다.
	m_SecondPoint = CPoint(0, 0); // 두번째로 기록된 점을 0,0으로 설정한다.
	m_pTempElement = NULL; // 임시 요소 포인터를 0으로 설정한다.
	m_pSelected = NULL;		// 초기에 어떤 요소도 선택되지 않았다.
	m_MoveMode = FALSE;		// 이동 모드를 off로 설정한다.
	m_CursorPos = CPoint(0, 0);		// 0으로 초기화한다.
	m_FirstPos = CPoint(0, 0);		// 0으로 초기화한다.
	m_Scale = 1; // scale을 1:1로 설정한다.
	SetScrollSizes(MM_TEXT, CSize(0, 0)); // 임의의 스크롤러 설정한다.

}

CSketcherView::~CSketcherView()
{

}

BOOL CSketcherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSketcherView 그리기

void CSketcherView::OnDraw(CDC* pDC)
{
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION aPos = pDoc->GetListHeadPosition();
	CElement* pElement = 0; // 요소 포인터를 저장한다.
	while (aPos) {			// aPos가 null이 아닌 한 루프를 돈다.

		pElement = pDoc->GetNext(aPos); // 현재 요소 포인터를 얻는다.

		// 요소가 보인다면
		if (pDC->RectVisible(pElement->GetBoundRect()))
			pElement->Draw(pDC, m_pSelected); // 현재 요소를 그린다.
	}
}


// CSketcherView 인쇄


void CSketcherView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSketcherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSketcherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSketcherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

// CSketcherView 진단
#ifdef _DEBUG
void CSketcherView::AssertValid() const
{
	CView::AssertValid();
}

void CSketcherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketcherDoc* CSketcherView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketcherDoc)));
	return (CSketcherDoc*)m_pDocument;
}
#endif //_DEBUG


void CSketcherView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 뷰에 대한 Device Context 객체를 정의한다.
	CClientDC aDC(this);
	OnPrepareDC(&aDC);				// 원점이 조정되도록 한다.

	// 만약 우리가 이동 모드에 있다면 선택된 요소를 이동시키고 리턴한다.
	if (m_MoveMode)
	{
		aDC.DPtoLP(&point);			// 논리 좌표로 변환시킨다.
		MoveElement(aDC, point);	// 요소를 이동시킨다.
		return;
	}

	if ((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		aDC.DPtoLP(&point);			// 점이 논리 좌표로 변환
		m_SecondPoint = point;     // Save the current cursor position

		if (m_pTempElement)
		{
			if (CURVE == GetDocument()->GetElementType())
			{
				// 곡선을 그리고있다.
				// 그러므로 세그먼트를 기존 곡선에 추가한다.
				(static_cast<CCurve*>(m_pTempElement))->AddSegment(m_SecondPoint);
				m_pTempElement->Draw(&aDC);	// 이제, 그것을 그린다.
				return;						// 작업이 끝났다.
			}
			aDC.SetROP2(R2_NOTXORPEN); // 드로잉 모드를 설정한다.

			// Redraw the old element so it disappears from the view
			m_pTempElement->Draw(&aDC);
			delete m_pTempElement;        // Delete the old element
			m_pTempElement = 0;           // Reset the pointer to 0

		}

		// Create a temporary element of the type and color that
		// is recorded in the document object, and draw it
		m_pTempElement = CreateElement();  // Create a new element
		m_pTempElement->Draw(&aDC);        // Draw the element
	}
	else				// 우리는 요소를 그리고있다.
	{					// 그러므로 반전시킨다.
		CRect aRect;
		CElement* pCurrentSelection = SelectElement(point);

		if (pCurrentSelection != m_pSelected)
		{
			if (m_pSelected)	// 이전 요소가 선택되었는가?
			{
				aRect = m_pSelected->GetBoundRect(); // 범위를 정하는 직사각형을 얻는다.
				aDC.LPtoDP(aRect);					// 디바이스 좌표로 변환시킨다.
				aRect.NormalizeRect();				// 노말라이즈한다.
				InvalidateRect(aRect, FALSE);		// 영역을 무효화한다.
			}
			m_pSelected = pCurrentSelection;		// 커서 밑에 있는 요소를 저장한다.

			if (m_pSelected)
			{
				aRect = m_pSelected->GetBoundRect(); // 범위를 정하는 직사각형을 얻는다.
				aDC.LPtoDP(aRect);					// 디바이스 좌표로 변환시킨다.
				aRect.NormalizeRect();				// 노말라이즈한다.
				InvalidateRect(aRect, FALSE);		// 영역을 무효화한다.
			}
		}
	}
}


void CSketcherView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (this == GetCapture())
		ReleaseCapture(); // 마우스 포착중단

	// 만약 요소가 있다면 그것을 도큐먼트에 추가한다.
	if (m_pTempElement)
	{
		GetDocument()->AddElement(m_pTempElement);
		GetDocument()->UpdateAllViews(0, 0, m_pTempElement);
		// 모든 뷰들에게 알린다.

		m_pTempElement = 0; // 요소 포인터 리셋
	}

}


void CSketcherView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC aDC(this); // 디바이스 컨텍스트를 생성한다.
	OnPrepareDC(&aDC);	 // 원점이 조정되도록 한다.
	aDC.DPtoLP(&point);  // 점이 논리 좌표로 변환한다.

	if (m_MoveMode)
	{
		// 이동 모드에 있다. 그러므로 요소를 드롭한다.
		m_MoveMode = FALSE; // 이동 모드를 죽인다.
		m_pSelected = 0;	// 요소를 선택한 것을 취소시킨다.
		GetDocument()->UpdateAllViews(0); // 모든 뷰들을 다시 그린다.
	}
	else {
		m_FirstPoint = point; // 현재 위치를 기록한다.
		SetCapture();		  // 이후에 나타나는 마우스 메시지를 포착한다.
	}

}



CElement* CSketcherView::CreateElement()
{
	//TRACE("CreateElement() 호출됨\n");
	// 이 뷰에 대한 도큐먼트 포인터를 얻는다.
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); // 포인터가 좋다는 것을 확인한다.

	// 도큐먼트 안에 저장되어 잇는 형식을 사용하여 요소를 선택한다.
	switch (pDoc->GetElementType())
	{
	case RECTANGLE:
		//TRACE("요소 타입: RECTANGLE\n");
		return new CRectangle(m_FirstPoint, m_SecondPoint, pDoc->GetElementColor(), pDoc->GetPenWidth());

	case CIRCLE:
		//TRACE("요소 타입: CIRCLE\n");
		return new CCircle(m_FirstPoint, m_SecondPoint, pDoc->GetElementColor(), pDoc->GetPenWidth());

	case CURVE:
		//TRACE("요소 타입: CURVE\n");
		return new CCurve(m_FirstPoint, m_SecondPoint, pDoc->GetElementColor(), pDoc->GetPenWidth());

	case LINE:
		//TRACE("요소 타입: LINE\n");
		return new CLine(m_FirstPoint, m_SecondPoint, pDoc->GetElementColor(), pDoc->GetPenWidth());

	default:
		// 무엇인가 잘못됨

		AfxMessageBox("잘못된 접근", MB_OK);
		AfxAbort();
		return NULL;
	}
}




void CSketcherView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// 가리켜지고 있는 요소에 대한 영역이 있다면 그것을 무효화시킨다.
	// 그렇지 않으면 전체 영역을 무효화시킨다ㅣ.
	if (pHint)
	{
		CClientDC aDC(this); // 디바이스 컨텍스트를 생성한다.
		OnPrepareDC(&aDC);	 // 원점이 조정되도록 한다.

		// 둘러싸는 직사각형을 얻고, 그것을 클라이언트 좌표로 변환한다.
		CRect aRect = static_cast<CElement*>(pHint)->GetBoundRect();
		aDC.LPtoDP(aRect);
		aRect.NormalizeRect();
		InvalidateRect(aRect);	// 영역이 다시 그려지게 한다.
	}
	else
		InvalidateRect(0);
}


void CSketcherView::OnInitialUpdate()
{
	ResetScrollSizes();		// 스크롤바를 설정한다.
	CScrollView::OnInitialUpdate();
}


void CSketcherView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 커서 메뉴를 생성한다.
	CMenu aMenu;
	aMenu.LoadMenu(IDR_CURSOR_MENU);		// 커서 메뉴를 로드한다.
	ClientToScreen(&point);					// 화면 좌표호 변환한다.
	
	//팝업을 커서 위치에 나타낸다.
	if (m_pSelected)
		aMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			point.x, point.y, this);
	else {
		// 색깔 메뉴 항목을 검사한다.
		COLORREF Color = GetDocument()->GetElementColor();
		aMenu.CheckMenuItem(ID_COLOR_BLACK,
			(BLACK == Color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		aMenu.CheckMenuItem(ID_COLOR_RED,
			(RED == Color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		aMenu.CheckMenuItem(ID_COLOR_GREEN,
			(GREEN == Color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		aMenu.CheckMenuItem(ID_COLOR_BLUE,		
			(BLUE == Color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);

		// 요소 메뉴 항목들을 검사한다.
		WORD ElementType = GetDocument()->GetElementType();
		aMenu.CheckMenuItem(ID_ELEMENT_LINE,
			(LINE == ElementType ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		aMenu.CheckMenuItem(ID_ELEMENT_RECTANGLE,
			(RECTANGLE == ElementType ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		aMenu.CheckMenuItem(ID_ELEMENT_CIRCLE,
			(CIRCLE == ElementType ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		aMenu.CheckMenuItem(ID_ELEMENT_CURVE,
			(CURVE == ElementType ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);

		// 빠른 팝업을 나타낸다.
		aMenu.GetSubMenu(1)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			point.x, point.y, this);
	}
}

void CSketcherView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_MoveMode)
	{
		// 이동 모드에 있다. 그러므로 요소를 원래 위치로 드롭한다.
		CClientDC aDC(this);
		OnPrepareDC(&aDC);	// 원점이 조정되도록 한다.
		MoveElement(aDC, m_FirstPos); // 요소를 원래 위치로 이동한다.
		m_MoveMode = FALSE;			// 이동 모드를 죽인다.
		m_pSelected = 0;			// 요소를 선택한 것을 취소시킨다.
		GetDocument()->UpdateAllViews(0);	// 작업을 끝마친다.
		return;
	}
}


// 커서에 있는 요소를 찾는다.
CElement* CSketcherView::SelectElement(CPoint aPoint)
{
	// aPoint 파라미터를 논리좌표로 변환한다.
	CClientDC aDC(this);
	OnPrepareDC(&aDC);
	aDC.DPtoLP(&aPoint);

	CSketcherDoc* pDoc = GetDocument(); // 도큐먼트에 대한 포인터를 얻는다.
	CElement* pElement = 0;				// 요소 포인터를 저장한다.
	CRect aRect(0, 0, 0, 0);			// 직사각형을 저장한다.
	POSITION aPos = pDoc->GetListTailPosition(); // 마지막 요소 위치를 얻는다.

	while (aPos)
	{
		pElement = pDoc->GetPrev(aPos);
		aRect = pElement->GetBoundRect();
		// 커서 밑에 나타나는 첫번째 요소를 선택한다.
		if (aRect.PtInRect(aPoint))
			return pElement;
	}
	return 0;

}


void CSketcherView::MoveElement(CClientDC& aDC, const CPoint& point) {
	
	CSize Distance = point - m_CursorPos;		// 이동 거리를 얻는다.
	m_CursorPos = point;						// 현재의 점을 이 다음 작업에서 첫 번째로 설정한다.

	// 만약 선택된 요소가 있다면, 그것을 이동시킨다.
	if (m_pSelected)
	{
		aDC.SetROP2(R2_NOTXORPEN);
		m_pSelected->Draw(&aDC, m_pSelected);	// 요소를 삭제하기 위해 그것을 그린다.
		m_pSelected->Move(Distance);			// 이제, 그것을 이동시킨다.
		m_pSelected->Draw(&aDC, m_pSelected);	// 이동된 요소를 그린다.
	}
}


void CSketcherView::OnMove()
{
	CClientDC aDC(this);
	OnPrepareDC(&aDC);              // Set up the device context
	GetCursorPos(&m_CursorPos);     // Get cursor position in screen coords
	ScreenToClient(&m_CursorPos);   // Convert to client coords
	aDC.DPtoLP(&m_CursorPos);       // Convert to logical
	m_FirstPos = m_CursorPos;       // Remember first position
	m_MoveMode = TRUE;              // Start move mode
}

void CSketcherView::OnDelete()
{
	if (m_pSelected)
	{
		CSketcherDoc* pDoc = GetDocument();  // Get the document pointer
		pDoc->DeleteElement(m_pSelected);    // Delete the element
		pDoc->UpdateAllViews(0);             // Redraw all the views
		m_pSelected = 0;                     // Reset selected element ptr
	}
}


void CSketcherView::OnSendtoBack()
{
	GetDocument()->SendToBack(m_pSelected);

}

void CSketcherView::OnViewScale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CScaleDialog aDlg;		// 대화 상자 객체 생성
	aDlg.m_Scale = m_Scale;	// view scale을 대화상자에 전달
	if (aDlg.DoModal() == IDOK)
	{
		m_Scale = aDlg.m_Scale; // 새로운 scale 얻는다.
		Invalidate(0);			// 전체 윈도우 무효화
	}
}


void CSketcherView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CScrollView::OnPrepareDC(pDC, pInfo);
	CSketcherDoc* pDoc = GetDocument();
	pDC->SetMapMode(MM_ANISOTROPIC);	// 맵 모드 설정
	CSize DocSize = pDoc->GetDocSize();	// 도큐먼트 크기를 얻는다.

	// MM_LOENGLISH를 원하기 때문에 y 범위는 음이 되어야 한다.
	DocSize.cy = -DocSize.cy;			// y의 부호를 변경한다.
	pDC->SetWindowExt(DocSize);			// 이제, 윈도우 범위를 설정한다.

	// x와 y에서의 인치당 픽셀 개수를 얻는다.
	int xLogPixels = pDC->GetDeviceCaps(LOGPIXELSX);
	int yLogPixels = pDC->GetDeviceCaps(LOGPIXELSY);

	// x와 y에서의 뷰 포트 범위를 계산한다.
	int xExtent = DocSize.cx * m_Scale * xLogPixels / 100;
	int yExtent = DocSize.cy * m_Scale * yLogPixels / 100;

	pDC->SetViewportExt(xExtent, -yExtent);
}

void CSketcherView::ResetScrollSizes()
{
	// TODO: 여기에 구현 코드 추가.
	CClientDC aDC(this);
	OnPrepareDC(&aDC);				// 디바이스 컨텍스트를 설정한다.
	CSize DocSize = GetDocument()->GetDocSize();	// 도큐먼트 크기를 얻는다.
	aDC.LPtoDP(&DocSize);				// 크기를 픽셀 단위로 얻는다.
	SetScrollSizes(MM_TEXT, DocSize);	//스크롤바들을 설정한다
}

