//��� Ŭ������ ���� ����
#include "pch.h"
#include "OurConstants.h"
#include "Elements.h"

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

CRect CElement::GetBoundRect() const
{
	CRect BoundingRect; // ��踦 ���� ���簢���� �����ϴ� ��ü
	BoundingRect = m_EnclosingRect; // �ѷ��δ� ���簢�� ����

	// ���簢���� ���� ����ŭ ������Ų��.
	int Offset = m_Pen == 0 ? 1 : m_Pen;// ���� ��� 1�� �Ǿ���Ѵ�.
	BoundingRect.InflateRect(Offset, Offset);

	return BoundingRect;			// ��踦 ���� ���簢���� �����Ѵ�.
}