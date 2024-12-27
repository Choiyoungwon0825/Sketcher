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
	m_Pen = PenWidth; // 선의 폭 설정

	// 둘러싸는 직사각형을 정의한다.
	m_EnclosingRect = CRect(Start, End);
	m_EnclosingRect.NormalizeRect();
}

// CLine 객체를 그린다.
void CLine::Draw(CDC* pDC, const CElement* pElement) const
{
	// 이 객체에 대한 펜을 생성하며, 그것을 객체 색깔과 선 폭으로 초기화한다.
	CPen aPen;
	COLORREF aColor = m_Color;	// 요소 색깔로 초기화
	if (this == pElement)		// 이 요소가 선택되었는가?
		aColor = SELECT_COLOR;	// 반전되는 색깔 설정

	if (!aPen.CreatePen(PS_SOLID, m_Pen, m_Color))
	{
		// 팬 생성이 실패했다. 프로그램을 종료한다.
		AfxMessageBox("Pen creation failed drawing a line", MB_OK);
		AfxAbort();
	}
	//TRACE("펜그려짐\n");


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
	m_Pen = 1; // 펜 폭 설정

}
// 곡선 객체에 대한 컨스트럭터
CCurve::CCurve(const CPoint& FirstPoint, const CPoint& SecondPoint, const COLORREF& Color, const int& PenWidth)
{
	m_PointList.AddTail(FirstPoint);
	m_PointList.AddTail(SecondPoint);


	m_Color = Color; // 색 저장
	m_Pen = PenWidth;		// 펜 폭 설정

	// MM_TEXT 
	m_EnclosingRect = CRect(FirstPoint, SecondPoint);
	m_EnclosingRect.NormalizeRect();
}


// 곡선을 그린다.
void CCurve::Draw(CDC* pDC, const CElement* pElement) const
{
	// 이 객체에 대한 펜을 생성하며, 그것을 객체 색과 1픽셀 선의 폭으로 초기화한다.
	CPen aPen;

	if (!aPen.CreatePen(PS_SOLID, m_Pen, m_Color))
	{
		// 펜 생성이 실패하였다. 프로그램을 종료한다.
		AfxMessageBox("Pen creation failed drawing a curve", MB_OK);
		AfxAbort();
	}
	//TRACE("커브 그려짐\n");
	CPen* pOldPen = pDC->SelectObject(&aPen); // 펜을 선택한다.

	// 이제 곡선을 그린다.
	// 첫번째 요소의 리스트에서 위치를 얻는다.

	POSITION aPosition = m_PointList.GetHeadPosition();

	// 그것이 유효하다며, 그 곳으로 이동한다.
	if (aPosition)
		pDC->MoveTo(m_PointList.GetNext(aPosition));

	// 다음에 나타나는 각 점들에 대해 세그먼트를 그린다.
	while (aPosition)
		pDC->LineTo(m_PointList.GetNext(aPosition));

	pDC->SelectObject(pOldPen); // 이전 펜 복구
}

// CRectangle 객체를 그린다.
void CRectangle::Draw(CDC* pDC, const CElement* pElement) const
{
	// 이 객체에 대한 펜을 생성하며, 그것을 객체 색깔과 선 폭으로 초기화한다.
	CPen aPen;

	if (!aPen.CreatePen(PS_SOLID, m_Pen, m_Color))
	{
		// 팬 생성이 실패했다. 프로그램을 종료한다.
		AfxMessageBox("Pen creation failed drawing a line", MB_OK);
		AfxAbort();
	}
	//TRACE("네모 그려짐\n");

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
void CCircle::Draw(CDC* pDC, const CElement* pElement) const
{
	// 이 객체에 대한 펜을 생성하며, 그것을 객체 색깔과 선 폭으로 초기화한다.
	CPen aPen;

	if (!aPen.CreatePen(PS_SOLID, m_Pen, m_Color))
	{
		// 팬 생성이 실패했다. 프로그램을 종료한다.
		AfxMessageBox("Pen creation failed drawing a line", MB_OK);
		AfxAbort();
	}
	//TRACE("원 그려짐\n");

	// 펜을 선택한다.
	CPen* pOldPen = pDC->SelectObject(&aPen);
	// null 브러시를 선택한다.
	CBrush* pOldBrush = static_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));

	// 이제, 원을 그린다.
	pDC->Ellipse(m_EnclosingRect);

	pDC->SelectObject(pOldBrush);		// 이전 브러쉬 복구
	pDC->SelectObject(pOldPen);				// 이전 펜 복구
}

void CCurve::AddSegment(const CPoint& Point)
{
	m_PointList.AddTail(Point);

	m_EnclosingRect = CRect(
		min(Point.x, m_EnclosingRect.left),
		min(Point.y, m_EnclosingRect.top),
		max(Point.x, m_EnclosingRect.right),
		max(Point.y, m_EnclosingRect.bottom));
}

void CLine::Move(const CSize& aSize)
{
	m_StartPoint += aSize;			// 시작점과 끝점을 이동시킨다.
	m_EndPoint += aSize;
	m_EnclosingRect += aSize;		// 둘러싸는 직사각형을 이동시킨다.
}

void CRectangle::Move(const CSize& aSize)
{
	m_EnclosingRect += aSize;	// 직사각형을 이동시킨다.
}

void CCircle::Move(const CSize& aSize)
{
	m_EnclosingRect += aSize;	// 직사각형을 이동시킨다.
}

void CCurve::Move(const CSize& aSize) {
	m_EnclosingRect += aSize;	// 직사각형을 이동시킨다.

	// 첫 번째 요소 위치를 얻는다.
	POSITION aPosition = m_PointList.GetHeadPosition();

	while (aPosition)
		m_PointList.GetNext(aPosition) += aSize; // 리스트 안 각 점을 이동시킨다.

}


// 요소를 둘러싸는 직사각형을 얻는다.
CRect CElement::GetBoundRect() const
{
	CRect BoundingRect; // 경계를 짓는 직사각형을 저장하는 객체
	BoundingRect = m_EnclosingRect; // 둘러싸는 직사각형 저장

	// 직사각형을 펜의 폭만큼 증가시킨다.
	int Offset = m_Pen == 0 ? 1 : m_Pen;// 폭은 적어도 1이 되어야한다.

	BoundingRect.InflateRect(Offset, Offset);

	return BoundingRect;			// 경계를 짓는 직사각형을 리턴한다.
}

CText::CText(const CPoint& Start, const CPoint& End, const CString String, const COLORREF& Color)
{
	m_Pen = 1;					// 범위를 정하는 직사각형에 대한 펜의 폭
	m_Color = Color;			// 텍스트에 대한 색깔을 설정한다.
	m_String = String;			// 문자열을 복사한다.
	m_StartPoint = Start;		// 문자열의 시작점

	m_EnclosingRect = CRect(Start, End);
	m_EnclosingRect.NormalizeRect();
}

void CText::Draw(CDC* pDC, const CElement* pElement) const
{
	COLORREF Color(m_Color);		// 요소 색깔로 초기화한다.

	if (this == pElement)
		Color = SELECT_COLOR;		// 선택된 색깔을 설정한다.

	// 텍스트 색깔을 설정하며 텍스트를 출력한다.
	pDC->SetTextColor(Color);
	pDC->TextOutA(m_StartPoint.x, m_StartPoint.y, m_String);
}

void CText::Move(const CSize& aSize)
{
	m_StartPoint += aSize;			// 시작점 이동
	m_EnclosingRect += aSize;		// 직사각형 이동
}