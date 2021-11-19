#pragma once


#include <iostream>
#include <vector>

#include <GL/glut.h>
#include <glm.hpp>

#include "Terrain.h"
#include "Player.h"
#include "ModelMD.h"

#include "q3Renderer.h"
#include "PhysicsManager.h"
#include "JsonLoader.h"

#include "DefineParameters.h"

namespace EngineComponents {

    class Application {
    private:

        Player player;

        glm::fvec2 oldmouse{ 0,0 };

        BruteForce bF;
        Fractal Fr;

        ModelMD modeldata(SOLDIER_MODEL);
        ModelMD* model_data_ptr = &modeldata;
        Md2Object model;

        int frame_count = 0;

        glm::dvec3 move = { 0,0,0 };
        glm::dvec3 turn = { 0,0,0 };
        glm::dvec3 model_move = { 0,0,0 };

        //q3Renderer render_;

        PhysicsManager physics;

        long double Previus_Time = 0;
        long double Delta_Time;

    public:
        void Initialize();
        static void display();
        void draw();
        static void drawBox();
        void inputEventUpdate();
        static void keyboard(unsigned char key, int x, int y);
        static void keyboardSpecial(int key, int x, int y);
        static void Update(int i);
        static void mouseButton(int key, int state, int x, int y);
        static void mouseMovePassive(int x, int y);
        static void animate(long double deltaT);
        void setupPhysics();
        void Run(int argc, char** argv);
    };
}