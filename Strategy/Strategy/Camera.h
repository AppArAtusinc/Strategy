#pragma once
#include<GL/glut.h>
#include<math.h>

class Camera
{
    struct Vector3D
    {
        float x, y, z;
    };
    Vector3D mPos;   //Вектор позиции камеры
    Vector3D mView;  //Куда смотрит камера
    Vector3D mUp;    //Вектор верхнего направления
    Vector3D mStrafe;//Вектор для стрейфа (движения влево и вправо) камеры.



    float Magnitude(Vector3D vNormal)
            {
                // Это даст нам величину нашей нормали,
                // т.е. длину вектора. Мы используем эту информацию для нормализации
                // вектора. Вот формула: magnitude = sqrt(V.x^2 + V.y^2 + V.z^2)   где V - вектор.

                return (float) sqrt((vNormal.x * vNormal.x) +
                        (vNormal.y * vNormal.y) +
                        (vNormal.z * vNormal.z));
            }
    Vector3D Normalize(Vector3D vVector)
            {
                // Вы спросите, для чего эта ф-я? Мы должны убедиться, что наш вектор нормализирован.
                // Вектор нормализирован - значит, его длинна равна 1. Например,
                // вектор (2,0,0) после нормализации будет (1,0,0).

                // Вычислим величину нормали
                float magnitude = Magnitude(vVector);

                // Теперь у нас есть величина, и мы можем разделить наш вектор на его величину.
                // Это сделает длинну вектора равной единице, так с ним будет легче работать.
                vVector.x = vVector.x / magnitude;
                vVector.y = vVector.y / magnitude;
                vVector.z = vVector.z / magnitude;

                return vVector;
            }
public:
    Camera(float pos_x, float pos_y, float pos_z,
                float view_x, float view_y, float view_z,
                float up_x, float up_y, float up_z)
    {
        Position_Camera(pos_x, pos_y, pos_z,
                        view_x, view_y, view_z,
                        up_x, up_y, up_z);
    }
    void Position_Camera(float pos_x, float pos_y, float pos_z,
                    float view_x, float view_y, float view_z,
                    float up_x, float up_y, float up_z)
            {
                mPos.x = pos_x;//Позиция камеры
                mPos.y = pos_y;//
                mPos.z = pos_z;//
                mView.x = view_x;//Куда смотрит, т.е. взгляд
                mView.y = view_y;//
                mView.z = view_z;//
                mUp.x = up_x;//Вертикальный вектор камеры
                mUp.y = up_y;//
                mUp.z = up_z;//
                mStrafe.x = 1;
                mStrafe.y = 1;
                mStrafe.z = 1;

            }

    void Move_Camera(float speed) //Задаем скорость
            {
				mPos.y +=  mStrafe.y * speed;
				mView.y += mStrafe.y * speed;
                /*Vector3D vVector; //Получаем вектор взгляда
                vVector.x = mView.x - mPos.x;
                vVector.y = mView.y - mPos.y;
                vVector.z = mView.z - mPos.z;

                vVector.y = 0.0f; // Это запрещает камере подниматься вверх
                vVector = Normalize(vVector);

                mPos.x += vVector.x * speed;
                mPos.z += vVector.z * speed;
                mView.x += vVector.x * speed;
                mView.z += vVector.z * speed;*/
            }
    void Strafe(float speed)
            {
                // добавим вектор стрейфа к позиции
               // mPos.x += mStrafe.x * speed;
                mPos.x += mStrafe.z * speed;

                // Добавим теперь к взгляду
                //mView.x += mStrafe.x * speed;
                mView.x += mStrafe.z * speed;
            }

    void upDown(float speed)
            {

                mPos.z += speed;
                mView.z+=speed;
				if(mPos.z<=20)
				{
					mPos.z=20;
					mView.z=10;
				}
				if(mPos.z>=70)
				{
					mPos.z=70;
					mView.z=60;
				}
            }
    void Look()
            {
                gluLookAt(mPos.x, mPos.y, mPos.z, //Нами ранее обсуждаемая команда =)
                              mView.x, mView.y, mView.z,
                              mUp.x, mUp.y, mUp.z);
            }
};


