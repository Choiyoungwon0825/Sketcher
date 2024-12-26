// CPenDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Sketcher.h"
#include "CPenDialog.h"
#include "afxdialogex.h"


// CPenDialog 대화 상자

IMPLEMENT_DYNAMIC(CPenDialog, CDialog)

CPenDialog::CPenDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PENWIDTH_DLG, pParent)
{

}

CPenDialog::~CPenDialog()
{
}

void CPenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPenDialog, CDialog)
	ON_COMMAND(IDC_PENWIDTH0, &CPenDialog::OnPenwidth0)
	ON_COMMAND(IDC_PENWIDTH1, &CPenDialog::OnPenwidth1)
	ON_COMMAND(IDC_PENWIDTH2, &CPenDialog::OnPenwidth2)
	ON_COMMAND(IDC_PENWIDTH3, &CPenDialog::OnPenwidth3)
	ON_COMMAND(IDC_PENWIDTH4, &CPenDialog::OnPenwidth4)
	ON_COMMAND(IDC_PENWIDTH5, &CPenDialog::OnPenwidth5)
	ON_BN_CLICKED(IDC_PENWIDTH0, &CPenDialog::OnBnClickedPenwidth0)
END_MESSAGE_MAP()


// CPenDialog 메시지 처리기

BOOL CPenDialog::OnInitDialog()
{
//CDialog:OnInitDialog();
	//펜의 폭에 해당하는 라디오 컨스트럭터를 검사한다.
	switch (m_PenWidth)
	{
	case 1:
		CheckDlgButton(IDC_PENWIDTH1, 1);
		break;
	case 2:
		CheckDlgButton(IDC_PENWIDTH2, 1);
		break;
	case 3:
		CheckDlgButton(IDC_PENWIDTH3, 1);
		break;
	case 4:
		CheckDlgButton(IDC_PENWIDTH4, 1);
		break;
	case 5:
		CheckDlgButton(IDC_PENWIDTH5, 1);
		break;
	default:
		CheckDlgButton(IDC_PENWIDTH0, 1);
	}
	return TRUE; // 컨트롤에 포커스를 설정하지 않았다면 TRUE를 리턴한다.
				 // 다만, OCX Property Pages는 FALSE를 리턴해야한다.

}

void CPenDialog::OnPenwidth0()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_PenWidth = 0;
}


void CPenDialog::OnPenwidth1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_PenWidth = 1;
}


void CPenDialog::OnPenwidth2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_PenWidth = 2;
}


void CPenDialog::OnPenwidth3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_PenWidth = 3;
}


void CPenDialog::OnPenwidth4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_PenWidth = 4;
}


void CPenDialog::OnPenwidth5()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_PenWidth = 5;
}


void CPenDialog::OnBnClickedPenwidth0()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
