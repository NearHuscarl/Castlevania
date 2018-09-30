#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "../Animation/Animation.h"


using namespace std;

class GameObject
{
protected:

	float x; 
	float y;

	float vx;
	float vy;

	int nx;	 

	int state;									

	static vector<Animation*> animations;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }

	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }


	static void AddAnimation(int aniId);

	GameObject();

	void Update(DWORD dt);
	void Render();
	
	virtual ~GameObject();
};