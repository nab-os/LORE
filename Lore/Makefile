VERSION=V1.0

ifeq ($(OS),Windows_NT)
	EXEC=Lore.lib
else
	EXEC=libLore.so
endif

SOURCES=Window.cpp Scene.cpp Camera.cpp Controller.cpp \
		Material.cpp \
		Mesh.cpp Light.cpp Object.cpp Node.cpp \
		Shader.cpp Texture.cpp CubeMap.cpp FrameBuffer.cpp \
		Lore.cpp Library.cpp \
		Importer.cpp \
		Cube.cpp

OUT_DIR=lib
OBJ_DIR=obj

OBJECTS=${SOURCES:%.cpp=$(OBJ_DIR)/%.o}
ifeq ($(OS),Windows_NT)

	SOURCES+= ThreadWindows.cpp
	
	IDIR=-I include \
		 -I C://Mingw/include \
		 -I C://Mingw/glew/include \
		 -I C://Mingw/glfw/include \
		 -I C://Mingw/SOIL/src \
		 -I C://Mingw/glm \
		 -I glTF2-loader/include \
		 -I stb
	
	LDIR=-L C://Mingw/lib \
		 -L C://MinGW/glew/lib/Release/Win32 \
		 -L C://Mingw/glfw/lib-mingw \
		 -L C://Mingw/SOIL/lib \
		 -L glTF2-loader/build
		 
	CFLAGS=-Wall -Wextra -O3 -g3 -std=c++11 -Wno-unused-variable -Wno-unused-parameter
	LFLAGS=-lstdc++ \
		   -lSOIL \
		   -lglfw3 -lopengl32 -lglu32 -lgdi32 -lglew32 \
		   -lgltf2-loader
else

	SOURCES+= ThreadPosix.cpp

	IDIR=-I include \
		 -I /usr/include \
		 -I /usr/include/SOIL \
		 -I /usr/include/libdrm \
		 -I glTF2-loader/include \
		 -I stb
	
	LDIR=-L /usr/lib \
		 -L /usr/local/lib \
		 -L /usr/lib64 \
		 -L /usr/lib/x86_64-linux-gnu \
		 -L glTF2-loader/build
		 
	CFLAGS=-Wall -Wextra -O3 -g3 -std=c++11 -Wno-unused-variable -Wno-unused-parameter -fPIC
	LFLAGS=-lstdc++ \
		   -lXi -lGLEW -lm -lGL -lm -lpthread -ldl -ldrm \
		   -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lXxf86vm \
		   -lglfw -lrt -lm -ldl -lXrandr -lXinerama -lXext -lXcursor -lXrender -lXfixes -lX11 \
		   -lpthread -lxcb -lXau -lXdmcp \
		   -lSOIL \
		   -lgltf2-loader \
		   -lpcre -lxml2 -lLLVM
endif

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
