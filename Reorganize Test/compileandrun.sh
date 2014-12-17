#!/bin/bash
g++ imagefile.cpp garden.cpp drawing.cpp main.cpp lights.cpp skybox.cpp textures.cpp material.cpp door.cpp house.cpp exceptioninfo.cpp -lGL -lfreeimage -lglut -lGLU
./a.out
