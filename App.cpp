#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	frame = new Grid();
	frame->Show();
	return true;
}
