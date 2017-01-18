#include <GL/glut.h>
#include <math.h>

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
      glColor3f (0.0, 0.0, 0.0);

      glVertex3f (0.1, 0.1, 0.0);
      glVertex3f (0.9, 0.1, 0.0);
      glVertex3f (0.9, 0.9, 0.0);
      glVertex3f (0.1, 0.9, 0.0);

    glEnd();

    glFlush();
}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}


void Initialize() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int iArgc, char** cppArgv) {
    glutInit(&iArgc, cppArgv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(950, 500);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Universum");
    Initialize();
    glutDisplayFunc(Draw);
    glClear(GL_COLOR_BUFFER_BIT);

    //DrawCircle(0.5, 0.5, 0.2, 5);

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_TRIANGLES);
        glVertex3f(0,0,-5);
        glVertex3f(0,1,-5);
        glVertex3f(1,1,-5);
    glEnd();
    glutMainLoop();
    return 0;

}
