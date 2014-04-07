#pragma once
#include<fstream>
#include<vector>
#include<string>
void LoadModel(
	char* filename, std::vector<std::vector<float>> &vertex,
	std::vector<std::vector<float>> &normals,
	std::vector<std::vector<float>> &texturecoords,
	std::vector<std::vector<float>> &indexcoord,
	std::vector<std::vector<float>> &textureindex
	)
{
	vertex.clear();
	normals.clear();
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
		normals.push_back(temp);
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