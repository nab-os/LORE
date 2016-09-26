EXEC=test

SOURCES=main.cpp

EXEC_DIR=bin
OBJ_DIR=obj

OBJECTS=${SOURCES:%.cpp=$(OBJ_DIR)/%.o}

IDIR=-I /usr/include/ -I /usr/local/include/bullet -I ../OpenGL

LDIR=-L /usr/lib -L /usr/local/lib -L /usr/lib64 -L /usr/lib/x86_64-linux-gnu -L ../OpenGL/bin

CFLAGS=-Wall -Wextra -O3 -g3 -std=c++11
LFLAGS=-lstdc++ ../OpenGL/bin/OpenGL.lib \
	   -lglfw3 -lGLEW \
	   -lGL -lGLU -lm -lXrandr -ldl -lXi -lX11 -ldl -lXxf86vm -lXinerama -lXcursor -lrt -pthread \
	   -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath

CC=g++

all: init $(EXEC_DIR)/$(EXEC)

$(EXEC_DIR)/$(EXEC): $(OBJECTS)
	@echo "\n=======LINKING=======\n"
	$(CC) -o $@ $^ $(LDIR) $(LFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@echo "\n=======COMPILING $@======="
	$(CC) $(IDIR) $(CFLAGS) -c $< -o $@

init:
	@mkdir -p "$(EXEC_DIR)"
	@mkdir -p "$(OBJ_DIR)"

clean:
	@rm -rf "$(OBJ_DIR)"
