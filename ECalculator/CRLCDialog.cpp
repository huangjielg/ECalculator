#include "stdafx.h"
#include "resource.h"
#include "CRLCDialog.h"
#include <math.h>
#include <corecrt_math_defines.h>
void CRLCDialog::DoCalc()
{
	std::vector<double> par;
	par.resize(4);
	//计算电阻
	std::function<double(void)>f1= [&]()->double {
		double r = par[0];
		double l = par[1];
		double c = par[2];
		double f = par[3];
		double w = 2 * M_PI * f;
		r = 2 * l * sqrt(1 / l / c - w * w);
		return r;
	};
	//计算电感
	std::function<double(void)>f2 = [&]()->double {
		return NAN;
	};
	//计算电容
	std::function<double(void)>f3 = [&]()->double {
		double r = par[0];
		double l = par[1];
		double c = par[2];
		double f = par[3];

		double w = 2 * M_PI * f;
		double r2l = r / 2 / l;

		c = 1 / (l * (w * w + r2l * r2l));
		return  c;
	};	
	//计算频率
	std::function<double(void)>f4 = [&]()->double {
		double r = par[0];
		double l = par[1];
		double c = par[2];
		double f = par[3];
		double r2l = r / 2 / l;
		f =  M_1_PI* sqrt(1 / (l * c) - r2l*r2l)/2;
		return f;
	};


	struct {
		CEdit& edt;
		double &d;
		std::function<double(void)> f;
		BOOL bOk;
	}v[] = {
		{m_edtR,par[0],f1},
		{m_edtL,par[1],f2},
		{m_edtC,par[2],f3},
		{m_edtFreq,par[3],f4}
	};
	INT numFail=0;
	for (int i = 0; i < sizeof(v) / sizeof(v[0]); i++)
	{
		CString s;
		v[i].edt.GetWindowText(s);
		v[i].bOk = _AtlSimpleFloatParse(s, v[i].d);
		if (!v[i].bOk)
			numFail++;
	}
	if (numFail == 0) {
		numFail = 1;
		v[3].bOk = FALSE;
	}
	if (numFail != 1) {
		return;
	}
	for (int i = 0; i < sizeof(v) / sizeof(v[0]); i++)
	{
		if (!v[i].bOk) {
			v[i].d = v[i].f();
			CString s;
			s.Format(_T("%4.5g"), v[i].d);
			v[i].edt.SetWindowText(s);
		}
	}

	double r = par[0];
	double l = par[1];
	double c = par[2];
	double f = par[3];
	double r2l = r / 2 / l;

	CString s;
	s.Format(_T("R/L=%4.5g"), r2l);
	s.AppendFormat(_T("\r\nQ=2*PI*f*L/R=%4.5g"), 2*M_PI*f*l/r);
	s.AppendFormat(_T("\r\n一个周期后幅度衰减为:Exp(-R/L/f/2)=%4.5g"), exp(-r/l/f/2));
	m_edtStatus.SetWindowText(s);
	
}
