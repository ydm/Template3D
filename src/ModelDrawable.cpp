#include "ModelDrawable.hpp"
#include <iostream>
#include <assimp/cimport.h>
// #include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "glm/ext.hpp"


ModelDrawable::ModelDrawable(const std::string& filename)
: Drawable()
, filename_(filename)
, scene_(nullptr)
, vao_(0)
{
	vbo_[0] = vbo_[1] = vbo_[2] = 0;
}


ModelDrawable::~ModelDrawable()
{
}


bool ModelDrawable::init()
{
	if (!Drawable::init())
	{
		return false;
	}

	// aiProcessPreset_TargetRealtime_MaxQuality
	const int FLAGS = aiProcess_Triangulate
		// | aiProcess_OptimizeMeshes
		// | aiProcess_JoinIdenticalVertices
		// | aiProcess_PreTransformVertices
		// | aiProcess_FlipUVs
		;
	scene_ = aiImportFile(filename_.c_str(), FLAGS);
	if (scene_ == nullptr)
	{
		std::cerr << "[E] ModelDrawable::init: scene is NULL, "
			<< "filename=" << filename_ << ", "
			<< "error=" << aiGetErrorString() << std::endl;
		return false;
	}
	if (!scene_->HasMeshes())
	{
		std::cerr << "[E] ModelDrawable::init: scene has no meshes" << std::endl;
		return false;
	}

	// Setup drawable(s)
	const aiMesh *const mesh = scene_->mMeshes[0];
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	{
		glGenBuffers(3, vbo_);
        
		// Location 0: Vertex position
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
		{
			glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(float), mesh->mVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			glEnableVertexArrayAttrib(vao_, 0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Location 1: Vertex normal
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
		{
			glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(float), mesh->mNormals, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			glEnableVertexArrayAttrib(vao_, 1);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Face indices
		assert(mesh->HasFaces());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[2]);
		{
			GLuint *const indices = new GLuint[3 * mesh->mNumFaces];
			for(unsigned i = 0; i < mesh->mNumFaces; ++i)
			{
				indices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
				indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
				indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
			}
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * mesh->mNumFaces * sizeof(GLuint), indices, GL_STATIC_DRAW);
			delete indices;
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	// aiReleaseImport(scene_);
	// scene_ = nullptr;

	return true;
}


void ModelDrawable::terminate()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(3, vbo_);
	
	aiReleaseImport(scene_);
	scene_ = nullptr;
	
	vao_ = 0;
	vbo_[0] = vbo_[1] = vbo_[2];
	scene_ = nullptr;

	Drawable::terminate();
}


bool ModelDrawable::update(const float dt)
{
    return false;
}


bool ModelDrawable::addShaders()
{
    return addShader(GL_VERTEX_SHADER, "shaders/Model.vert") && addShader(GL_FRAGMENT_SHADER, "shaders/Model.frag");
}


void ModelDrawable::drawWithShader()
{
    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_[2]);
    glDrawElements(GL_TRIANGLES, 3 * scene_->mMeshes[0]->mNumFaces, GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
