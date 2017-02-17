EXEC=libLore.so

SOURCES=Window.cpp Scene.cpp Camera.cpp Controller.cpp \
		Material.cpp \
		Model.cpp ModelRender.cpp Object.cpp \
		Shader.cpp Texture.cpp CubeMap.cpp FrameBuffer.cpp \
		Lore.cpp Library.cpp Loader.cpp \
		Importer.cpp GeometryImporter.cpp ImportErrorHandler.cpp

OUT_DIR=lib
OBJ_DIR=obj

OBJECTS=${SOURCES:%.cpp=$(OBJ_DIR)/%.o}

IDIR=-I include \
	 -I /usr/include \
	 -I /usr/include/SOIL \
	 -I /usr/include/libdrm \
	 -I /usr/include/opencollada \
	 -I /usr/include/opencollada/COLLADAFramework \
	 -I /usr/include/opencollada/COLLADASaxFramework \
	 -I /usr/include/opencollada/COLLADABaseUtils

LDIR=-L /usr/lib \
	 -L /usr/local/lib \
	 -L /usr/lib64 \
	 -L /usr/lib/x86_64-linux-gnu \
	 -L /usr/lib/opencollada \
	 -L /usr/lib/opencollada/COLLADAFramework \
	 -L /usr/lib/opencollada/COLLADASaxFrameworkLoader \
	 -L /usr/lib/opencollada/COLLADABaseUtils


CFLAGS=-Wall -Wextra -O3 -g3 -std=c++11 -Wno-unused-variable -Wno-unused-parameter -fPIC
LFLAGS=-lstdc++ \
	   -lXi -lGLEW -lGLU -lm -lGL -lm -lpthread -ldl -ldrm \
	   -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lXxf86vm \
	   -lglfw -lrt -lm -ldl -lXrandr -lXinerama -lXext -lXcursor -lXrender -lXfixes -lX11 \
	   -lpthread -lxcb -lXau -lXdmcp \
	   -lSOIL \
	   -lOpenCOLLADAFramework -lOpenCOLLADABaseUtils -lOpenCOLLADAStreamWriter -lOpenCOLLADASaxFrameworkLoader \
	   -lGeneratedSaxParser -lMathMLSolver -lOpenCOLLADABaseUtils -lpcre -lxml2 -lLLVM-3.8

CC=g++

all: init $(OUT_DIR)/$(EXEC)

$(OUT_DIR)/$(EXEC): $(OBJECTS)
	@echo "\n=======LINKING=======\n"
	#ar rcs $@ $^
	$(CC) -o $@ $^ $(LDIR) $(LFLAGS) -shared

$(OBJ_DIR)/%.o: src/%.cpp
	@echo "\n=======COMPILING $@======="
	$(CC) -o $@ -c $< $(IDIR) $(CFLAGS)

init:
	@mkdir -p "$(OUT_DIR)"
	@mkdir -p "$(OBJ_DIR)"

clean:
	@rm -rf "$(OUT_DIR)"
	@rm -rf "$(OBJ_DIR)"
