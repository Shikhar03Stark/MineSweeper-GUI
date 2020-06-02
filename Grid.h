#pragma once

#include <wx/wx.h>

class Grid: public wxFrame
{

public:
	Grid();

	unsigned int gridWidth = 10;
	unsigned int gridHeight = 10;
	wxButton** cell;
	bool isGameStart = false;
	bool* mine;
	unsigned int numMine = 30;
	
	wxDECLARE_EVENT_TABLE();

	void onCellClick(wxCommandEvent& e);


	
};

