#include "RenderSystem.h"
#ifdef _DEBUG
    #include <assert.h>
#endif
#include <fstream>
#include <sstream>
#include "SceneSystem.h"
#include "../../Game/Mains/Application.h"
#include "../../Base/Source/Main/Game/Systems/ObjectManager.h"

RenderSystem::RenderSystem()
	: SceneEntity()
{
	SetEntityID("System_Render");
	if (modelStack)
	{
		delete modelStack;
		modelStack = nullptr;
	}
	if (viewStack)
	{
		delete viewStack;
		viewStack = nullptr;
	}
	if (projectionStack)
	{
		delete projectionStack;
		projectionStack = nullptr;
	}
	OrthogonalModeActive = false;
}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::Init()
{
	// Black background
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, (GLclampf)0.1f);
	glEnable(GL_ALPHA_TEST);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_gPassShaderID = LoadShaders("Shader//GPass.vertexshader", "Shader//GPass.fragmentshader");
	m_parameters[U_LIGHT_DEPTH_MVP_GPASS] = glGetUniformLocation(m_gPassShaderID, "lightDepthMVP");

	m_programID = LoadShaders("Shader//comg.vertexshader", "Shader//comg.fragmentshader");
	m_parameters[U_LIGHT_DEPTH_MVP] = glGetUniformLocation(m_programID, "lightDepthMVP");
	m_parameters[U_SHADOW_MAP] = glGetUniformLocation(m_programID, "shadowMap");

	ObjectManager::Instance().WorldHeight = 100.f;
	ObjectManager::Instance().WorldWidth = ObjectManager::Instance().WorldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Use our shader
	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	// Create meshes that can be used in any scene here
	// Other scene specific meshes should only be inited in the respective scene
	Mesh* newMesh = MeshBuilder::GenerateAxes("reference", 1000.f, 1000.f, 1000.f);
	MeshList.insert(std::pair<std::string, Mesh*>(newMesh->name, newMesh));

#ifdef _DEBUG
	assert(loadingMeshDriven("CSVFiles/MeshDriven.csv"));
#else
	loadingMeshDriven("CSVFiles/MeshDriven.csv");
#endif
	ExportedFont = MeshList.find("text")->second;
}

