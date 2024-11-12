#include "Renderer.h"
#include <stdexcept>

void APIENTRY openglCallbackFunction(
    GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam)
{
    std::string sourceStr;
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             sourceStr = "API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceStr = "Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceStr = "Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     sourceStr = "Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           sourceStr = "Other"; break;
    }

    std::string typeStr;
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               typeStr = "Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated Behavior"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeStr = "Undefined Behavior"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         typeStr = "Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         typeStr = "Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              typeStr = "Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          typeStr = "Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           typeStr = "Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               typeStr = "Other"; break;
    }

    std::string severityStr;
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         severityStr = "High"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       severityStr = "Medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          severityStr = "Low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "Notification"; break;
    }

    std::cerr << "OpenGL Debug Message\n"
        << "Source: " << sourceStr << "\n"
        << "Type: " << typeStr << "\n"
        << "ID: " << id << "\n"
        << "Severity: " << severityStr << "\n"
        << "Message: " << message << std::endl;
}

Renderer::Renderer(GameWindow& window) : pWindow(window) {
    initialize();
    setupCallbacks();
}

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::swapBuffers() {
    glfwSwapBuffers(pWindow.getNativeWindow());
}

void Renderer::initialize() {
    pWindow.setWindowHints([]() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        });

    glfwMakeContextCurrent(pWindow.getNativeWindow());

    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    // Enable debug
    //glEnable(GL_DEBUG_OUTPUT);
    //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Makes sure errors are reported immediately
    //glDebugMessageCallback(openglCallbackFunction, nullptr);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, pWindow.getWidth(), pWindow.getHeight());

    // temp code:
    // 1. Create and compile shaders
    /*const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 vPos;

        uniform mat4 ModelMatrix;
        uniform mat4 ViewMatrix;
        uniform mat4 ProjectionMatrix;

        //out vec4 debugPos;

        void main() {
            gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vPos, 1.0);
            //debugPos = ModelMatrix * vec4(vPos, 1.0);
        }
    )";
    const char* fragmentShaderSource = R"(
        #version 330 core
        //in vec4 debugPos;
        out vec4 FragColor;

        void main() {
            FragColor = vec4(1.0f, 0.0, 0.0f, 1.0f);
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Verificar errores de compilación
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Error al compilar shader: " << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    success = 0;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Error al compilar shader: " << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Verificar errores de 
    int maxLength = 0;
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(shaderProgram, 1024, nullptr, infoLog);
        std::cerr << "Error al enlazar shaders: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader); // safe to delete shader. Why?
    glDeleteShader(fragmentShader);

    
    // 2. Create VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 3. Bind VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 4. Set up vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 5. Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    */
}

void Renderer::draw(unsigned int dataCount, GLenum drawingMode, bool indexed){
    if (indexed) {
        glDrawElements(drawingMode, dataCount, GL_UNSIGNED_INT, 0);
    }
    else {
        glDrawArrays(drawingMode, 0, dataCount);
    }
    
}

void Renderer::setupCallbacks() {
    pWindow.setResizeCallback([this](GLFWwindow* window, int width, int height) {
        this->framebufferSizeCallback(window, width, height);
        });
}

void Renderer::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    // Additional rendering adjustments can be made here
}

//float tmp = 0.0f;
//void Renderer::drawTriangle(const Vector3 v1, const Vector3 v2, const Vector3 v3, const Matrix4 modelMatrix)
//{
//    // 1. Define the vertex data
//    float vertices[] = { // 36 bytes
//        v1.x, v1.y, v1.z, // 4 x 3 = 12
//        v2.x, v2.y, v2.z, // 4 x 3 = 12
//        v3.x, v3.y, v3.z  // 4 x 3 = 12
//    };
//
//    // 2. Bind to Vertex Array Object
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)/*36 bytes*/, 
//        vertices /*pointer to the first element*/, GL_DYNAMIC_DRAW);
//
//    // 3. Call the shader program
//    glUseProgram(shaderProgram);
//
//    // Camera
//    // This part is usually responsibility of a camera, but since we started shaping the whole system
//    // let's do it here for now:
//
//    // temp view matrix
//    tmp += 0.01f;
//    Vector3 cameraPos(0.0f, 0.0f, 2.0);
//    Vector3 cameraTarget = cameraPos + Vector3(0.0f, 0.0f, -1.0f);
//    Vector3 upVector(0.0f, 1.0f, 0.0f);
//    Matrix4 viewMatrix = Matrix4::lookAt(cameraPos, cameraTarget, upVector);
//
//
//
//    // Set up perspective projection matrix
//    float aspectRatio = static_cast<float>(pWindow.getWidth()) / static_cast<float>(pWindow.getHeight());
//    Matrix4 projectionMatrix = Matrix4::perspective(45.0f * 3.14159f / 180.0f, aspectRatio, 0.1f, 10000.0f);
//
//
//    // setup matrices
//    GLint modelMatrixLoc = glGetUniformLocation(shaderProgram, "ModelMatrix");
//    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix.getData());
//
//    GLint viewMatrixLoc = glGetUniformLocation(shaderProgram, "ViewMatrix");
//    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, viewMatrix.getData());
//
//    GLint projectionMatrixLoc = glGetUniformLocation(shaderProgram, "ProjectionMatrix");
//    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, projectionMatrix.getData());
//
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//
//    glBindVertexArray(0);
//
//    glUseProgram(0);
//
//
//
//    
//}
