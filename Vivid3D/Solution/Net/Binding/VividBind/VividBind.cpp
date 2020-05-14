// VividBind.cpp : Defines the exported functions for the DLL.
//
#include "pch.h"

#include <VividApp.h>

#include "VMesh2D.h"
#include "Draw2D.h"
#include "Texture2D.h"
#include "SceneBase.h"
#include "Importer.h"
#include "SceneRenderer.h"
#include "NodeLight.h"
using namespace Vivid::App;

#include "framework.h"
#include "VividBind.h"

#include <iostream>

#include "EngineMain.h"


// This is an example of an exported variable
VIVIDBIND_API int nVividBind=0;

// This is an example of an exported function.
VIVIDBIND_API int fnVividBind(void)
{
    return 0;
}

extern "C" {

    VIVIDBIND_API Vivid::Draw::Draw2D* vNewDraw2D() {

        return new Vivid::Draw::Draw2D();

    }

    VIVIDBIND_API void vDraw2D_Rect(Vivid::Draw::Draw2D* d2d, int x, int y, int w, int h) {

        d2d->Rect(x, y, w, h);

    }

    VIVIDBIND_API void vDraw2D_SetTexture(Vivid::Draw::Draw2D* d2d, Vivid::Texture::Texture2D* tex)
    {

        d2d->SetTexture(tex);

    }

    VIVIDBIND_API void vDraw2D_Bind(Vivid::Draw::Draw2D* d2d) {

        d2d->Bind();

    }

    // SCENE

    VIVIDBIND_API Vivid::Scene::SceneBase* vNewScene() {

        return new Vivid::Scene::SceneBase();

    }

    VIVIDBIND_API Vivid::Scene::VSceneNode* vNewSceneNode() {

        return new Vivid::Scene::VSceneNode();

    }

    VIVIDBIND_API void vNodeMove(Vivid::Scene::VSceneNode* node, float x, float y, float z) {

        node->Move(x, y, z);

    }

    VIVIDBIND_API void vSceneSetRoot(Vivid::Scene::SceneBase* scene, Vivid::Scene::VSceneNode* node) {

        scene->SetRoot(node);

    }

    VIVIDBIND_API void vSceneNodeAddNode(Vivid::Scene::VSceneNode* node1, Vivid::Scene::VSceneNode* node2) {

        node1->AddNode(node2);

    }

    VIVIDBIND_API int vSceneNodeNodeCount(Vivid::Scene::VSceneNode* node) {

        return node->NodeCount();

    }

    VIVIDBIND_API Vivid::Scene::VSceneNode* vSceneNodeGetNode(Vivid::Scene::VSceneNode* node, int num) {

        return node->GetNode(num);

    }

    VIVIDBIND_API int vSceneNodeGetType(Vivid::Scene::VSceneNode* node) {
        
        auto isn = dynamic_cast<VSceneEntity*>(node);

        if (isn == NULL) {
            return 1;
        }
        else {
            return 2;
        }
        return 0;

      
    }

    VIVIDBIND_API const char* _vSceneNodeGetName(Vivid::Scene::VSceneNode* node) {

        return node->GetName();

    }

    VIVIDBIND_API void vSceneNodeSetName(Vivid::Scene::VSceneNode* node, const char* name) {
        node->SetName(name);
    }



    VIVIDBIND_API void vSceneRender(Vivid::Scene::SceneBase* scene) {

        

    }

    VIVIDBIND_API void vSceneNodeSetPos(Vivid::Scene::VSceneNode* node, float x, float y, float z) {

        node->SetPosition(x, y, z);

    }

    VIVIDBIND_API float vSceneNodeGetPosX(Vivid::Scene::VSceneNode* node) {

        return node->GetPosition().x;

    }

    VIVIDBIND_API float vSceneNodeGetPosY(Vivid::Scene::VSceneNode* node) {

        return node->GetPosition().y;

    }
    VIVIDBIND_API float vSceneNodeGetPosZ(Vivid::Scene::VSceneNode* node) {

        return node->GetPosition().z;

    }

    VIVIDBIND_API Vivid::Scene::Nodes::NodeCam* vSceneGetCam(Vivid::Scene::SceneBase* scene) {

        return scene->GetCam();

    }

    VIVIDBIND_API void vSceneNodeSetRotate(Vivid::Scene::VSceneNode* node, float pitch, float yaw, float roll) {

        node->SetRotation(pitch, yaw, roll);

    }

    // :- App

    VIVIDBIND_API void vAppSetSize(int w, int h) {

        VividApp::SetSize(w, h);

    }


    // :- Meshes

    VIVIDBIND_API Vivid::Mesh::Mesh3D* vNewMesh(int vertices, int tris) {

        return new Vivid::Mesh::Mesh3D(vertices, tris);

    }

    VIVIDBIND_API void vSetMeshVertex(Vivid::Mesh::Mesh3D *mesh,int ix, float x1, float y1, float z1, float u, float v, float w, float nx, float ny, float nz, float tx, float ty, float tz, float bx, float by, float bz) {

        auto vert = new Vivid::DataTypes::Vertex3D();

        vert->Pos = float3(x1, y1, z1);
        vert->Normal = float3(nx, ny, nz);
        vert->Tangent = float3(tx, ty, tz);
        vert->BiNormal = float3(bx, by, bz);
        vert->UV = float3(u, v, w);
       
        mesh->SetVertex(ix, vert);

    }

    VIVIDBIND_API void vSetMeshTri(Vivid::Mesh::Mesh3D* mesh, int ix, int v0, int v1, int v2) {

        auto tri = new Vivid::DataTypes::Tri();

        tri->V0 = v0;
        tri->V1 = v1;
        tri->V2 = v2;

        mesh->SetTri(ix, tri);

    }

    VIVIDBIND_API void vMeshFinal(Vivid::Mesh::Mesh3D* mesh) {

        mesh->Final();

    }

    // :- Lights

    VIVIDBIND_API void vSceneAddLight(Vivid::Scene::SceneBase* scene, Vivid::Scene::Nodes::NodeLight *light) {

        scene->AddLight(light);

    }

    VIVIDBIND_API Vivid::Scene::Nodes::NodeLight* vNewLight() {

        return new Vivid::Scene::Nodes::NodeLight();

    }

    VIVIDBIND_API void vLightSetDiff(Vivid::Scene::Nodes::NodeLight *l, float r, float g, float b) {

        l->SetDiffuse(r, g, b);

    }

    // :- Entity

    VIVIDBIND_API Vivid::Scene::Nodes::VSceneEntity* vNewEntity() {

        return new Vivid::Scene::Nodes::VSceneEntity();


    }

    VIVIDBIND_API void vEntityAddMesh(Vivid::Scene::Nodes::VSceneEntity * ent,Vivid::Mesh::Mesh3D* mesh) {

        ent->AddMesh(mesh);

    }

    VIVIDBIND_API void vEntitySetRenderMode(Vivid::Scene::Nodes::VSceneEntity * ent,int mode) {

        switch (mode) {
        case 0:
            ent->SetRenderMode(Vivid::Scene::Nodes::RenderMode::Lit);
            break;
        case 1:
            ent->SetRenderMode(Vivid::Scene::Nodes::RenderMode::FullBright);
            break;
        }
    }

    // :- Renderer

    VIVIDBIND_API Vivid::Renderer::SceneRenderer * vNewRenderer(Vivid::Scene::SceneBase* scene) {

        return new Vivid::Renderer::SceneRenderer(scene);

    }

    VIVIDBIND_API void vRendererRender(Vivid::Renderer::SceneRenderer* ren)
    {

        ren->Render();

    }




    // :- Import

    VIVIDBIND_API Vivid::Scene::Nodes::VSceneEntity* vImportEntityAI(const char* path) {

        return Vivid::Import::Importer::LoadEntityAI(path);

    }

    VIVIDBIND_API int testBind(int f)
    {

        return f * 2;
    }

    VIVIDBIND_API int vSetPath(const char* path) {

        Vivid::App::VividApp::SetPath(path);
        return 0;
    }

    VIVIDBIND_API void vSetImpPath(const char* path) {

        Vivid::App::VividApp::SetImpPath(path);

    }

    VIVIDBIND_API int initWinHW(HWND hw)
    {

        Vivid::Engine::initWindowHW(hw);
        return 1;

    }
    VIVIDBIND_API int vRender() {

        Vivid::Engine::eRender();
        return 1;
    }

    VIVIDBIND_API int vPresent() {

        Vivid::Engine::ePresent();
        return 1;

    }

    // :- Texture

    VIVIDBIND_API Vivid::Texture::Texture2D* vLoadTexture2D(const char* path,int useImp) {

        if (useImp) {
            return new Vivid::Texture::Texture2D(path,true);
        }
        else {
            return new Vivid::Texture::Texture2D(path, false);
        }
    }

    VIVIDBIND_API Vivid::Texture::Texture2D* vCreateTexture2D(void* data, int w, int h,int bpp  ) {

        return new Vivid::Texture::Texture2D(data, w, h,bpp);

    }

}

// This is the constructor of a class that has been exported.
CVividBind::CVividBind()
{
    return;
}
