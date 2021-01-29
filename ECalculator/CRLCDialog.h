#pragma once
#include "ICalc.h"
class CRLCDialog:public CDialogImpl<CRLCDialog>
	, public CUpdateUI<CRLCDialog>
	, public CMessageFilter, public CIdleHandler
	, public CWinDataExchange<CRLCDialog>
	, public CDialogResize< CRLCDialog>
	,public  ICalc
{
	CEdit m_edtR;
	CEdit m_edtL;
	CEdit m_edtC;
	CEdit m_edtFreq;
	CEdit m_edtStatus;
public:
	INT IDD = IDD_DIALOG_RLC;

	BEGIN_MSG_MAP(CRLCDialog)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		CHAIN_MSG_MAP(CDialogResize<CRLCDialog>)
	END_MSG_MAP()

	BEGIN_UPDATE_UI_MAP(CRLCDialog)
	END_UPDATE_UI_MAP()

	BEGIN_DDX_MAP(CRLCDialog)
		DDX_CONTROL_HANDLE(IDC_EDIT_R, m_edtR)
		DDX_CONTROL_HANDLE(IDC_EDIT_L, m_edtL)
		DDX_CONTROL_HANDLE(IDC_EDIT_C, m_edtC)
		DDX_CONTROL_HANDLE(IDC_EDIT_FREQ, m_edtFreq)
		DDX_CONTROL_HANDLE(IDC_EDIT_STATUS, m_edtStatus)
		
	END_DDX_MAP()

	BEGIN_DLGRESIZE_MAP(CRLCDialog)
	//	DLGRESIZE_CONTROL(ID_APP_ABOUT, DLSZ_MOVE_X)
	//	DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X)
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
		// center the dialog on the screen
		//CenterWindow();
		UIAddChildWindowContainer(m_hWnd);
		DlgResize_Init();
		DoDataExchange(false);
		return TRUE;
	}

	

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{

		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
	
		return 0;
	}
	BOOL OnIdle()
	{
		UIUpdateChildWindows();
		return FALSE;
	}

	virtual void DoCalc();
	virtual HWND    GetHWnd() {
		return m_hWnd;
	}


	static BOOL _AtlSimpleFloatParse(LPCTSTR lpszText, double& d)
	{
		ATLASSERT(lpszText != NULL);
		while ((*lpszText == _T(' ')) || (*lpszText == _T('\t')))
			lpszText++;

		TCHAR chFirst = lpszText[0];
		d = _tcstod(lpszText, (LPTSTR*)&lpszText);
		if ((d == 0.0) && (chFirst != _T('0')))
			return FALSE;   // could not convert
		while ((*lpszText == _T(' ')) || (*lpszText == _T('\t')))
			lpszText++;

		if (*lpszText != _T('\0'))
			return FALSE;   // not terminated properly

		return TRUE;
	}
};

