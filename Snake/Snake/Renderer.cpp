#include "Renderer.h"

Renderer::Renderer()
{
	Projection = glm::mat4(1.0f); //glm::perspective(45.0f, 800.0f / 600.0f, 0.0f, 100.0f);
	View = glm::mat4(1.0f);
	Model = glm::mat4(1.0f);

	textImage.x = 0;
	textImage.y = 0;
	textImage.n = 0;
	textImage.data = nullptr;
}

Renderer::~Renderer(){}

void Renderer::Initialize(GUI* g)
{
	gui = g;

	LoadImage(&textImage, "Textures\\testta.png");

	glGenTextures(1, &textTexture);
	glBindTexture(GL_TEXTURE_2D, textTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textImage.x, textImage.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textImage.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	std::vector<GLuint> shaderList;
	std::vector<GLuint> selectionShaderList;

	shaderList.push_back(CreateShaderFromTextFile(GL_VERTEX_SHADER, "Shaders\\VS.glsl"));
	shaderList.push_back(CreateShaderFromTextFile(GL_FRAGMENT_SHADER, "Shaders\\FS.glsl"));
	shaderProgram = CreateProgram(shaderList);

	unfMat = glGetUniformLocation(shaderProgram, "uMat");
	unfColor = glGetUniformLocation(shaderProgram, "uColor");
	unfAtlasTexcoords = glGetUniformLocation(shaderProgram, "uAtlasTexcoords");
	unfTexture = glGetUniformLocation(shaderProgram, "uTexture");
	
	glUniform1i(unfTexture, 0);

	selectionShaderList.push_back(CreateShaderFromTextFile(GL_VERTEX_SHADER, "Shaders\\VS.glsl"));
	selectionShaderList.push_back(CreateShaderFromTextFile(GL_FRAGMENT_SHADER, "Shaders\\selection.fs"));
	selectionProgram = CreateProgram(selectionShaderList);
	unfMatSel = glGetUniformLocation(selectionProgram, "uMat");
	unfCode   = glGetUniformLocation(selectionProgram, "uCode");
	
	glViewport(0, 0, 800, 600);
	glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);


}

