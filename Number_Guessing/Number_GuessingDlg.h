
// Number_GuessingDlg.h : header file
//

#pragma once


// CNumberGuessingDlg dialog
class CNumberGuessingDlg : public CDialogEx
{
// Construction
public:
	CNumberGuessingDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NUMBER_GUESSING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonSubmit();
	void GenerateRandomNumber(int,int);
	int secret_number;
	int attempts = 0;
	int max_attempts = 3;
	CString m_num;
	CEdit m_range;
	CEdit m_attempts;
	CEdit m_secret_num;
	
	afx_msg void OnBnClickedButtonPlayAgain();
};
