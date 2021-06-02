// Lab4_task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include <GL/glut.h>
#include <glm.hpp>

#include "Terrain.h"
#include "Player.h"
#include "ModelMD.h"

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

#define MOVEMENT_SPEED 2
#define ROTATION_SPEED 0.03
#define MOVEMENT_SPEED_MODEL 1



Player player;

glm::fvec2 oldmouse{ 0,0 };

BruteForce bF;
Fractal Fr;

ModelMD modeldata(SOLDIER_MODEL);
//modeldata->LoadTexture()
ModelMD* model_data_ptr = &modeldata;
Md2Object model;//(model_data_ptr);

int frame_count = 0;

glm::fvec3 move = { 0,0,0 };
glm::fvec3 turn = { 0,0,0 };
glm::fvec3 model_move = { 0,0,0 };

void Initialize();
void display();
void draw();
void inputEventUpdate();
void keyboard(unsigned char key, int x, int y);
void keyboardSpecial(int key, int x, int y);
void drawCallback(int i) { glutPostRedisplay(); };
void mouseButton(int key, int state, int x, int y);
void mouseMovePassive(int x, int y);

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glEnable(GL_TEXTURE_2D);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Task 1: Design and implement Terrain");

    Initialize();

    glutTimerFunc(6, drawCallback, 0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);
    glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mouseMovePassive);

    glutMainLoop();
}

void Initialize()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    bF.loadHeightfield(HEIGHTFIELD_MAP, 128);
    bF.loadHeightfieldTexture(GRASS_TEXTURE, 128);
    bF.setScalingFactor(SCALE_X, SCALE_Y, SCALE_Z);

    Fr.generateFractalHeightfield(2);
    Fr.setScalingFactor(SCALE_X, SCALE_Y, SCALE_Z);

    model_data_ptr->loadTexture(SOLDIER_TEXTURE);
    model.setModel(model_data_ptr);
    model.setScale(2);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'W':
    {
        move[2] += MOVEMENT_SPEED;
        break;
    }
    case 'w':
    {
        move[2] += MOVEMENT_SPEED;
        break;
    }
    case 'A':
    {
        move[0] -= MOVEMENT_SPEED;
        break;
    }
    case 'a':
    {
        move[0] -= MOVEMENT_SPEED;
        break;
    }
    case 'S':
    {
        move[2] -= MOVEMENT_SPEED;
        break;
    }
    case 's':
    {
        move[2] -= MOVEMENT_SPEED;
        break;
    }
    case 'D':
    {
        move[0] += MOVEMENT_SPEED;
        break;
    }
    case 'd':
    {
        move[0] += MOVEMENT_SPEED;
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
       /* std::cout << "position: " << player.camera.getCameraView()[0][0] << "\n"
            << player.camera.getCameraView()[0][1] << "\n"  << player.camera.getCameraView()[0][2] << std::endl;*
        std::cout << "position: " << model.getTranslate()[0] << "\n" <<
            model.getTranslate()[1] <<"\n"<< model.getTranslate()[2] << std::endl;*/

        break;
    }
    default:
        break;
    }
    glutPostRedisplay();
}

void keyboardSpecial(int key, int x, int y)
{
    
    switch (key)
    {
    case GLUT_KEY_UP:
    {
        model_move[2] += MOVEMENT_SPEED_MODEL;
        
        break;
    }
    case GLUT_KEY_DOWN:
    {
        model_move[2] -= MOVEMENT_SPEED_MODEL;
        break;
    }
    case GLUT_KEY_RIGHT:
    {
        model_move[0] -= MOVEMENT_SPEED_MODEL;
        break;
    }
    case GLUT_KEY_LEFT:
    {
        model_move[0] += MOVEMENT_SPEED_MODEL;
        break;
    }
    default:
        break;
    }
    glutPostRedisplay();
}

void mouseMovePassive(int x, int y)
{
    float deltax = x - oldmouse[0];
    float deltay = y - oldmouse[1];
    turn = { deltax * ROTATION_SPEED * -1, deltay * ROTATION_SPEED *-1, 0 };

    oldmouse = { x, y };

    glutPostRedisplay();
}

void mouseButton(int key, int state, int x, int y)
{

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // inputEventUpdate();

    player.camera.translate(move);
    player.camera.rotate(turn);
    model_move[1] = bF.getSurfaceHeight(static_cast<int> (model.getTranslate()[0]), static_cast<int>(model.getTranslate()[2]));
    model.setTranslate(model_move);
    move = turn = model_move = { 0,0,0 };

   // model_move[1] = bF.getHeight(model.getTranslate()[0], model.getTranslate()[2]);

   /* gluLookAt(cam.posX, cam.posY, cam.posZ, cam.forwardX, cam.forwardY,
        cam.forwardZ, cam.upX, cam.upY, cam.upZ);*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(player.camera.getCameraPerspective()[0], player.camera.getCameraPerspective()[1],
        player.camera.getCameraPerspective()[2], player.camera.getCameraPerspective()[3]);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(player.camera.getCameraView()[0][0], player.camera.getCameraView()[0][1], player.camera.getCameraView()[0][2],
        player.camera.getCameraView()[1][0], player.camera.getCameraView()[1][1], player.camera.getCameraView()[1][2],
        player.camera.getCameraView()[2][0], player.camera.getCameraView()[2][1], player.camera.getCameraView()[2][2]);

    draw();
    glutSwapBuffers();
    glFlush();
}

void draw()
{

    bF.render();

    model.drawObjectFrame(frame_count);
    //Fr.render();
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
