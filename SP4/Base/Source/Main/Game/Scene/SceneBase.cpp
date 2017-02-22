#include "SceneBase.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "../Miscellaneous/MeshBuilder.h"
#include "../../Game/Mains/Application.h"
#include "../Systems/ObjectManager.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
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

	m_programID = LoadShaders( "Shader//comg.vertexshader", "Shader//comg.fragmentshader" );

	ObjectManager::Instance().WorldHeight = 100.f;
	ObjectManager::Instance().WorldWidth = ObjectManager::Instance().WorldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
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
	
	glUniform1i(m_parameters[U_NUMLIGHTS], 0);
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

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_BALL] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1), 2.f);
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//ExportedFont.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	meshList[GEO_BULLET] = MeshBuilder::GenerateAvatar("Ship", Color(1.f, 1.f, 0.f), 1);

	meshList[GEO_SCAVENGER] = MeshBuilder::GenerateQuad("TexQuad", Color(),3);
	meshList[GEO_SCAVENGER]->textureID = LoadTGA("Image//ScavengerSprite_1.tga");

	meshList[GEO_DRONE] = MeshBuilder::GenerateQuad("TexQuad", Color(),3);
	meshList[GEO_DRONE]->textureID = LoadTGA("Image//Drone.tga");

	meshList[GEO_ZOMBIE] = MeshBuilder::GenerateQuad("Zombie", Color(), 3);
	meshList[GEO_ZOMBIE]->textureID = LoadTGA("Image//Zombie.tga");

	meshList[GEO_WILDLIFE] = MeshBuilder::GenerateQuad("WildLife", Color(), 3);
	meshList[GEO_WILDLIFE]->textureID = LoadTGA("Image//WildLife.tga");

	meshList[GEO_BLOOD] = MeshBuilder::GenerateQuad("TexQuad", Color(), 3);
	meshList[GEO_BLOOD]->textureID = LoadTGA("Image//BloodParticle.tga");

	meshList[GEO_EXPLOSION] = MeshBuilder::GenerateQuad("TexQuad", Color(), 3);
	meshList[GEO_EXPLOSION]->textureID = LoadTGA("Image//ExplosionParticle.tga");

	meshList[GEO_SMOKE] = MeshBuilder::GenerateQuad("TexQuad", Color(), 3);
	meshList[GEO_SMOKE]->textureID = LoadTGA("Image//SmokeParticle.tga");

	meshList[GEO_AMMOPACK] = MeshBuilder::GenerateQuad("TexQuad", Color(), 1);
	meshList[GEO_AMMOPACK]->textureID = LoadTGA("Image//AmmoBox.tga");

	meshList[GEO_HEALTHPACK] = MeshBuilder::GenerateQuad("TexQuad", Color(), 1);
	meshList[GEO_HEALTHPACK]->textureID = LoadTGA("Image//Medkit.tga");

	meshList[GEO_REDBAR] = MeshBuilder::GenerateQuad("TexQuad", Color(), 1);
	meshList[GEO_REDBAR]->textureID = LoadTGA("Image//RedBar.tga");

	meshList[GEO_GREENBAR] = MeshBuilder::GenerateQuad("TexQuad", Color(), 1);
	meshList[GEO_GREENBAR]->textureID = LoadTGA("Image//GreenBar.tga");

	meshList[GEO_BLUEBAR] = MeshBuilder::GenerateQuad("TexQuad", Color(), 1);
	meshList[GEO_BLUEBAR]->textureID = LoadTGA("Image//BlueBar.tga");

	meshList[GEO_BACKGROUND] = MeshBuilder::GenerateQuad("TexQuad", Color(), 1);
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//warzone_city.tga");

	meshList[GEO_CRAFT_REDPOT] = MeshBuilder::GenerateQuad("Red Potion", Color(0.f,0.f,0.f), 1);
	meshList[GEO_CRAFT_REDPOT]->textureID = LoadTGA("Image//Buttons//Red Potion.tga");
	meshList[GEO_CRAFT_BLUEPOT] = MeshBuilder::GenerateQuad("Blue Potion", Color(0.f, 0.f, 0.f), 1);
	meshList[GEO_CRAFT_BLUEPOT]->textureID = LoadTGA("Image//Buttons//Blue Potion.tga");
	meshList[GEO_CRAFT_ATKPOT] = MeshBuilder::GenerateQuad("Attack Potion", Color(0.f, 0.f, 0.f), 1);
	meshList[GEO_CRAFT_ATKPOT]->textureID = LoadTGA("Image//Buttons//Attack Potion.tga");
	meshList[GEO_CRAFT_DEFPOT] = MeshBuilder::GenerateQuad("Defence Potion", Color(0.f, 0.f, 0.f), 1);
	meshList[GEO_CRAFT_DEFPOT]->textureID = LoadTGA("Image//Buttons//Defence Potion.tga");
	meshList[GEO_CRAFT_BANDAGE] = MeshBuilder::GenerateQuad("Bandage", Color(0.f, 0.f, 0.f), 1);
	meshList[GEO_CRAFT_BANDAGE]->textureID = LoadTGA("Image//Buttons//Bandage.tga");

	meshList[GEO_USE_REDPOT] = MeshBuilder::GenerateQuad("Red Potion", Color(0.f, 0.f, 0.f), 1);
	meshList[GEO_USE_REDPOT]->textureID = LoadTGA("Image//Buttons//Red Potion.tga");
	meshList[GEO_USE_BLUEPOT] = MeshBuilder::GenerateQuad("Blue Potion", Color(0.f, 0.f, 0.f), 1);
	meshList[GEO_USE_BLUEPOT]->textureID = LoadTGA("Image//Buttons//Blue Potion.tga");
	meshList[GEO_USE_ATKPOT] = MeshBuilder::GenerateQuad("Attack Potion", Color(0.f, 0.f, 0.f), 1);
	meshList[GEO_USE_ATKPOT]->textureID = LoadTGA("Image//Buttons//Attack Potion.tga");

	meshList[GEO_USE_BANDAGE] = MeshBuilder::GenerateQuad("Bandage", Color(0.f, 0.f, 0.f), 1);
	meshList[GEO_USE_BANDAGE]->textureID = LoadTGA("Image//Buttons//Bandage.tga");

	meshList[GEO_DES_CRAFT_REDPOT] = MeshBuilder::GenerateQuad("Red Potion Des", Color(1.f, 0.f, 0.f), 1);
	meshList[GEO_DES_CRAFT_REDPOT]->textureID = LoadTGA("Image//Descriptions//RedPotDescription.tga");
	meshList[GEO_DES_CRAFT_BLUEPOT] = MeshBuilder::GenerateQuad("Blue Potion Des", Color(1.f, 0.f, 0.f), 1);
	meshList[GEO_DES_CRAFT_BLUEPOT]->textureID = LoadTGA("Image//Descriptions//BluePotDescription.tga");
	meshList[GEO_DES_CRAFT_ATKPOT] = MeshBuilder::GenerateQuad("Attack Potion Des", Color(1.f, 0.f, 0.f), 1);
	meshList[GEO_DES_CRAFT_ATKPOT]->textureID = LoadTGA("Image//Descriptions//AtkPotDescription.tga");
	meshList[GEO_DES_CRAFT_DEFPOT] = MeshBuilder::GenerateQuad("Defence Potion Des", Color(1.f, 0.f, 0.f), 1);
	meshList[GEO_DES_CRAFT_DEFPOT]->textureID = LoadTGA("Image//Descriptions//DefPotDescription.tga");
	meshList[GEO_DES_CRAFT_BANDAGE] = MeshBuilder::GenerateQuad("Bandage Des", Color(1.f, 0.f, 0.f), 1);
	meshList[GEO_DES_CRAFT_BANDAGE]->textureID = LoadTGA("Image//Descriptions//BandageDescription.tga");


	meshList[GEO_WARRIOR] = MeshBuilder::GenerateQuad("Warrior", Color(0.f, 0.f, 0.f), 1.f);
	meshList[GEO_WARRIOR]->textureID = LoadTGA("Image//Warrior.tga");

	meshList[GEO_WARRIOR_FRONT] = MeshBuilder::GenerateQuad("Warrior", Color(0.f, 0.f, 0.f), 1.f);
	meshList[GEO_WARRIOR_FRONT]->textureID = LoadTGA("Image//Warrior_Front.tga");

	bLightEnabled = false;
}

void SceneBase::Update(double dt)
{
	//Keyboard Section
	if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	fps = (float)(1.f / dt);
}

void SceneBase::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0)
		return;
	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.5f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneBase::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ObjectManager::Instance().WorldHeight = 100.f;
	ObjectManager::Instance().WorldWidth = ObjectManager::Instance().WorldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

}

void SceneBase::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
