#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#include "texture.h"

void bmpread(const char *imname, Image *image){	
	FILE *fp;
	
	if ((fp = fopen(imname, "rb")) == NULL){
		printf("Error (ReadImage) : Cannot read the file!!\n");
		exit(-1);
	}

	fseek(fp, 0x0012, SEEK_SET);
	fread(&image->width, 4, 1, fp);
	fread(&image->height, 4, 1, fp);
	fseek(fp, 54, SEEK_SET);

	GLint line_bytes = image->width * 3;
    while(line_bytes % 4 != 0)
		++line_bytes;

    GLint total_bytes = line_bytes * image->height;

	image->pixels = (GLubyte*)malloc(total_bytes);
	if(image->pixels == 0){
		printf("Not enough memory\n");  
		fclose(fp);
		exit(-2);
	}
       
    if(fread(image->pixels, total_bytes, 1, fp) <= 0) // read to buffer
        free(image->pixels);     

	fclose(fp);  
	
}

float sign(float x){
	if(x > 0) 
		return 1.0;
	else if(x < 0)
		return -1.0;
	else
		return 0.0;
}

int power_of_two(int n){
    if( n <= 0 )
        return 0;
    return (n & (n-1)) == 0;
}

bool loadGLTextures(GLuint& unTexture, const char* chFileName){

    Image *texture_1 = (Image*)malloc(sizeof(Image));
	bmpread(chFileName, texture_1);	

    glGenTextures(1, &unTexture);              
	glBindTexture(GL_TEXTURE_2D, unTexture);        

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
	// GL_BGR_EXT must be used, since bmp file use sequence: Blue, Green, Red to store pixel intensities, rather than RGB used in openGL
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture_1->width, texture_1->height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, texture_1->pixels);
    
	free(texture_1->pixels);
    free(texture_1);
    
    return true;
}

int	getNextInterval(int count){
	int next_interval = ANIM_DELTA_T * (1 - cos(count*PI/(2*ANIM_TOTAL_N+2)))/2;

	return next_interval; // in miliseconds
}