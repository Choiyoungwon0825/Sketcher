#if !defined(Elements_h)
#define Elements_h
#pragma once


// 일반적인 요소 클래스
class CElement : public CObject
{
	// 가상 함수 선언을 여기에 추가한다.

protected:
	COLORREF m_Color; // 요소의 색깔

	CRect m_EnclosingRect;	// 요소를 둘러싸는 직사각형
	int m_Pen;		  // 펜 폭

public:
	virtual ~CElement() {}		//가상 디스트럭터

	// 가상 draw 작업
	virtual void Draw(CDC* pDC) const {} // 가상 draw 작업
	CRect GetBoundRect() const; // 요소를 둘러싸는 직사각형을 얻는다.

protected:
	CElement() {} // 디퐅르 디스트럭터
};

// 선 객체를 정의하는 클래스
class CLine : public CElement
{
	// 클래스 정의를 여기에 추가하라.

public:
	virtual void Draw(CDC* pDC) const; // 선을 나타내는 함수
	// 선 객체에 대한 컨스트럭터
	CLine(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth);

protected:
	CPoint m_StartPoint;	// 선의 시작점
	CPoint m_EndPoint;		// 선의 끝점
	

	CLine() {}				// 디폴트 컨스트럭터 - 사용되어선 안된다.
};

// 직사각형 객체를 정의하는 클래스
class CRectangle : public CElement
{
	// 클래스 정의를 여기에 추가하라.
};

// 원 객체를 정의하는 클래스
class CCircle : public CElement
{
	// 클래스 정의를 여기에 추가하라.
};

// 곡선 객체를 정의하는 클래스
class CCurve : public CElement
{
	// 클래스 정의를 여기에 추가하라.
};
#endif