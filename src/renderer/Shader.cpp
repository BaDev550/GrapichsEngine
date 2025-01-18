#include <renderer/Shader.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void checkCompileErrors(unsigned int shader, std::string type);
void Shader::setupShader(const char* vertexPath, const char* fragmentPath){
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
    
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
    
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
    
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
    
        // shader Program
        shaderID = glCreateProgram();
        glAttachShader(shaderID, vertex);
        glAttachShader(shaderID, fragment);
        glLinkProgram(shaderID);
        checkCompileErrors(shaderID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
}

void Shader::Use(){
    glUseProgram(shaderID); 
}

void Shader::setBool(const std::string& name, bool value){
    this->Use();
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string& name, int value){
    this->Use();
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value); 
}

void Shader::setFloat(const std::string& name, float value){
    this->Use();
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value); 
}

void Shader::setVec2(const std::string& name, const glm::vec2& value){
    this->Use();
    glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y){
    this->Use();
    glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value){
    this->Use();
    glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z){
    this->Use();
    glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value){
    this->Use();
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILE of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM::LINKING of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
