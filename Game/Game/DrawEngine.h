#pragma once
#include "GameEngine.h"
#include "Gui.h"
#include "Camera.h"
class DrawEngine
{
	vector<GuiObj*> guiObj;
	vector<Unit*>* AllUnitObj;
	Camera* camera;
public:
	DrawEngine(Gui* gui, GameEngine* GEngine)
	{
		//guiObj = gui->ObjectForDraw();
		AllUnitObj = GEngine->GetUnits();
		camera = gui->GetCamera();
	}
	void Loop()
	{
		Draw();
	}
	void Draw()
	{//+прикрутить гуи
		
		static int time =0,count=1000;
		if((clock() - time) > 1000)
		{
			//system("cls");
			time = clock();
				std::cout<<"FPS:"<<count<<" "<<endl;//фпс и количество объектов
				count=0;
		}
		else
			count++;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		camera->Look();
		glEnable(GL_FOG); 
		glColor3f(0.0,1.0,1.0);
		glBegin(GL_POLYGON);
			glVertex3f(-20,-20,0);
			glVertex3f(20,-20,0);
			glVertex3f(20,20,0);
			glVertex3f(-20,20,0);
		glEnd();
		
		int len = AllUnitObj->size();
		for(int i=0;i<len;i++)
			(*AllUnitObj)[i]->Draw();
		
		glutSwapBuffers();
	}
	~DrawEngine(void){}
};

