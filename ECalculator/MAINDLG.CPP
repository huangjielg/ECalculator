#include "stdafx.h"
#include "resource.h"
#include "MainDlg.h"
#include "CRLCDialog.h"

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ

	return 0;
}


LRESULT CMainDlg::OnCbnSelchangeComboMode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	if (m_pChildDialog != NULL)
	{
		::EndDialog(m_pChildDialog->GetHWnd(), IDOK); 
		delete m_pChildDialog;
	}
	RECT r;
	m_stcChild.GetWindowRect(&r);
	this->ScreenToClient(&r);
	switch (m_comboMode.GetCurSel())
	{
	case 0: {
			CRLCDialog* p = new CRLCDialog();
			p->Create(this->m_hWnd, r, 0);
			p->ShowWindow(SW_SHOW);
			m_pChildDialog = p;
			p->SetFocus();
		}
		break;
	}
	return 0;
}


LRESULT CMainDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	CDialogResize<CMainDlg>::OnSize(uMsg, wParam, lParam, bHandled);
	RECT r;
	m_stcChild.GetWindowRect(&r);
	this->ScreenToClient(&r);
	::MoveWindow(m_pChildDialog->GetHWnd(),r.left,r.top,r.right-r.left,r.bottom-r.top,true);
	return 0;
}


LRESULT CMainDlg::OnBnClickedButtonQuit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	
	EndDialog(IDOK);
	return 0;
}
LRESULT CMainDlg::OnBnClickedButtonCalc(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if (m_pChildDialog) {
		m_pChildDialog->DoCalc();
	}
	
	return 0;
}