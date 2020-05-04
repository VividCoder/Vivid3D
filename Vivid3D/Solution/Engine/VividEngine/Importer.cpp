#include "pch.h"
#include "Importer.h"
#include "assimp\cimport.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Material.h"
#include "VMesh3D.h"
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}
using namespace Vivid::Import;

vector<Vivid::Mesh::Mesh3D*> meshes;
vector<Vivid::Material::Material*> mats;

void add_node(const C_STRUCT aiNode* nd, VSceneEntity* ent)
{

	//DBOUT("Adding Node:" << nd->mName.C_Str() << " Meshes:" << nd->mNumMeshes << "\n");// << " Meshes:" << nd->mNumMeshes);

	Vivid::Scene::Nodes::VSceneEntity *ne = new Vivid::Scene::Nodes::VSceneEntity();

	ent->AddNode(ne);

	ne->SetName(nd->mName.C_Str());



	for (int i = 0; i < nd->mNumMeshes; i++) {

		int mi = nd->mMeshes[i];

		//DBOUT("Mesh:" << mi << "\n");

		ne->AddMesh(meshes.at(mi));

	}

//	DBOUT("MeshCount:" << ne->MeshCount() << "\n");

	for (int i = 0; i < nd->mNumChildren; i++) {

		add_node(nd->mChildren[i], ne);

	}

}

VSceneEntity* Importer::LoadEntityAI(const char* path) {

	auto rpath = Vivid::App::VividApp::GetResPath(path);

	unsigned int flags = aiProcessPreset_TargetRealtime_MaxQuality;

	auto root = aiImportFile(rpath, flags);

	//vector<Vivid::Mesh::Mesh3D*> meshes;

	meshes.resize(0);
	mats.resize(0);
//	DBOUT("Importing: NumberMeshes:" << root->mNumMeshes << "\n");
	
	//if (root->HasTextures) {



		//if(root->hasm)

	//}

	aiString tpath;

//	DBOUT("Mats:" << root->mNumMaterials << "\n");

	for (int i = 0; i < root->mNumMaterials; i++) {

		Vivid::Material::Material* mat = new Material::Material();

		auto am = root->mMaterials[i];

		am->GetTexture(aiTextureType_DIFFUSE, 0, &tpath);

		string p = string(&tpath.data[0]);

		string p2 = p.replace(0, 2, "");



		Texture2D* tex = new Texture2D(&tpath.data[0]);

	//	DBOUT("Mat:" << i << " Tex:" << p2.c_str() << "\n");

		mat->SetDiffuse(tex);

		mats.push_back(mat);
	}

	for (int i = 0; i < root->mNumMeshes; i++) {

		const C_STRUCT aiMesh* mesh = root->mMeshes[i];

		auto mati = mesh->mMaterialIndex;


	//	DBOUT("Mesh:" << i << " Verts:" << mesh->mNumVertices << " Faces:" << mesh->mNumFaces << "\n");

		auto eMesh = new Vivid::Mesh::Mesh3D(mesh->mNumVertices, mesh->mNumFaces);

	//	DBOUT("Mesh:" << i << " Mat:" << mati << " \n");

		auto rm = mats.at(mati);


		eMesh->SetMaterial(mats.at(mati));

		meshes.push_back(eMesh);

		for (int v = 0; v < mesh->mNumVertices; v++) {

			auto nv = new Vivid::DataTypes::Vertex3D();

			auto pv = mesh->mVertices[v];
			auto nmv = mesh->mNormals[v];
			aiVector3D tv, bv;
			if (mesh->HasTangentsAndBitangents()) {
				tv = mesh->mTangents[v];
				bv = mesh->mBitangents[v];
			}
			auto uv = mesh->mTextureCoords[0];

			auto uvv = uv[v];

		

			nv->Pos = Diligent::float3((float)pv.x, (float)pv.y, (float)pv.z);
			nv->Normal = Diligent::float3(nmv.x, nmv.y, nmv.z);
			nv->BiNormal = Diligent::float3(bv.x, bv.y, bv.z);
			nv->Tangent = Diligent::float3(tv.x, tv.y, tv.z);
			nv->UV = Diligent::float3(uvv.x,1.0f-uvv.y, uvv.z);
	
			eMesh->SetVertex(v, nv);

		}

		for (int t = 0; t < mesh->mNumFaces; t++) {

			const C_STRUCT aiFace* face = &mesh->mFaces[t];

			auto nt = new Vivid::DataTypes::Tri();

			nt->V0 = (int)face->mIndices[0];
			nt->V1 = (int)face->mIndices[1];
			nt->V2 = (int)face->mIndices[2];

			eMesh->SetTri(t, nt);
		

		}
		
		eMesh->Final();

	}

	auto res = new Vivid::Scene::Nodes::VSceneEntity();


	add_node(root->mRootNode, res);

	

	return res;

};