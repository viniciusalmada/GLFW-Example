#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void InitScene();

void Init();

void Display();

void DrawScene();

void CreateShaderProgram();

void CompileShader(GLuint id);

void LinkProgram(GLuint id);

void Error(const char *);

GLuint program;
GLuint vao;
GLFWwindow *window;

static const char *vsource =
		"#version 430 core\n"
		"layout(location = 0) in vec4 inVertex;\n"
		"layout(location = 1) in vec4 inColor;\n"
		"out vec4 color;\n"
		"void main(void)\n"
		"{\n"
		"color = inColor;\n"
		"gl_Position = inVertex;\n"
		"}";

static const char *fsource =
		"#version 430 core\n"
		"in vec4 color;\n"
		"out vec4 FragColor;\n"
		"void main(void)\n"
		"{\n"
		"FragColor = color;\n"
		"}";

int main() {
	printf("%s", "main()\n");

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, [](GLFWwindow*, int w, int h){
		printf("%s", "Reshape()\n");
		glViewport(0, 0, w, h);
		Display();
	});

	Init();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

static void LinkProgram(GLuint id) {
	printf("%s", "LinkProgram()\n");
	GLint status;
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if (!status) {
		GLint len;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);
		char *message = new char();
		glGetProgramInfoLog(id, len, nullptr, message);
		Error(message);
		delete message;
	}
}

static void CompileShader(GLuint id) {
	printf("%s", "CompileShader()\n");
	GLint status;
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (!status) {
		GLint len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char *message = new char();
		glGetShaderInfoLog(id, len, nullptr, message);
		Error(message);
		delete message;
	}
}

void Error(const char *message) {
	fprintf(stderr, "%s", message);
}

void Init() {
	printf("%s", "Init()\n");
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	printf("OpenGL version = %s\n", glGetString(GL_VERSION));
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	CreateShaderProgram();
	Display();
}

void CreateShaderProgram() {
	printf("%s", "CreateShaderProgram()\n");
	GLuint v_id = glCreateShader(GL_VERTEX_SHADER);
	if (v_id == 0) Error("Could not create vertex shader object");
	glShaderSource(v_id, 1, &vsource, nullptr);
	CompileShader(v_id);

	GLuint f_id = glCreateShader(GL_FRAGMENT_SHADER);
	if (v_id == 0) Error("Could not create fragment shader object");
	glShaderSource(f_id, 1, &fsource, nullptr);
	CompileShader(f_id);

	program = glCreateProgram();
	if (program == 0) Error("Could not create program object");
	glAttachShader(program, v_id);
	glAttachShader(program, f_id);
	LinkProgram(program);
}

void DrawScene() {
	printf("%s", "DrawScene()\n");
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Display() {
	printf("%s", "Display()\n");
	static bool first = true;
	if (first) {
		InitScene();
		first = false;
	}

	glClear((GLuint) GL_COLOR_BUFFER_BIT | (GLuint) GL_DEPTH_BUFFER_BIT);

	DrawScene();

	glfwSwapBuffers(window);
}

void InitScene() {
	printf("%s", "InitScene()\n");
	float coord[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
	};

	float color[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint id[2];
	glGenBuffers(2, id);

	glBindBuffer(GL_ARRAY_BUFFER, id[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coord), (void *) coord, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, id[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), (void *) color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(1);
}
