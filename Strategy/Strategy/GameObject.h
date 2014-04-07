#ifndef GAMEOBJ
#define GAMEOBJ


#include<string>
#include<vector>
#include"TextureLoader.h"
#include"ModelLoader.h"
using namespace std;


class Model
{
	TextureImage *tex;
	vector<vector<float>> vertex,texture,index,tindex;
public:
	Model(char* modelfile, char* texturefile)
	{
		tex = new TextureImage();
		LoadTexture(IL_JPG,texturefile,tex);
		LoadModel(modelfile,vertex,texture,index,tindex);
	}
	void Draw()
	{
			glBindTexture(GL_TEXTURE_2D, tex->texID);

		glEnable(GL_TEXTURE_2D);
	
		for(int  i=0;i<index.size();i++)
		{
			glBegin(GL_POLYGON);
			for(int  j=0;j<index[i].size();j++)
			{
				glTexCoord2d(texture[tindex[i][j]-1][0], texture[tindex[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][1],vertex[index[i][j]-1][2]);
			}
			glEnd();
		}
			glDisable(GL_TEXTURE_2D);
	}
	
};

class State
{
};

class GameObject
{
	float x, y, z; // koord
	float width, height; //razmer
	string id;
	bool visible;
public:
	void Draw();
	void Move(float x, float z)
	{
		this->x = x;
		this->z = z;
	}
	void Raise(float y);
	inline float GetX();
	inline float GetY();
	inline float GetZ();
	string GetID();
	bool Visible();
	void SetVisible(bool value);
};

class Unit:public GameObject
{
	float damage, attackSpeed, attackRange, noiseRange, obserRange, 
		  HP, speed, armor, 
		  angle, viewAngle;
	Model* model;
	State* state;
	vector<int> abilities;
public:
	Unit(/*vector<float> data, */Model* ml/*, State* state, vector<int> abilities*/) 
	{
		model = ml;
	};
	void Interaction(State* state);
	void Draw()
	{
		model->Draw();
	}
	void Processing();
};

class FactoryUnit
{
	vector< vector<float> > data;
	vector<Model*> models;
public:
	FactoryUnit(string filename){};
	void Load(char* modelfile, char* texturefile)
	{
		models.push_back(new Model(modelfile,texturefile));
	}
	Unit* GetUnit(int id, float x, float z)
	{
		Unit* t = new Unit(models[0]);
		t->Move(0,0);
		return t;
	}
};


class Building:public GameObject
{

};
#endif 