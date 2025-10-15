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

    uint32_t clear_color = rgb_to_uint32(0, 128, 0);
    Buffer buffer;
    buffer.width  = buffer_width;
    buffer.height = buffer_height;
    buffer.data   = new uint32_t[buffer.width * buffer.height];
    buffer_clear(&buffer, clear_color); 

    const char* vertex_shader =
     "\n"
     "#version 330\n"
     "\n"
     "noperspective out vec2 TexCoord;\n"
     "\n"
     "void main(void){\n"
     "\n"
     "    TexCoord.x = (gl_VertexID == 2)? 2.0: 0.0;\n"
     "    TexCoord.y = (gl_VertexID == 1)? 2.0: 0.0;\n"
     "    \n"
     "    gl_Position = vec4(2.0 * TexCoord - 1.0, 0.0, 1.0);\n"
     "}\n";

    const char* fragment_shader =
     "\n"
     "#version 330\n"
     "\n"
     "uniform sampler2D buffer;\n"
     "noperspective in vec2 TexCoord;\n"
     "\n"
     "out vec3 outColor;\n"
     "\n"
     "void main(void){\n"
     "    outColor = texture(buffer, TexCoord).rgb;\n"
     "}\n";

    GLuint fullscreen_triangle_vao;
    glGenVertexArrays(1, &fullscreen_triangle_vao);
    glBindVertexArray(fullscreen_triangle_vao);

    glClearColor(1.0, 0.0, 0.0, 1.0);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();


