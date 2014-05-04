#pragma once
#include <gl\glew.h>
#include <GL\glut.h>
#include <time.h>
#include "Camera.h"
#include "GameObject.h"
class GameKeyBoard
{
	bool keys[256];
public:
	GameKeyBoard()
	{
		for(int i=0;i<256;i++)
		keys[i] = false;
	}
	inline bool isDown(char key)
	{
		return keys[key];
	}
	inline bool isUp(char key)
	{
		return !keys[key];
	}
	inline void Set(char key, bool value)
	{
		keys[key] = value;
	}

};

class GameMouse
{
	bool left, middle, right;
	GLint x,y;
public:
	//cMouse();				//по идее он не нужен...
	bool IsLeft();
	bool IsMiddle();
	bool IsRight();
	void Left(bool value)		//изменяет соответвующие значения
	{
		left = value;
	}
	void Middle(bool value)
	{
		middle = value;
	}
	void Right(bool value)
	{
		right = value;
	}
	void SetPos(GLint X, GLint Y)
	{
		x = X;
		y = Y;
	}
	inline GLuint GetX();
	inline GLuint GetY();
};
class GuiObj;
class Gui
{
	GLuint time;
	Camera* camera;
	GameMouse mouse;
	GameKeyBoard keyboard;
	//std::vector<GuiObject> interface; 
	GameEngine* GEngine;
	vector<GLuint> ids;
	GLuint height, width;
public:
	Gui(GLuint Height, GLuint Width, GameEngine* GEngine)
	{
		ids = vector<GLuint>(1);
		height = Height;
		width = Width;
		time = clock();
		this->GEngine = GEngine;
		camera = new Camera(0,10,10,0,0,0,0,0,1);
	}
	void Keyboard(int key,bool state, int x, int y )
	{
		keyboard.Set(key, state);
	}
	void Mouse(int button, int state, int x, int y)
	{
		 /*if(button == GLUT_LEFT_BUTTON)
		{
			mouse.Left( state);
			mouse.SetPos(x,y);
		}*/
		if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			glDisable(GL_FOG);
			Indificator ID;
			ID.bytes[3]=0;
			glClear(GL_COLOR_BUFFER_BIT);
			vector< Unit*> *units = GEngine->GetUnits(); 
			int len = units->size();
			for(int i=0;i<len;i++)
				(*units)[i]->ColorDraw();
			glReadPixels ( x, height-y, 1, 1,  GL_BGR_EXT, GL_UNSIGNED_BYTE, ID.bytes );
			//system("cls");
			if(ID.bytes[0] == 255 && ID.bytes[1] == 255 && ID.bytes[2] == 255)
				cout<<"Empty"<<endl;
			else
			{
				ids[0]=ID.ID;
				cout<<"ID:"<<ID.ID<<endl;
			}
			GEngine->SetUnitStatus(ids[0],State("Jump"));
		}
		if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		{
			GEngine->SetUnitStatus(ids[0],State("GoTo",x,y));
		}
		if(button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
		{
			GEngine->SetUnitStatus(ids[0],State("Jump"));
		}
	}
	void MouseMoution(int x, int y)
	{
}
	Camera* GetCamera()
	{
		return camera;
	}
	vector<GuiObj*>* ObjectForDraw();
	void Proccesing()
	{
		if((clock() - time) < 10)
			return;
		time = clock();
#define gspeed 1
		if(keyboard.isDown('w'))
				camera->Move_Camera(gspeed);
		if(keyboard.isDown('s'))
			camera->Move_Camera(-gspeed);

		if(keyboard.isDown('a'))
			camera->Strafe(gspeed);
		if(keyboard.isDown('d'))
			camera->Strafe(-gspeed);

		if(keyboard.isDown('q'))
			camera->upDown(gspeed);
		if(keyboard.isDown('e'))
			camera->upDown(-gspeed);
	}

	void SendToGame()
	{

	}
	~Gui(void);
};

