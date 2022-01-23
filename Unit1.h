//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.ImgList.hpp>
#include <System.ImageList.hpp>
#include <FMX.Ani.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TListBox *TasksListBox;
	TButton *RollDice;
	TImage *BackgroundImage;
	TImage *PlayerImage;
	TGroupBox *PlayerSelect;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton3;
	TRadioButton *RadioButton4;
	TButton *Start;
	TImageList *ImageList1;
	TButton *ResetButton;
	TTimer *WalkingTimer;
	TButton *Button1;
	TTimer *EnableToAnimate;
	void __fastcall RollDiceClick(TObject *Sender);
	void __fastcall TasksListBoxItemClick(TCustomListBox * const Sender, TListBoxItem * const Item);
	void __fastcall StartGameClick(TObject *Sender);
	void __fastcall ResetButtonClick(TObject *Sender);
	void __fastcall WalkingTimerTimer(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall EnableToAnimateTimer(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
