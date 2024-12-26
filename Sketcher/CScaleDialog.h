#pragma once


// CScaleDialog 대화 상자

class CScaleDialog : public CDialog
{
	DECLARE_DYNAMIC(CScaleDialog)

public:
	CScaleDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CScaleDialog();
	int m_Scale;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCALE_DLG };
	
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void

};
