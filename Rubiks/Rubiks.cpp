//
//  Rubiks.cpp
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 8/4/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#include "Rubiks.h"

Rubiks::Rubiks()    {
    
    cubeState = getSolvedCube();
    
    x_rot = 45;
    
    y_rot = -45;
    
    z_rot = 0;
    
    solvingCube = false;
}

bool Rubiks::cubieIsInFace(int cubie, RUBIKS_CUBE_FACE FACE, int * x, int * y, int * z)    {
    
    switch (FACE) {
        case TOP:
            *x = 0;
            *y = -1;
            *z = 0;
            return cubie >= 18;
            break;
        case FRONT:
            *x = 0;
            *y = 0;
            *z = -1;
            return cubie % 9 >= 6;
            break;
        case RIGHT:
            *x = -1;
            *y = 0;
            *z = 0;
            return cubie % 3 == 2;
            break;
        case BACK:
            *x = 0;
            *y = 0;
            *z = 1;
            return cubie % 9 < 3;
            break;
        case LEFT:
            *x = 1;
            *y = 0;
            *z = 0;
            return cubie % 3 == 0;
            break;
        case BOTTOM:
            *x = 0;
            *y = 1;
            *z = 0;
            return cubie < 9;
            break;
        default:
            return false;
            break;
    }
}

void Rubiks::moveRubiksCube(RUBIKS_CUBE_FACE FACE, RUBIKS_CUBE_MOVE_DIRECTION DIRECTION, uint32_t * cState)    {
    
    for (int i = 0; i < DIRECTION; i++) {
        /*
         *  Once for clockwise rotation
         *  twice for half turn
         *  thrice for counterclockwise rotation
         */
        
        //first, move the face clockwise
        
        cState[FACE] = moveFaceClockwise(cState[FACE]);
        
        //then, move the strip around the face clockwise
        
        switchRow(cState, FACE);
        
    }
}

void Rubiks::switchRow(uint32_t * cState, RUBIKS_CUBE_FACE FACE)  {
    
    switch (FACE) {
        case TOP:
            switchSquaresDifferentFace(FRONT, 0, LEFT, 2, cState);
            switchSquaresDifferentFace(FRONT, 1, LEFT, 5, cState);
            switchSquaresDifferentFace(FRONT, 2, LEFT, 8, cState);
            
            switchSquaresDifferentFace(RIGHT, 6, FRONT, 0, cState);
            switchSquaresDifferentFace(RIGHT, 3, FRONT, 1, cState);
            switchSquaresDifferentFace(RIGHT, 0, FRONT, 2, cState);

            switchSquaresDifferentFace(BACK, 8, RIGHT, 6, cState);
            switchSquaresDifferentFace(BACK, 7, RIGHT, 3, cState);
            switchSquaresDifferentFace(BACK, 6, RIGHT, 0, cState);
            break;
        case FRONT:
            switchSquaresDifferentFace(BOTTOM, 0, LEFT, 8, cState);
            switchSquaresDifferentFace(BOTTOM, 1, LEFT, 7, cState);
            switchSquaresDifferentFace(BOTTOM, 2, LEFT, 6, cState);
            
            switchSquaresDifferentFace(RIGHT, 8, BOTTOM, 0, cState);
            switchSquaresDifferentFace(RIGHT, 7, BOTTOM, 1, cState);
            switchSquaresDifferentFace(RIGHT, 6, BOTTOM, 2, cState);
            
            switchSquaresDifferentFace(TOP, 8, RIGHT, 8, cState);
            switchSquaresDifferentFace(TOP, 7, RIGHT, 7, cState);
            switchSquaresDifferentFace(TOP, 6, RIGHT, 6, cState);
            break;
        case RIGHT:
            switchSquaresDifferentFace(FRONT, 2, TOP, 2, cState);
            switchSquaresDifferentFace(FRONT, 5, TOP, 5, cState);
            switchSquaresDifferentFace(FRONT, 8, TOP, 8, cState);
            
            switchSquaresDifferentFace(BOTTOM, 2, FRONT, 2, cState);
            switchSquaresDifferentFace(BOTTOM, 5, FRONT, 5, cState);
            switchSquaresDifferentFace(BOTTOM, 8, FRONT, 8, cState);
            
            switchSquaresDifferentFace(BACK, 2, BOTTOM, 2, cState);
            switchSquaresDifferentFace(BACK, 5, BOTTOM, 5, cState);
            switchSquaresDifferentFace(BACK, 8, BOTTOM, 8, cState);
            break;
        case BACK:
            switchSquaresDifferentFace(TOP, 0, LEFT, 0, cState);
            switchSquaresDifferentFace(TOP, 1, LEFT, 1, cState);
            switchSquaresDifferentFace(TOP, 2, LEFT, 2, cState);
            
            switchSquaresDifferentFace(RIGHT, 0, TOP, 0, cState);
            switchSquaresDifferentFace(RIGHT, 1, TOP, 1, cState);
            switchSquaresDifferentFace(RIGHT, 2, TOP, 2, cState);
            
            switchSquaresDifferentFace(BOTTOM, 8, RIGHT, 0, cState);
            switchSquaresDifferentFace(BOTTOM, 7, RIGHT, 1, cState);
            switchSquaresDifferentFace(BOTTOM, 6, RIGHT, 2, cState);
            break;
        case LEFT:
            switchSquaresDifferentFace(FRONT, 0, BOTTOM, 0, cState);
            switchSquaresDifferentFace(FRONT, 3, BOTTOM, 3, cState);
            switchSquaresDifferentFace(FRONT, 6, BOTTOM, 6, cState);
            
            switchSquaresDifferentFace(TOP, 0, FRONT, 0, cState);
            switchSquaresDifferentFace(TOP, 3, FRONT, 3, cState);
            switchSquaresDifferentFace(TOP, 6, FRONT, 6, cState);
            
            switchSquaresDifferentFace(BACK, 0, TOP, 0, cState);
            switchSquaresDifferentFace(BACK, 3, TOP, 3, cState);
            switchSquaresDifferentFace(BACK, 6, TOP, 6, cState);
            break;
        case BOTTOM:
            switchSquaresDifferentFace(BACK, 0, LEFT, 6, cState);
            switchSquaresDifferentFace(BACK, 1, LEFT, 3, cState);
            switchSquaresDifferentFace(BACK, 2, LEFT, 0, cState);
            
            switchSquaresDifferentFace(RIGHT, 2, BACK, 0, cState);
            switchSquaresDifferentFace(RIGHT, 5, BACK, 1, cState);
            switchSquaresDifferentFace(RIGHT, 8, BACK, 2, cState);
            
            switchSquaresDifferentFace(FRONT, 8, RIGHT, 2, cState);
            switchSquaresDifferentFace(FRONT, 7, RIGHT, 5, cState);
            switchSquaresDifferentFace(FRONT, 6, RIGHT, 8, cState);
            break;
        default:
            break;
    }
}

