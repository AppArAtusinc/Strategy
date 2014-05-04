#ifndef MLOADER
#define MLOADER

#include<GL\glew.h>
#include<fstream>
#include<vector>
#include<string>


void VBOLoadModel(char* filename, GLuint& VertexID, GLuint& TextureID, GLuint Count)
{
	std::vector<float> vertex,texcoords;
	std::ifstream in(filename);
	std::string s = "v ";
	float temp;
	while(!in.eof())
	{
		in>>s;
		if(s == "v")
		{
			in>>temp;
			vertex.push_back(temp);
			in>>temp;
			vertex.push_back(temp);
			in>>temp;
			vertex.push_back(temp);
		}
		if(s == "vt")
		{
			in>>temp;
			vertex.push_back(temp);
			in>>temp;
			vertex.push_back(temp);
		}
		/*if(s == "vn")
			goto nor;*/
		if(s == "f")//не конец
		{
			in>>temp;
			vertex.push_back(temp);
		}
		while(!in.eof() && in.peek()!='\n')in.get();
	}
}

void LoadModel(
	char* filename, std::vector<std::vector<float>> &vertex,
	std::vector<std::vector<float>> &texturecoords,
	std::vector<std::vector<float>> &indexcoord,
	std::vector<std::vector<float>> &textureindex
	)
{
	vertex.clear();
	texturecoords.clear();
	std::ifstream in(filename);
	std::string s = "v ";
	std::vector<float> temp,temp2;
	float t;
choose:
	while(!in.eof())
	{
		in>>s;
		if(s == "v")
			goto coords;
		if(s == "vt")
			goto text;
		if(s == "vn")
			goto nor;
		if(s == "f")
			goto index;
		while(!in.eof() && in.peek()!='\n')in.get();
	}
	return ;
coords:
		in>>t;
		temp.push_back(t);
		in>>t;
		temp.push_back(t);
		in>>t;
		temp.push_back(t);
		vertex.push_back(temp);
		temp.clear();
		goto choose;

text:
		in>>t;
		temp.push_back(t);
		in>>t;
		temp.push_back(t);
		texturecoords.push_back(temp);
		temp.clear();
		goto choose;

nor:
		in>>t;
		temp.push_back(t);
		in>>t;
		temp.push_back(t);
		in>>t;
		temp.push_back(t);
		//normals.push_back(temp);
		temp.clear();
		goto choose;

index:
		while( !in.eof() && in.peek()!='\n')
		{
			in>>t;
			temp.push_back(t);
			if(in.peek() == '/' )
			{
				in.get();
				in>>t;
				temp2.push_back(t);
			}
		}
		indexcoord.push_back(temp);
		if(temp2.size())textureindex.push_back(temp2),temp2.clear();
		temp.clear();
		goto choose;
	
}
#endif 