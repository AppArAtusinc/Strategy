#ifndef GAMEOBJ
#define GAMEOBJ


#include<string>
#include<vector>
#include"TextureLoader.h"
#include"ModelLoader.h"
using namespace std;

union Indificator
{
	GLuint ID;
	unsigned char bytes[4];
};/*
class ModelVBO
{
	TextureImage *tex;
	GLuint textureID;
	GLuint BufferTextureId, BufferVertexId,VertexCount;
public:
	ModelVBO(char* modelfile, char* texturefile)
	{
		tex = new TextureImage();
		LoadTexture(IL_JPG,texturefile,tex);
		VBOLoadModel(modelfile,BufferVertexId,BufferTextureId,VertexCount);
	}

	void Draw()
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glBindBuffer( GL_ARRAY_BUFFER_ARB, BufferVertexId );
		// Задать указатель на вершины в вершинном буферe
		glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

		glBindBuffer( GL_ARRAY_BUFFER_ARB, BufferTextureId );
		// Задать указатель на TexCoord в буфере TexCoord
		glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );
		glDrawArrays(GL_TRIANGLES,0,VertexCount);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}


};*/

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
	void EasyDraw()
	{
		for(int  i=0;i<index.size();i++)
		{
			glBegin(GL_TRIANGLES);
			for(int  j=0;j<index[i].size();j++)
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
			glEnd();
		}
	}
	void Draw()
	{
		glBindTexture(GL_TEXTURE_2D, tex->texID);
		glEnable( GL_DEPTH_TEST );
		glEnable(GL_TEXTURE_2D);
	
		for(int  i=0;i<index.size();i++)
		{
			glBegin(GL_POLYGON);
			for(int  j=0;j<index[i].size();j++)
			{
				glTexCoord2d(texture[tindex[i][j]-1][0], texture[tindex[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
			}
			glEnd();
		}
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_DEPTH_TEST);
	}


};

class State
{
};

class GameObject
{
protected:
	float x, y, z; // koord
	float width, height; //razmer
	string id;
	bool visible;
public:
	void Draw();
	void Move(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void Raise(float y);
	inline float GetX();
	inline float GetY();
	inline float GetZ();
	string GetID();
	/*void WireDraw()//я допишу, тут буде ще менше детализации
	{
			glBegin(GL_LINE_STRIP);
				glVertex3f(x/2,y/2, 0);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
				glVertex3f(vertex[index[i][j]-1][0],vertex[index[i][j]-1][2],vertex[index[i][j]-1][1]);
			glEnd();
		}
	}*/
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
	Indificator ID;
public:
	Unit(/*vector<float> data, */Model* ml,GLuint id /*float x, float y, State* state, vector<int> abilities*/) 
	{
		ID.ID = id;
		model = ml;
	};
	GLuint GetID()
	{
		return ID.ID;
	}
	void Interaction(State* state);
	void Rotage(double angle)
	{
		this->angle += angle;
	}
	void SetRotage(double angle)
	{
		this->angle =  angle;
	}
	void Draw()
	{
		glPushMatrix();
		glTranslated(x,y,0);
		glRotated(angle,0,0,1);
		model->Draw();
		glPopMatrix();
	}
	void EasyDraw()
	{
		glPushMatrix();
		glTranslated(x,y,0);
		glRotated(angle,0,0,1);
		glColor3ub(ID.bytes[2],ID.bytes[1],ID.bytes[0]);
		model->EasyDraw();
		glPopMatrix();

	}
	/*void WireDraw()
	{
		glPushMatrix();
		glTranslated(x,y,0);
		glColor3b(0,0,0)
		//WireDraw();
		glPopMatrix();
	}*/
	void Processing();
};

class FactoryUnit
{
	vector< vector<float> > data;
	vector<Model*> models;
	GLuint currID;
public:
	FactoryUnit(string filename){ currID =1;};
	void Load(char* modelfile, char* texturefile)
	{
		models.push_back(new Model(modelfile,texturefile));
	}
	Unit* GetUnit(int Type, float x, float y, float angle)
	{
		Unit* t = new Unit(models[0], currID++);
		t->Move(x,y);
		t->SetRotage(angle);
		return t;
	}
};


class Building:public GameObject
{

};
#endif 