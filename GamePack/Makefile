EXEC=libGamePack.a

SOURCES=OpenGL_Window.cpp Scene.cpp Camera.cpp Controller.cpp \
		Material.cpp \
		ModelBullet.cpp Model.cpp ModelRender.cpp Object.cpp \
		Shader.cpp Texture.cpp CubeMap.cpp FrameBuffer.cpp \
		GamePack.cpp Library.cpp

EXEC_DIR=bin
OBJ_DIR=obj

OBJECTS=${SOURCES:%.cpp=$(OBJ_DIR)/%.o}

IDIR=-I /usr/include/ -I /usr/include/opencollada -I /usr/include/opencollada/COLLADABaseUtils -I /usr/local/include/bullet

LDIR=-L /usr/lib -L/usr/local/lib -L /usr/lib64 -L /usr/lib/x86_64-linux-gnu/ -L /usr/lib/opencollada

CFLAGS=-Wall -Wextra -O3 -g3 -std=c++11 -Wno-unused-variable -Wno-unused-parameter
LFLAGS=-lstdc++ \
		-lm -lXrandr -ldl -lXi -lX11 -ldl -lXxf86vm -lXinerama -lXcursor -lrt -pthread \
	   	-lGL -lGLU -lGLEW -lglfw3 -lSOIL -lOpenCOLLADAFramework \
	   	-lBulletDynamics -lBulletCollision -lLinearMath

CC=g++

all: init $(EXEC_DIR)/$(EXEC)

$(EXEC_DIR)/$(EXEC): $(OBJECTS)
	@echo "\n=======LINKING=======\n"
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.cpp
	@echo "\n=======COMPILING $@======="
	$(CC) $(IDIR) $(CFLAGS) -c $< -o $@

init:
	@mkdir -p "$(EXEC_DIR)"
	@mkdir -p "$(OBJ_DIR)"

clean:
	@rm -rf "$(OBJ_DIR)"
