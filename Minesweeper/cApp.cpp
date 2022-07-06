#include "cApp.h"



wxIMPLEMENT_APP(cApp); //used to make the App the starting point of the program


bool cApp::OnInit() {
	m_frame1 = new cMain();
	m_frame1->Show();
	return true;
}