void Rubiks::switchSquaresDifferentFace(RUBIKS_CUBE_FACE FACE_A, int squareAIndex, RUBIKS_CUBE_FACE FACE_B, int squareBIndex, uint32_t * cState)   {
    
    uint32_t mask = 0b111;
    
    uint32_t squareA = (cState[FACE_A] >> (squareAIndex * 3)) & mask;
    
    uint32_t squareB = (cState[FACE_B] >> (squareBIndex * 3)) & mask;
    
    assert(squareA < 6 && squareB < 6);
    
    cState[FACE_A] = cState[FACE_A] & ~(mask << (squareAIndex * 3));
    
    cState[FACE_B] = cState[FACE_B] & ~(mask << (squareBIndex * 3));
    
    cState[FACE_A] = cState[FACE_A] | (squareB << (squareAIndex * 3));
    
    cState[FACE_B] = cState[FACE_B] | (squareA << (squareBIndex * 3));

}

uint32_t Rubiks::moveFaceClockwise(uint32_t face)   {
    
    /*
     *  corners first
     *  then edges
     */
    
    face = switchSquares(face, 0, 6);
    
    face = switchSquares(face, 6, 8);
    
    face = switchSquares(face, 2, 8);
    
    //edges
    
    face = switchSquares(face, 3, 7);
    
    face = switchSquares(face, 7, 5);
    
    face = switchSquares(face, 5, 1);
    
    return face;
}

uint32_t Rubiks::switchSquares(uint32_t face, int squareAIndex, int squareBIndex)    {
    
    uint32_t mask = 0b111;
    
    uint32_t squareA = (face >> (squareAIndex * 3)) & mask;
    
    uint32_t squareB = (face >> (squareBIndex * 3)) & mask;
    
    assert(squareA < 6  && squareB < 6);
    
    face = face & (~(mask << (squareAIndex * 3))) & (~(mask << (squareBIndex * 3)));
    
    face = face | (squareA << (squareBIndex * 3)) | (squareB << (squareAIndex * 3));
    
    return face;
}

uint32_t * Rubiks::getRubiksCubeColorArray() {
    
    static uint32_t tmpColorArray[54];
    
    int face, square;
    
    uint32_t mask = 0b111;
    
    for (face = 0; face < 6; face++) {
        for (square = 0; square < 9; square++) {
            tmpColorArray[square + face * 9] = (cubeState[face] >> (3 * square)) & mask;
        }
    }
    
    return tmpColorArray;
    
}

uint32_t * Rubiks::getSolvedCube()  {
    
    /*static uint32_t tmpCubeState[6];
    
    tmpCubeState[TOP] = 0;    //all white face
    
    for (int i = 8; i >=0; i--) {
        tmpCubeState[FRONT] += RED << (i * 3);
    }
    for (int i = 8; i >=0; i--) {
        tmpCubeState[RIGHT] += BLUE << (i * 3);
    }
    for (int i = 8; i >=0; i--) {
        tmpCubeState[BACK] += ORANGE << (i * 3);
    }
    for (int i = 8; i >=0; i--) {
        tmpCubeState[LEFT] += GREEN << (i * 3);
    }
    for (int i = 8; i >=0; i--) {
        tmpCubeState[BOTTOM] += YELLOW << (i * 3);
    }
    
    
    return tmpCubeState;*/
    return makeCubeState(finalGoal);
}
