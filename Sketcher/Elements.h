#if !defined(Elements_h)
#define Elements_h
#pragma once

#include <math.h>

// �Ϲ����� ��� Ŭ����
class CElement : public CObject
{
	// ���� �Լ� ������ ���⿡ �߰��Ѵ�.

protected:
	COLORREF m_Color; // ����� ����
	CRect m_EnclosingRect;	// ��Ҹ� �ѷ��δ� ���簢��
	int m_Pen;		  // �� ��

public:
	virtual ~CElement() {}		//���� ��Ʈ����
	virtual void Draw(CDC* pDC, const CElement* pElement = 0) const {} // ���� draw �۾�
	virtual void Move(const CSize& Size) const {}	//��Ҹ� �̵���Ų��.
	CRect GetBoundRect() const; // ��Ҹ� �ѷ��δ� ���簢���� ��´�.

protected:
	CElement() {} // ��j�� ��Ʈ����
};

// �� ��ü�� �����ϴ� Ŭ����
class CLine : public CElement
{
	// Ŭ���� ���Ǹ� ���⿡ �߰��϶�.

public:
	virtual void Draw(CDC* pDC, const CElement* pElement = 0) const; // ���� ��Ÿ���� �Լ�
	// �� ��ü�� ���� ����Ʈ����
	virtual void Move(const CSize& aSize);
	CLine(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth);

protected:
	CPoint m_StartPoint;	// ���� ������
	CPoint m_EndPoint;		// ���� ����


	CLine() {}				// ����Ʈ ����Ʈ���� - ���Ǿ �ȵȴ�.
};

// ���簢�� ��ü�� �����ϴ� Ŭ����
class CRectangle : public CElement
{
public:
	virtual void Draw(CDC* pDC ,const CElement* pElement = 0) const; // ���簢���� ��Ÿ���� �Լ�
	virtual void Move(const CSize& aSize); // ��Ҹ� �̵���Ű�� �Լ�

	// ���簢�� ��ü�� ���� ����Ʈ����
	CRectangle(const CPoint& Start, const CPoint& End, const COLORREF& Color,
		const int& PenWidth);

protected:
	CRectangle() {}	 //����Ʈ ����Ʈ���� - ���Ǿ�� �ȵȴ�.
};

// �� ��ü�� �����ϴ� Ŭ����
class CCircle : public CElement
{
	// Ŭ���� ���Ǹ� ���⿡ �߰��϶�.
public:
	virtual void Draw(CDC* pDC, const CElement* pElement) const; // ���� ��Ÿ���� �Լ�
	virtual void Move(const CSize& aSize); // ��Ҹ� �̵���Ű�� �Լ�.
	// �� ��ü�� ���� ����Ʈ����
	CCircle(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth);

protected:
	CCircle() {}
};

// � ��ü�� �����ϴ� Ŭ����
class CCurve : public CElement
{
	// Ŭ���� ���Ǹ� ���⿡ �߰��϶�.
public:
	virtual void Draw(CDC* pDC, const CElement* pElement) const; // ��� ��Ÿ���� �Լ�
	// � ��ü�� ���� ����Ʈ����
	virtual void Move(const CSize& aSize);
	CCurve(const CPoint& FirstPoint, const CPoint& SecondPoint, const COLORREF& Color, const int& PenWidth);

	void AddSegment(const CPoint& Point); // ���׸�Ʈ�� ��� �߰��Ѵ�.


protected:
	// ���⿡ ��ġ�ϰ� �� CCurve ������ ���

	CList<CPoint, const CPoint&> m_PointList; // Type safe ����Ʈ ����Ʈ
	
	CCurve() {} // ����Ʈ ����Ʈ���� - ���Ǿ�� �ȵȴ�.
};
#endif