#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>


using namespace std;

GLfloat Light0Ambient[]={ 1.0f, 0.2f, 0.2f, 1.0f };
GLfloat Light0Diffuse[]={ 0.3f, 1.0f, 0.3f, 1.0f };

GLfloat LightAmbient[]={ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]={ 0.3f, 0.3f, 0.8f, 1.0f };
GLfloat LightSpecular[]={ 0.5f, 0.3f, 1.0f, 1.0f };
GLfloat LightPosition[]={ 5.0f, 0.0f, -7.0f, 1.0f };
GLfloat SpotDirection[]={-1.0f, 0.0f, 0.0f};
GLfloat SpotCutoff=15.0f;

GLfloat MaterialAmbient[]={ 1.0f, 1.0f, 0.1f, 1.0f };
GLfloat MaterialDiffuse[]={ 1.0f, 1.0f, 0.1f, 1.0f };
GLfloat MaterialShininess[] ={ 70.0 };
GLfloat MaterialSpecular[] ={ 1.0, 1.0, 1.0, 1.0 };

double const square = 10;
float angleX = 0, angleY = 0, angleZ = 0, dist = -10,vecX[] = {1,0,0} ,vecY[] = {0,1,0},vecZ[] = {0,0,1};

static double * body_mass, * positionX, * nextPositionX, * positionY, * nextPositionY,
              * velocityX, * nextVelocityX, * velocityY, * nextVelocityY, accuracy, PI = 3.141592654;
static const double G = 1;

static int n_steps, n_bodies;




void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Diffuse);

    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, SpotDirection);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, SpotCutoff);
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);

    glEnable(GL_LIGHT1);

    glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, MaterialShininess);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
}

void drawSphere(int k){
    double masa = body_mass[k];
    double X = positionX[k];
    double Y = positionY[k];

    float radio=0.1*pow(masa,1.0/3);
    float teta;
    float phi;
    float porcentajex=0;
    float porcentajey=1;
    int ResolucionEsfera = 40;
    float incrementox=(float)(1/((float)2*ResolucionEsfera)); //1/20
    float incrementoy=(float)(-1/((float)ResolucionEsfera)); //1/10
    float increRad=(float)(PI/ResolucionEsfera);
    float Vertice1x,Vertice1y, Vertice1z=0;
    float Vertice2x,Vertice2y, Vertice2z=0;
    float Vertice3x,Vertice3y, Vertice3z=0;
    float Vertice4x,Vertice4y, Vertice4z=0;
    //-----------\/---------Construcción de la esfera poco a poco---------------
    double FinalPhi = 2*PI;
    double FinalTeta = PI;
    //if(FinalPhi<2*PI)FinalPhi+=increRad/50;/*FinalPhi=2*PI;*/
    //if(FinalTeta<PI)FinalTeta+=increRad/100;/*FinalTeta=(float)PI;*/
             //-----------/\---------Construcción de la esfera poco a poco---------------
    for(teta=0;teta<FinalTeta;teta+=increRad){
        for(phi=0;phi<FinalPhi;phi+=increRad){
                          //VERTICE 1
            Vertice1z=(radio)*((float) sin(teta))*((float)cos(phi));
            Vertice1x=X+(radio)*((float) sin(teta))*((float)sin(phi));
            Vertice1y=Y+(radio)*((float) cos(teta));
                          //VERTICE 2
            Vertice2z=(radio)*((float) sin(teta+increRad))*((float)cos(phi));
            Vertice2x=X+(radio)*((float) sin(teta+increRad))*((float)sin(phi));
            Vertice2y=Y+(radio)*((float) cos(teta+increRad));
                          //VERTICE 3
            Vertice3z=(radio)*((float) sin(teta+increRad))*((float)cos(phi+increRad));
            Vertice3x=X+(radio)*((float) sin(teta+increRad))*((float)sin(phi+increRad));
            Vertice3y=Y+(radio)*((float) cos(teta+increRad));
                          //VERTICE 4
            Vertice4z=(radio)*((float) sin(teta))*((float)cos(phi+increRad));
            Vertice4x=X+(radio)*((float) sin(teta))*((float)sin(phi+increRad));
            Vertice4y=Y+(radio)*((float) cos(teta));

            glNormal3f((float)1.5*sin(teta)*sin(phi),(float)1.5*cos(teta),(float)1.5*sin(teta)*cos(phi));
            //glNormal3f(0,-10,10);

            glBegin(GL_TRIANGLES);
              //TRIANGULO 1
                glTexCoord2f(porcentajex, porcentajey);glVertex3f(Vertice1x, Vertice1y,Vertice1z);
                glTexCoord2f(porcentajex,porcentajey+incrementoy);glVertex3f(Vertice2x, Vertice2y,Vertice2z);
                glTexCoord2f(porcentajex+incrementox,porcentajey+incrementoy);glVertex3f(Vertice3x,Vertice3y,Vertice3z);
                                            //TRIANGULO
                glTexCoord2f(porcentajex, porcentajey);glVertex3f(Vertice1x, Vertice1y,Vertice1z);
                glTexCoord2f(porcentajex+incrementox,porcentajey+incrementoy);glVertex3f(Vertice3x, Vertice3y,Vertice3z);
                glTexCoord2f(porcentajex+incrementox,porcentajey);glVertex3f(Vertice4x, Vertice4y,Vertice4z);

            glEnd();

            porcentajex+=incrementox;
        }
        porcentajey+=incrementoy;
        porcentajex=0;
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT1);
    glLoadIdentity();
    glTranslatef(0,0,dist);
    glRotatef(angleX,vecX[0],vecX[1],vecX[2]);
    glRotatef(angleY,vecY[0],vecY[1],vecY[2]);
    glRotatef(angleZ,vecZ[0],vecZ[1],vecZ[2]);
    double colour = 0.5, inc = 0.5/n_bodies;
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
        glVertex3f(-square,-square,0);
        glVertex3f(-square,square,0);
        glVertex3f(square,square,0);
        glVertex3f(square,-square,0);
    glEnd();
    for(int i = 0; i < n_bodies; i ++){
        glColor3f(colour,1-colour,colour);
        drawSphere(i);
        colour+=inc;
    }
}



