#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <GL/glut.h>
#include "imageloader.h"
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
GLuint _textureIdmove; //The id of the texture
GLuint _textureIdsg; //The id of the texture
GLuint _textureIdn; //The id of the texture
GLuint _textureIdtele; //The id of the texture
GLuint _textureIdsky; //The id of the texture

// Function Declarations
void drawScene();
void update(int value);
void check_obstacle();
void drawBox(float len);
void declare();
void level2();
void level3();
void drawBall(float rad);
void check_man_y();
void draw_man() ;
void create_tile();
void generate();
void draw_tile();
void draw_man_dead();
void check_miss();
void tile_mov(int i,int j);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void draw_jump_man();
void handleMouseclick(int button, int state, int x, int y);
void check_complete_out();
void check_tile();
void man_dead();

float mouse_x,mouse_y,x_angle,y_angle;

void motion(int x,int y)
{
	float dx = x-mouse_x;
	float dy = y-mouse_y;
	mouse_x = x;
	mouse_y = y;
	x_angle += dx;
	y_angle += dy;
}


GLUquadricObj  *object;
GLUquadricObj  *object1;
typedef struct Tile
{
	float x,y,z;
	int mov;
	int mov_dir;
	int miss;
	int obstacle;
	int left;
	int spring;
	int teleporte;
	int coin;
	int collected;
}Tile;
Tile Tiles[20][20];





//global for block moving 
int score=0;
float totaltime=0;
float cube_len=1;
float flag_static=1;
float y_val=-2.15;
float flag_tileview=0;
int Tileblock1=9,Tileblock2=9;
float t_jump_block=0,flag_jump_onblock=0;
int onblock1=0,onblock2=0,onblock_miss=0;
// Global Variables
float flag_dead=0,flag_move_stop=0,t_var=10;
float t_dead=0,dead_num=5;
int rand_num;
float t_up[20][20],t_down[20][20],t_left[20][20],temp_x_left[20][20],t_spring[20][20],temp_t=5,temp_s_t=10,temp_t1=2,t_count=0.02,t_s_count=0.05;
float it1,it2,temp_dis=6,it_val=60;
float ball_x = 1.0f;
float coin_angle=0;
float ball_y = 0.0f;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float ball_rad = 0.2f;
float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 
//Declared Variables ::
int angle_up_joint=0.0f;
int angle_down_joint=0.0f;
int flag_up=0;
int flag_right=0;
float flag_down=0;
float flag_temp=0;
int  flag=0;
int  flag_camera=2;
float man_x=1;
float zoom=1;
float man_y=0;
float man_z=1;
float ang = 0;
float dir_x=0,dir_y=0,dir_z=-10;
int a = 0;
int s = 0;
int d = -1;
//levels data
int flag_level=1;


//jump
int flag_jump;
float t,max_t=1;
float dis=15;
float dis_x=6.0;
float temp_x,temp_y,temp_z;


int main(int argc, char **argv) {
	create_tile();
	declare();
	// ialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w * 2 / 3;
	int windowHeight = h * 2 / 3;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("CSE251_sampleCode"); 
	// Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	glutMotionFunc(motion);
	glutTimerFunc(10, update, 0);

	glutMainLoop();
	return 0;
}


