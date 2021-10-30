// Lab4_task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include <GL/glut.h>
#include <glm.hpp>

#include "Terrain.h"
#include "Player.h"
#include "ModelMD.h"

//#include <coldet.h>
//#include <cdmath3d.h>
//#include <q3.h>
#include "q3Renderer.h"
#include "PhysicsManager.h"

//#include "BruteForce.h"
// textures
#define HEIGHTFIELD_MAP "image/height128.raw"
#define GRASS_TEXTURE "image/grass02.png"
#define WOOD_TEXTURE "image/Wood.png"
#define DIRT_TEXTURE "image/DIRT.png"

//models
#define SOLDIER_MODEL "models/soldier/tris.md2"
#define SOLDIER_TEXTURE "models/soldier/skin.tga"

#define SHIP_MODEL "models/bigviper/tris.md2"
#define SHIP_TEXTURE "models/bigviper/skin.tga"

#define MODEL_OTHER "models/hueteotl/tris.md2"

#define SCALE_X 30
#define SCALE_Y 1.8
#define SCALE_Z 30

#define MOVEMENT_SPEED 5
#define ROTATION_SPEED 0.18
#define MOVEMENT_SPEED_MODEL 1

#define REFRESH_RATE_MS 1



Player player;

glm::fvec2 oldmouse{ 0,0 };

BruteForce bF;
Fractal Fr;

ModelMD modeldata(SOLDIER_MODEL);
ModelMD* model_data_ptr = &modeldata;
Md2Object model;//(model_data_ptr);

int frame_count = 0;

glm::dvec3 move = { 0,0,0 };
glm::dvec3 turn = { 0,0,0 };
glm::dvec3 model_move = { 0,0,0 };

//q3Box box1;
//q3Vec3 vec;

q3Renderer render_;

PhysicsManager physics;

long double Previus_Time;
long double Delta_Time;

void Initialize();
void display();
void draw();
void drawBox();
void inputEventUpdate();
void keyboard(unsigned char key, int x, int y);
void keyboardSpecial(int key, int x, int y);
void Update(int i);// { glutPostRedisplay(); };
void mouseButton(int key, int state, int x, int y);
void mouseMovePassive(int x, int y);
void animate(long double deltaT);

void setupPhysics() {
    std::shared_ptr<RigidBody> body1 = std::make_shared<RigidBody>();
    //body1.get()->setLinearVelocity(VelocityVec3(0,0,0.05));
    
    physics.AddRigidBody(body1);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glEnable(GL_TEXTURE_2D);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Task 1: Design and implement Terrain");

    Initialize();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);
    glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mouseMovePassive);

    glutTimerFunc(REFRESH_RATE_MS, Update, REFRESH_RATE_MS);
    Previus_Time = glutGet(GLUT_ELAPSED_TIME);

    glutMainLoop();
}

void Initialize()
{
    glClearColor(0.3, 0.3, 0.8, 0.5);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    GLfloat light_pos[] = { 10, 10, -10, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    bF.loadHeightfield(HEIGHTFIELD_MAP, 128);
    bF.loadHeightfieldTexture(GRASS_TEXTURE, 128);
    bF.setScalingFactor(SCALE_X, SCALE_Y, SCALE_Z);

    Fr.generateFractalHeightfield(2);
    Fr.setScalingFactor(SCALE_X, SCALE_Y, SCALE_Z);

    model_data_ptr->loadTexture(SOLDIER_TEXTURE);
    model.setModel(model_data_ptr);
    model.setScale(2);

    setupPhysics();

    player.camera_controller.setCameraPosition(glm::fvec3{0,0,-5});
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'W':
    {
        move[2] += MOVEMENT_SPEED * Delta_Time;
        break;
    }
    case 'w':
    {
        move[2] += MOVEMENT_SPEED * Delta_Time;
        break;
    }
    case 'A':
    {
        move[0] -= MOVEMENT_SPEED * Delta_Time;
        break;
    }
    case 'a':
    {
        move[0] -= MOVEMENT_SPEED * Delta_Time;
        break;
    }
    case 'S':
    {
        move[2] -= MOVEMENT_SPEED * Delta_Time;
        break;
    }
    case 's':
    {
        move[2] -= MOVEMENT_SPEED * Delta_Time;
        break;
    }
    case 'D':
    {
        move[0] += MOVEMENT_SPEED * Delta_Time;
        break;
    }
    case 'd':
    {
        move[0] += MOVEMENT_SPEED * Delta_Time;
        break;
    }
    case 'q':
    {
        move[1] -= MOVEMENT_SPEED * Delta_Time;
        break;
    }
    case 'e':
    {
        move[1] += MOVEMENT_SPEED * Delta_Time;
        break;
    }
    case 'm':
    {
        if (frame_count < modeldata.getFramecount())
        {
            frame_count++;
        }
        else { frame_count = 0; }
        break;
    }
    case ' ':
    {
        glm::fvec3 pos = player.camera_controller.getCameraPosition();
        std::cout << "position" << pos[0] << "  " << pos[1] << "  " << pos[2] << std::endl;
        break;
    }
    default:
        break;
    }
    //glutPostRedisplay();
}

