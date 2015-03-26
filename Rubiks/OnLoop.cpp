//
//  OnLoop.cpp
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 8/4/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#include "World.h"

void World::OnLoop()    {
    
    /*static int x = 0;
    
    if (!faceIsRotating) {
        switch (x++ % 4) {
            case 0:
                rotateFace(FRONT);
                break;
            case 1:
                rotateFace(RIGHT);
                break;
            case 2:
                rotateFace(BACK);
                break;
            case 3:
                rotateFace(LEFT);
                break;
            default:
                break;
        }
    }*/
    
    if (rubiks.solvingCube && !faceIsRotating) {
        //We need to iterate through the movesStack
        if (!rubiks.movesStack.empty()) {
            rotateFace(rubiks.movesStack.back().face, rubiks.movesStack.back().direction);
            rubiks.movesStack.pop_back();
        }
        else    {
            rubiks.solvingCube = false;
        }
    }
    
    if (rubiksCubeIsShuffling && !faceIsRotating) {
        
        static int rotations = 0;
        
        static int lastFaceRotated = -1;
        
        RUBIKS_CUBE_FACE face = (RUBIKS_CUBE_FACE)(rand() % 6);
        
        while (face == lastFaceRotated) {
            face = (RUBIKS_CUBE_FACE)(rand() % 6);
        }
        
        lastFaceRotated = face;
        
        rotateFace(face, (RUBIKS_CUBE_MOVE_DIRECTION)((rand() % 3) + 1));
        
        if (rotations++ >= 40) {
            rubiksCubeIsShuffling = false;
            rotations = 0;
        }
    }
    
    if ((SDL_GetTicks() - startRotateTime > TURN_TIME) && faceIsRotating) {
        faceIsRotating = false;
        rubiks.moveRubiksCube(faceToRotate, directionToRotate, rubiks.cubeState);
    }
}

void World::rotateFace(RUBIKS_CUBE_FACE FACE, RUBIKS_CUBE_MOVE_DIRECTION direction) {
    
    if (!faceIsRotating) {
        faceIsRotating = true;
        
        startRotateTime = SDL_GetTicks();
        
        faceToRotate = FACE;
        
        directionToRotate = direction;
    }
}