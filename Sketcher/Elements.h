#if !defined(Elements_h)
#define Elements_h
#pragma once

#include <math.h>

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
	virtual void Draw(CDC* pDC, const CElement* pElement = 0) const {} // 가상 draw 작업
	virtual void Move(const CSize& Size) const {}	//요소를 이동시킨다.
	CRect GetBoundRect() const; // 요소를 둘러싸는 직사각형을 얻는다.

protected:
	CElement() {} // 디퐅르 디스트럭터
};

// 선 객체를 정의하는 클래스
class CLine : public CElement
{
	// 클래스 정의를 여기에 추가하라.

public:
	virtual void Draw(CDC* pDC, const CElement* pElement = 0) const; // 선을 나타내는 함수
	// 선 객체에 대한 컨스트럭터
	virtual void Move(const CSize& aSize);
	CLine(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth);

protected:
	CPoint m_StartPoint;	// 선의 시작점
	CPoint m_EndPoint;		// 선의 끝점


	CLine() {}				// 디폴트 컨스트럭터 - 사용되어선 안된다.
};

// 직사각형 객체를 정의하는 클래스
class CRectangle : public CElement
{
public:
	virtual void Draw(CDC* pDC ,const CElement* pElement = 0) const; // 직사각형을 나타내는 함수
	virtual void Move(const CSize& aSize); // 요소를 이동시키는 함수

	// 직사각형 객체에 대한 컨스트럭터
	CRectangle(const CPoint& Start, const CPoint& End, const COLORREF& Color,
		const int& PenWidth);

protected:
	CRectangle() {}	 //디폴트 컨스트럭터 - 사용되어서는 안된다.
};

// 원 객체를 정의하는 클래스
class CCircle : public CElement
{
	// 클래스 정의를 여기에 추가하라.
public:
	virtual void Draw(CDC* pDC, const CElement* pElement) const; // 원을 나타내는 함수
	virtual void Move(const CSize& aSize); // 요소를 이동시키는 함수.
	// 원 객체에 대한 컨스트럭터
	CCircle(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth);

protected:
	CCircle() {}
};

// 곡선 객체를 정의하는 클래스
class CCurve : public CElement
{
	// 클래스 정의를 여기에 추가하라.
public:
	virtual void Draw(CDC* pDC, const CElement* pElement) const; // 곡선을 나타내는 함수
	// 곡선 객체에 대한 컨스트럭터
	virtual void Move(const CSize& aSize);
	CCurve(const CPoint& FirstPoint, const CPoint& SecondPoint, const COLORREF& Color, const int& PenWidth);

	void AddSegment(const CPoint& Point); // 세그먼트를 곡선에 추가한다.


protected:
	// 여기에 위치하게 될 CCurve 데이터 멤버

	CList<CPoint, const CPoint&> m_PointList; // Type safe 포인트 리스트
	
	CCurve() {} // 디폴트 컨스트럭터 - 사용되어서는 안된다.
};
#endif