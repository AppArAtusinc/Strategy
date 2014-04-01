#include<GL\glut.h>
#include<GL\freeglut.h>
#include"engine.h"
#pragma comment(lib,"DevIL.lib")
#pragma comment(lib,"ilut.lib")
#pragma comment(lib,"ilu.lib")
engine *eng;

void Display(void)
{/*
*/
}
void Reshape(GLint w, GLint h)
{
    glViewport(0,0,w,h);
    gluPerspective(45, (float)w/h, 0.1, 200);
    /*Width = w;
    Height =h;*/

}
 int keys[256];
void KeyboardDown( unsigned char key, int x, int y )
{
#define ESCAPE '\033'

    if( key == ESCAPE )
        exit(0);

    eng->Keyboard(key,x,y);

}
void KeyboarUp( unsigned char key, int x, int y )
{
    eng->Keyboard(key,x,y);
}

void Init()
{

                glClearColor(1, 1, 1,1);


                glMatrixMode( GL_PROJECTION);
                glLoadIdentity();

                gluPerspective(45, 1366.0/768, 0.1, 200);

                glMatrixMode( GL_MODELVIEW);
                glLoadIdentity();

                glEnable( GL_DEPTH_TEST);
                glEnable( GL_LIGHTING);
                glEnable( GL_LIGHT0);

                glBlendFunc( GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA);
                glHint( GL_LINE_SMOOTH_HINT,  GL_NICEST);
                glEnable( GL_BLEND);
                glEnable( GL_LINE_SMOOTH);
                glLineWidth(1.0f);
                eng = new engine();
   //укажем начальную позицию камеры,взгляда и вертикального вектора.


}

void Time(int)
{
    eng->Proccesing();
    eng->Draw();
    glutTimerFunc(50,Time,0);
}
void MouseMotion(int x, int y)
{
    eng->MouseMoution(x,y);
}

void Mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
        eng->Mouse(button, state,x,y);
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    //glutInitWindowSize(512, 288);
 
	//glutGameModeString( "1024x768:32@60" );
	//glutEnterGameMode();
    glutCreateWindow("let's start");
    glutIgnoreKeyRepeat(true);
    Init();
	glutFullScreen();
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(KeyboardDown);
    glutKeyboardUpFunc(KeyboarUp);
    glutMouseFunc(Mouse);
    glutMotionFunc(MouseMotion);
    glutTimerFunc(50,Time,0);
    glutMainLoop();
}
