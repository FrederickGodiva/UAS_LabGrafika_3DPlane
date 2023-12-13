// Project_UAS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <glut.h>

float translationX = 0, translationY = 0, translationZ = -8, rotationX = 0, rotationY = 0, rotationZ = 4;
bool START = false;
int mouseX = 0;
int mouseY = 0;
bool mouseClick = false;


void resize(int width, int height);
void idle();
void mouseButton(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void drawPlane();
void display();



int main(int argc, char* argv[]) 
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(128, 128);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("UAS Lab Grafika Komputer");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
}



void resize(int width, int height)
{
    // Avoid division by zero
    if (height == 0)
    {
        height = 1;
    }

    // Set the viewport to the entire window
    glViewport(0, 0, width, height);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(width) / static_cast<double>(height), 1.0, 700.0);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Apply translation to the view
    glTranslatef(0.0, 0.0, -10.0);
}

void idle()
{
    glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseClick = true;
        mouseX = x;
        mouseY = y;
    }
    else
    {
        mouseClick = false;
    }
}


void mouseMotion(int x, int y)
{
    if (mouseClick)
    {
        int deltaX = x - mouseX;
        int deltaY = y - mouseY;

        rotationY += deltaX * 0.2;
        rotationX += deltaY * 0.2;

        mouseX = x;
        mouseY = y;

        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        translationY += 0.3;
        break;
    case 's':
        translationY -= 0.3;
        break;
    case 'a':
        translationX -= 0.2;
        break;
    case 'd':
        translationX += 0.2;
        break;
    case 'q':
        translationZ += 0.3;
        break;
    case 'e':
        translationZ -= 0.3;
        break;
    case 'p':
        START = !START;
        break;
    }

    glutPostRedisplay();
}

void drawPlane()
{
    // Plane Body
    glColor3d(0.53, 0.67, 0.55);
    glPushMatrix();
        glTranslated(0, 0, 0);
        glScaled(3, 0.4, 0.5);
        glutSolidSphere(1, 30, 30);
    glPopMatrix();

    // Plane Cockpit
    glColor3d(0, 0, 0);
    glPushMatrix();
        glTranslated(1.7, 0.1, 0);
        glScaled(1.5, 0.7, 0.8);
        glRotated(40, 0, 1, 0);
        glutSolidSphere(0.45, 30, 30);
    glPopMatrix();

    // Right Wing
    glColor3d(0.93, 0.78, 0.67);
    glPushMatrix();
        glTranslated(0, 0, 1.2);
        glRotated(-50, 0, 1, 0);
        glScaled(0.7, 0.1, 3);
        glRotated(25, 0, 1, 0);
        glutSolidCube(1);
    glPopMatrix();

    // Right Wing Outer Machine
    glColor3d(0.68, 0.78, 0.67);
    glPushMatrix();
        glTranslated(-0.3, -0.15, 1.5);
        glRotated(90, 0, 1, 0);
        glScaled(0.1, 0.1, 0.9);
        glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    // Right Wing Inner Machine
    glColor3d(0.68, 0.78, 0.67);
    glPushMatrix();
        glTranslated(0.2, -0.15, 0.9);
        glRotated(90, 0, 1, 0);
        glScaled(0.1, 0.1, 0.9);
        glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    // Left Wing
    glColor3d(0.93, 0.78, 0.67);
    glPushMatrix();
        glTranslated(0, 0, -1.2);
        glRotated(50, 0, 1, 0);
        glScaled(0.7, 0.1, 3);
        glRotated(-25, 0, 1, 0);
        glutSolidCube(1);
    glPopMatrix();

    // Left Wing Outer Machine
    glColor3d(0.68, 0.78, 0.67);
    glPushMatrix();
        glTranslated(-0.3, -0.15, -1.5);
        glRotated(90, 0, 1, 0);
        glScaled(0.1, 0.1, 0.9);
        glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    // Left Wing Inner Machine
    glColor3d(0.68, 0.78, 0.67);
    glPushMatrix();
        glTranslated(0.2, -0.15, -0.9);
        glRotated(90, 0, 1, 0);
        glScaled(0.1, 0.1, 0.9);
        glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    glPushMatrix();
        // Position Set
        glTranslated(-2.8, 0, 0);
        glScaled(0.8, 0.5, 0.3);

        // Right Tail Wing
        glColor3d(0.93, 0.78, 0.67);
        glPushMatrix();
            glTranslated(0.4, 0, 1.5);
            glRotated(-30, 0, 1, 0);
            glScaled(0.7, 0.1, 3);
            glRotated(10, 0, 1, 0);
            glutSolidCube(1);
        glPopMatrix();

        // Left Tail Wing
        glColor3d(0.93, 0.78, 0.67);
        glPushMatrix();
            glTranslated(0.4, 0, -1.5);
            glRotated(30, 0, 1, 0);
            glScaled(0.7, 0.1, 3);
            glRotated(-10, 0, 1, 0);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();

    // Tail Body
    glColor3d(0.77, 1, 0.97);
    glPushMatrix();
        glTranslated(-2.7, 0.5, 0);
        glRotated(45, 0, 0, 1);
        glScaled(0.8, 2, 0.1);
        glRotated(-20, 0, 0, 1);
        glutSolidCube(0.5);
    glPopMatrix();

    // Tail Head
    glColor3d(0.77, 1, 0.97);
    glPushMatrix();
        glTranslated(-2.95, 0.85, 0);
        glRotated(90, 0, 1, 0);
        glScaled(0.05, 0.05, 0.6);
        glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();
}

void display()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double v = t * 50.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLoadIdentity();

    gluLookAt(0.0, 4.5, 10.0, 0, 4, 0, 0, 1.0f, 0.0f);
    glTranslatef(translationX, translationY, translationZ);
    glRotated(rotationX, 1, 0, 0);
    glRotated(rotationY, 0, 1, 0);
    glRotated(rotationZ, 0, 0, 1);

    if (START)
    {
        glPushMatrix();
            glTranslated(0, 0, 0);
            glScaled(2, 2, 2);
            glRotated(v, 0, 1, 0);
            drawPlane();
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
            glTranslated(0, 0, 0);
            glScaled(2, 2, 2);
            glRotated(0, 0, 1, 0);
            drawPlane();
        glPopMatrix();
    }

    glutSwapBuffers();
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file