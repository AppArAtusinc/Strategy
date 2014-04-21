#include"engine.h"
#include<time.h>
#include<vector>
#include<IL\il.h>
#include<GL/freeglut.h>
#include<iostream>
#include"GameObject.h"
#include"TextureLoader.h"
vector<Unit*> units;
FactoryUnit* fac;
TextureImage* tex;
void DrawGrid(int x, float quad_size)
{
            //x - количество или длина сетки, quad_size - размер клетки
    glPushMatrix(); //Рисуем оси координат, цвет объявлен в самом начале

    glTranslated((-x * 2) / 2, 0, 0);
    glRotated(90, 0, 1, 0);
    glutSolidCylinder(0.02, x * 2, 12, 12);
    glPopMatrix();

    glPushMatrix();

    glTranslated(0, 0, (-x * 2) / 2);
    glutSolidCylinder(0.02, x * 2, 12, 12);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, x / 2, 0);
    glRotated(90, 1, 0, 0);
    glutSolidCylinder(0.02, x, 12, 12);
    glPopMatrix();

    glBegin(GL_LINES);


            // Рисуем сетку 1х1 вдоль осей
            for (float i = -x; i <= x; i += 1)
            {
                glBegin(GL_LINES);
                // Ось Х
                glVertex3f(-x * quad_size, 0, i * quad_size);
                glVertex3f(x * quad_size, 0, i * quad_size);

                // Ось Z
                glVertex3f(i * quad_size, 0, -x * quad_size);
                glVertex3f(i * quad_size, 0, x * quad_size);
                glEnd();
            }
        }

engine::engine(int Test)
{      
	srand((unsigned int)&units);
	ilInit();
    iluInit();
    camera = new Camera(0,10,10,0,0,0,0,0,1);
	tex = new TextureImage();
	LoadTexture(IL_JPG,"grass.jpg",tex);
	fac = new  FactoryUnit("sdf");
	fac->Load("cube2.obj", "wall.jpg");
	int randn = 100;
	for(int i=0;i<randn;i++)
		units.push_back(fac->GetUnit(0,rand()%50 - rand()%50,rand()%50 - rand()%50));
	//color[3] = new unsigned char[3];
}
void engine::Keyboard(int key, int x, int y)
{
    keyboard[key]= !keyboard[key];
}
void engine::Mouse(int button, int state, int x, int y)
{

    if(button == GLUT_LEFT_BUTTON)
    {
        mouse.left = state;
        mouse.x = x;
        mouse.y = y;
        mouse.tx = mouse.x;
        mouse.ty = mouse.y;
    }
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Indificator ID;
		ID.bytes[3]=0;
		glClear(GL_COLOR_BUFFER_BIT);
			for(int i=0;i<units.size();i++ )
				units[i]->EasyDraw();
			glReadPixels ( x, 288-y, 1, 1,  GL_BGR_EXT, GL_UNSIGNED_BYTE, ID.bytes );
		//system("cls");
		if(ID.bytes[0] == 255 && ID.bytes[1] == 255 && ID.bytes[2] == 255)
			cout<<"Empty"<<endl;
		else
			cout<<"ID:"<<ID.ID<<endl;
	}
}
void engine::MouseMoution(int x, int y)
{
    if(mouse.left)
    {
    }

}
void engine::Draw()//<--пока типа заглушка
{
	static int time =0,count=1000;
	if((clock() - time) > 1000)
	{
		//system("cls");
		time = clock();
			std::cout<<"FPS:"<<count<<" "<<"NumOfObj:"<<units.size()<<endl;//фпс и количество объектов
			count=0;
		
	}
	else
		count++;
	glColor3f(1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera->Look(); //Обновляем взгляд камеры
	glBindTexture(GL_TEXTURE_2D,tex->texID);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glTexCoord2f(0,0);glVertex3f(-20,-20,0);
	glTexCoord2f(1,0);glVertex3f(20,-20,0);
	glTexCoord2f(1,1);glVertex3f(20,20,0);
	glTexCoord2f(0,1);glVertex3f(-20,20,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	for(int i=0;i<units.size();i++ )
		units[i]->EasyDraw();
	/*glPushMatrix();
		DrawGrid(30,1);
	glPopMatrix();*/
	
  glutSwapBuffers();
}
void engine::Proccesing()
{
    for(std::map<int,bool>::iterator i = keyboard.begin();i!=keyboard.end();i++)
    {
        if((*i).first == 'w' && (*i).second)
            camera->Move_Camera(1);
        if((*i).first == 's' && (*i).second)
            camera->Move_Camera(-1);
        if((*i).first == 'a' && (*i).second)
            camera->Strafe(1);
        if((*i).first == 'd' && (*i).second)
            camera->Strafe(-1);
        if((*i).first == 'q' && (*i).second)
            camera->upDown(1);
        if((*i).first == 'e' && (*i).second)
            camera->upDown(-1);
    }
}



