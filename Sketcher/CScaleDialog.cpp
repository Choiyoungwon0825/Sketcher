// CScaleDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Sketcher.h"
#include "CScaleDialog.h"
#include "afxdialogex.h"


// CScaleDialog 대화 상자

IMPLEMENT_DYNAMIC(CScaleDialog, CDialog)

CScaleDialog::CScaleDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SCALE_DLG, pParent)
{
	m_Scale = -1;
}

CScaleDialog::~CScaleDialog()
{
}

void CScaleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_LBIndex(pDX, IDC_SCALELIST, m_Scale);
}


BEGIN_MESSAGE_MAP(CScaleDialog, CDialog)
	ON_LBN_SELCHANGE(IDC_SCALELIST, &CScaleDialog::OnLbnSelchangeScalelist)
END_MESSAGE_MAP()


// CScaleDialog 메시지 처리기


BOOL CScaleDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CListBox* pListBox = static_cast<CListBox*>(GetDlgItem(IDC_SCALELIST));
	pListBox->AddString("Scale 1");
	pListBox->AddString("Scale 2");
	pListBox->AddString("Scale 3");
	pListBox->AddString("Scale 4");
	pListBox->AddString("Scale 5");
	pListBox->AddString("Scale 6");
	pListBox->AddString("Scale 7");
	pListBox->AddString("Scale 8");
	pListBox->SetCurSel(m_Scale - 1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CScaleDialog::OnLbnSelchangeScalelist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
