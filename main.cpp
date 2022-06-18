#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Objects/VAO.h"
#include "Objects/BO.h"
#include "Objects/Texture.h";
#include "Camera.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

// The MAIN function, from here we start the application and run the game loop
int main()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error.
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    // Successfully loaded OpenGL
    std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    auto shader = Shader("shaders/default.vert", "shaders/default.frag");
    auto lightShader = Shader("shaders/light.vert", "shaders/light.frag");

    // buffer
    auto vao = VAO();
    auto vbo = BO(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    auto ebo = BO(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    vao.link(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    vao.link(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.link(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    auto vaoLight = VAO();
    auto vboLight = BO(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);
    auto eboLight = BO(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);
    vaoLight.link(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    vaoLight.unbind();
    vboLight.unbind();
    eboLight.unbind();

    // light 
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(1.f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    // texture
    Texture tex("images/luffy.png", GL_TEXTURE_2D, GL_TEXTURE0, 0, GL_RGBA, 0, GL_RGBA, GL_UNSIGNED_BYTE);

    // uniform
    
    GLuint u_light = glGetUniformLocation(lightShader.m_id, "model");
    GLuint u_lightCamera = glGetUniformLocation(lightShader.m_id, "camera");
    GLuint u_lightColor = glGetUniformLocation(lightShader.m_id, "lightColor");

    GLuint u_scale = glGetUniformLocation(shader.m_id, "scale");
    GLuint u_model = glGetUniformLocation(shader.m_id, "model");
    GLuint u_camera = glGetUniformLocation(shader.m_id, "camera");

    lightShader.use();
    glUniformMatrix4fv(u_light, 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(u_lightColor, lightColor.r, lightColor.g, lightColor.b, lightColor.a);

    shader.use();
    glUniform1f(u_scale, 1.);
    tex.uniform("tex0", 0);

    // camera
    Camera camera(WIDTH, HEIGHT);

    // depth
    glEnable(GL_DEPTH_TEST);

    float rotation = 0.;
    auto start = glfwGetTime();
    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // matrix
        auto curr = glfwGetTime();
        rotation = glm::mod(100 * (curr - start), 360.);
        auto model = glm::mat4(1.);
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0., 1., 0.));

        camera.control(window);
        auto cam_mat = camera.getMatrix();
        
        // Draw
        shader.use();
        vao.bind();
        tex.bind();
        glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(u_camera, 1, GL_FALSE, glm::value_ptr(cam_mat));
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, (void*)0);

        lightShader.use();
        vaoLight.bind();
        glUniformMatrix4fv(u_lightCamera, 1, GL_FALSE, glm::value_ptr(cam_mat));
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(lightIndices[0]), GL_UNSIGNED_INT, (void*)0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Delete
    vao.unlink(0);
    vao.unlink(1);
    vao.unlink(2);
    vaoLight.unlink(0);

    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}