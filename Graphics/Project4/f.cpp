#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<math.h>

float kat=0.0;
float kat2=0.0;
float sm1=0.0;
float sm2=0.0;
float sm1zm=0.0;
float sm2zm=0.0;
bool bl,br,kl=false;
float kolor[]={1.0,0.0,0.0};

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void DrawCube()
{
		glBegin(GL_POLYGON);			// top face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();
		glBegin(GL_POLYGON);			// front face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_POLYGON);			// right face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
		glBegin(GL_POLYGON);			// left face
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_POLYGON);			// bottom face
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_POLYGON);			// back face
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

    glTranslatef(0.0,0.0,-10.0);
    glRotatef(kat,0.0,1.0,0.0);
    glRotatef(kat2,0.0,0.0,1.0);

    glColor3f(kolor[0],kolor[1],kolor[2]);

    glPushMatrix();                 //korpus
    glScalef(2.0,1.0,1.0);
    DrawCube();
    glPopMatrix();

    glPushMatrix();                 //ogon
    glTranslatef(-2.0,0.3,0.0);
    glScalef(2.0,0.3,0.3);
    DrawCube();
    glPopMatrix();

    glPushMatrix();                 //ploza1
    glTranslatef(0.0,-0.7,0.3);
    glScalef(2.5,0.2,0.2);
    DrawCube();
    glPopMatrix();

    glPushMatrix();                 //ploza2
    glTranslatef(0.0,-0.7,-0.3);
    glScalef(2.5,0.2,0.2);
    DrawCube();
    glPopMatrix();

    glColor3f(0.2,0.2,0.2);

    glPushMatrix();                 //smiglo glowne
    glTranslatef(0.0,0.6,0.0);
    glRotatef(sm1,0.0,1.0,0.0);
    glScalef(4.5,0.02,0.2);
    DrawCube();
    glPopMatrix();

    glPushMatrix();                 //smiglo tylne
    glTranslatef(-2.8,0.3,0.3);
    glRotatef(sm2,0.0,0.0,1.0);
    glScalef(1.0,0.1,0.02);
    DrawCube();
    glPopMatrix();

    sm1+=sm1zm;
    sm2+=sm2zm;

}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    bool petla=true;
    Uint32 start;
    SDL_Event zdarzenie;

 //   SDL_EnableKeyRepeat(10,10);

    init();
    while (petla==true)
    {
        start=SDL_GetTicks();
        while (SDL_PollEvent(&zdarzenie))
        {
            switch(zdarzenie.type)
            {
                case SDL_QUIT:
                petla=false;
                break;

                case SDL_KEYDOWN:
                if (zdarzenie.key.keysym.sym==SDLK_ESCAPE)
                {
                    petla=false;
                }

                if (zdarzenie.key.keysym.sym==SDLK_SPACE)
                {
                    if (kl==false) {kl=true; kolor[0]=0.0; kolor[1]=1.0; kolor[2]=0.0;}
                    else {kl=false; kolor[0]=1.0; kolor[1]=0.0; kolor[2]=0.0;}
                }
                break;


                case SDL_MOUSEBUTTONDOWN:
                if (zdarzenie.button.button==SDL_BUTTON_LEFT)
                {
                    if (bl==false) { sm1zm=1.5; bl=true;}
                    else {bl=false; sm1zm=0.0;}
                }
                if (zdarzenie.button.button==SDL_BUTTON_RIGHT)
                {
                    if (br==false) { sm2zm=1.5; br=true;}
                    else {br=false; sm2zm=0.0;}
                }
                break;


                case SDL_MOUSEMOTION:
                kat=zdarzenie.button.x;
                kat2=-zdarzenie.button.y;
                break;

            }
        }
        display();
        SDL_GL_SwapBuffers();
        if (1000/30>(SDL_GetTicks()-start)) SDL_Delay(SDL_GetTicks()-start);
    }
    SDL_Quit();
    return 0;
}
