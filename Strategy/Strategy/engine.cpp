#include"engine.h"
#include<time.h>
#include<vector>
#include<IL\il.h>
#include<GL/freeglut.h>
#include<iostream>
#include"GameObject.h"
#include"TextureLoader.h"
Unit* unit;
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
	ilInit();
    iluInit();
    camera = new Camera(0,10,10,0,0,0,0,0,-1);
	tex = new TextureImage();
	LoadTexture(IL_JPG,"grass.jpg",tex);
	fac = new  FactoryUnit("sdf");
	fac->Load("women.obj", "wall.jpg");
	unit = fac->GetUnit(0,0,0);
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
}
void engine::MouseMoution(int x, int y)
{
    if(mouse.left)
    {
    }

}
void engine::Draw()//<--пока типа заглушка
{
	static int time =0,count=0;
	if((clock() - time) > 1000)
	{
		system("cls");
		time = clock();
		std::cout<<count;
		count=0;
	}
	else
		count++;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera->Look(); //Обновляем взгляд камеры
	glBindTexture(GL_TEXTURE_2D,tex->texID);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glTexCoord2f(0,0);glVertex3f(-20,0,-20);
	glTexCoord2f(1,0);glVertex3f(20,0,-20);
	glTexCoord2f(1,1);glVertex3f(20,0,20);
	glTexCoord2f(0,1);glVertex3f(-20,0,20);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	unit->Draw();
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
            camera->Strafe(-1);
        if((*i).first == 'd' && (*i).second)
            camera->Strafe(1);
        if((*i).first == 'q' && (*i).second)
            camera->upDown(1);
        if((*i).first == 'e' && (*i).second)
            camera->upDown(-1);
    }
}



