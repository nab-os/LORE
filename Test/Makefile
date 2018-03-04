EXEC=test

SOURCES=main.cpp

OUT_DIR=bin
OBJ_DIR=obj

OBJECTS=${SOURCES:%.cpp=$(OBJ_DIR)/%.o}

ifeq ($(OS),Windows_NT)
	
	IDIR=-isystem ../Lore/include \
		 -I C://Mingw/include \
		 -I C://Mingw/glew/include \
		 -I C://Mingw/glfw/include \
		 -I C://Mingw/SOIL/src \
		 -I C://Mingw/glm \
		 -I ../Lore/glTF2-loader/include
	
	LDIR=-L C://Mingw/lib \
		 -L C://MinGW/glew/lib/Release/Win32 \
		 -L C://Mingw/glfw/lib-mingw \
		 -L C://Mingw/SOIL/lib \
		 -L ../Lore/lib \
		 -L ../Lore/glTF2-loader/build
		 
	CFLAGS=-Wall -Wextra -O3 -g3 -std=c++11 -Wno-unused-variable -Wno-unused-parameter
	LFLAGS=-lstdc++ \
		   -lLore \
		   -lSOIL \
		   -lglfw3 -lopengl32 -lglu32 -lgdi32 -lglew32 \
		   -lgltf2-loader
else

	IDIR=-isystem ../Lore/include \
		 -I /usr/include \
		 -I /usr/include/SOIL \
		 -I /usr/include/libdrm \
		 -I ../Lore/glTF2-loader/include
	
	LDIR=-L /usr/lib \
		 -L /usr/local/lib \
		 -L /usr/lib64 \
		 -L /usr/lib/x86_64-linux-gnu \
		 -L ../Lore/lib \
		 -L ../Lore/glTF2-loader/build
		 
	CFLAGS=-Wall -Wextra -O3 -g3 -std=c++11 -Wno-unused-variable -Wno-unused-parameter
	LFLAGS=-lstdc++ \
		   -lLore \
		   -lXi -lGLEW -lm -lGL -lm -lpthread -ldl -ldrm \
		   -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lXxf86vm \
		   -lglfw -lrt -lm -ldl -lXrandr -lXinerama -lXext -lXcursor -lXrender -lXfixes -lX11 \
		   -lpthread -lxcb -lXau -lXdmcp \
		   -lSOIL \
		   -lgltf2-loader \
		   -lpcre -lxml2 -lLLVM
endif

CC=g++

all: clean init $(OUT_DIR)/$(EXEC)

$(OUT_DIR)/$(EXEC): $(OBJECTS)
	@echo "\n=======LINKING=======\n"
	$(CC) -o $@ $^ $(LDIR) $(LFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@echo "\n=======COMPILING $@======="
	$(CC) -o $@ -c $< $(IDIR) $(CFLAGS)

init:
	@mkdir -p "$(OUT_DIR)"
	@mkdir -p "$(OBJ_DIR)"

clean:
	@rm -rf "$(OUT_DIR)"
	@rm -rf "$(OBJ_DIR)"
