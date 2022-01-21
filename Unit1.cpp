//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
#include "main.h"
#include "Board.h"
#include "Grid2D.h"
#include "PlayerClass.h"
#include <vector>
#include <random>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//Player me{ "Donovan" };
//Player angie{ "Angie" };
//std::vector<Player> players{me, angie};

Player* player1{ new Player{} };
Player* player2{ new Player{} };
Player* player3{ new Player{} };
Player* player4{ new Player{} };
std::vector<Player*> playersVector{ player1, player2, player3, player4 };

int playersPlaying{};
static int global_playerTurnCounter{ 0 };
static int global_max_players{ 4 };
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	setupRandomiser();
	for (int i = 0; i < 4; ++i){
		TasksListBox->Items->Add("initialising image");
		TImage* playerImg;
		playerImg = new TImage(Form1);
		playerImg->Parent = Form1;
		playerImg->Width = 50;
		playerImg->Height = 50;
		playerImg->Position->X = i * 30 + 3;
		playerImg->Position->Y = 542.4;
		playerImg->Bitmap->Assign(
			ImageList1->Bitmap(playerImg->Size->Size, i));

		playersVector[i]->playerImage = playerImg;

	}
}
//---------------------------------------------------------------------------
Player* getTurn()
{
	return playersVector[global_playerTurnCounter++ % playersPlaying];
}
//---------------------------------------------------------------------------
int findByValue(std::map<int, int>& mapToLook, int valueToFind) {
	// returns the Key of the corresponding value found, otherwise returns -1;
	auto current{ mapToLook.begin() };
	while (current != mapToLook.end()) {
		if (current->second == valueToFind) {
			return current->first;
		}
		++current;
	}
	return -1;
}
//---------------------------------------------------------------------------
void mainMove(Player* player, int steps){
	player->move(steps);
	int stepOnPlayer{ findByValue(Board::occupiedPositions, player->getGrid()) };
	if (stepOnPlayer != -1){
		// stepped on somebody
		Board::occupiedPositions[stepOnPlayer] =
			Board::occupiedPositions[player->getID()];

		// feels quite inefficient but whatever stepping doesn't occur everytime
		int previousPos{ Board::occupiedPositions[player->getID()] };
		int rowIndex{};
		int columnIndex{};
		player->myPosition.convertGridToRowColumnOut(previousPos, rowIndex, columnIndex);
		if (previousPos == 0){
			playersVector[stepOnPlayer]->resetPos(
				player->getID() * 30 + 3, 542.4, 0);
		}
		else{
			playersVector[stepOnPlayer]->resetPos(
				Board::horizontalCoords[columnIndex]
				, Board::verticalCoords[rowIndex]
				, previousPos);
		}
	}
	Board::occupiedPositions[player->getID()] = player->getGrid();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RollDiceClick(TObject *Sender)
{
	int randNum{ getRandomNumber(1, 6) };
	TasksListBox->Items->Clear();
//	std::this_thread::sleep_for(static_cast<std::chrono::milliseconds>(500));
	TasksListBox->Items->Insert(0, "Rolling... ");


	TasksListBox->Items->Insert(1, randNum);

	Player* currentPlayer = getTurn();

	TasksListBox->Items->Insert(1, currentPlayer->getID());

	mainMove(currentPlayer, randNum);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::TasksListBoxItemClick(TCustomListBox * const Sender, TListBoxItem * const Item)

{
	int index{ Item->Index };
	TasksListBox->Items->Delete(Item->Index);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StartGameClick(TObject *Sender)
{
	// brute force is the only way i can do it, tried for damn long
	if (RadioButton1->IsChecked){
		playersPlaying = 1;
	}
	if (RadioButton2->IsChecked){
		playersPlaying = 2;
	}
	if (RadioButton3->IsChecked){
		playersPlaying = 3;
	}
	if (RadioButton4->IsChecked){
		playersPlaying = 4;
	}
	TasksListBox->Items->Add(playersPlaying);

	for (int i = 0; i < 4; ++i){
		if (i < playersPlaying)
			playersVector[i]->playerImage->Visible = 1;
		else
			playersVector[i]->playerImage->Visible = 0;
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	static int index{ 0 };
	Image1->Bitmap->Assign(ImageList1->Bitmap(Image1->Size->Size, index++ % 4));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if (Image1){
		delete Image1;
		Image1 = nullptr;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ResetButtonClick(TObject *Sender)
{
	 global_playerTurnCounter = 0;
	 for (int i = 0; i <  global_max_players; ++i){
		 playersVector[i]->resetPos(i * 30 + 3, 542.4);
	 }
}
//---------------------------------------------------------------------------

