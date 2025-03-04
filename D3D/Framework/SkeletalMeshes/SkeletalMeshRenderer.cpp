#include "Framework.h"
#include "SkeletalMeshRenderer.h"

SkeletalMeshRenderer::SkeletalMeshRenderer(Shader* shader)
	: shader(shader)
{
	skeletalMesh = new SkeletalMesh();

	transform = new Transform(shader);
}

SkeletalMeshRenderer::~SkeletalMeshRenderer()
{
	SafeDelete(skeletalMesh);
	SafeDelete(transform);
}

void SkeletalMeshRenderer::Update()
{
	if (bRead == true)
	{
		bRead = false;

		for (SkeletalMesh_Mesh* mesh : skeletalMesh->Meshes())
			mesh->SetShader(shader);

		UpdateTransforms();
	}

	for (SkeletalMesh_Mesh* mesh : skeletalMesh->Meshes())
		mesh->Update();
}

void SkeletalMeshRenderer::Render()
{
	//static int index = -1;
	//ImGui::InputInt("Bone Index", &index);

	//static Vector3 scale = Vector3(1, 1, 1);
	//ImGui::SliderFloat3("Scale", scale, 0.1f, 10.f);
	//transform->Scale(scale);

	//if (index >= (int)skeletalMesh->MeshCount())
	//	index = -1;

	////모든 본 보기
	//if (index < 0)
	//{
	//	for (SkeletalMesh_Mesh* mesh : skeletalMesh->Meshes())
	//	{
	//		mesh->SetTransform(transform); //World
	//		mesh->Render();
	//	}
	//}
	////특정 본 보기
	//else
	//{
	//	SkeletalMesh_Mesh* mesh = skeletalMesh->MeshByIndex(index);
	//	mesh->SetTransform(transform); //World
	//	mesh->Render();
	//}

	for (SkeletalMesh_Mesh* mesh : skeletalMesh->Meshes())
	{
		mesh->SetTransform(transform); //World
		mesh->Render();
	}
}

void SkeletalMeshRenderer::ReadMesh(wstring file)
{
	skeletalMesh->ReadMesh(file);

	bRead = true;
}

void SkeletalMeshRenderer::Pass(UINT pass)
{
	for (SkeletalMesh_Mesh* mesh : skeletalMesh->Meshes())
		mesh->Pass(pass);
}

void SkeletalMeshRenderer::UpdateTransforms()
{
	for (UINT i = 0; i < skeletalMesh->BoneCount(); i++)
	{
		SkeletalMesh_Bone* bone = skeletalMesh->BoneByIndex(i);
		transforms[i] = bone->Transform();
	}

	for (SkeletalMesh_Mesh* mesh : skeletalMesh->Meshes())
		mesh->Transforms(transforms);
}
