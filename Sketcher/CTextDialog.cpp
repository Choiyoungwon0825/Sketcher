// CTextDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Sketcher.h"
#include "CTextDialog.h"
#include "afxdialogex.h"


// CTextDialog 대화 상자

IMPLEMENT_DYNAMIC(CTextDialog, CDialog)

CTextDialog::CTextDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TEXT_DLG, pParent)
	, m_TextString(_T(""))
{

}

CTextDialog::~CTextDialog()
{
}

void CTextDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITTEXT, m_TextString);
}


BEGIN_MESSAGE_MAP(CTextDialog, CDialog)
END_MESSAGE_MAP()


// CTextDialog 메시지 처리기
