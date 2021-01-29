// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
class ICalc;
class CMainDlg : public CDialogImpl<CMainDlg>
	,public CUpdateUI<CMainDlg>
	,public CMessageFilter, public CIdleHandler
	, public CWinDataExchange<CMainDlg>
	, public CDialogResize< CMainDlg>
{
	CComboBox m_comboMode;
	CStatic   m_stcChild;
	ICalc* m_pChildDialog;
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		
		
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_HANDLER(IDC_COMBO_MODE, CBN_SELCHANGE, OnCbnSelchangeComboMode)
		MESSAGE_HANDLER(WM_SIZE, OnSize)


		CHAIN_MSG_MAP(CDialogResize<CMainDlg>)
		COMMAND_HANDLER(ID_BUTTON_QUIT, BN_CLICKED, OnBnClickedButtonQuit)
		COMMAND_HANDLER(ID_BUTTON_CALC, BN_CLICKED, OnBnClickedButtonCalc)
	END_MSG_MAP()

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_DDX_MAP(CMainDlg)
		DDX_CONTROL_HANDLE(IDC_COMBO_MODE, m_comboMode)
		DDX_CONTROL_HANDLE(IDC_STATIC_CHILD, m_stcChild)
	END_DDX_MAP()

	BEGIN_DLGRESIZE_MAP(CMainDlg)
		DLGRESIZE_CONTROL(ID_APP_ABOUT, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(ID_BUTTON_QUIT, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(ID_BUTTON_CALC, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_STATIC_CHILD, DLSZ_SIZE_X| DLSZ_SIZE_Y)
		//DLGRESIZE_CONTROL(IDC_EDIT_DIR2, DLSZ_SIZE_X)
		//DLGRESIZE_CONTROL(IDC_LIST_LOG, DLSZ_SIZE_Y | DLSZ_SIZE_X)
		//DLGRESIZE_CONTROL(IDC_EDIT_INFO, DLSZ_SIZE_X)
		//DLGRESIZE_CONTROL(IDC_BUTTON_GO, DLSZ_MOVE_X)
	END_DLGRESIZE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return ::IsDialogMessage(m_hWnd, pMsg);
	}

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_pChildDialog = NULL;
		// center the dialog on the screen
		CenterWindow();
		UIAddChildWindowContainer(m_hWnd);
		DlgResize_Init();
		DoDataExchange(false);

		// set icons
		HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
		SetIcon(hIconSmall, FALSE);
		m_comboMode.AddString(_T("RLC"));
		m_comboMode.SetCurSel(0);
		BOOL b;
		OnCbnSelchangeComboMode(0, 0, 0, b);
		return TRUE;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add validation code 
		//EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
	BOOL OnIdle()
	{
		UIUpdateChildWindows();
		return FALSE;
	}
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCbnSelchangeComboMode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonQuit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonCalc(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
