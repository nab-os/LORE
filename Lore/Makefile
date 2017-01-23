EXEC=libLore.a

SOURCES=OpenGL_Window.cpp Scene.cpp Camera.cpp Controller.cpp \
		Material.cpp \
		Model.cpp ModelRender.cpp Object.cpp \
		Shader.cpp Texture.cpp CubeMap.cpp FrameBuffer.cpp \
		Lore.cpp Library.cpp Loader.cpp \
		Importer.cpp GeometryImporter.cpp ImportErrorHandler.cpp \
#		ModelBullet.cpp

OUT_DIR=lib
OBJ_DIR=obj

OBJECTS=${SOURCES:%.cpp=$(OBJ_DIR)/%.o}

IDIR=-I include \
	 -I /usr/include \
	 -I /usr/include/SOIL \
	 -I /usr/include/opencollada \
	 -I /usr/include/opencollada/COLLADAFramework \
	 -I /usr/include/opencollada/COLLADASaxFramework \
	 -I /usr/include/opencollada/COLLADABaseUtils \
#	 -I /usr/local/include/bullet

LDIR=-L src \
	 -L /usr/lib \
	 -L /usr/local/lib \
	 -L /usr/lib64 \
	 -L /usr/lib/x86_64-linux-gnu/ \
	 -L /usr/lib/opencollada \
	 -L /usr/lib/opencollada/COLLADAFramework \
	 -L /usr/lib/opencollada/COLLADASaxFrameworkLoader \
	 -L /usr/lib/opencollada/COLLADABaseUtils


CFLAGS=-Wall -Wextra -O3 -g3 -std=c++11 -Wno-unused-variable -Wno-unused-parameter
LFLAGS=-lstdc++ \
		-lm -lXrandr -ldl -lXi -lX11 -ldl -lXxf86vm -lXinerama -lXcursor -lrt -pthread \
	   	-lGL -lGLU -lGLEW -lglfw -lSOIL \
		-lOpenCOLLADAFramework -lOpenCOLLADASaxFrameworkLoader -lOpenCOLLADABaseUtils \
#	   	-lBulletDynamics -lBulletCollision -lLinearMath

CC=g++

all: init $(OUT_DIR)/$(EXEC)

$(OUT_DIR)/$(EXEC): $(OBJECTS)
	@echo "\n=======LINKING=======\n"
	ar rcs $@ $^

$(OBJ_DIR)/%.o: src/%.cpp
	@echo "\n=======COMPILING $@======="
	$(CC) $(IDIR) $(CFLAGS) -c $< -o $@

init:
	@mkdir -p "$(OUT_DIR)"
	@mkdir -p "$(OBJ_DIR)"

clean:
	@rm -rf "$(OBJ_DIR)"
