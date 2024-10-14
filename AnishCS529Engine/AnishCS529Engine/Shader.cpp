#include "Shader.h"

/*!****************************************************************************
 * \brief Shader constructor
 * 
 * Constructor will create the relevant shaders and link them to the Shader
 * program.
 * 
 * \param shaderFilePaths String with shader file paths separated by newline.
 *****************************************************************************/
Shader::Shader(std::string& shaderFilePaths) {
	std::istringstream pathsStream(shaderFilePaths);
	std::string shaderFilePath;

	while (std::getline(pathsStream, shaderFilePath)) {
		GLenum type = readShaderType(shaderFilePath);
		const GLchar* source = readShaderFile(shaderFilePath).c_str();
		shaderIDs[type] = loadShader(type, source);
	}

	linkShaders();

	for (const auto& [key, id] : shaderIDs) {
		deleteShader(id);
	}

}

Shader::~Shader() {
	glDeleteProgram(programID);
}

/*!****************************************************************************
 * \brief Helper function to convert a string to lowercase
 * 
 * \param str String to be covnerted to lowercase.
 * \return \b std::string The lowercase string.
 *****************************************************************************/
std::string Shader::toLowerCase(const std::string& str) {
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
		[](unsigned char c) { return std::tolower(c); });
	return lowerStr;
}

/*!****************************************************************************
 * \brief Get shader type from file name
 * 
 * \param path Shader file name.
 * \return \b GLenum Shader type.
 *****************************************************************************/
GLenum Shader::readShaderType(std::string path) {
	std::string lowercasePath = toLowerCase(path);

	if (lowercasePath.find("vertex") != std::string::npos) 
		return GL_VERTEX_SHADER;
	if (lowercasePath.find("fragment") != std::string::npos) 
		return GL_FRAGMENT_SHADER;
	if (lowercasePath.find("geometry") != std::string::npos) 
		return GL_GEOMETRY_SHADER;
	if (lowercasePath.find("compute") != std::string::npos) 
		return GL_COMPUTE_SHADER;
}

/*!****************************************************************************
 * \brief Read shader data from a file
 * 
 * \param path File path of the shader.
 * \return \b std::string Shader file contents.
 *****************************************************************************/
std::string Shader::readShaderFile(std::string path) {
	std::ifstream shaderFile(path);
	if (!shaderFile.is_open()) {
		std::cerr << "ERROR::SHADER::FILE::FILE_OPEN_FAILED: " << path <<
			std::endl;
		throw "ERROR::SHADER::FILE::FILE_OPEN_FAILED";
	}

	std::stringstream buffer;
	buffer << shaderFile.rdbuf();

	shaderFile.close();

	return buffer.str();
}

/*!****************************************************************************
 * \brief Create glShader object
 * 
 * \param type Type of shader to be created.
 * \param source Source code of the shader.
 * \return \b GLuint Shader ID of the new Shader.
 *****************************************************************************/
GLuint Shader::loadShader(GLenum type, const GLchar* source) {
	int  success;
	char infoLog[512];
	GLuint shaderId;

	shaderId = glCreateShader(type);

	glShaderSource(shaderId, 1, &source, NULL);
	glCompileShader(shaderId);

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog <<
			std::endl;
	}

	return shaderId;
}

/*!****************************************************************************
 * \brief Delete glShader object
 * 
 * \param id
 *****************************************************************************/
void Shader::deleteShader(GLuint id) {
	glDeleteShader(id);
}

/*!****************************************************************************
 * \brief Link glShaders and create the Shader Program
 * 
 *****************************************************************************/
void Shader::linkShaders() {
	int  success;
	char infoLog[512];

	programID = glCreateProgram();

	for (const auto& [type, id] : shaderIDs) {
		glAttachShader(programID, id);
	}

	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog <<
			std::endl;
	}
}

/*!****************************************************************************
 * \brief Function to use the Shader Program
 * 
 * This should be used every time a draw call needs to use this specific
 * shader.
 * 
 *****************************************************************************/
void Shader::use() {
	glUseProgram(programID);
}

void Shader::initializeBasicUniforms() {
	modelMatrixLoc = glGetUniformLocation(shaderProgramId, "modelMatrix");
	viewMatrixLoc = glGetUniformLocation(shaderProgramId, "viewMatrix");
	perspectiveMatrixLoc = glGetUniformLocation(shaderProgramId, "perspectiveMatrix");
	orthographicMatrixLoc = glGetUniformLocation(shaderProgramId, "orthographicMatrix");
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, Matrix4().getData());
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, Matrix4::lookAt(Vector3(0.0f, 0.0f, 3.0f), Vector3(), Vector3(0.0f, 1.0f, 0.0f)).getData());
	glUniformMatrix4fv(perspectiveMatrixLoc, 1, GL_FALSE, Matrix4::perspective(90.0f * pi / 180, gameWindow.getWidth() / gameWindow.getHeight(), 0.1f, 100.0f).getData());
	glUniformMatrix4fv(orthographicMatrixLoc, 1, GL_FALSE, Matrix4::orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f).getData());
}