//요소 클래스에 대한 구현
#include "pch.h"
#include "OurConstants.h"
#include "Elements.h"

// 멤버 함수들에 대한 정의를 여기에 추가.

// CLine 클래스 컨스트럭터
CLine::CLine(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth)
{
	m_StartPoint = Start; // 선의 시작점 설정
	m_EndPoint = End; // 선의 끝점 설정
	m_Color = Color; // 선의 색깔 설정
	m_Pen = 1; // 선의 폭 설정

	// 둘러싸는 직사각형을 정의한다.
	m_EnclosingRect = CRect(Start, End);
	m_EnclosingRect.NormalizeRect();
}

void CLine::Draw(CDC* pDC) const
{
	// 이 객체에 대한 펜을 생성하며, 그것을 객체 색깔과 선 폭으로 초기화한다.
	CPen aPen;

	if (!aPen.CreatePen(PS_SOLID, m_Pen, m_Color))
	{
		// 팬 생성이 실패했다. 프로그램을 종료한다.
		AfxMessageBox("Pen creation failed drawing a line", MB_OK);
		AfxAbort();
	}

	CPen* pOldPen = pDC->SelectObject(&aPen);	// 펜을 선택한다.

	// 이제, 선을 그린다.
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);

	pDC->SelectObject(pOldPen);				// 이전 펜 복구
}

CRect CElement::GetBoundRect() const
{
	CRect BoundingRect; // 경계를 짓는 직사각형을 저장하는 객체
	BoundingRect = m_EnclosingRect; // 둘러싸는 직사각형 저장

	// 직사각형을 펜의 폭만큼 증가시킨다.
	int Offset = m_Pen == 0 ? 1 : m_Pen;// 폭은 적어도 1이 되어야한다.
	BoundingRect.InflateRect(Offset, Offset);

	return BoundingRect;			// 경계를 짓는 직사각형을 리턴한다.
}