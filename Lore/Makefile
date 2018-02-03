EXEC=libLore.so

SOURCES=Window.cpp Scene.cpp Camera.cpp Controller.cpp \
		Material.cpp \
		Mesh.cpp Object.cpp Node.cpp \
		Shader.cpp Texture.cpp CubeMap.cpp FrameBuffer.cpp \
		Lore.cpp Library.cpp \
		Importer.cpp \
		Cube.cpp

OUT_DIR=lib
OBJ_DIR=obj

OBJECTS=${SOURCES:%.cpp=$(OBJ_DIR)/%.o}

IDIR=-I include \
	 -I /usr/include \
	 -I /usr/include/SOIL \
	 -I /usr/include/libdrm \
	 -I glTF2-loader/include

LDIR=-L /usr/lib \
	 -L /usr/local/lib \
	 -L /usr/lib64 \
	 -L /usr/lib/x86_64-linux-gnu \
	 -L glTF2-loader/build


CFLAGS=-Wall -Wextra -O3 -g3 -std=c++11 -Wno-unused-variable -Wno-unused-parameter -fPIC
LFLAGS=-lstdc++ \
	   -lXi -lGLEW -lGLU -lm -lGL -lm -lpthread -ldl -ldrm \
	   -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lXxf86vm \
	   -lglfw -lrt -lm -ldl -lXrandr -lXinerama -lXext -lXcursor -lXrender -lXfixes -lX11 \
	   -lpthread -lxcb -lXau -lXdmcp \
	   -lSOIL \
	   -lgltf2-loader \
	   -lpcre -lxml2 -lLLVM

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