void RenderSystem::Update(float dt)
{
	if (Application::IsKeyPressed('1')) {
	glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('2')) {
	glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('6')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (Application::IsKeyPressed('7')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void RenderSystem::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::Exit()
{
	if (MeshList.empty() == false)
	{
		for (auto it : MeshList)
		{
			delete it.second;
		}
		MeshList.clear();
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	modelStack = nullptr;
	viewStack = nullptr;
	projectionStack = nullptr;
}

void RenderSystem::RenderText(Mesh& mesh, const std::string &text, Color &color)
{
	if (mesh.textureArray[0] <= 0/* || mesh.textureID <= 0*/)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh.textureArray[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.75f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack->Top() * viewStack->Top() * modelStack->Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh.Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void RenderSystem::RenderText(const std::string &text, Color &color)
{
	if (ExportedFont->textureArray[0] <= 0/* || mesh.textureID <= 0*/)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ExportedFont->textureArray[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.75f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack->Top() * viewStack->Top() * modelStack->Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		ExportedFont->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void RenderSystem::RenderTextOnScreen(Mesh& mesh, const std::string &text, Color &color, const float &size, const float &x, const float &y)
{
	if (mesh.textureArray[0] <= 0)
		return;

	viewStack->PushMatrix();
	viewStack->LoadIdentity();
	modelStack->PushMatrix();
	modelStack->LoadIdentity();
	modelStack->Translate(x, y, 0);
	modelStack->Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh.textureArray[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.75f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack->Top() * viewStack->Top() * modelStack->Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh.Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack->PopMatrix();
	viewStack->PopMatrix();
}

void RenderSystem::RenderTextOnScreen(const std::string &text, Color &color, const float &size, const float &x, const float &y)
{
	if (ExportedFont->textureArray[0] <= 0)
		return;

	viewStack->PushMatrix();
	viewStack->LoadIdentity();
	modelStack->PushMatrix();
	modelStack->LoadIdentity();
	modelStack->Translate(x, y, 0);
	modelStack->Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ExportedFont->textureArray[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.75f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack->Top() * viewStack->Top() * modelStack->Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		ExportedFont->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack->PopMatrix();
	viewStack->PopMatrix();
}

void RenderSystem::RenderMeshIn2D(Mesh &mesh, const bool &enableLight, const float &size, const float &x, const float &y)
{
	viewStack->PushMatrix();
	viewStack->LoadIdentity();
	modelStack->PushMatrix();
	modelStack->LoadIdentity();
	modelStack->Translate(x, y, 0);

	modelStack->Scale(size, size, size);
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack->Top() * viewStack->Top() * modelStack->Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	for (int i = 0; i < Mesh::MAX_TEXTURES; ++i)
	{
		if (mesh.textureArray[i] > 0)
		{
			//theres texture lets load it!!
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh.textureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{

			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	glUniform1i(m_parameters[U_LIGHTENABLED], enableLight);
	mesh.Render();
	if (mesh.textureArray[0] > 0 || mesh.textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack->PopMatrix();
	viewStack->PopMatrix();
}

void RenderSystem::RenderMeshIn2D(Mesh &mesh, const bool &enableLight, const float &sizeX, const float &sizeY, const float &x, const float &y)
{
	viewStack->PushMatrix();
	viewStack->LoadIdentity();
	modelStack->PushMatrix();
	modelStack->LoadIdentity();
	modelStack->Translate(x, y, 0);

	modelStack->Scale(sizeX, sizeY, 1);
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack->Top() * viewStack->Top() * modelStack->Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	for (int i = 0; i < Mesh::MAX_TEXTURES; ++i)
	{
		if (mesh.textureArray[i] > 0)
		{
			//theres texture lets load it!!
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh.textureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{

			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	glUniform1i(m_parameters[U_LIGHTENABLED], enableLight);
	mesh.Render();
	if (mesh.textureArray[0] > 0 || mesh.textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack->PopMatrix();
	viewStack->PopMatrix();
}

void RenderSystem::RenderMesh(Mesh &mesh, const bool &enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack->Top() * viewStack->Top() * modelStack->Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack->Top() * modelStack->Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		modelView = viewStack->Top() * modelStack->Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh.material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh.material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh.material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh.material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	for (int i = 0; i < Mesh::MAX_TEXTURES; ++i)
	{
		if (mesh.textureArray[i] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 1);

			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh.textureArray[i]);
			glUniform1i(m_parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	mesh.Render();
	if (mesh.textureArray[0] > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void RenderSystem::RenderText(const std::string &meshName, const std::string &text, Color &color)
{
	std::map<std::string, Mesh*>::iterator it = MeshList.find(meshName);
#ifdef _DEBUG
	assert(it != MeshList.end());
#endif
	RenderText(*it->second, text, color);
}

void RenderSystem::RenderTextOnScreen(const std::string &meshName, const std::string &text, Color &color, const float &size, const float &x, const float &y)
{
	std::map<std::string, Mesh*>::iterator it = MeshList.find(meshName);
#ifdef _DEBUG
    assert(it != MeshList.end());
#endif
    RenderTextOnScreen(*it->second, text, color, size, x, y);
}

void RenderSystem::RenderMeshIn2D(const std::string &meshName, const bool &enableLight, const float &size, const float &x, const float &y)
{
	std::map<std::string, Mesh*>::iterator it = MeshList.find(meshName);
#ifdef _DEBUG
    assert(it != MeshList.end());
#endif
    RenderMeshIn2D(*it->second, enableLight, size, x, y);
}

void RenderSystem::RenderMeshIn2D(const std::string &meshName, const bool &enableLight, const float &sizeX, const float &sizeY, const float &x, const float &y)
{
	std::map<std::string, Mesh*>::iterator it = MeshList.find(meshName);
#ifdef _DEBUG
    assert(it != MeshList.end());
#endif
    RenderMeshIn2D(*it->second, enableLight, sizeX, sizeY, x, y);
}

void RenderSystem::RenderMesh(const std::string &meshName, const bool &enableLight)
{
	std::map<std::string, Mesh*>::iterator it = MeshList.find(meshName);
#ifdef _DEBUG
    assert(it != MeshList.end());
#endif
    RenderMesh(*it->second, enableLight);
}

void RenderSystem::SetHUD(const bool& m_bHUDmode)
{
	if (m_bHUDmode)
	{
		if (OrthogonalModeActive == false)
		{
			OrthogonalModeActive = true;
			glDisable(GL_DEPTH_TEST);
			Mtx44 ortho;
			ortho.SetToOrtho(0, Application::GetWindowWidth(), 0, Application::GetWindowHeight(), -10, 10);
			projectionStack->PushMatrix();
			projectionStack->LoadMatrix(ortho);
		}
	}
	else
	{
		if (OrthogonalModeActive == true)
		{
			OrthogonalModeActive = false;
			projectionStack->PopMatrix();
			glEnable(GL_DEPTH_TEST);
		}
	}
}

bool RenderSystem::loadingMeshDriven(const std::string &fileLocation)
{
	std::ifstream file(fileLocation.c_str());
	if (file.is_open())
	{
		std::string data = "";
		std::vector<std::string> theKeys;
		std::vector<std::string> theValues;
		std::map<std::string, GLuint> targaStuff;
		while (getline(file, data))
		{
			if (data == "" || data == "\n" || data == "\r")
				continue;
			std::string token;
			std::istringstream iss(data);
			if (theKeys.empty())
			{   //Get the keys from CSV
				while (getline(iss, token, ','))
				{
					CapitalizeString(token);
					theKeys.push_back(token);
				}
			}
			else 
			{  //Begin getting all the values from the CSV
				while (getline(iss, token, ','))
				{
					theValues.push_back(token);
				}
				//NAME
				std::vector<std::string>::iterator it;
				it = std::find(theKeys.begin(), theKeys.end(), "NAME");
				size_t pos = it - theKeys.begin();
				std::string theName = theValues[pos];
				//NAME
				Mesh *newMesh = nullptr;
				//COLORS
				float r = 0, g = 0, b = 0;
				it = std::find(theKeys.begin(), theKeys.end(), "COLORR");
				pos = it - theKeys.begin();
				if (theValues[pos] == "")
					r = 1;
				else
					r = stof(theValues[pos]);
				it = std::find(theKeys.begin(), theKeys.end(), "COLORG");
				pos = it - theKeys.begin();
				if (theValues[pos] == "")
					g = 1;
				else
					g = stof(theValues[pos]);
				it = std::find(theKeys.begin(), theKeys.end(), "COLORB");
				pos = it - theKeys.begin();
				if (theValues[pos] == "")
					b = 1;
				else
					b = stof(theValues[pos]);
				//COLORS
				//OBJECTYPE
				it = std::find(theKeys.begin(), theKeys.end(), "OBJECTTYPE");
				pos = it - theKeys.begin();
				CapitalizeString(theValues[pos]);
				//OBJECTYPE
				std::string objectFile;
				if (theValues[pos] == "TEXT") 
				{
					newMesh = MeshBuilder::GenerateText(theName, 16, 16);
				}
				else if (theValues[pos] == "QUAD") 
				{
					newMesh = MeshBuilder::GenerateQuad(theName, Color(r, g, b), 1.f);
				}
				else if (theValues[pos] == "3DOBJECT") 
				{
					it = std::find(theKeys.begin(), theKeys.end(), "OBJECTFILE");
					pos = it - theKeys.begin();
					newMesh = MeshBuilder::GenerateOBJ(theName, theValues[pos]);
				}
				else if (theValues[pos] == "CUBE") 
				{
					newMesh = MeshBuilder::GenerateCube(theName, Color(r, g, b));
				}
				else 
				{
					continue;
				}
				//TEXTURES
				for (unsigned num = 0; num < Mesh::MAX_TEXTURES; ++num)
				{
					std::ostringstream ss;
					ss << "TEXTURE" << num + 1;
					it = std::find(theKeys.begin(), theKeys.end(), ss.str());
					pos = it - theKeys.begin();
					if (theValues[pos] == "" || theValues[pos] == "\n" || theValues[pos] == "\r")
						continue;
					std::map<std::string, GLuint>::iterator it = targaStuff.find(theValues[pos]);
					if (it != targaStuff.end())
					{
						newMesh->textureArray[num] = it->second;
					}
					else {
						newMesh->textureArray[num] = LoadTGA(theValues[pos].c_str());
						targaStuff.insert(std::pair<std::string, GLuint>(theValues[pos], newMesh->textureArray[num]));
					}
					if (num == 0)
						newMesh->textureID = newMesh->textureArray[num];
				}
				//TEXTURES
				MeshList.insert(std::pair<std::string, Mesh*>(newMesh->name, newMesh));
				theValues.clear();
			}
		}
        file.close();
		return true;
	}

	return false;
}

bool RenderSystem::ReadTileLayout(const std::string &fileLocation)
{
	std::ifstream file(fileLocation.c_str());
	if (file.is_open())
	{
		std::string data = "";
		std::vector<std::string> thekeys;
		while (getline(file, data))
		{
			if (data == "" || data == "\n" || data == "\r")
				continue;
			std::string token;
			std::istringstream iss(data);
		}
		return true;
	}
	return false;
}