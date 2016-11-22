#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>


GLfloat Light0Ambient[]={ 1.0f, 0.2f, 0.2f, 1.0f };
GLfloat Light0Diffuse[]={ 0.3f, 1.0f, 0.3f, 1.0f };

GLfloat LightAmbient[]={ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]={ 0.3f, 0.3f, 0.8f, 1.0f };
GLfloat LightSpecular[]={ 0.5f, 0.3f, 1.0f, 1.0f };
GLfloat LightPosition[]={ 5.0f, 0.0f, -7.0f, 1.0f };
GLfloat SpotDirection[]={-1.0f, 0.0f, 0.0f};
GLfloat SpotCutoff=15.0f;


void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Diffuse);

//    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, SpotDirection);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, SpotCutoff);
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);

//    glEnable(GL_LIGHT1);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
}

void DrawCube()
{
		glBegin(GL_POLYGON);
			glNormal3f(0.0f, 1.0f, 0.0f);	// top face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3f(0.0f, 0.0f, 1.0f);	// front face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3f(1.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3f(-1.0f, 0.0f, 0.0f);	// left face
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3f(0.0f, -1.0f, 0.0f);	// bottom face
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3f(0.0f, 0.0f, -1.0f);	// back face
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-1.0,-1.0,-7.0);

    glColor3f(1.0,0.0,0.0);
    DrawCube();

}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Surface* ekran=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int petla=1;
//    Uint32 start;
    SDL_Event zdarzenie;
    init();
    while (petla==1)
    {
//        start=SDL_GetTicks();
        while (SDL_PollEvent(&zdarzenie))
        {
            switch(zdarzenie.type)
            {
                case SDL_QUIT:
                petla=0;
                break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
//        if (1000/30>(SDL_GetTicks()-start)) SDL_Delay(SDL_GetTicks()-start);
    }
    SDL_Quit();
    return 0;
}
