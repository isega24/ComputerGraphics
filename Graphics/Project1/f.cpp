#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>


void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}


void DrawCube(){
    glColor3f(1.0,0.0,0.0);
		glBegin(GL_QUADS);			// top face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();
    glColor3f(1.0,1.0,0.0);
		glBegin(GL_QUADS);			// front face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
    glColor3f(0.0,1.0,0.0);
		glBegin(GL_QUADS);			// right face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
    glColor3f(0.0,1.0,1.0);
		glBegin(GL_QUADS);			// left face
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
		glEnd();
    glColor3f(0.0,0.0,1.0);
		glBegin(GL_QUADS);			// bottom face
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
    glColor3f(1.0,0.0,1.0);
		glBegin(GL_QUADS);			// back face
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0,0.0,0.0);
    glTranslatef(0,0,-5);
    glRotatef(45,45,45,1);
    glScalef(1,1,1);
    DrawCube();
}
int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

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
