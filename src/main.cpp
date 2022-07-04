#include"Renderer/ShaderProgram.h"
#include"Resources/ResourceManager.h"
#include"Renderer/Texture2D.h"
#include<glm/vec2.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
GLfloat point[] = {
     0.0f, 50.f,0.0f,
     50.f,-50.f,0.0f,
     -50.f,-50.f,0.0f
};
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat texCoord[] = {
    0.5f, 1.0f, 
    1.0f, 0.0f,
    0.0f, 0.0f  
};





glm::ivec2 g_windowSize(640, 460);


void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    g_windowSize.x = width;
    g_windowSize.y = height;
    glViewport(0, 0, g_windowSize.x, g_windowSize.y);//���� �������� ��� �� ����� ��������
//0,0 ��� ����
}

void glfwCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}



int main(int argc,char** argv)
{
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//core profile ��� ������������ ������� opengl ���� �� �������� ��� ������� �� �������� ������������� ��������� ������ opengl
    /* Initialize the library */
    if (!glfwInit()) {//�������� ������� ������������� glwf
        std::cout << "glfwInit failed" << std::endl;
        return -1;
    }
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//�������� ������ openGL
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);//���� � ��� ����� ������ ������ 4 � 6, �� �� ������ �� ������ ������� ����

     /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);//�������� ����
    if (!pWindow)//���� ���� �� ���� ������� �������, �� ������� �� ���������
    {
        //������� ��������� �� ������
        std::cout << "glfwCreateWindow is falied\n";
        glfwTerminate();//����������� ��� �������
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwCallback);

    /* Make the window's context current */
   //�� ������ �������� ������ ��� �������� ����, ���� � ��� ����� ���� ���������
   //� ��� ������� ���� � ��� ����� ���� ���� ���� ��  ��������
   //������� �� ������ ������� ������� ������ ����
    glfwMakeContextCurrent(pWindow);

    //�������������� ���������� ����
    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD!" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;//���������� ����� ������������ ����� �����
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;//���������� ����� ������������� ������ opengl



    glClearColor(1, 1, 0, 1);

    
    {
        ResourceManager resourceManager(argv[0]);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram) {
            cerr << "Can't create shader program: " << "DefaultShader " << endl;
            return -1;
        }

        auto tex = resourceManager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");
       
        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint texCoord_vbo = 0;
        glGenBuffers(1, &texCoord_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);




        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);
       
        glm::mat4 modelMatrix_1 = glm::mat4(1.f);
        modelMatrix_1 = glm::translate(modelMatrix_1,glm::vec3(100.f,50.f,0.f));


        glm::mat4 modelMatrix_2 = glm::mat4(1.f);
        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));
        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y),-100.f,100.f);

        pDefaultShaderProgram->setmMatrix4("projectionMat", projectionMatrix);



        /* Loop until the user closes the window */
    //���� ���������, ����� ������� ���� �� ����� �������
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);//����� ���������� ������ �����
           
            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            tex->bind();

            pDefaultShaderProgram->setmMatrix4("modelMat", modelMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);


            pDefaultShaderProgram->setmMatrix4("modelMat", modelMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();//���� �������� glfw ������������ ��� ������� �� ���,
            //����� ��� ������� ������� , ��������� ������� �������, ��������� �������� ����,
            //�������� ���� , �� � ��������������� ������� ��������������
        }
    }

    glfwTerminate();
    return 0;
}