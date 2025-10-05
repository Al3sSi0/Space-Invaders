#include <cstdio>
#include <GLFW/glfw3.h>
#include <GL/glew.h>

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main(){
	glfwSetErrorCallback(error_callback);
}
