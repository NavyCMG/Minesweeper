#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(30,30), wxSize(800,600) ) {

	btn = new wxButton * [nFieldWidth * nFieldHight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHight, 0, 0);

	nField = new int[nFieldWidth * nFieldHight];

	for (int x = 0; x < nFieldWidth; ++x)
	{
		for (int y = 0; y < nFieldHight; ++y)
		{
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);

			nField[y * nFieldWidth + x] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();
}
cMain::~cMain() {
	delete[] btn;

}

void cMain::OnButtonClicked(wxCommandEvent& evt) {

	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (bFirstClick) {
		int mines = 30;
		while (mines) {

			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHight;

			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y) {
				nField[ry * nFieldHight + rx] = -1;
				--mines;
			}
		}
		bFirstClick = false;
	}

	btn[y * nFieldWidth + x]->Enable(false);

	if (nField[y * nFieldWidth + x] == -1)
	{
		wxMessageBox(" You hit a mine, Game Over");

		bFirstClick = true;
		for (int x = 0; x < nFieldWidth; ++x) {
			for (int y = 0; y < nFieldWidth; ++y) {
				nField[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
			}
			
		}
	}
	else {
		int mine_count = 0;
		for (int i = -1; i < 2; ++i) {
			for (int j = -1; j < 2; ++j) {
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHight) {
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1) {
						++mine_count;
					}
				}
			}
		}
		if (mine_count > 0) {
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
	}

	evt.Skip();
}