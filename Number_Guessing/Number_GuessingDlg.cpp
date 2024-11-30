
// Number_GuessingDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Number_Guessing.h"
#include "Number_GuessingDlg.h"
#include "afxdialogex.h"
#include "cstdlib" // For rand() and srand()
#include "ctime"   // For time()

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNumberGuessingDlg dialog



CNumberGuessingDlg::CNumberGuessingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NUMBER_GUESSING_DIALOG, pParent)
	, m_num(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNumberGuessingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_num);
	DDX_Control(pDX, IDC_EDIT_RANGE, m_range);
	DDX_Control(pDX, IDC_EDIT_ATTEMPTS, m_attempts);
	DDX_Control(pDX, IDC_EDIT_SECRET_NUM, m_secret_num);
}

BEGIN_MESSAGE_MAP(CNumberGuessingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CNumberGuessingDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDCANCEL, &CNumberGuessingDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CNumberGuessingDlg::OnBnClickedButtonSubmit)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_AGAIN, &CNumberGuessingDlg::OnBnClickedButtonPlayAgain)
END_MESSAGE_MAP()


// CNumberGuessingDlg message handlers

BOOL CNumberGuessingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetDlgItemInt(IDC_EDIT_ATTEMPTS, max_attempts);
	GenerateRandomNumber(1, 10);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNumberGuessingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNumberGuessingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNumberGuessingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNumberGuessingDlg::OnBnClickedButtonHelp()
{
	// TODO: Add your control notification handler code here
	CString helpText = _T("How to Play:\n\n")
		_T("1. The program randomly selects a number between a given range (1 to 10).\n")
		_T("2. You need to guess the number by entering your guess and clicking the 'Submit' button.\n")
		_T("3. The program will provide feedback:\n")
		_T("   - 'Too Low!' if your guess is lower than the secret number.\n")
		_T("   - 'Too High!' if your guess is higher than the secret number.\n")
		_T("4. You win if you guess the correct number within the allowed attempts.\n")
		_T("5. If you run out of attempts, the game will reveal the secret number.\n\n")
		_T("Enjoy the game!");
	MessageBox(helpText, _T("How to play"), MB_ICONINFORMATION | MB_OK);
}

void CNumberGuessingDlg::GenerateRandomNumber(int lower, int upper)
{
	// Seed the random number generator
	srand(static_cast<unsigned int>(time(nullptr)));

	// Generate a random number in the range [lower, upper]
	secret_number = lower + (rand() % (upper - lower + 1));
}

void CNumberGuessingDlg::OnBnClickedButtonSubmit()
{
	// TODO: Add your control notification handler code here
	max_attempts--; //count the number of attempts left
	SetDlgItemInt(IDC_EDIT_ATTEMPTS, max_attempts); //display attempts left

	//get the input from the edit control
	GetDlgItem(IDC_EDIT_NUMBER)->GetWindowText(m_num);
	
	//check if the field is empty
	if (m_num == _T("0") || m_num == _T(""))
	{
		SetDlgItemTextW(IDC_EDIT_RANGE, _T("Enter number greater than 0"));
		return;
	}

	//convert CString to int
	int number = _ttoi(m_num);

	//check if the entered number is equal, greater or lesser than secret number
	if (number > secret_number)
		SetDlgItemTextW(IDC_EDIT_RANGE, _T("too high"));
	else if (number < secret_number)
		SetDlgItemTextW(IDC_EDIT_RANGE, _T("too low"));
	else
	{
		MessageBox(_T("Congragulations.You won"), _T("Congragulation"));
		max_attempts = 3;
		SetDlgItemInt(IDC_EDIT_ATTEMPTS, max_attempts);
		GenerateRandomNumber(1, 10);
		SetDlgItemText(IDC_EDIT_NUMBER, _T(""));
		SetDlgItemText(IDC_EDIT_RANGE, _T(""));
		return;
	}
	if (max_attempts == 0)
	{
		MessageBox(_T("Reached max number of attempts. Better luck next time\n"), _T("Info"), MB_ICONERROR);
		SetDlgItemInt(IDC_EDIT_SECRET_NUM, secret_number); //reveal the secret number
		//enable play again button
		GetDlgItem(IDC_BUTTON_PLAY_AGAIN)->EnableWindow(TRUE);
	}	
}

void CNumberGuessingDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CNumberGuessingDlg::OnBnClickedButtonPlayAgain()
{
	// TODO: Add your control notification handler code here
	max_attempts = 3;
	SetDlgItemInt(IDC_EDIT_ATTEMPTS, max_attempts);
	GenerateRandomNumber(1, 10);
	SetDlgItemText(IDC_EDIT_NUMBER, _T(""));
	SetDlgItemText(IDC_EDIT_RANGE, _T(""));
	SetDlgItemText(IDC_EDIT_SECRET_NUM, _T(""));
	//again disable the play again button
	GetDlgItem(IDC_BUTTON_PLAY_AGAIN)->EnableWindow(FALSE);
}
