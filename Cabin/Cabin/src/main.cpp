#include <iostream>


#include <glad.h>
#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include "Graphics/ShaderManager.h"
#include "Graphics/TextureManager.h"
#include "Graphics/GeoManager.h"


#include "Graphics/Geometry.h"
#include "Graphics/Vertex.h"
#include "Graphics/Texture.h"
#include "Graphics/RenderTarget.h"

#include "Data/Stack.h"
#include "Data/Array.h"
#include "Core/EventHandler.h"
#include "Maths/Random.h"

//*
unsigned int screenWidth = 800;
unsigned int screenHeight = 600;

int main()
{
	if (!glfwInit())
	{
		std::cout << "glfw failed to initialise." << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Cobin", nullptr, nullptr);
	if (!window)
	{
		std::cout << "window failed to create." << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "glad failed to initialise." << std::endl;
		return -1;
	}
	
	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.17f, 0.17f, 0.2f, 0.0f);

	ShaderRef screenShader = ShaderManager::GetInstance().Load("src/Shaders/DefaultScreen.shd");
	RenderTarget renderTarget(screenWidth * 0.10f, screenHeight * 0.10f, RenderTargetType::Texture, ColourChannels::RGB);
	GeoRef screenQuad = GeoManager::GetInstance().Create("ScreenQuad");
	screenQuad->vertices.Add({ { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } });
	screenQuad->vertices.Add({ { 1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } });
	screenQuad->vertices.Add({ { -1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } });
	screenQuad->vertices.Add({ { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } });
	screenQuad->indices.Add(0); screenQuad->indices.Add(1); screenQuad->indices.Add(2);
	screenQuad->indices.Add(3); screenQuad->indices.Add(2); screenQuad->indices.Add(1);
	screenQuad->Upload();


	ShaderRef shader = ShaderManager::GetInstance().Load("src/Shaders/DefaultSprite.shd");
	TextureRef texture = TextureManager::GetInstance().Load("../working/RealmPuncher_Character_01.png");

	GeoRef geo = GeoManager::GetInstance().Create("Quad");
	geo->vertices.Add({{ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }});
	geo->vertices.Add({{ 0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }});
	geo->vertices.Add({{ -0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }});
	geo->vertices.Add({{ 0.5f, 0.5f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }});
	geo->indices.Add(0); geo->indices.Add(1); geo->indices.Add(2);
	geo->indices.Add(3); geo->indices.Add(2); geo->indices.Add(1);
	geo->Upload();

	shader->Bind();
	texture->Bind(0);
	geo->Bind();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderTarget.Bind();

		shader->Bind();
		texture->Bind(0);
		geo->Bind();
		geo->Draw();
		geo->Unbind();
		texture->Unbind(0);
		shader->Unbind();

		renderTarget.Unbind();

		glViewport(0, 0, screenWidth, screenHeight);

		screenShader->Bind();
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, renderTarget.GetTextureId());
		//screenShader->SetUniform(screenShader->GetUniformLocation("image"), renderTarget.GetTextureId());
		screenQuad->Bind();
		screenQuad->Draw();
		screenQuad->Unbind();
		screenShader->Unbind();
		glBindTexture(GL_TEXTURE_2D, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
//*/

/*
void SomeEvent(void* context, void* data)
{
	std::cout << "SomeEvent: " << (char*)data << std::endl;
}
void SomeOtherEvent(void* context, void* data)
{
	std::cout << "SomeOtherEvent: " << (char*)data << std::endl;
}

int main()
{
	EventHandler eventHandler;

	eventHandler.AddEventListener("first event", nullptr, &SomeEvent);
	eventHandler.AddEventListener("first event", nullptr, &SomeOtherEvent);

	eventHandler.AddEventListener("second event", (void*)23, &SomeEvent);
	eventHandler.AddEventListener("second event", (void*)29, &SomeEvent);
	eventHandler.AddEventListener("second event", (void*)29, &SomeEvent);
	eventHandler.AddEventListener("second event", nullptr, &SomeOtherEvent);

	eventHandler.CallEvent("first event", (void*)"this is the data for the first event");
	std::cout << "\n\n\n";
	eventHandler.CallEvent("second event", (void*)"data for the second event");

	std::cout << "\n=================================================\n\n";

	std::cout << "\n\n\n";
	eventHandler.RemoveEventListener("second event", (void*)23, &SomeEvent);
	eventHandler.CallEvent("second event", (void*)"this is the data for the first event");
	std::cout << "\n\n\n";
	eventHandler.RemoveEventListener("second event", (void*)29, &SomeEvent);
	eventHandler.CallEvent("second event", (void*)"this is the data for the first event");
	std::cout << "\n\n\n";
	eventHandler.RemoveEventListener("second event", (void*)29, &SomeOtherEvent);
	eventHandler.CallEvent("second event", (void*)"this is the data for the first event");
	std::cout << "\n\n\n";
	eventHandler.RemoveEventListener("second event", nullptr, &SomeOtherEvent);
	eventHandler.CallEvent("second event", (void*)"this is the data for the first event");
	return 0;
}
*/

/*
void PrintObjectHierachy(Object* object, int depth = 0)
{
	for (int i = 0; i < depth; ++i)
	{
		std::cout << ((i == depth - 1) ? ">" : " ");
	}


	std::cout << object->name.c_str() << std::endl;
	for (Object* child : object->GetChildren())
	{
		PrintObjectHierachy(child, depth + 1);
	}
}

void PrintFindParent(String toFind, Object* object)
{
	Object* maybe = object->FindParent(toFind);
	if (maybe) std::cout << "Found parent of name: '" << toFind.c_str() << "', from '" << object->name.c_str() << "'" << std::endl;
	else std::cout << "Failed to find parent of name: '" << toFind.c_str() << "', from '" << object->name.c_str() << "'" << std::endl;
}

void PrintFindChild(String toFind, Object* object)
{
	Object* maybe = object->FindChild(toFind);
	if (maybe) std::cout << "Found child of name: '" << toFind.c_str() << "', from '" << object->name.c_str() << "'" << std::endl;
	else std::cout << "Failed to find child of name: '" << toFind.c_str() << "', from '" << object->name.c_str() << "'" << std::endl;
}

int main()
{
	Object root; root.name = "root"; root.SetParent(nullptr);

	Object a; a.name = "a"; a.SetParent(&root);
	Object b; b.name = "b"; b.SetParent(&a);
	Object b2; b2.name = "b2"; b2.SetParent(&a);

	Object one; one.name = "one"; one.SetParent(&root);
	Object two; two.name = "two"; two.SetParent(&one);
	Object three; three.name = "three"; three.SetParent(&two);

	PrintObjectHierachy(&root);

	std::cout << "\n\n====================\n\n";
	one.SetParent(&b);
	PrintObjectHierachy(&root);

	std::cout << "\n\n====================\n\n";
	two.SetParent(&two);
	PrintObjectHierachy(&root);

	std::cout << "\n\n====================\n\n";
	
	PrintFindParent("b", &two);
	PrintFindParent("b2", &two);
	PrintFindParent("one", &two);
	PrintFindParent("two", &two);

	std::cout << "\n\n====================\n\n";

	PrintFindChild("root", &one);
	PrintFindChild("a", &one);
	PrintFindChild("b", &one);
	PrintFindChild("b2", &one);
	PrintFindChild("one", &one);
	PrintFindChild("two", &one);
	PrintFindChild("three", &a);
	PrintFindChild("b2", &a);

	return 0;
}
*/
