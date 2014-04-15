#include "Renderer.h"

Renderer::Renderer()
{
	Projection = glm::perspective(45.0f, 640.0f/480.0f, 0.0f, 100.0f);
	View = glm::mat4(1.0f);
	Model = glm::mat4(1.0f);
}
Renderer::~Renderer(){}

void Renderer::Initialize()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShaderFromTextFile(GL_VERTEX_SHADER, "Shaders\\VS.glsl"));
	shaderList.push_back(CreateShaderFromTextFile(GL_FRAGMENT_SHADER, "Shaders\\FS.glsl"));
	shaderProgram = CreateProgram(shaderList);
	unfMat = glGetUniformLocation(shaderProgram, "uMat");

	const float quadVertices[] = 
	{
		//  X     Y     Z           U     V
		+0.5f, +0.5f, 0.0f,      1.0f, 1.0f, //v0   
		-0.5f, +0.5f, 0.0f,		 0.0f, 1.0f, //v1   
		+0.5f, -0.5f, 0.0f,		 1.0f, 0.0f, //v2   
		-0.5f, -0.5f, 0.0f,		 0.0f, 0.0f  //v3
	};

	const unsigned short quadIndices[] =	{	0, 2, 1,	1, 3, 2	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (char*)0 + 0 * sizeof(float));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (char*)0 + 3 * sizeof(float));

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);
}

void Renderer::Draw()
{
	const float lightskycolor[] = { 0.53f, 0.81f, 0.98f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, lightskycolor);

	View = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 MVP = Projection * View * Model;
	glUniformMatrix4fv(unfMat, 1, GL_FALSE, glm::value_ptr(MVP));

	glBindVertexArray(VAO);
	glUseProgram(shaderProgram);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glFlush();
}

GLuint Renderer::CreateShaderFromTextFile(GLenum shadertype, char const* filename)
{
	std::string line, ShaderSource;
	std::ifstream ShaderTextFile(filename);

	if (ShaderTextFile.is_open())
	{
		while (ShaderTextFile.good())
		{
			std::getline(ShaderTextFile, line);
			ShaderSource += line + "\n";
		}
	}
	else
	{
		ShaderTextFile.close();
		std::cout << "unable to open shader file";
	}

	ShaderTextFile.close();

	std::cout << ShaderSource << ShaderSource.capacity() << std::endl;

	const char *strFileData = ShaderSource.c_str();

	GLuint shader = glCreateShader(shadertype);

	glShaderSource(shader, 1, &strFileData, nullptr);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (shadertype)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}
	else
		std::cout << "Shader compiled" << std::endl;

	return shader;
}

GLuint Renderer::CreateProgram(std::vector<unsigned> const& shaderList)
{
	GLuint program = glCreateProgram();

	for (int i = 0; i < shaderList.size(); i++)
		glAttachShader(program, shaderList[i]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
	else
		std::cout << "Program linked" << std::endl;
	return program;
}
