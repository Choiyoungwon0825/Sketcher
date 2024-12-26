// CScaleDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Sketcher.h"
#include "CScaleDialog.h"
#include "afxdialogex.h"
#include "SketcherView.h"


// CScaleDialog 대화 상자

IMPLEMENT_DYNAMIC(CScaleDialog, CDialog)

CScaleDialog::CScaleDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SCALE_DLG, pParent)
{

}

CScaleDialog::~CScaleDialog()
{
}

void CScaleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleDialog)
	DDX_Text(pDx, IDC_SCAL, m_Scale);
	DDV_MinMaxInt(pDx, m_Scale, 1, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleDialog, CDialog)
	ON_COMMAND(ID_VIEW_SCALE, &CScaleDialog::OnViewScale)
END_MESSAGE_MAP()


// CScaleDialog 메시지 처리기
BOOL CScaleDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// spin control에 대한 포인터를 먼저 얻는다.
	CSpinButtonCtrl* pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_SCALE);

	// 여러분이 spin control의 속성 안에 있는 auto buddy 옵션을 체크하지 않았다면
	// 여기에서 buddy control을 설정한다.

	// spin control 범위 설정.
	pSpin->SetRange(1, 8);

	return TRUE;
}

