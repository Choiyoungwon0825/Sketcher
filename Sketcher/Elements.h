#if !defined(Elements_h)
#define Elements_h
#pragma once


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

	// ���� draw �۾�
	virtual void Draw(CDC* pDC) const {} // ���� draw �۾�
	CRect GetBoundRect() const; // ��Ҹ� �ѷ��δ� ���簢���� ��´�.

protected:
	CElement() {} // ��j�� ��Ʈ����
};

// �� ��ü�� �����ϴ� Ŭ����
class CLine : public CElement
{
	// Ŭ���� ���Ǹ� ���⿡ �߰��϶�.

public:
	virtual void Draw(CDC* pDC) const; // ���� ��Ÿ���� �Լ�
	// �� ��ü�� ���� ����Ʈ����
	CLine(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth);

protected:
	CPoint m_StartPoint;	// ���� ������
	CPoint m_EndPoint;		// ���� ����
	

	CLine() {}				// ����Ʈ ����Ʈ���� - ���Ǿ �ȵȴ�.
};

// ���簢�� ��ü�� �����ϴ� Ŭ����
class CRectangle : public CElement
{
	// Ŭ���� ���Ǹ� ���⿡ �߰��϶�.
};

// �� ��ü�� �����ϴ� Ŭ����
class CCircle : public CElement
{
	// Ŭ���� ���Ǹ� ���⿡ �߰��϶�.
};

// � ��ü�� �����ϴ� Ŭ����
class CCurve : public CElement
{
	// Ŭ���� ���Ǹ� ���⿡ �߰��϶�.
};
#endif