void calcGForce(int j, double & gForceX, double & gForceY){
    double Gi,Di2;
    gForceX = gForceY = 0;
    for(int i = 0; i < n_bodies; i++){
        if(i != j){
          // Square dist from the i bodie.
          Di2 = (positionX[j]-positionX[i])*(positionX[j]-positionX[i])
          + (positionY[j]-positionY[i])*(positionY[j]-positionY[i]);
          if(abs(Di2) > 0.1){
              // Module of the force from the i bodie.
              Gi = G*body_mass[j]*body_mass[i]/Di2;

              // X coordenate of the force from the i bodie.
              gForceX -= Gi*(positionX[j]-positionX[i])/sqrt(Di2);

              // Y coordenate of the force from the i bodie.
              gForceY -= Gi*(positionY[j]-positionY[i])/sqrt(Di2);
          }
          else{
              gForceX = gForceY = 0;
          }
        }
    }
}

int main(int argc, char const *argv[]) {

    if(argc < 2){
        cout << "This program need a file to work\n";
        return 1;
    }
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);
    init();
    // Text file opened
    ifstream inputFile;
    inputFile.open(argv[1]);

    // Initialice this three variables with the file information

    char buffer[50];
    inputFile.getline(buffer,50,' ');
    n_steps = atoi(buffer);
    inputFile.getline(buffer,50,' ');
    accuracy = atof(buffer);
    inputFile.getline(buffer,50,'\n');
    n_bodies = atoi(buffer);

    // Initialice the important vectors.

    body_mass = new double [n_bodies];
    positionX = new double [n_bodies];
    nextPositionX = new double [n_bodies];
    positionY = new double [n_bodies];
    nextPositionY = new double [n_bodies];
    velocityX = new double [n_bodies];
    nextVelocityX = new double [n_bodies];
    velocityY = new double [n_bodies];
    nextVelocityY = new double [n_bodies];

    // Getting the information of the file of each body.

    for(int i = 0; i < n_bodies; i++){
        inputFile.getline(buffer,50,' ');
        body_mass[i] = atof(buffer);
        inputFile.getline(buffer,50,' ');
        positionX[i] = atof(buffer);
        inputFile.getline(buffer,50,' ');
        positionY[i] = atof(buffer);
        inputFile.getline(buffer,50,' ');
        velocityX[i] = atof(buffer);
        inputFile.getline(buffer,50,'\n');
        velocityY[i] = atof(buffer);
    }

    double forceX, forceY;

    int petla=1;
    SDL_Event myevent;
    bool space, w, s, down, up, right, left;
    space = down = up = right = left = false;
    while(petla == 1){
        while (SDL_PollEvent(&myevent)){
            switch(myevent.type){
                case SDL_QUIT:
                petla=0;
                break;
                case SDL_KEYDOWN:
                if (myevent.key.keysym.sym==SDLK_SPACE) space = true;
                if( myevent.key.keysym.sym == SDLK_DOWN) down = true;
                if( myevent.key.keysym.sym == SDLK_UP) up = true;
                if( myevent.key.keysym.sym == SDLK_RIGHT) right = true;
                if( myevent.key.keysym.sym == SDLK_LEFT) left = true;
                if( myevent.key.keysym.sym == SDLK_w) w = true;
                if( myevent.key.keysym.sym == SDLK_s) s = true;
                break;
                case SDL_KEYUP:
                if (myevent.key.keysym.sym==SDLK_SPACE) space = false;;
                if( myevent.key.keysym.sym == SDLK_DOWN) down = false;
                if( myevent.key.keysym.sym == SDLK_UP) up = false;
                if( myevent.key.keysym.sym == SDLK_RIGHT) right = false;
                if( myevent.key.keysym.sym == SDLK_LEFT) left = false;
                if( myevent.key.keysym.sym == SDLK_w) w = false;
                if( myevent.key.keysym.sym == SDLK_s) s = false;
                break;

            }
        }
        if(space){
            //angle+=1;
        }
        if(up){
            angleX+=1;
        }
        if(down){
            angleX -=1;
        }
        if(right){
            angleY +=1;
        }
        if(left){
            angleY -=1;
        }
        if(w){
            dist-=1;
        }
        if(s){
            dist+=1;
        }
        for(int j = 0; j < n_bodies; j++){
            calcGForce(j,forceX, forceY);
            // Calculing next position and display it.
            nextPositionX[j] = positionX[j] + accuracy*velocityX[j];
            nextPositionY[j] = positionY[j] + accuracy*velocityY[j];
            // Calculing next velocity.
            nextVelocityX[j] = velocityX[j] + accuracy*forceX/body_mass[j];
            nextVelocityY[j] = velocityY[j] + accuracy*forceY/body_mass[j];
            if((nextPositionX[j]>= square and nextVelocityX[j]> 0) or (nextPositionX[j] <= -square and nextVelocityX[j] < 0)){
                nextVelocityX[j] = -nextVelocityX[j];
            }
            if((nextPositionY[j]>= square and nextVelocityY[j]> 0) or (nextPositionY[j] <= -square and nextVelocityY[j] < 0)){
                nextVelocityY[j] = -nextVelocityY[j];
            }


        }

        // Calculing the next step and displaing the position.
        for(int j = 0; j < n_bodies; j++){
            positionX[j] = nextPositionX[j];
            positionY[j] = nextPositionY[j];
            velocityX[j] = nextVelocityX[j];
            velocityY[j] = nextVelocityY[j];
        }
        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();

    // Deleting all the vectors We have used.

    delete body_mass;
    delete positionX ;
    delete nextPositionX ;
    delete positionY ;
    delete nextPositionY ;
    delete velocityX ;
    delete nextVelocityX ;
    delete velocityY ;
    delete nextPositionY ;

    // Closing the file.
    inputFile.close();

    return 0;
}
