#ifndef CASSIMPMODEL_H
#define CASSIMPMODEL_H
#define INVALID_OGL_VALUE 0xFFFFFFFF
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>
#include <shaderprogram.h>
#include "ctexture.h"
#include "util.h"
using namespace std;

struct Vertex
{
    glm::vec3 m_pos;
    glm::vec2 m_tex;
    glm::vec3 m_normal;

    Vertex() {}

    Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal)
    {
        m_pos    = pos;
        m_tex    = tex;
        m_normal = normal;
    }
};

class CAssimpModel
{
public:
    CAssimpModel();
    ~CAssimpModel();
    CAssimpModel(ShaderProgram& p);
    bool LoadModelFromFile(const string& filename);
    void render();


private:
    bool isLoaded;
    int iNumMaterials;
    struct MeshEntry {
        MeshEntry();

        ~MeshEntry();

        void init(const std::vector<Vertex>& Vertices,
                  const std::vector<unsigned int>& Indices);

        //For vertex buffer
        GLuint VB;
        //For index buffer
        GLuint IB;
        unsigned int numIndices;
        unsigned int materialIndex;
    };

    void initMesh(unsigned int Index, const aiMesh* paiMesh);
    bool initMaterial(const aiScene* pScene, const string& filePath);
    ShaderProgram* prog;
    vector<MeshEntry> meshEntries;
    vector<CTexture*> textures;
};

#endif // CASSIMPMODEL_H
