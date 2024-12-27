
// ChildFrm.cpp: CChildFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Sketcher.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CChildFrame 생성/소멸

// 생성 컨스트럭터
CChildFrame::CChildFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}


// 소멸 컨스트럭터
CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서 Window 클래스 또는 스타일을 수정합니다.
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 진단

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 메시지 처리기


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	
	// 상태바를 생성한다.
	m_StatusBar.Create(this);

	// 우리가 나타내고자 하는 텍스트의 폭을 계산한다.
	CRect textRect;
	CClientDC aDC(&m_StatusBar);

	aDC.SelectObject(m_StatusBar.GetFont());
	aDC.DrawText("View Scale:99", -1, textRect, DT_SINGLELINE | DT_CALCRECT);

	// 텍스트를 포함할 수 있을 만한 정도의 부분을 설정한다.
	int width = textRect.Width();
	m_StatusBar.GetStatusBarCtrl().GetParts(1, &width);

	// 상태바에 대한 텍스트를 초기화한다.
	m_StatusBar.GetStatusBarCtrl().SetText("View Scale:1", 0, 0);

	return 0;
}
