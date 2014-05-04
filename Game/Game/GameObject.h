#ifndef GAMEOBJ
#define GAMEOBJ


#include<string>
#include<vector>
#include<glm\glm.hpp>
#include"TextureLoader.h"
#include"ModelLoader.h"
#include"objloader.hpp"
#include"vboindexer.hpp"

using namespace std;


class State
{
public:
	string name;
	vector<float> values;

	State()
	{
		name = "Stand";
		values.push_back(0);
	}
	State(string Name)
	{
		name = Name;
		values.push_back(0);
	}
	State(string Name, vector<float> Values)
	{
		name = Name;
		values = Values;
	}
	State(string Name, float value1, float value2)
	{
		name = Name;
		values.push_back(value1);
		values.push_back(value2);

	}
};


union Indificator
{
	GLuint ID;
	unsigned char bytes[4];
};
class ModelVBO
{

	GLuint textureID;
	GLuint BufferTextureId, BufferVertexId, BufferNormalId, BufferIndexId, IndexCount;
public:
	ModelVBO(char* modelfile, char* texturefile)
	{
		TextureImage tex;
		LoadTexture(IL_JPG,texturefile,&tex);
		textureID = tex.texID;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		bool res = loadOBJ(modelfile, vertices, uvs, normals);

		std::vector<unsigned short> indices;
		std::vector<glm::vec3> indexed_vertices;
		std::vector<glm::vec2> indexed_uvs;
		std::vector<glm::vec3> indexed_normals;
		indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

		// Load it into a VBO

		glGenBuffers(1, &BufferVertexId);
		glBindBuffer(GL_ARRAY_BUFFER, BufferVertexId);
		glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &BufferTextureId);
		glBindBuffer(GL_ARRAY_BUFFER, BufferTextureId);
		glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

		glGenBuffers(1, &BufferNormalId);
		glBindBuffer(GL_ARRAY_BUFFER, BufferNormalId);
		glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

		// Generate a buffer for the indices as well
		glGenBuffers(1, &BufferIndexId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferIndexId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);
		IndexCount = indices.size();
	}

	void Draw()
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glBindBuffer( GL_ARRAY_BUFFER_ARB, BufferVertexId );
		// Задать указатель на вершины в вершинном буферe
		glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

		glBindBuffer( GL_ARRAY_BUFFER_ARB, BufferTextureId );
		// Задать указатель на TexCoord в буфере TexCoord
		glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );
		glBindBuffer(GL_NORMAL_ARRAY,BufferNormalId);
		glNormalPointer(GL_FLOAT,0,(char*)NULL);
			glDrawElements(
			GL_TRIANGLES,      // mode
			IndexCount,    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
		);
		
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);

	}
	void ColorDraw()
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer( GL_ARRAY_BUFFER_ARB, BufferVertexId );
		// Задать указатель на вершины в вершинном буферe
		glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );
		glDrawElements(
			GL_TRIANGLES,      // mode
			IndexCount,    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
		);
		glDisableClientState(GL_VERTEX_ARRAY);

	}
	void WireDraw()
	{
		glColor3f(0,0,0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer( GL_ARRAY_BUFFER_ARB, BufferVertexId );
		// Задать указатель на вершины в вершинном буферe
		glVertexPointer(3, GL_FLOAT, 0, (char *) NULL );
		glDrawArrays(GL_POINTS,0,IndexCount);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

};
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


class GameObject
{
protected:
	float x, y, z; // koord
	float width, height; //razmer
	string id;
	bool visible;
public:
	GameObject()
	{
		visible = true;
		x=y=z=0;
	}
	void Draw()
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslated(x,y,z);
		glBegin(GL_POLYGON);
			glVertex3f(x-10,y-10,z);
			glVertex3f(x+10,y-10,z);
			glVertex3f(x+10,y+10,z);
			glVertex3f(x-10,y+10,z);
		glEnd();
		glPopMatrix();
	}
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
	
	bool Visible()
	{
		return visible;
	}
	void SetVisible(bool value)
	{
		visible = value;
	}
};

class Unit:public GameObject
{
	friend void Do(Unit* u);
	float damage, attackSpeed, attackRange, noiseRange, obserRange, 
		  HP, speed, armor, 
		  angle, viewAngle;
	ModelVBO* model;
	State state;
	vector<int> abilities;
	Indificator ID;
public:
	Unit(/*vector<float> data, */ModelVBO* ml,GLuint id /*float x, float y, State* state, vector<int> abilities*/) 
	{
		speed = 1;
		ID.ID = id;
		model = ml;
	};
	GLuint GetID()
	{
		return ID.ID;
	}
	void Do()
	{
		if(state.name == "Stand")return;
			//cout<<ID.ID<<" stand on ("<<this->x<< ";" <<this->y<<")"<<endl;

		if(state.name == "GoTo")
		{
			//cout<<ID.ID<<" must go to "<<state.values[0]<< " " <<state.values[1]<<endl;
			state = State("Stand",this->x,this->y);
		}
		if(state.name == "Jump")
		{

			if(state.values[0] > 10)
			{
				z-=.1;
				if(z<0)
					z=0,
					state.values[0]=0,
					state = State("Stand");
			}
			else
				z+=.1;
			state.values[0]+=.1;
		}
	}
	void Interaction(State state)
	{
		this->state = state;
	}
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
		glTranslated(x,y,z);		
		glRotated(angle,0,0,1);
		model->Draw();
		glPopMatrix();
	}
	void ColorDraw()
	{
		glPushMatrix();
		glTranslated(x,y,z);
		glRotated(angle,0,0,1);

		glColor3ub(ID.bytes[2],ID.bytes[1],ID.bytes[0]);
		model->ColorDraw();
		glPopMatrix();

	}
	void WireDraw()
	{
		glPushMatrix();

		glPushName(ID.ID);
		glTranslated(x,y,0);	
		glRotated(angle,0,0,1);
		glColor3b(0,0,0);
		model->WireDraw();
		glPopMatrix();
	}
	void Processing();
};

class FactoryUnit
{
	vector< vector<float> > data;
	vector<ModelVBO*> models;
	GLuint currID;
public:
	FactoryUnit(string filename){ currID =1;};
	void Load(char* modelfile, char* texturefile)
	{
		models.push_back(new ModelVBO(modelfile,texturefile));
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