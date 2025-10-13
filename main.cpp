#include <cstdio>
#include <cstdint>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

struct Buffer
{
    size_t width, height;
    uint32_t* data;
};

int main()
{
    glfwSetErrorCallback(error_callback);
    if(!glfwInit())
    {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Space Invaders", NULL, NULL);
    if(!window)
    {
    	glfwTerminate();
    	return -1;
    }
    glfwMakeContextCurrent(window);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        fprintf(stderr, "Error initializing GLEW.\n");
        glfwTerminate();
        return -1;
    }
    int glVersion[2] = {-1, 1};
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

    printf("Using OpenGL: %d.%d\n", glVersion[0], glVersion[1]);

    uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b){
        return (r << 24) | (g << 16) | (b << 8) | 255;
    }

    void buffer_clear(Buffer* buffer, uint32_t color){
        for(size_t i = 0; i < buffer->width * buffer->height; ++i){
            buffer->data[i] = color;
        }
    }

    glClearColor(1.0, 0.0, 0.0, 1.0);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

}
