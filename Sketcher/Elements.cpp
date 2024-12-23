//��� Ŭ������ ���� ����
#include "pch.h"
#include "OurConstants.h"
#include "Elements.h"
#include <math.h>

// ��� �Լ��鿡 ���� ���Ǹ� ���⿡ �߰�.
// CLine Ŭ���� ����Ʈ����
CLine::CLine(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth)
{
	m_StartPoint = Start; // ���� ������ ����
	m_EndPoint = End; // ���� ���� ����
	m_Color = Color; // ���� ���� ����
	m_Pen = 1; // ���� �� ����

	// �ѷ��δ� ���簢���� �����Ѵ�.
	m_EnclosingRect = CRect(Start, End);
	m_EnclosingRect.NormalizeRect();
}

// CLine ��ü�� �׸���.
void CLine::Draw(CDC* pDC) const
{
	// �� ��ü�� ���� ���� �����ϸ�, �װ��� ��ü ����� �� ������ �ʱ�ȭ�Ѵ�.
	CPen aPen;

	if (!aPen.CreatePen(PS_SOLID, m_Pen, m_Color))
	{
		// �� ������ �����ߴ�. ���α׷��� �����Ѵ�.
		AfxMessageBox("Pen creation failed drawing a line", MB_OK);
		AfxAbort();
	}


	CPen* pOldPen = pDC->SelectObject(&aPen);	// ���� �����Ѵ�.

	// ����, ���� �׸���.
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);

	pDC->SelectObject(pOldPen);				// ���� �� ����
}
// CRectangle Ŭ���� ����Ʈ����
CRectangle::CRectangle(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth)
{
	m_Color = Color; // ���簢�� �� ����
	m_Pen = PenWidth; // �� �� ����

	// �ѷ��δ� ���簢�� ����
	m_EnclosingRect = CRect(Start, End);
	m_EnclosingRect.NormalizeRect();

}
// �� ��ü�� ���� ����Ʈ����
CCircle::CCircle(const CPoint& Start, const CPoint& End, const COLORREF& Color, const int& PenWidth)
{
	// ����, �������� ���
	// �ε��Ҽ����� ����Ѵ�.
	// �ֳ��ϸ� �������� ����ϴµ� ���̺귯���Լ�(math.h)���� �װ��� �ʿ�� �ϱ� ����
	long Radius =
		static_cast<long>(sqrt(static_cast<double>((End.x - Start.x)*(End.x - Start.x) + (End.x - Start.y)*(End.y - Start.y))));

	// �ѷ��δ� ���簢�� ���
	// ���� MM_TEXT ���� ���� ����
	m_EnclosingRect = CRect(Start.x - Radius, Start.y - Radius, Start.x + Radius, Start.y + Radius);

	m_Color = Color; // �� �� ����
	m_Pen = PenWidth; // �� �� ����

}
// � ��ü�� ���� ����Ʈ����
CCurve::CCurve(const COLORREF& Color, const int& PenWidth)
{
	m_Color = Color; // �� ����
	m_EnclosingRect = CRect(0, 0, 0, 0);
	m_Pen = 1;		// �� �� ����
}
// ��� �׸���.
void CCurve::Draw(CDC* pDC) const
{
}

// CRectangle ��ü�� �׸���.
void CRectangle::Draw(CDC* pDC) const
{
	// �� ��ü�� ���� ���� �����ϸ�, �װ��� ��ü ����� �� ������ �ʱ�ȭ�Ѵ�.
	CPen aPen;

	if (!aPen.CreatePen(PS_SOLID, m_Pen, m_Color))
	{
		// �� ������ �����ߴ�. ���α׷��� �����Ѵ�.
		AfxMessageBox("Pen creation failed drawing a line", MB_OK);
		AfxAbort();
	}

	// ���� �����Ѵ�.
	CPen* pOldPen = pDC->SelectObject(&aPen);
	// �귯�ø� �����Ѵ�.
	CBrush* pOldBrush = static_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));

	// ����, ���簢���� �׸���.
	pDC->Rectangle(m_EnclosingRect);

	pDC->SelectObject(pOldBrush);		// ���� �귯�� ����
	pDC->SelectObject(pOldPen);				// ���� �� ����
}

// ���� �׸���.
void CCircle::Draw(CDC* pDC) const
{
	// �� ��ü�� ���� ���� �����ϸ�, �װ��� ��ü ����� �� ������ �ʱ�ȭ�Ѵ�.
	CPen aPen;

	if (!aPen.CreatePen(PS_SOLID, m_Pen, m_Color))
	{
		// �� ������ �����ߴ�. ���α׷��� �����Ѵ�.
		AfxMessageBox("Pen creation failed drawing a line", MB_OK);
		AfxAbort();
	}

	// ���� �����Ѵ�.
	CPen* pOldPen = pDC->SelectObject(&aPen);
	// null �귯�ø� �����Ѵ�.
	CBrush* pOldBrush = static_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));

	// ����, ���� �׸���.
	pDC->Ellipse(m_EnclosingRect);

	pDC->SelectObject(pOldBrush);		// ���� �귯�� ����
	pDC->SelectObject(pOldPen);				// ���� �� ����
}




// ��Ҹ� �ѷ��δ� ���簢���� ��´�.
CRect CElement::GetBoundRect() const
{
	CRect BoundingRect; // ��踦 ���� ���簢���� �����ϴ� ��ü
	BoundingRect = m_EnclosingRect; // �ѷ��δ� ���簢�� ����

	// ���簢���� ���� ����ŭ ������Ų��.
	//int Offset = m_Pen == 0 ? 1 : m_Pen;// ���� ��� 1�� �Ǿ���Ѵ�.

	//BoundingRect.InflateRect(Offset, Offset);

	//BoundingRect = m_EnclosingRect;
	//BoundingRect.top -= m_Pen;
	//BoundingRect.left -= m_Pen;
	//BoundingRect.bottom += m_Pen;
	//BoundingRect.right += m_Pen;


	return BoundingRect;			// ��踦 ���� ���簢���� �����Ѵ�.
}