void create_tile()
{
	float k=1,l=1;
	int it1,it2;
	for( it1=0;k<it_val;it1++,k+=temp_dis)
	{
		for( it2=0;l<it_val;it2++,l+=temp_dis)
		{

			srand(1000*t_var);
			t_var+=15;
			rand_num=rand()%10;
			if(rand_num%2==0 && rand_num==0)
			{
				Tiles[it1][it2].x=k;
				Tiles[it1][it2].y=y_val;
				Tiles[it1][it2].z=l;
				Tiles[it1][it2].mov=1;
				Tiles[it1][it2].mov_dir=1;
				Tiles[it1][it2].miss=0;
				Tiles[it1][it2].obstacle=0;
				Tiles[it1][it2].left=0;
				Tiles[it1][it2].spring=0;
				Tiles[it1][it2].teleporte=0;
				Tiles[it1][it2].coin=0;
				Tiles[it1][it2].collected=0;
			}
			else if(rand_num%2==0 && rand_num==10)
			{
				Tiles[it1][it2].x=k;
				Tiles[it1][it2].y=y_val;
				Tiles[it1][it2].z=l;
				Tiles[it1][it2].mov=1;
				Tiles[it1][it2].mov_dir=-1;
				Tiles[it1][it2].miss=0;
				Tiles[it1][it2].obstacle=0;
				Tiles[it1][it2].left=0;
				Tiles[it1][it2].spring=0;
				Tiles[it1][it2].teleporte=0;
				Tiles[it1][it2].coin=0;
				Tiles[it1][it2].collected=0;
			}

			//spring
			else if(rand_num%2==0 && (rand_num==2  || rand_num==6) && (it1!=0 || it2!=0)  && (it1!=9  || it2!=9))
			{
				Tiles[it1][it2].x=k;
				Tiles[it1][it2].y=y_val;
				Tiles[it1][it2].z=l;
				Tiles[it1][it2].mov=0;
				Tiles[it1][it2].mov_dir=0;
				Tiles[it1][it2].miss=0;
				Tiles[it1][it2].obstacle=0;
				Tiles[it1][it2].left=0;
				Tiles[it1][it2].spring=1;
				Tiles[it1][it2].teleporte=0;
				Tiles[it1][it2].coin=0;
				Tiles[it1][it2].collected=0;
			}
			//miss
			else if (rand_num==4)
			{
				Tiles[it1][it2].x=k;
				Tiles[it1][it2].y=y_val;
				Tiles[it1][it2].z=l;
				Tiles[it1][it2].mov=0;
				Tiles[it1][it2].mov_dir=0;
				Tiles[it1][it2].miss=1;
				Tiles[it1][it2].obstacle=0;
				Tiles[it1][it2].left=0;
				Tiles[it1][it2].spring=0;
				Tiles[it1][it2].teleporte=0;
				Tiles[it1][it2].coin=0;
				Tiles[it1][it2].collected=0;
				Tiles[it1][it2].coin=0;
				Tiles[it1][it2].collected=0;
			}
			//obstacle
			else if( (rand_num==9   || rand_num==7 ) && it1!=0 && it2!=0  && it1!=9  && it2!=9  && flag_level==3 )
			{
				Tiles[it1][it2].x=k;
				Tiles[it1][it2].y=y_val;
				Tiles[it1][it2].z=l;
				Tiles[it1][it2].mov=0;
				Tiles[it1][it2].mov_dir=0;
				Tiles[it1][it2].miss=0;
				Tiles[it1][it2].obstacle=1;
				Tiles[it1][it2].left=0;
				Tiles[it1][it2].spring=0;
				Tiles[it1][it2].teleporte=0;
				Tiles[it1][it2].coin=0;
				Tiles[it1][it2].collected=0;
			}
			else if(rand_num%2!=0 && rand_num==9 && it1!=0 && it2!=0  && it1!=9  && it2!=9  && flag_level>=2 )
			{
				Tiles[it1][it2].x=k;
				Tiles[it1][it2].y=y_val;
				Tiles[it1][it2].z=l;
				Tiles[it1][it2].mov=0;
				Tiles[it1][it2].mov_dir=0;
				Tiles[it1][it2].miss=0;
				Tiles[it1][it2].obstacle=1;
				Tiles[it1][it2].left=0;
				Tiles[it1][it2].spring=0;
				Tiles[it1][it2].teleporte=0;
				Tiles[it1][it2].coin=0;
				Tiles[it1][it2].collected=0;
			}
			else if(rand_num%2!=0 &&  rand_num==7 )
			{
				Tiles[it1][it2].x=k;
				Tiles[it1][it2].y=y_val;
				Tiles[it1][it2].z=l;
				Tiles[it1][it2].mov=0;
				Tiles[it1][it2].mov_dir=0;
				Tiles[it1][it2].miss=0;
				Tiles[it1][it2].obstacle=0;
				Tiles[it1][it2].left=0;
				temp_x_left[it1][it2]=k;
				Tiles[it1][it2].teleporte=1;
				Tiles[it1][it2].spring=0;
				Tiles[it1][it2].coin=0;
				Tiles[it1][it2].collected=0;
			}
			else if(rand_num%2!=0  && rand_num>=3 && rand_num<=5  && it1!=0 && it2!=0  && it1!=9  && it2!=9)
			{
				Tiles[it1][it2].x=k;
				Tiles[it1][it2].y=y_val;
				Tiles[it1][it2].z=l;
				Tiles[it1][it2].mov=0;
				Tiles[it1][it2].mov_dir=0;
				Tiles[it1][it2].miss=0;
				Tiles[it1][it2].obstacle=0;
				Tiles[it1][it2].left=1;
				temp_x_left[it1][it2]=k;
				Tiles[it1][it2].teleporte=0;
				Tiles[it1][it2].spring=0;
				Tiles[it1][it2].coin=0;
				Tiles[it1][it2].collected=0;
			}
			else if(rand_num==1 && flag_level<=2)
			{
				Tiles[it1][it2].x=k;
				Tiles[it1][it2].y=y_val;
				Tiles[it1][it2].z=l;
				Tiles[it1][it2].mov=0;
				Tiles[it1][it2].mov_dir=0;
				Tiles[it1][it2].miss=0;
				Tiles[it1][it2].obstacle=0;
				Tiles[it1][it2].left=0;
				Tiles[it1][it2].spring=0;
				Tiles[it1][it2].coin=1;
				Tiles[it1][it2].collected=0;
			}

			else if((rand_num==1 || rand_num==3 || rand_num==2) && flag_level==3)
			{
				Tiles[it1][it2].x=k;
				Tiles[it1][it2].y=y_val;
				Tiles[it1][it2].z=l;
				Tiles[it1][it2].mov=0;
				Tiles[it1][it2].mov_dir=0;
				Tiles[it1][it2].miss=0;
				Tiles[it1][it2].obstacle=0;
				Tiles[it1][it2].left=0;
				Tiles[it1][it2].spring=0;
				Tiles[it1][it2].coin=1;
				Tiles[it1][it2].collected=0;
			}

			else
			{
				Tiles[it1][it2].x=k;
				Tiles[it1][it2].y=y_val;
				Tiles[it1][it2].z=l;
				Tiles[it1][it2].mov=0;
				Tiles[it1][it2].mov_dir=0;
				Tiles[it1][it2].miss=0;
				Tiles[it1][it2].obstacle=0;
				Tiles[it1][it2].left=0;
				Tiles[it1][it2].spring=0;
				Tiles[it1][it2].coin=0;
				Tiles[it1][it2].collected=0;
			}

		}
		l=1;
	}
}


void declare()
{
	int i,j;
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			t_up[i][j]=0;
			t_down[i][j]=0;
			t_left[i][j]=0;
		}
	}
}





