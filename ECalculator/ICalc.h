#pragma once
class ICalc
{
public:
	virtual void DoCalc() = 0;
	virtual HWND    GetHWnd() = 0;
};