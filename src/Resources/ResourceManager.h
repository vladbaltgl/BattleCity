#pragma once
#include<string>
#include<memory>
#include<map>


using namespace std;
namespace Renderer {
	class ShaderProgram;
	class Texture2D;
}

class ResourceManager {
public:
	ResourceManager(const string& executablePath);
	~ResourceManager() = default;
	
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&&) = delete;

	//функция для загрузки шейдера
	//функция будет возвращать поинтер на саму шейдерерную програму
	
	shared_ptr<Renderer::ShaderProgram>loadShaders(const string& shaderName,const string&vertexPath,const string&fragmentPath);
	shared_ptr<Renderer::ShaderProgram>getShaderProgram(const string&shaderName);
	
	shared_ptr<Renderer::Texture2D>loadTexture(const string& textureName, const std::string& texturePath);
	//shared_ptr<Renderer::Texture2D>loadTexture(const string& textureName, const string& vertexPath, const string& texturePath);
	shared_ptr<Renderer::Texture2D>getTexture(const string& textureName);
	
	//что таоке синглтоны????
	
	
private:
	 string getFileString(const string& relativeFilePath)const;
	typedef map<const string, shared_ptr<Renderer::ShaderProgram> > ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	typedef map<const string,shared_ptr<Renderer::Texture2D> >TexturesMap;
	TexturesMap m_textures;
	string m_path;
};