void draw_tile()
{
	glPushMatrix();
	glColor3f(0,0,1);
	glTranslatef(0.0,-5.0,0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(10.0f, 10.0f);
	glVertex3f(80.0,0.0,80.0);
	glTexCoord2f(10.0f, 0.0f);
	glVertex3f(-80.0,0.0,80.0);
	glTexCoord2f(0.0f, 10.0f);
	glVertex3f(-80.0,0.0,-80.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(80.0,0.0,-80.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	for(int it1=0;it1<10;it1++)
	{
		for(int it2=0;it2<10;it2++)
		{
			if(Tiles[it1][it2].mov==1 && Tiles[it1][it2].mov_dir==1)
			{
				if(t_up[it1][it2]<1.05)
				{
					Tiles[it1][it2].y=y_val+temp_t*t_up[it1][it2]-(temp_t*t_up[it1][it2]*t_up[it1][it2]);
					t_up[it1][it2]+=t_count;
				}
				if(t_down[it1][it2]<1.05 && t_up[it1][it2]>1.05)
				{
					Tiles[it1][it2].y=y_val-temp_t*t_down[it1][it2]+(temp_t*t_down[it1][it2]*t_down[it1][it2]);
					t_down[it1][it2]+=t_count;
				}
				else if(t_up[it1][it2]>1.05  && t_down[it1][it2]>1.05)
				{
					t_up[it1][it2]=0;
					t_down[it1][it2]=0;
				}
			}
			else if(Tiles[it1][it2].mov==1 && Tiles[it1][it2].mov_dir==-1)
			{
				if(t_down[it1][it2]<1.05)
				{
					Tiles[it1][it2].y=y_val-temp_t*t_down[it1][it2]+(temp_t*t_down[it1][it2]*t_down[it1][it2]);
					t_down[it1][it2]+=t_count;
				}
				if(t_up[it1][it2]<1.05 && t_down[it1][it2]>1.05)
				{
					Tiles[it1][it2].y=y_val+temp_t*t_up[it1][it2]-(temp_t*t_up[it1][it2]*t_up[it1][it2]);
					t_up[it1][it2]+=t_count;
				}
				else if(t_up[it1][it2]>1.05  && t_down[it1][it2]>1.05)
				{
					t_up[it1][it2]=0;
					t_down[it1][it2]=0;
				}
			}
			//		printf("%d\n",it2%2);
			if(Tiles[it1][it2].mov==1 && Tiles[it1][it2].miss!=1)
			{
				glPushMatrix();
				glTranslatef(Tiles[it1][it2].x,Tiles[it1][it2].y,Tiles[it1][it2].z);
				glColor3f(255.0/255,255.0/255,255.0/255);
				glEnable(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glEnable(GL_TEXTURE_GEN_T);
				glBindTexture(GL_TEXTURE_2D, _textureIdmove);
				glutSolidCube(1.8);
				glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glDisable(GL_TEXTURE_GEN_T);
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			else if(  Tiles[it1][it2].mov!=1 && Tiles[it1][it2].miss!=1)
			{
				glPushMatrix();
				glColor3f(255.0/255,255.0/255,255.0/255);
				glTranslatef(Tiles[it1][it2].x,Tiles[it1][it2].y,Tiles[it1][it2].z);
				glEnable(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glEnable(GL_TEXTURE_GEN_T);
				glBindTexture(GL_TEXTURE_2D, _textureIdn);
				glutSolidCube(1.9);
				glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glDisable(GL_TEXTURE_GEN_T);
				glDisable(GL_TEXTURE_2D);
				if(Tiles[it1][it2].coin==1 && Tiles[it1][it2].collected==0)
				{
					glTranslatef(0,1.9,0);
					glColor3f(255.0/255,215.0/255,0/255);
					glRotatef(coin_angle,0,1,0);
					glScalef(1,1,0.4);
					glutSolidSphere(0.8,25,25);
				}
				glPopMatrix();
			}
			if(Tiles[it1][it2].obstacle==1 && Tiles[it1][it2].left!=1)
			{
				glPushMatrix();
				glTranslatef(Tiles[it1][it2].x,Tiles[it1][it2].y+1.9,Tiles[it1][it2].z);
				glColor3f(205.0/255,181/255,205/255);
				glutSolidSphere(1.2,10,10);
				glPopMatrix();
			}

			if(Tiles[it1][it2].teleporte==1 && Tiles[it1][it2].obstacle!=1 )
			{

				glPushMatrix();
				glTranslatef(Tiles[it1][it2].x,Tiles[it1][it2].y,Tiles[it1][it2].z);
				//	glColor3f(200.0/255,234.0/255,67.0/255);
				//	glColor3f(255.0/255,255.0/255,255.0/255);
				glEnable(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glEnable(GL_TEXTURE_GEN_T);
				glBindTexture(GL_TEXTURE_2D, _textureIdtele);
				glutSolidCube(2.1);
				glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glDisable(GL_TEXTURE_GEN_T);
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			if(Tiles[it1][it2].spring==1 && Tiles[it1][it2].obstacle!=1 )
			{
				glPushMatrix();
				glTranslatef(Tiles[it1][it2].x,Tiles[it1][it2].y,Tiles[it1][it2].z);
				//	glColor3f(255.0/255,255.0/255,255.0/255);
				glEnable(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glEnable(GL_TEXTURE_GEN_T);
				glBindTexture(GL_TEXTURE_2D, _textureIdsg);
				glutSolidCube(2.0);
				glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
				glDisable(GL_TEXTURE_GEN_T);
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			if(Tiles[it1][it2].left==1 &&  Tiles[it1][it2].miss!=1 && Tiles[it1][it2].obstacle!=1)
			{
				if(t_left[it1][it2]<1.05)
				{
					Tiles[it1][it2].x=temp_x_left[it1][it2]-temp_t1*t_left[it1][it2]+(temp_t1*t_left[it1][it2]*t_left[it1][it2]);
					t_left[it1][it2]+=t_count;
					glPushMatrix();
					glTranslatef(Tiles[it1][it2].x,Tiles[it1][it2].y,Tiles[it1][it2].z);
					//	glColor3f(000.0/255,100.0/255,000.0/255);
					glEnable(GL_TEXTURE_2D);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
					glEnable(GL_TEXTURE_GEN_T);
					glBindTexture(GL_TEXTURE_2D, _textureIdn);
					glutSolidCube(1.8);
					glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
					glDisable(GL_TEXTURE_GEN_T);
					glDisable(GL_TEXTURE_2D);
					//glutSolidCube(1.0f);
					glPopMatrix();
				}
				else if(t_left[it1][it2]>1.05)
				{
					t_left[it1][it2]=0;
				}
			}
		}
	}
}


void tile_mov(int i,int j)
{
	Tiles[i][j].mov=1;
	return ;
}



// Function to draw objects on the screen
void drawScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(x_angle,0,1,0);
	glRotatef(y_angle,1,0,0);
	if(flag_camera==1)
	{
		if(d == +1)
			gluLookAt(man_x,man_y,man_z-0.4,man_x,man_y,man_z-1,0,1,0);
		else if(a == 1)
			gluLookAt(man_x+0.3,man_y,man_z,man_x+10,man_y,man_z,0,1,0);
		else if(d == -1)
			gluLookAt(man_x,man_y,man_z+0.3,man_x,man_y,man_z+10,0,1,0);
		else if(a == -1)
			gluLookAt(man_x-0.3,man_y,man_z,man_x-10,man_y,man_z,0,1,0);
	}
	if(flag_camera==2)
	{
		glTranslatef(-10,-5,-30);
		gluLookAt(10*zoom,10*zoom,-10*zoom,it_val/2,0,it_val/2,0,1,0);
	}
	if(flag_camera==3)
	{
		if(d == +1)
			gluLookAt(man_x,man_y,man_z-0.3+3,man_x,man_y,man_z-1,0,1,0);
		else if(a == 1)
			gluLookAt(man_x+0.3-3,man_y,man_z,man_x+10,man_y,man_z,0,1,0);
		else if(d == -1)
			gluLookAt(man_x,man_y,man_z+0.3-3,man_x,man_y,man_z+10,0,1,0);
		else if(a == -1)
			gluLookAt(man_x-0.3-3,man_y,man_z,man_x-10,man_y,man_z,0,1,0);
	}
	if(flag_camera==4)
	{
		gluLookAt(Tiles[Tileblock1][Tileblock2].x,0,Tiles[Tileblock1][Tileblock2].z,man_x,0,man_z,0,1,0);
	}
	glPushMatrix();
	draw_tile();
	glPopMatrix();
	check_complete_out();
	glPopMatrix();
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	// Draw Box

	if(flag_up==1)
	{
		if(d == 0)
		{
			if(a == -1)
			{
				man_x-=0.1;
			}
			else if(a == 1)
			{
				man_x += 0.1;
			}
		}
		else if(a == 0)
		{
			if(d == -1)
			{
				man_z += 0.1;
			}
			else if(d == 1)
			{
				man_z -= 0.1;
			}
		}
		flag_up=0;
	}

	if(flag_up == 2)
	{
		if(d == 0)
		{
			if(a == 1)
			{
				man_x -= 0.1;
			}
			else if(a == -1)
			{
				man_x += 0.1;
			}
		}
		else if(a == 0)
		{
			if(d == 1)
			{
				man_z += 0.1;
			}
			else if(d == -1)
			{
				man_z -= 0.1;
			}
		}
		flag_up = 0;
	}




	glTranslatef(man_x,man_y,man_z);
	glRotatef(ang,0,1,0);
	if(flag_dead==1 && onblock_miss==1)
	{
		man_dead();
	}
	if(flag_jump==0 && flag_dead!=1)
	{
		glPushMatrix();
		glScalef(2.5,2.5,2.5);
		glTranslatef(0,1.07,0);
		draw_man();
		glPopMatrix();
	}
	else if(flag_jump==1 && flag_dead!=1)
	{
		glPushMatrix();
		glScalef(2.5,2.5,2.5);
		glTranslatef(0,1.07,0);
		draw_jump_man();
		glPopMatrix();
	}
	//	glPopMatrix();
	glPopMatrix();

	//sky
	glPushMatrix();
	//glColor3f(0.196078,0.196078,0.8);
	glColor3f(1,1,1);
	glTranslatef(0.0,0.0,0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureIdsky);

	//sky
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(100.0,-10.0,-100.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-100.0,-10.0,-100.0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-100.0,100.0,-100.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(100.0,100.0,-100.0);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(100.0,-10.0,100.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-100.0,-10.0,100.0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-100.0,100.0,100.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(100.0,100.0,100.0);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(100.0,-10.0,-100.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(100.0,100.0,-100.0);
	glTexCoord2f(0.0f, .0f);
	glVertex3f(100.0,100.0,100.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(100.0,-10.0,100.0);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0,1.0,0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-100.0,-10.0,-100.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-100.0,100.0,-100.0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-100.0,100.0,100.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-100.0,-10.0,100.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers();
}

void man_dead()
{
	//glPushMatrix();
	//glTranslatef(man_x,man_y,man_z);
	if(t_dead==0)
	{
		draw_man_dead();
	}
	//glPopMatrix();
	//	printf("%f\n",t_dead);
	t_dead+=0.05;
	if(t_dead < 1.05)
	{
		man_y=-2-(dead_num*t_dead*t_dead);
	}
	else
	{
		exit(0);
	}
}

void check_tile()
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if((man_x<=Tiles[i][j].x+0.5 && man_x >= Tiles[i][j].x-0.5 )  && (man_z <= Tiles[i][j].z+0.5  && man_z >= Tiles[i][j].z-0.5))
			{
				onblock1=i;
				onblock2=j;
				//			onblock_miss=Tiles[i][j].miss;
				//				printf("%d \n",onblock_miss);
				if(Tiles[i][j].obstacle==1)
				{
					//					printf("a=%d d=%d\n",a,d);

					if(Tiles[onblock1][onblock2].obstacle==1 && a==1)
					{
						onblock1=onblock1-1;
					}
					else if(Tiles[onblock1][onblock2].obstacle==1 && a==-1)
					{
						onblock1=onblock1+1;
					}
					else if(Tiles[onblock1][onblock2].obstacle==1 && d==1)
					{
						onblock2=onblock2+1;
					}
					else if(Tiles[onblock1][onblock2].obstacle==1 && d==-1)
					{
						onblock2=onblock2-1;
					}
					//				printf("%d %d\n",onblock1,onblock2);
					man_y=Tiles[onblock1][onblock2].y+2.15;
					man_x=Tiles[onblock1][onblock2].x;
					man_z=Tiles[onblock1][onblock2].z;
				}
				else if(Tiles[i][j].left==1 && flag_static==1 )
				{
					man_y=Tiles[i][j].y+2.15;
					man_x=Tiles[i][j].x;
				}
				else if(Tiles[i][j].teleporte==1)
				{
					man_y=Tiles[4][7].y+2.15;
					man_x=Tiles[4][7].x;
					man_z=Tiles[4][7].z;
				}
				else if(Tiles[i][j].spring==1)
				{
					man_x=Tiles[i][j].x;
					man_z=Tiles[i][j].z;
					if(t_spring[i][j]<1.05)
					{
						man_y=Tiles[i][j].y+2.15+temp_s_t*t_spring[i][j]-(temp_s_t*t_spring[i][j]*t_spring[i][j]);
						t_spring[i][j]+=t_s_count;
					}
					else if(t_spring[i][j]>1.05 )
					{
						t_spring[i][j]=0;
					}
				}
				else if(Tiles[i][j].coin==1 && Tiles[i][j].collected==0)
				{
					Tiles[i][j].collected=1;
					score++;
				}
				else
				{
					man_y=Tiles[i][j].y+2.15;
				}
				if(i==9&&j==9)
				{
					flag_level=flag_level+1;
					if(flag_level==4)
					{
						printf("GameOver ...Your Score = %d  :)\n",score );
					}
					else if(flag_level==2)
					{
						level2();
					}
					else if(flag_level==3)
					{
						level3();
					}
				}

			}
		}
	}

}
void level3()
{
	t_var=10;
	create_tile();
	man_x=Tiles[0][0].x;
	man_y=Tiles[0][0].y+y_val;
	man_z=Tiles[0][0].z;
}
void level2()
{
	t_var=10;
	create_tile();
	man_x=Tiles[0][0].x;
	man_y=Tiles[0][0].y+y_val;
	man_z=Tiles[0][0].z;
}
void check_miss()
{
	if(flag_jump== 0 && (onblock_miss==1 ||  Tiles[onblock1][onblock2].miss==1))
	{
		//	printf("hey\n");
		flag_dead=1;
		man_dead();
	}
}

void check_man_y()
{
	if(man_y<-0.3)
	{
		flag_move_stop=1;
	}
	else
	{
		flag_move_stop=0;
	}
}


// Function to handleall calculations in the scene
// updated evry 10 milliseconds
void update(int value) {

	check_tile();
	check_miss();
	check_man_y();
	generate();
	coin_angle+=5;
	//printf("%f  %f   %f\n",man_x,man_y,man_z);
	if(flag_jump==1)
	{

		man_y=temp_y+(dis*t)-(dis*t*t);
		if(a==1)
		{
			man_x=temp_x+(dis_x*t);
		}
		if(a==-1)
		{
			man_x=temp_x-(dis_x*t);
		}
		if(d==-1)
		{
			man_z=temp_z+(dis_x*t);
		}
		if(d==1)
		{
			man_z=temp_z-(dis_x*t);
		}
		t+=0.05;
		if(t>1.05)
		{
			flag_jump=0;
			t=0;
		}
	}
	totaltime+=10;
	printf("time=%f\n",(totaltime/1000)*(3.9));
	glutTimerFunc(10, update, 0);
}

void drawBox(float len) 
{

	glutSolidCube(0.50f);
}



void check_complete_out()
{
	if((man_x > it_val+0.5 || man_x < 0.50 ) ||  (man_z >it_val+0.50 || man_z < 0.50 ) )
	{
		//	printf("out  %d  %d\n",a,d);
		flag_dead=1;
		man_dead();
	}
	else
	{
		flag_dead=0;
		//
	}
}

void draw_man() 
{
	float theta;
	theta = atan(0.4/0.7);

	//	printf("in draw triangle   flag=%d\n",flag);
	object = gluNewQuadric();
	gluQuadricNormals(object,GLU_SMOOTH);    
	gluQuadricTexture(object,GLU_TRUE);    

	//    glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	//body
	glTranslatef(0.0,0.0,0.2);
	glColor3f(1.0f,1.0f,0.0f);
	gluCylinder(object,0.3,0.3,0.7,5,5);
	glTranslatef(0.0,0.0,0.7);

	//head
	glPushMatrix();
	glTranslatef(0.0,0.0,-1.0);
	glColor3f(0.0f,1.0f,0.0f);
	gluSphere(object,0.3,100,100);
	glPopMatrix();



	//eye
	glPushMatrix();
	glTranslatef(-0.10,0.3,-1.0);
	glColor3f(0.0f,0.0f,1.0f);
	gluSphere(object,0.04,100,100);
	glPopMatrix();


	//eye
	glPushMatrix();
	glTranslatef(0.10,0.3,-1.0);
	glColor3f(0.0f,0.0f,1.0f);
	gluSphere(object,0.04,100,100);
	//glutSolidSphere(0.3,50,50);
	glPopMatrix();

	if(flag==0 || flag==2)
	{

		//right-hand
		glPushMatrix();
		glTranslatef(0.30,0.0,-0.650);
		glColor3f(0.0f,1.0f,0.0f);
		glRotatef(25,0.0,1.0,0.0);
		gluCylinder(object,0.08,0.08,0.25,100,100);
		glTranslatef(0.02,0.0,0.20);
		glRotatef(-25,0.0,1.0,0.0);
		glColor3f(0.0f,1.0f,0.0f);
		gluCylinder(object,0.08,0.08,0.35,100,100);
		glTranslatef(0.0,0.0,0.30);
		gluSphere(object,0.1,5,5);
		glPopMatrix();


		//left-hand
		glPushMatrix();
		glTranslatef(-0.30,0.0,-0.650);
		glColor3f(0.0f,1.0f,0.0f);
		glRotatef(-25,0.0,1.0,0.0);
		gluCylinder(object,0.08,0.08,0.25,100,100);
		glTranslatef(-0.02,0.0,0.20);
		glRotatef(25,0.0,1.0,0.0);
		glColor3f(0.0f,1.0f,0.0f);
		gluCylinder(object,0.08,0.08,0.35,100,100);
		glTranslatef(0.0,0.0,0.30);
		gluSphere(object,0.1,5,5);
		glPopMatrix();



		//right leg
		glPushMatrix();
		theta = atan(0.4/0.7);
		glRotatef((theta*(180/3.14)),0.0f,1.0f,0.0f);
		glTranslatef(0.0,0.0,0.1);
		glColor3f(0.0f,1.0f,0.0f);
		gluCylinder(object,0.15,0.15,0.3,100,100);
		glTranslatef(0.0,0.0,0.25);
		glRotatef(-(theta*(180/3.14)),0.0f,1.0f,0.0f);
		gluCylinder(object,0.15,0.15,0.45,100,100);
		glPopMatrix();


		//left leg
		glPushMatrix();
		theta = atan(0.4/0.7);
		glRotatef(-(theta*(180/3.14)),0.0f,1.0f,0.0f);
		glTranslatef(0.0,0.0,0.1);
		glColor3f(0.0f,1.0f,0.0f);
		gluCylinder(object,0.15,0.15,0.3,100,100);
		glTranslatef(0.0,0.0,0.25);
		glRotatef((theta*(180/3.14)),0.0f,1.0f,0.0f);
		gluCylinder(object,0.15,0.15,0.45,100,100);
		glPopMatrix();
		glPopMatrix();
	}

	else if(flag==3)
	{
		//right-hand
		glPushMatrix();
		glTranslatef(0.37,0.0,-0.650);
		glColor3f(0.0f,1.0f,0.0f);
		// glRotatef(25,0.0,1.0,0.0);
		glRotatef(-30,1.0f,0.0f,0.0f);
		gluCylinder(object,0.08,0.08,0.70,10,10);
		glPopMatrix();


		//left-hand
		glPushMatrix();
		glTranslatef(-0.30,0.0,-0.650);
		glColor3f(0.0f,1.0f,0.0f);
		glRotatef(-25,0.0,1.0,0.0);
		gluCylinder(object,0.08,0.08,0.25,100,100);
		glTranslatef(-0.02,0.0,0.20);
		glRotatef(25,0.0,1.0,0.0);
		glColor3f(0.0f,1.0f,0.0f);
		gluCylinder(object,0.08,0.08,0.35,100,100);
		glTranslatef(0.0,0.0,0.30);
		gluSphere(object,0.1,5,5);
		glPopMatrix();



		//right leg
		glPushMatrix();
		theta = atan(0.4/0.7);
		glRotatef((theta*(180/3.14)),0.0f,1.0f,0.0f);
		glTranslatef(0.0,0.0,0.1);
		glColor3f(0.0f,1.0f,0.0f);
		gluCylinder(object,0.15,0.15,0.3,100,100);
		glTranslatef(0.0,0.0,0.25);
		glRotatef(-(theta*(180/3.14)),0.0f,1.0f,0.0f);
		gluCylinder(object,0.15,0.15,0.35,10,10);
		glPopMatrix();


		//left leg
		glPushMatrix();
		theta = atan(0.4/0.7);
		glTranslatef(-0.17,0.0,0.1);
		glColor3f(0.0f,1.0f,0.0f);
		glRotatef(-30,1.0f,0.0f,0.0f);
		gluCylinder(object,0.15,0.15,0.60,100,100);
		glPopMatrix();
		glPopMatrix();
	}

	else if(flag==1)
	{
		//right-hand
		glPushMatrix();
		glTranslatef(0.30,0.0,-0.650);
		glColor3f(0.0f,1.0f,0.0f);
		glRotatef(25,0.0,1.0,0.0);
		gluCylinder(object,0.08,0.08,0.25,100,100);
		glTranslatef(0.02,0.0,0.20);
		glRotatef(-25,0.0,1.0,0.0);
		glColor3f(0.0f,1.0f,0.0f);
		gluCylinder(object,0.08,0.08,0.35,100,100);
		glTranslatef(0.0,0.0,0.30);
		gluSphere(object,0.1,5,5);
		glPopMatrix();


		//left-hand
		glPushMatrix();
		glTranslatef(-0.37,0.0,-0.650);
		glColor3f(0.0f,1.0f,0.0f);
		// glRotatef(-25,0.0,1.0,0.0);
		glRotatef(-30,1.0f,0.0f,0.0f);
		gluCylinder(object,0.08,0.08,0.7,100,100);
		glTranslatef(-0.02,0.0,0.20);
		glPopMatrix();



		//right leg
		glPushMatrix();
		theta = atan(0.4/0.7);
		//glRotatef((theta*(180/3.14)),0.0f,1.0f,0.0f);
		glTranslatef(0.17,0.0,0.1);
		glColor3f(0.0f,1.0f,0.0f);
		glRotatef(-30,1.0f,0.0f,0.0f);
		gluCylinder(object,0.15,0.15,0.65,100,100);
		glPopMatrix();


		//left leg
		glPushMatrix();
		theta = atan(0.4/0.7);
		glRotatef(-(theta*(180/3.14)),0.0f,1.0f,0.0f);
		glTranslatef(0.0,0.0,0.1);
		glColor3f(0.0f,1.0f,0.0f);
		gluCylinder(object,0.15,0.15,0.3,100,100);
		glTranslatef(0.0,0.0,0.25);
		glRotatef((theta*(180/3.14)),0.0f,1.0f,0.0f);
		gluCylinder(object,0.15,0.15,0.35,100,100);
		glPopMatrix();
		glPopMatrix();
	}
}


void draw_jump_man() 
{
	float theta;
	theta = atan(0.4/0.7);

	//	printf("in draw triangle   flag=%d\n",flag);
	object = gluNewQuadric();
	gluQuadricNormals(object,GLU_SMOOTH);    
	gluQuadricTexture(object,GLU_TRUE);    

	//    glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	//body
	glTranslatef(0.0,0.0,0.2);
	glColor3f(1.0f,1.0f,0.0f);
	gluCylinder(object,0.3,0.3,0.7,5,5);
	glTranslatef(0.0,0.0,0.7);

	//head
	glPushMatrix();
	glTranslatef(0.0,0.0,-1.0);
	glColor3f(0.0f,1.0f,0.0f);
	gluSphere(object,0.3,100,100);
	glPopMatrix();



	//eye
	glPushMatrix();
	glTranslatef(-0.10,0.3,-1.0);
	glColor3f(0.0f,0.0f,1.0f);
	gluSphere(object,0.04,100,100);
	glPopMatrix();


	//eye
	glPushMatrix();
	glTranslatef(0.10,0.3,-1.0);
	glColor3f(0.0f,0.0f,1.0f);
	gluSphere(object,0.04,100,100);
	//glutSolidSphere(0.3,50,50);
	glPopMatrix();


	//right-hand
	glPushMatrix();
	glTranslatef(0.30,0.0,-0.650);
	glColor3f(0.0f,1.0f,0.0f);
	glRotatef(-90,1.0,0.0,0.0);
	gluCylinder(object,0.08,0.08,0.25,100,100);
	glTranslatef(0.00,0.0,0.25);
	glRotatef(-25,1.0,0.0,0.0);
	glColor3f(0.0f,1.0f,0.0f);
	gluCylinder(object,0.08,0.08,0.35,100,100);
	glTranslatef(0.0,0.0,0.30);
	gluSphere(object,0.1,5,5);
	gluCylinder(object,0.08,0.08,0.35,100,100);
	glTranslatef(0.0,0.0,0.30);
	glColor3f(1.0f,0.0f,0.0f);
	gluSphere(object,0.1,5,5);
	glPopMatrix();


	//left-hand
	glPushMatrix();
	glTranslatef(-0.30,0.0,-0.650);
	glColor3f(0.0f,1.0f,0.0f);
	glRotatef(90,1.0,0.0,0.0);
	gluCylinder(object,0.08,0.08,0.25,100,100);
	glTranslatef(0.00,0.0,0.25);
	glRotatef(25,1.0,0.0,0.0);
	glColor3f(0.0f,1.0f,0.0f);
	gluCylinder(object,0.08,0.08,0.35,100,100);
	glTranslatef(0.0,0.0,0.30);
	glColor3f(1.0f,0.0f,0.0f);
	gluSphere(object,0.1,5,5);
	glPopMatrix();



	//right leg
	glPushMatrix();
	theta = atan(0.4/0.7);
	glRotatef(-(theta*(180/3.14)),1.0f,0.0f,0.0f);
	//		glTranslatef(0.0,0.0,0.1);
	glColor3f(0.0f,1.0f,0.0f);
	gluCylinder(object,0.15,0.15,0.65,100,100);
	glTranslatef(0.0f,0.0f,0.65f);
	glColor3f(1.0f,0.0f,0.0f);
	glutSolidCube(0.20);
	glPopMatrix();


	//left leg
	glPushMatrix();
	theta = atan(0.4/0.7);
	glRotatef(+(theta*(180/3.14)),1.0f,0.0f,0.0f);
	//	glTranslatef(0.0,0.0,0.1);
	glColor3f(0.0f,1.0f,0.0f);
	gluCylinder(object,0.15,0.15,0.7,100,100);
	glTranslatef(0.0f,0.0f,0.65f);
	glColor3f(1.0f,0.0f,0.0f);
	glutSolidCube(0.20);
	glPopMatrix();
	glPopMatrix();



}

void draw_man_dead()
{
	float theta;
	theta = atan(0.4/0.7);

	//	printf("in draw triangle   flag=%d\n",flag);
	object = gluNewQuadric();
	gluQuadricNormals(object,GLU_SMOOTH);    
	gluQuadricTexture(object,GLU_TRUE);    

	//    glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	//body
	glTranslatef(0.0,0.0,0.2);
	glColor3f(1.0f,1.0f,0.0f);
	gluCylinder(object,0.3,0.3,0.7,5,5);
	glTranslatef(0.0,0.0,0.7);

	//head
	glPushMatrix();
	glTranslatef(0.0,0.0,-1.0);
	glColor3f(0.0f,1.0f,0.0f);
	gluSphere(object,0.3,100,100);
	glPopMatrix();



	//eye
	glPushMatrix();
	glTranslatef(-0.10,0.3,-1.0);
	glColor3f(0.0f,0.0f,1.0f);
	gluSphere(object,0.09,100,100);
	glPopMatrix();


	//eye
	glPushMatrix();
	glTranslatef(0.10,0.3,-1.0);
	glColor3f(0.0f,0.0f,1.0f);
	gluSphere(object,0.09,100,100);
	//glutSolidSphere(0.3,50,50);
	glPopMatrix();


	//right-hand
	glPushMatrix();
	glTranslatef(0.30,0.0,-0.650);
	glColor3f(0.0f,1.0f,0.0f);
	glRotatef(90,0.0,1.0,0.0);
	gluCylinder(object,0.08,0.08,0.60,100,100);
	glPopMatrix();


	//left-hand
	glPushMatrix();
	glTranslatef(-0.30,0.0,-0.650);
	glColor3f(0.0f,1.0f,0.0f);
	glRotatef(-90,0.0,1.0,0.0);
	gluCylinder(object,0.08,0.08,0.60,100,100);
	glPopMatrix();



	//right leg
	glPushMatrix();
	theta = atan(0.4/0.7);
	glRotatef((theta*(180/3.14)),0.0f,1.0f,0.0f);
	glTranslatef(0.0,0.0,0.1);
	glColor3f(0.0f,1.0f,0.0f);
	gluCylinder(object,0.15,0.15,0.7,100,100);
	glPopMatrix();


	//left leg
	glPushMatrix();
	theta = atan(0.4/0.7);
	glRotatef(-(theta*(180/3.14)),0.0f,1.0f,0.0f);
	glTranslatef(0.0,0.0,0.1);
	glColor3f(0.0f,1.0f,0.0f);
	gluCylinder(object,0.15,0.15,0.7,100,100);
	glPopMatrix();

	glPopMatrix();


}
// ializing some openGL 3D rendering options
void initRendering()
{

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL); 
	Image* imagesky = loadBMP("./bmp/sky.bmp");
	_textureIdsky = loadTexture(imagesky);
	delete imagesky;
	Image* image = loadBMP("./bmp/vtr.bmp");
	_textureId = loadTexture(image);
	delete image;
	Image* imagemove = loadBMP("./bmp/white.bmp");
	_textureIdmove = loadTexture(imagemove);
	delete imagemove;
	Image* imagetele = loadBMP("./bmp/red.bmp");
	_textureIdtele = loadTexture(imagetele);
	delete imagetele;
	Image* imagesg = loadBMP("./bmp/orange.bmp");
	_textureIdsg = loadTexture(imagesg);
	delete imagesg;
	Image* imagen = loadBMP("./bmp/grey.bmp");
	_textureIdn = loadTexture(imagen);
	delete imagen;
}

// Function called when the window is resized
void handleResize(int w, int h) 
{

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void generate()
{
	if(flag_jump==0 &&  flag_dead==0)
	{
		flag_static=1;
	}
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27)
	{
		exit(0);     // escape key is pressed
	}
	if(key=='n')
	{
		flag_camera=3;
	}
	if(key=='t')
	{
		//		printf("hii\n");
		flag_camera=2;
	}
	if(key=='h')
	{
		flag_camera=1;
	}
	if(key=='j' &&  flag_jump!=1)
	{
		flag_jump=1;
		temp_x=man_x;
		temp_y=man_y;
		temp_z=man_z;
		t=0;
	}
	if(key=='n')
	{
		flag_camera=3;
	}
	if(key=='x')
	{
		flag_camera=4;
	}
	if(flag_camera==4 &&  key=='w')
	{
		if((Tileblock1 <=9 && Tileblock1>0) &&  (Tileblock2<=9 && Tileblock2>=0))
		{
			Tileblock1--;
		}
	}
	if(flag_camera==4 &&  key=='d')
	{
		if((Tileblock1 <=9 && Tileblock1>=0) &&  (Tileblock2<=9 && Tileblock2>0))
		{
			Tileblock2--;
		}
	}
	if(flag_camera==4 &&  key=='a')
	{
		if((Tileblock1<=9 && Tileblock1>=0) &&  (Tileblock2<9 && Tileblock2>=0))
		{
			Tileblock2++;
		}
	}
	if(flag_camera==4 &&  key=='s')
	{
		if((Tileblock1 <9 && Tileblock1>=0) &&  (Tileblock2<9 && Tileblock2>-1))
		{
			Tileblock1++;
		}
	}

}

void handleKeypress2(int key, int x, int y) {

	if (key == GLUT_KEY_LEFT && flag_move_stop!=1)
	{
		flag_temp=0;
		if(a == 0)
		{
			a = -d;
			d = 0;
		}
		else if(d == 0)
		{
			d  = a;
			a = 0;
		}
		ang += 90;
		//hey
	}
	if (key == GLUT_KEY_RIGHT && flag_move_stop!=1)
	{
		flag_temp=0;
		if(a == 0){
			a = d;
			d = 0;
		}
		else if(d == 0){
			d = -a;
			a = 0;
		}

		ang -= 90;
		//hey

	}
	if (key == GLUT_KEY_UP && flag_move_stop!=1)
	{
		flag_up=1;
		flag=flag%4;
		//  printf("hii  baby  flag_up=%d   flag=%d\n",flag_up,flag);
		if(flag==1)
		{
			flag_static=0;
			flag++;
		}	
		else if(flag==3)
		{
			flag_static=0;
			flag=0;
		}	
		else if(flag==2 || flag==0)
		{
			flag_static=0;
			flag++;
		}	
	}
	if (key == GLUT_KEY_DOWN && flag_move_stop!=1)
	{
		flag_up=2;
		//  printf("hii  baby  flag_up=%d   flag=%d\n",flag_up,flag);
		if(flag==1)
		{
			flag_static=0;
			flag++;
		}	
		else if(flag==3)
		{
			flag_static=0;
			flag=0;
		}	
		else if(flag==2 || flag==0)
		{
			flag_static=0;
			flag++;
		}	
	}
}

void handleMouseclick(int button, int state, int x, int y) {

	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			theta += 15;
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			theta -= 15;
		}
		else if(button==3 && zoom<4)
		{
			zoom+=0.1;
		}
		else if(button==4 &&  zoom >0)
		{
			zoom-=0.1;
		}
	}
}
