#pragma once
#include "wx/wx.h"


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	int nFieldWidth = 10;
	int nFieldHight = 10;
	wxButton** btn;
	int* nField = nullptr;
	bool bFirstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