void Renderer::Update()
{
	//View = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Renderer::Draw()
{
	const float lightskycolor[] = { gui->background, 0.81f, 0.98f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, lightskycolor);

	glUseProgram(shaderProgram);

	//for (int i = 0; i < 3; i++)
	//{
	

	for (int i = 0; i < 4; i++)
	{
		Sprite* sprite = &gui->checkbox[i].GetButtonSprite();
		MVP = Projection * View * sprite->GetModelMatrix();
		glUniformMatrix4fv(unfMat, 1, GL_FALSE, glm::value_ptr(MVP));
		glUniform4fv(unfColor, 1, glm::value_ptr(sprite->GetColor()));
		glUniform4fv(unfAtlasTexcoords, 1, glm::value_ptr(sprite->GetAtlasTexcoords()));
		sprite->Draw();
	}

	for (int i = 0; i < 1; i++)
	{
		Sprite* sprite = &gui->textbox[i].GetButtonSprite();
		MVP = Projection * View * sprite->GetModelMatrix();
		glUniformMatrix4fv(unfMat, 1, GL_FALSE, glm::value_ptr(MVP));
		glUniform4fv(unfColor, 1, glm::value_ptr(sprite->GetColor()));
		glUniform4fv(unfAtlasTexcoords, 1, glm::value_ptr(sprite->GetAtlasTexcoords()));
		sprite->Draw();
	}
//}

	//MVP = Projection * View * gui->scrollbar.buttons[1].GetSprite().GetModelMatrix();
	//glUniformMatrix4fv(unfMat, 1, GL_FALSE, glm::value_ptr(MVP));
	//glUniform4fv(unfColor, 1, glm::value_ptr(gui->scrollbar.buttons[1].GetSprite().GetColor()));
	//gui->scrollbar.buttons[1].GetSprite().Draw();
	//
	//MVP = Projection * View * gui->scrollbar.buttons[0].GetSprite().GetModelMatrix();
	//glUniformMatrix4fv(unfMat, 1, GL_FALSE, glm::value_ptr(MVP));
	//glUniform4fv(unfColor, 1, glm::value_ptr(gui->scrollbar.buttons[0].GetSprite().GetColor()));
	////glUniform4fv(unfAtlasTexcoords, 1, glm::value_ptr(gui->scrollbar.buttons[0].GetSprite().GetAtlasTexcoords()));
	//gui->scrollbar.buttons[0].GetSprite().Draw();

	for (int i = 0; i < 4; i++)
	{
		Text* text = &gui->checkbox[i].GetText();
		for (int i = 0; i < text->size; i++)
		{
			MVP = Projection * View * text->GetSprite()[i].GetModelMatrix();
			glUniformMatrix4fv(unfMat, 1, GL_FALSE, glm::value_ptr(MVP));
			glUniform4fv(unfColor, 1, glm::value_ptr(text->GetSprite()[i].GetColor()));
			glUniform4fv(unfAtlasTexcoords, 1, glm::value_ptr(text->GetSprite()[i].GetAtlasTexcoords()));
			text->GetSprite()[i].Draw();
		}
	}

	for (int i = 0; i < 1; i++)
	{
		Text* text = &gui->textbox[i].GetText();
		for (int i = 0; i < text->size; i++)
		{
			MVP = Projection * View * text->GetSprite()[i].GetModelMatrix();
			glUniformMatrix4fv(unfMat, 1, GL_FALSE, glm::value_ptr(MVP));
			glUniform4fv(unfColor, 1, glm::value_ptr(text->GetSprite()[i].GetColor()));
			glUniform4fv(unfAtlasTexcoords, 1, glm::value_ptr(text->GetSprite()[i].GetAtlasTexcoords()));
			text->GetSprite()[i].Draw();
		}
	}
	glFlush();
}

void Renderer::DrawSelection()
{
	const float blackcolor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, blackcolor);

	glUseProgram(selectionProgram);
	
	for (int i = 0; i < 4; i++)
	{
		Sprite* sprite = &gui->checkbox[i].GetButtonSprite();
		MVP = Projection * View * sprite->GetModelMatrix();
		glUniformMatrix4fv(unfMatSel, 1, GL_FALSE, glm::value_ptr(MVP));
		glUniform1i(unfCode, sprite->GetId());
		sprite->Draw();
	}

	for (int i = 0; i < 1; i++)
	{
		Sprite* sprite = &gui->textbox[i].GetButtonSprite();
		MVP = Projection * View * sprite->GetModelMatrix();
		glUniformMatrix4fv(unfMatSel, 1, GL_FALSE, glm::value_ptr(MVP));
		glUniform1i(unfCode, sprite->GetId());
		sprite->Draw();
	}
	/*Sprite* sprite = &gui->checkbox.GetButtonSprite();
	MVP = Projection * View * sprite->GetModelMatrix();
	glUniformMatrix4fv(unfMat, 1, GL_FALSE, glm::value_ptr(MVP));
	glUniform1i(unfCode, sprite->GetId());
	sprite->Draw();*/

	//for (int i = 0; i < 3; i++)
	//{
	//	MVP = Projection * View * gui->buttons[i].GetSprite().GetModelMatrix();
	//	glUniformMatrix4fv(unfMatSel, 1, GL_FALSE, glm::value_ptr(MVP));
	//	glUniform1i(unfCode, gui->buttons[i].GetSprite().GetId());
	//	gui->buttons[i].GetSprite().Draw();
	//}

	//MVP = Projection * View * gui->scrollbar.buttons[1].GetSprite().GetModelMatrix();
	//glUniformMatrix4fv(unfMatSel, 1, GL_FALSE, glm::value_ptr(MVP));
	//glUniform1i(unfCode, gui->scrollbar.buttons[1].GetSprite().GetId());
	//gui->scrollbar.buttons[1].GetSprite().Draw();
	//
	//MVP = Projection * View * gui->scrollbar.buttons[0].GetSprite().GetModelMatrix();
	//glUniformMatrix4fv(unfMatSel, 1, GL_FALSE, glm::value_ptr(MVP));
	//glUniform1i(unfCode, gui->scrollbar.buttons[0].GetSprite().GetId());
	//gui->scrollbar.buttons[0].GetSprite().Draw();
	
	glFlush();
}

unsigned char Renderer::ProcessSelection(int x, int y)
{
	unsigned char response[4];
	GLint viewport[4];

	DrawSelection();
	DrawSelection();

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &response);

	return response[0];
}

void Renderer::Resize(int w, int h)
{
	float aspect = (float)w / (float)h;
	Projection = glm::perspective(45.0f, aspect, 0.0f, 100.0f);
	glViewport(0, 0, w, h);
}

void Renderer::LoadImage(Image* image, const char* filename)
{
	int force_channels = 4;
	image->data = stbi_load(filename, &image->x, &image->y, &image->n, force_channels);
	if (!image->data)
		printf("ERROR: could not load image\n");

	int width_in_bytes = image->x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = image->y / 2;

	for (int row = 0; row < half_height; row++) {
		top = image->data + row * width_in_bytes;
		bottom = image->data + (image->y - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}

	
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
