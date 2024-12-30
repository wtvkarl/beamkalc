#include "Shader.h"

std::string getFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);	// creates file reader in binary mode to prevent data loss
	if (in)											
	{
		std::string contents; //empty string

		in.seekg(0, std::ios::end); // in.seekg(offset, direction)
		contents.resize(in.tellg()); // resizes string to exact size of given file -> also an example of dynamic mem allocation
		in.seekg(0, std::ios::beg);  // moves pointer to the beginning of the file to prepare for fileread. 
		in.read(&contents[0], contents.size()); //reads file and uses pointer to string that will hold the contents of the file
		in.close();	// close the file reader
		return contents; //return the new string
	}
	printf("could not find shader file: %s:", filename);
	throw(errno); //errno throws the code corresponding to the failure
}

Shader::Shader(const char* vertFile, const char* fragFile)
{
	std::string vertCode = getFileContents(vertFile); //extract shader code
	const char* vertSource = vertCode.c_str();	//convert the string to const char*
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER); //create a VERTEX shader 
	glShaderSource(vertShader, 1, &vertSource, NULL); //give the new shader its corresponding code
	glCompileShader(vertShader);	//compile the shader
	compileErrors(vertShader, "VERTEX");	//check for errors 

	//same process for the fragment shader below

	std::string fragCode = getFileContents(fragFile); 
	const char* fragSource = fragCode.c_str();
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, NULL);
	glCompileShader(fragShader);
	compileErrors(fragShader, "FRAGMENT");

	ID = glCreateProgram();	//create a PROGRAM, not another shader
	glAttachShader(ID, vertShader); //assign the program both the vertex and fragment shaders
	glAttachShader(ID, fragShader);
	glLinkProgram(ID); //link the program to the main program with an ID
	compileErrors(ID, "PROGRAM"); //compile the program

	glDeleteShader(vertShader); //get rid of the shaders since the program has copies of them now
	glDeleteShader(fragShader);

}

void Shader::activate()
{
	glUseProgram(ID);
}

void Shader::discard()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(GLuint shader, const char* type)
{
	GLint hasCompiled; //use GLint or GLuint for portability

	char infoLog[1024]; // error log
	if (type != "PROGRAM") 
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled); // returns the status of whatever we pick and stores it in variable of our choosing
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog); // gives us the info log of shader within a predetermined max size for the log, stored in a char array
			std::cout << "SHADER COMPILE ERROR for type: " << type << "\n" << infoLog << "\n";
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled); // same thing as above code but this time its for linkage errors
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER LINKING ERROR for: " << type << "\n" << infoLog << "\n";
		}
	}
}