#pragma once

struct KeyEventArgs
{
	KeyEventArgs(int keyCode, int modifier)
	{
		this->KeyCode = keyCode;
		this->Modifier = modifier;
	}
	int KeyCode;
	int Modifier = -1;
};

//struct KeyDownEventArgs
//{
//	KeyDownEventArgs(int keyCode, int modifier)
//	{
//		this->keyCode = keyCode;
//		this->modifier = modifier;
//	}
//	int keyCode;
//	int modifier = -1;
//};
//
//struct KeyUpEventArgs
//{
//	KeyUpEventArgs(int keyCode, int modifier)
//	{
//		this->keyCode = keyCode;
//		this->modifier = modifier;
//	}
//	int keyCode;
//	int modifier = -1;
//};