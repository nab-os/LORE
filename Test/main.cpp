#include <iostream>
#include <string>

#include <GamePack.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
int main(int argc, char** argv)
{

	cout << "===== INIT =====" << endl;

	OpenGL_Window* window = GamePack::init(); // Initializes OpenGL context and creates a Window
	if(!window)
	{
		cout << "Error during OpenGL context initialization." << endl;
		GamePack::unload();
		return -1;
	}

	string file = "/home/guy/Bureau/simple.dae";

	if(argc >= 2)
	{

		file = argv[1];

	}

  	Assimp::Importer importer;
  	const aiScene* scene = importer.ReadFile( file, 
	    aiProcess_CalcTangentSpace       | 
	    aiProcess_Triangulate            |
	    aiProcess_JoinIdenticalVertices  |
	    aiProcess_SortByPType);

  	if(!scene)
  	{

  		cout << "File does not exist or is corrupted : " << file << endl;

  	}else
  	{

  		cout << "Let's load !" << endl;

  	}

    //----------

	Controller* controller = new Controller(); // a Controller to bind the ESCAPE key to the Window

	controller->bind(GLFW_KEY_ESCAPE, [&window](double x, double y) {

		window->close();

    });

	//===================================
	cout << "===== RENDER =====" << endl;

	while (!window->shouldClose())
	{

		int start = window->startFrame(); // Begin the frame render process

		controller->check(window); // Checks all bindings for the Window and execute de fonction if it matches

		window->render(); // 

		window->endFrame(start); // End the frame render process and display the image on the window

	}

	//================================
	cout << "===== END =====" << endl;

	GamePack::unload(); // Unload all dictionnaries, and unload OpenGL context

    return 0;

}