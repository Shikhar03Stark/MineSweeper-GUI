#include "Grid.h"

wxBEGIN_EVENT_TABLE(Grid, wxFrame)

wxEND_EVENT_TABLE()

Grid::Grid() :wxFrame(nullptr, wxID_ANY, "MineSweeper - Shikhar03STARK", wxPoint(60, 60), wxSize(1000, 800)) {
	cell = new wxButton * [gridWidth * gridHeight];
	wxGridSizer* grid = new wxGridSizer(gridHeight, gridWidth, 2, 2);
	mine = new bool[gridHeight * gridWidth];
	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	for (int i = 0; i < gridHeight; i++)
	{
		for (int j = 0; j < gridWidth; j++) {
			cell[i * gridHeight + j] = new wxButton(this, 1000 + (i * gridHeight + j));
			cell[i * gridHeight + j]->SetFont(font);
			grid->Add(cell[i * gridHeight + j], 1, wxEXPAND | wxALL);
			mine[i * gridHeight + j] = 0;
			//add Event Listener
			cell[i * gridHeight + j]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Grid::onCellClick, this);
		}
	}

	this->SetSizer(grid);
	this->Layout();
}

void Grid::onCellClick(wxCommandEvent& e) {
	//get Coordinates of Cell
	unsigned int x = (e.GetId() - 1000) / gridWidth;
	unsigned int y = (e.GetId() - 1000) % gridHeight;

	if (!isGameStart) {
		for (int i = 0; i < numMine; i++) {
			unsigned int rx = rand() % 10;
			unsigned int ry = rand() % 10;

			if (mine[rx * gridHeight + ry] == 1 || (rx == x && ry == y)) {
				rx = rand() % 10;
				ry = rand() % 10;
				i--;
			}
			else {
				mine[rx * gridHeight + ry] = 1;
			}
		}

		int mineCount = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (x + i > 0 && y + j > 0 && x + i < gridWidth && y + j < gridHeight) {
					if (mine[(x + i) * gridHeight + (y + j)] == 1) {
						mineCount++;
					}
				}
			}
		}

		cell[x * gridHeight + y]->Enable(false);
		cell[x * gridHeight + y]->SetLabel(std::to_string(mineCount));

		isGameStart = true;
	}
	else {
		if (mine[x * gridHeight + y] == 1) {
			wxMessageBox("Booom!! You hit a Mine. Game Over", "Game Over");
			for (int i = 0; i < gridHeight*gridWidth; i++) {
				mine[i] = 0;
				cell[i]->Enable(true);
				cell[i]->SetLabel("");
			}
			isGameStart = false;
		}
		else {
			int mineCount = 0;
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (x + i > 0 && y + j > 0 && x+i < gridWidth && y+j < gridHeight) {
						if (mine[(x + i) * gridHeight + (y + j)] == 1) {
							mineCount++;
						}
					}
				}
			}

			cell[x * gridHeight + y]->Enable(false);
			cell[x * gridHeight + y]->SetLabel(std::to_string(mineCount));

		}
	}

	e.Skip();
}