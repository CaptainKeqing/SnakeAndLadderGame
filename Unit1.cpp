//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
#include "main.h"
#include "Board.h"
#include "Grid2D.h"
#include "PlayerClass.h"
#include <vector>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;

Player* player1{ new Player{} };
Player* player2{ new Player{} };
Player* player3{ new Player{} };
Player* player4{ new Player{} };
std::vector<Player*> playersVector{ player1, player2, player3, player4 };

int playersPlaying{};
static int global_playerTurnCounter{ 0 };
static int global_max_players{ 4 };

// for animations
static int ticks{ };
static double yChange{ };
static double xChange{ };
static int count{0};

static std::array<double, 2> startCoords{};
static std::array<double, 2> endCoords{};
static TImage* travellingImage;

static std::vector<std::array<double, 2>> waypoints{};
static int currentWaypoint{ 0 };

// random waypoints for testing
static std::array<double, 2> StartZone{50, 250};
static std::array<double, 2> EndZone{250, 50};
static std::array<double, 2> MiddleZone{250, 250};

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
void mainMove(Player* player, int steps, TTimer* animator){
	int currentPlayerGrid{ player->getGrid() };
	int supposedPlayerGrid{ currentPlayerGrid + steps };
	waypoints.clear();
	int rowIndex{};
	int columnIndex{};
	for (int step = 0; step <= steps; ++step){
		player->myPosition.convertGridToRowColumnOut(currentPlayerGrid + step, rowIndex, columnIndex);
		std::array<double, 2> nextWaypoint{ Board::horizontalCoords[columnIndex],
							Board::verticalCoords[rowIndex]};
		waypoints.push_back(nextWaypoint);
	}
	player->move(steps);
	// if stepped on Snake / Ladder, actual grid != supposedPlayerGrid.
	if (player->getGrid() < supposedPlayerGrid){
		// stepped on Snake. Ideally, I actually already know the index
		// of the snake/ladder i stepped on, but its burried so deep within
		// the Board that i dont know an elegant way to extract that info.
		auto snake{ Board::SnakesCoords[Board::steppedOnInfo.index] };
		for (int i = 0; i < snake.size(); ++i){
			waypoints.push_back(snake[i]);
		}
//		waypoints = Board::SnakesCoords[Board::steppedOnInfo.index];
	}
	else if (player->getGrid() > supposedPlayerGrid){
		// stepped on ladder.
		player->myPosition.convertGridToRowColumnOut(player->getGrid(), rowIndex, columnIndex);
		std::array<double, 2> nextWaypoint{ Board::horizontalCoords[columnIndex],
							Board::verticalCoords[rowIndex]};
		waypoints.push_back(nextWaypoint);
	}
//	else{
//		player->playerImage->Position->X = player->getPos()[0];
//		player->playerImage->Position->Y = player->getPos()[1];
//	}
	animator->Enabled = True;

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
	if (EnableToAnimate->Enabled){   // prevent clicking of button when already in action
		return;
	}

	int randNum{ getRandomNumber(1, 6) };
	TasksListBox->Items->Clear();

	TasksListBox->Items->Insert(0, "Rolling... ");


	TasksListBox->Items->Insert(1, randNum);

	Player* currentPlayer = getTurn();

	TasksListBox->Items->Insert(1, currentPlayer->getID());

	mainMove(currentPlayer, randNum, EnableToAnimate);

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

void __fastcall TForm1::ResetButtonClick(TObject *Sender)
{
	 global_playerTurnCounter = 0;
	 for (int i = 0; i <  global_max_players; ++i){
		 playersVector[i]->resetPos(i * 30 + 3, 542.4);
	 }
}
//---------------------------------------------------------------------------
void animate(TTimer* Timer, const std::array<double, 2>& start
						  , const std::array<double, 2>& end
							  , int tics, TImage* traveller)
{
	Timer->Enabled = True;
	startCoords = start;
	endCoords = end;
	ticks = tics;
	yChange = startCoords[1] - endCoords[1];
	xChange = startCoords[0] - endCoords[0];
	travellingImage = traveller;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::WalkingTimerTimer(TObject *Sender)
{
	while (count < ticks){
		travellingImage->Position->X -= xChange / ticks;
		travellingImage->Position->Y -= yChange / ticks;
		++count;
		return;
	}
	travellingImage->Position->X = endCoords[0];
	travellingImage->Position->Y = endCoords[1];
	WalkingTimer->Enabled = False;
	count = 0;
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
//	waypoints = { {475, 94}, {411, 78}, {387, 150}, {315, 174}, {315, 238},
//				  {379, 254}, {395, 302}, {363, 334}, {323, 326} };
	waypoints = Board::SnakesCoords[9];
	EnableToAnimate->Enabled = True;

//	animate(WalkingTimer, StartZone, EndZone, 30, PlayerImage);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EnableToAnimateTimer(TObject *Sender)
{

	animate(WalkingTimer, waypoints[currentWaypoint], waypoints[currentWaypoint + 1]
				, 15, playersVector[(global_playerTurnCounter - 1) % playersPlaying]->playerImage);
	currentWaypoint++;
	if (currentWaypoint == waypoints.size() - 1){
		EnableToAnimate->Enabled = False;
		currentWaypoint = 0;
	}
}
//---------------------------------------------------------------------------

