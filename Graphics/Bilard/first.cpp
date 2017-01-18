#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<math.h>

float angle=0.0;
float x=0.0;
float y=0.0;
float kx=0.0;
float ky=0.0;
float speed=0.02;
float deltax;   //przyrost na osi Ox
float deltay;   //przyrost na osi OY

bool start=false;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void compass(float a)   //rysowanie kompasu
{
    glColor3f(1.0,1.0,1.0);
    for (float i=0; i<360; i++)
    {
        glBegin(GL_LINES);
        glVertex3f(cos(i*M_PI/180),sin(i*M_PI/180),0.0);
        glVertex3f(cos((i+1)*M_PI/180),sin((i+1)*M_PI/180),0.0);
        glEnd();
    }
    glColor3f(0.0,1.0,0.0);
    glPushMatrix();
        glRotatef(a,0.0,0.0,1.0);
        glBegin(GL_LINES);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(1.0,0.0,0.0);
        glEnd();
    glPopMatrix();
}

void square(float dim)
{
    glPushMatrix();
    glScalef(dim,dim,1.0);
    glBegin(GL_QUADS);
        glVertex3f(-0.5,-0.5,0.0);
        glVertex3f(-0.5,0.5,0.0);
        glVertex3f(0.5,0.5,0.0);
        glVertex3f(0.5,-0.5,0.0);
    glEnd();
    glPopMatrix();
}

void table(float width, float height)   //rysowanie planszy
{
    glColor3f(0.8,0.8,0.8);
    glPushMatrix();
        glScalef(width,height,1.0);
        square(1.0);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0,0.0,-10.0);

    glPushMatrix();
        glTranslatef(-3.0,-2.0,0.0);
        compass(angle);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2.0,0.0,0.0);
        table(4.0,6.0);
        if (start)  //warunki odbicia od sciany
        {
            if (kx>1.9 || kx<-1.9) deltax=-deltax;
            if (ky>2.9 || ky<-2.9) deltay=-deltay;
            kx=kx+deltax;
            ky=ky+deltay;
        }
        glTranslatef(kx,ky,0.01);
        glColor3f(0.0,0.0,1.0);
        square(0.2);
    glPopMatrix();
}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int loop=1;
    SDL_Event myevent;
    SDL_EnableKeyRepeat(10,10);

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
                if (myevent.key.keysym.sym==SDLK_LEFT & !start) angle+=1.0;
                if (myevent.key.keysym.sym==SDLK_RIGHT & !start) angle-=1.0;
                if (myevent.key.keysym.sym==SDLK_SPACE & !start)
                {
                    start=true;
                    deltax=speed*cos(angle*M_PI/180);
                    deltay=speed*sin(angle*M_PI/180);
                }
                if (myevent.key.keysym.sym==SDLK_ESCAPE)
                {
                    start=false;
                    kx=0.0;
                    ky=0.0;
                }
                break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
