    #pragma once
    #include<IL\il.h>
    #include<IL\ilu.h>
    #include<IL\ilut.h>
	#include<iostream>
    
   // Создадим структуру TextureImage для хранения данных текстуры.
    struct TextureImage
    {
        GLubyte *imageData;     // Данные текстуры
        GLuint  bpp;            // Байт на пиксел
        GLuint width,height;    // Высота и ширина
        GLuint texID;           // ID текстуры
    };
         
void LoadTexture(ILenum FileType, char *filename, TextureImage *texture)
{
    // Просим DevIL загрузить файл
    ilLoad(FileType, reinterpret_cast<const wchar_t*>(filename));
 
    // Проверяем, нет ли ошибок при открытии файла
    int err=ilGetError();
    if(err!=IL_NO_ERROR)
    {
        const wchar_t* strError = iluErrorString(err);
        std::cout<<"Error:"<<strError<<std::endl;
        return;
    }
 
    // Получаем данные текстуры
    texture->width = ilGetInteger(IL_IMAGE_WIDTH);          // Ширина
    texture->height = ilGetInteger(IL_IMAGE_HEIGHT);        // Высота
    texture->bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);      // Байт на пиксель
 
    // Загружаем данные в нашу текстуру
    texture->imageData = ilGetData();
 
    ilEnable(IL_CONV_PAL);
 
    // Тип данных изображения
    unsigned int type = ilGetInteger(IL_IMAGE_FORMAT);
 
    // Генерируем текстуру
    glGenTextures(1, &texture->texID);
 
    // Привязываем данные текстуры к ID
    glBindTexture(GL_TEXTURE_2D,texture->texID);
 
    // биндим мип-мапы
    gluBuild2DMipmaps(GL_TEXTURE_2D, texture->bpp, texture->width,
        texture->height, type, GL_UNSIGNED_BYTE, texture->imageData);
 
    // Устанавливаем качество текстур
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}
 