#include "engine.h"
#include<GL/freeglut.h>

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
    camera = new Camera(0,10,10,0,0,0,0,0,-1);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3i(255, 0, 0);
    camera->Look(); //Обновляем взгляд камеры
    glPushMatrix();
    DrawGrid(30, 1);//Нарисуем сетку
    glPopMatrix();
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