void keyboardSpecial(int key, int x, int y)
{
    
    switch (key)
    {
    case GLUT_KEY_UP:
    {
        model_move[2] += MOVEMENT_SPEED_MODEL * Delta_Time;
        
        break;
    }
    case GLUT_KEY_DOWN:
    {
        model_move[2] -= MOVEMENT_SPEED_MODEL * Delta_Time;
        break;
    }
    case GLUT_KEY_RIGHT:
    {
        model_move[0] -= MOVEMENT_SPEED_MODEL * Delta_Time;
        break;
    }
    case GLUT_KEY_LEFT:
    {
        model_move[0] += MOVEMENT_SPEED_MODEL * Delta_Time;
        break;
    }
    default:
        break;
    }
    //glutPostRedisplay();
}

void mouseMovePassive(int x, int y)
{
    float deltax = x - oldmouse[0];
    float deltay = y - oldmouse[1];
    if(deltax < 100 && deltax > -100 && deltay > -100 && deltay < 100)
        turn += glm::fvec3({ deltax * ROTATION_SPEED * Delta_Time, deltay * ROTATION_SPEED * Delta_Time, 0 });

    oldmouse = { x, y };

   
}

void mouseButton(int key, int state, int x, int y)
{

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    player.camera_controller.FreeFloatingCameraTranslate(move);
    player.camera_controller.FreeFloatingCameraRotate(turn);

    model_move[1] = bF.getSurfaceHeight(static_cast<int> (model.getTranslate()[0]), static_cast<int>(model.getTranslate()[2]));
    model.setTranslate(model_move);
    move = turn = model_move = { 0,0,0 };

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glm::fvec4 perspective = player.camera_controller.getCameraPerspective();
    gluPerspective(perspective[0], perspective[1], perspective[2], perspective[3]);
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glm::dmat3 lookat_matrix = player.camera_controller.getCameraViewMatrix();
    gluLookAt(lookat_matrix[0][0], lookat_matrix[0][1], lookat_matrix[0][2],
        lookat_matrix[1][0], lookat_matrix[1][1], lookat_matrix[1][2],
        lookat_matrix[2][0], lookat_matrix[2][1], lookat_matrix[2][2]);

    draw();
    glutSwapBuffers();
    glFlush();
}

void draw()
{
    drawBox();

    //bF.render();
    //model.drawObjectFrame(frame_count);
}

void drawBox()
{
    //box1.Render(box1.local, true, &render_);
    physics.Render(&render_);
}


void animate(long double deltaT)
{

}

void Update(int i)
{
    glutTimerFunc(REFRESH_RATE_MS, Update, REFRESH_RATE_MS);
    long double current_time = glutGet(GLUT_ELAPSED_TIME)/1000.0 ;
    Delta_Time = (current_time - Previus_Time);
    Previus_Time = current_time;

    physics.Step(Delta_Time);

    animate(Delta_Time);

    glutPostRedisplay();

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
