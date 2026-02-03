#ifdef _WIN64
	#include <windows.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <iostream>
#include <filesystem>

//settings
const unsigned int SCR_WIDTH{ 800 };
const unsigned int SCR_HEIGHT{ 600 };

//glfw: window size change callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//process all input
void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int argc, char* argv[])
{
	//save executable directory
	std::filesystem::path exePath { argv[0] };
	exePath.remove_filename();

	//glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	//glfw window creation
	GLFWwindow* window { glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL) };
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad: load all OpenGL function pointers
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//build and compile our shader program
	std::filesystem::path vertPath{ exePath / "res" / "shader.vert" }; 
	std::filesystem::path fragPath{ exePath / "res" / "shader.frag" };
	Shader shader{vertPath, fragPath};
	
	//set up vertex data and buffers and configure vertex attributes
	float vertices[] 
	{
		//positions		//colors
		 0.5f, -0.5f, 0.0f, 	1.0f, 0.0f, 0.0f, 	//bottom right
		-0.5f, -0.5f, 0.0f, 	0.0f, 1.0f, 0.0f, 	//bottom left
		 0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f 	//top
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//bind the Vertex Array Object first, then bind and set vertex buffers, then configure vertex attributes.
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glBindVertexArray(0);

	//render loop
	while(!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//render the triangle
		shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glfw:swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//de-allocate all resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}
