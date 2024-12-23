//요소 클래스에 대한 구현
#include "pch.h"
#include "OurConstants.h"
#include "Elements.h"
#include <math.h>

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

// CLine 객체를 그린다.
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
// CRectangle 클래스 컨스트럭터
CRectangle::CRectangle(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth)
{
	m_Color = Color; // 직사각형 색 설정
	m_Pen = PenWidth; // 펜 폭 설정

	// 둘러싸는 직사각형 정의
	m_EnclosingRect = CRect(Start, End);
	m_EnclosingRect.NormalizeRect();

}
// 원 객체에 대한 컨스트럭터
CCircle::CCircle(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth)
{
	// 먼저, 반지름을 계산
	// 부동소수점을 사용한다.
	// 왜냐하면 제곱근을 계산하는데 라이브러리함수(math.h)에서 그것을 필요로 하기 때문
	long Radius =
		static_cast<long>(sqrt(static_cast<double>((End.x - Start.x)*(End.x - Start.x) + (End.x - Start.y)*(End.y - Start.y))));

	// 둘러싸는 직사각형 계산
	// 원은 MM_TEXT 맵핑 모드로 가정
	m_EnclosingRect = CRect(Start.x - Radius, Start.y - Radius, Start.x + Radius, Start.y + Radius);

	m_Color = Color; // 원 색 설정
	m_Pen = PenWidth; // 펜 폭 설정

}
// 곡선 객체에 대한 컨스트럭터
CCurve::CCurve(const COLORREF& Color, const int& PenWidth)
{
	m_Color = Color; // 색 저장
	m_EnclosingRect = CRect(0, 0, 0, 0);
	m_Pen = 1;		// 펜 폭 설정
}
// 곡선을 그린다.
void CCurve::Draw(CDC* pDC) const
{
}

// CRectangle 객체를 그린다.
void CRectangle::Draw(CDC* pDC) const
{
	// 이 객체에 대한 펜을 생성하며, 그것을 객체 색깔과 선 폭으로 초기화한다.
	CPen aPen;

	if (!aPen.CreatePen(PS_SOLID, m_Pen, m_Color))
	{
		// 팬 생성이 실패했다. 프로그램을 종료한다.
		AfxMessageBox("Pen creation failed drawing a line", MB_OK);
		AfxAbort();
	}

	// 펜을 선택한다.
	CPen* pOldPen = pDC->SelectObject(&aPen);
	// 브러시를 선택한다.
	CBrush* pOldBrush = static_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));

	// 이제, 직사각형을 그린다.
	pDC->Rectangle(m_EnclosingRect);

	pDC->SelectObject(pOldBrush);		// 이전 브러쉬 복구
	pDC->SelectObject(pOldPen);				// 이전 펜 복구
}

// 원을 그린다.
void CCircle::Draw(CDC* pDC) const
{
	// 이 객체에 대한 펜을 생성하며, 그것을 객체 색깔과 선 폭으로 초기화한다.
	CPen aPen;

	if (!aPen.CreatePen(PS_SOLID, m_Pen, m_Color))
	{
		// 팬 생성이 실패했다. 프로그램을 종료한다.
		AfxMessageBox("Pen creation failed drawing a line", MB_OK);
		AfxAbort();
	}

	// 펜을 선택한다.
	CPen* pOldPen = pDC->SelectObject(&aPen);
	// null 브러시를 선택한다.
	CBrush* pOldBrush = static_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));

	// 이제, 원을 그린다.
	pDC->Ellipse(m_EnclosingRect);

	pDC->SelectObject(pOldBrush);		// 이전 브러쉬 복구
	pDC->SelectObject(pOldPen);				// 이전 펜 복구
}




// 요소를 둘러싸는 직사각형을 얻는다.
CRect CElement::GetBoundRect() const
{
	CRect BoundingRect; // 경계를 짓는 직사각형을 저장하는 객체
	BoundingRect = m_EnclosingRect; // 둘러싸는 직사각형 저장

	// 직사각형을 펜의 폭만큼 증가시킨다.
	//int Offset = m_Pen == 0 ? 1 : m_Pen;// 폭은 적어도 1이 되어야한다.

	//BoundingRect.InflateRect(Offset, Offset);

	//BoundingRect = m_EnclosingRect;
	//BoundingRect.top -= m_Pen;
	//BoundingRect.left -= m_Pen;
	//BoundingRect.bottom += m_Pen;
	//BoundingRect.right += m_Pen;


	return BoundingRect;			// 경계를 짓는 직사각형을 리턴한다.
}