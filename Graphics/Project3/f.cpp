#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

float angle=0.0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(angle,0.0,0.0,1.0);
        glColor3f(1.0,0.0,0.0);
    	glBegin(GL_TRIANGLES);
		glVertex3f( 0.0, 1.0, -5.0);
		glVertex3f(-1.0,-1.0, -5.0);
		glVertex3f( 1.0,-1.0, -5.0);
	glEnd();
}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int loop=1;
    SDL_Event myevent;
    init();
    while (loop==1)
    {
        while (SDL_PollEvent(&myevent))
        {
            switch(myevent.type)
            {
                case SDL_QUIT:
                loop=0;
                break;

                case SDL_KEYDOWN:
                if (myevent.key.keysym.sym==SDLK_SPACE) angle+=30;
                break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
