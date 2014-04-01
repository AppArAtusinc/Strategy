#ifndef ENGINE_H
#define ENGINE_H

#include<map>
#include<time.h>
#include"Camera.h"
struct SMouse
{
    double x,y;
    int tx,ty;
    bool left,midle,right;
	SMouse()
	{
		left = midle = right = 0;
	}
};

class engine
{
    SMouse mouse;
    Camera* camera;
    std::map<int,bool> keyboard;

public:
    engine(int Test = 0);
    void Keyboard(int key,int x, int y );
    void Mouse(int button, int state, int x, int y);
    void MouseMoution(int x, int y);
    void Draw();
    void Proccesing();
};

#endif // ENGINE_H
