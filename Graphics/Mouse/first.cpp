#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

static double mouseX, mouseY;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

bool isInside(int i, int j){
    int r = 20;
    if(-r*5 +3*i*r + 180 > )
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_QUADS);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(isInside(i,j)){
                glColor3f(1.0f, 0.0f, 0.0f);
            }
            else{
                glColor3f(0.0f, 1.0f, 0.0f);
            }
            glVertex3f(-4+3*i,4-3*j, -10);
        	glVertex3f(-4+3*i,3-3*j, -10);
        	glVertex3f(-3+3*i,3-3*j, -10);
        	glVertex3f(-3+3*i,4-3*j, -10);
        }

    }
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
                	if (myevent.key.keysym.sym==SDLK_SPACE);
                        break;

                case SDL_MOUSEMOTION:
                        mouseX=myevent.button.x;
                        mouseY=myevent.button.y;
                        break;

                case SDL_MOUSEBUTTONDOWN:
                        if (myevent.button.button==SDL_BUTTON_LEFT);
                        break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
