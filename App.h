#pragma once

#include <wx/wx.h>
#include "Grid.h"

class App: public wxApp
{
private:
	Grid* frame = nullptr;
public:
	virtual bool OnInit();
};

