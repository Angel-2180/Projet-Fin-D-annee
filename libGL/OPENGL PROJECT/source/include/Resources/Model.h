#pragma once

#include <utility>
#include <vector>
#include "Resources/Resourcesmanager.h"
#include "../Resources/Texture.h"
#include "Vec2/Vec2.h"
#include "Vec3/Vec3.h"
#include "btBulletCollisionCommon.h"
#include "Shader.h"

#pragma region USING NAMESPACE
using namespace lm;
using namespace Resources;
#pragma endregion

namespace Resources
{
	// ReSharper disable once CppInconsistentNaming
	class Model : public IResource
	{
	private:
		btTriangleMesh* tri_shape = nullptr;
		btCollisionShape* model_shape = nullptr;
		struct vertex
		{
			vec3 position;
			vec2 texture_uv;
			vec3 normal;

			vertex(vec3 position, vec2 texture_uv, vec3 normal)
				: position(std::move(position)), texture_uv(std::move(texture_uv)), normal(std::move(normal))
			{};
		};

		class buffer
		{
		public:
			GLuint id_vbo = GL_FALSE;
			~buffer();

			void init_vbo(Model* model);
		};

		class vertex_attributes
		{
			GLuint id_vao_ = GL_FALSE;
		public:
			~vertex_attributes();

			void init_vao();
			void bind();
		};

		std::vector<vertex> vertex_buffer_;
		std::vector<uint32_t> index_buffer_;

	public:
		buffer vbo;
		vertex_attributes vao;

		bool only_vertices;

		Model(const char* filename);

		bool load_obj(const char* filename);
		void binding_vao();
		void draw(Shader* shaders);
	};
}
