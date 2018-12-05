#pragma once

#include <glad/glad.h>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
public:
	unsigned int ID;
	
	Shader() = delete;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath,const GLchar* geometryPath=nullptr);

	//activate-deactivate shader
	void Use();

	//utility
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetMat4(const std::string &name, glm::mat4 value) const;
	void SetVec3(const std::string &name, glm::vec3 &value) const;
	void SetVec3(const std::string &name, float x, float y, float z) const;
	
	~Shader();
};

