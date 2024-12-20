
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
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketcherView

IMPLEMENT_DYNCREATE(CSketcherView, CView)

BEGIN_MESSAGE_MAP(CSketcherView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSketcherView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_COLOR_BLACK, &CSketcherView::OnColorBlack)
	ON_COMMAND(ID_COLOR_BLUE, &CSketcherView::OnColorBlue)
	ON_COMMAND(ID_COLOR_GREEN, &CSketcherView::OnColorGreen)
	ON_COMMAND(ID_COLOR_RED, &CSketcherView::OnColorRed)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CSketcherView 생성/소멸

CSketcherView::CSketcherView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_FirstPoint = CPoint(0, 0); // 처음으로 기록된 점을 0,0으로 설정한다.
	m_SecondPoint = CPoint(0, 0); // 두번째로 기록된 점을 0,0으로 설정한다.
	m_pTempElement = NULL; // 임시 요소 포인터를 0으로 설정한다.
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
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	pDC->MoveTo(50, 50); // 현재 위치 설정
	pDC->LineTo(50, 200); // 아래 방향으로 150unit 만큼 수직선을 그린다.
	pDC->LineTo(150, 200); // 오른쪽 방향으로 100unit만큼 수평선을 그린다.
	pDC->LineTo(150, 50); // 윗쪽 방향으로 150unit만큼 수직선을 그린다.
	pDC->LineTo(50, 50); // 왼쪽 방향으로 150 unit만큼 수직선을 그린다.

	pDC->Arc(50, 50, 150, 150, 100, 50, 150, 100); // 첫번째의 가장 큰 원을 그린다

	// 펜 객체를 선언하며, 그것을 2픽셀 폭을 갖는 빨간 실선 펜으로서 초기화한다.
	CPen aPen;
	aPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	CPen* pOldPen = pDC->SelectObject(&aPen);	// aPen을 펜으로써 선택한다.


	// 두번째보다 작은 원을 감싸는 직사각형을 정의한다.
	CRect* pRect = new CRect(250, 50, 300, 100);
	CPoint Start(275, 100);  // 호의 시작점
	CPoint End(250, 75);     // 호의 끝점
	pDC->Arc(pRect, Start, End); // 두번째 원을 그린다.
	delete pRect;

	pDC->SelectObject(pOldPen);

	/*
	CBrush aBrush(RGB(255, 0, 0)); // 빨간색 브러시 정의

	CBrush aBrush; // 브러시 객체 정의

	aBrush.CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));

	pDC - SelectObject(&aBrush); //브러시를 디바이스 컨텍스트 안으로 선택해서 갖고온다.
	*/
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

void CSketcherView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSketcherView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
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


// CSketcherView 메시지 처리기


void CSketcherView::OnColorBlack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CSketcherView::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CSketcherView::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CSketcherView::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CSketcherView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDblClk(nFlags, point);
}


void CSketcherView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);
	m_FirstPoint = point;
}


void CSketcherView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);

	m_SecondPoint = point; // 현재 커서 위치를 저장한다.
	// 이전의 임시 요소를 검사한다.
	{
		// 이전의 마우스 이동이 있었다면 이 곳에 이르게 된다. 
		// 그러므로 이전 요소를 삭제하는 코드를우ㅊ가한다.
	}

	// 새로운 요소를 생성하는 코드를 추가하며, 그것이 그려지도록 한다. 
}
