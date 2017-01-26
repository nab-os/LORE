EXEC=test

SOURCES=main.cpp

OUT_DIR=bin
OBJ_DIR=obj

OBJECTS=${SOURCES:%.cpp=$(OBJ_DIR)/%.o}

IDIR=-I ../Lore/include \
	 -I /usr/include/ \
	 -I /usr/include/SOIL \
	 -I /usr/include/libdrm \
	 -I /usr/include/opencollada \
	 -I /usr/include/opencollada/COLLADAFramework \
	 -I /usr/include/opencollada/COLLADASaxFramework \
	 -I /usr/include/opencollada/COLLADABaseUtils

LDIR=-L /usr/lib \
	 -L /usr/local/lib \
	 -L /usr/lib64 \
	 -L /usr/lib/x86_64-linux-gnu/ \
	 -L /usr/lib/opencollada \
	 -L /usr/lib/opencollada/COLLADAFramework \
	 -L /usr/lib/opencollada/COLLADASaxFrameworkLoader \
	 -L /usr/lib/opencollada/COLLADABaseUtils \
	 -L ../Lore/lib

CFLAGS=-Wall -Wextra -O3 -g3 -std=c++11 -Wno-unused-variable -Wno-unused-parameter
LFLAGS=-lstdc++ \
		-lm -lXrandr -ldl -lXi -lX11 -ldl -lXxf86vm -lXinerama -lXcursor -lrt -pthread \
	   	-lGL -lGLU -lGLEW -lglfw3 -lSOIL \
		-lOpenCOLLADAFramework -lOpenCOLLADASaxFrameworkLoader -lOpenCOLLADABaseUtils \
		-lLore

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
	@rm -rf "$(OBJ_DIR)"
