#include "MeshRenderer.h"

namespace HX
{
	MeshRenderer::MeshRenderer(Mesh mesh, Material* material)
	{
		this->m_mesh = mesh;
		this->m_material = material;
	}

	MeshRenderer::MeshRenderer(const MeshRenderer& meshRenderer)
	{
		this->m_mesh = meshRenderer.m_mesh;
		this->m_material = meshRenderer.m_material;

		this->m_VAO = meshRenderer.m_VAO;
		this->m_VBO = meshRenderer.m_VBO;
	}

	MeshRenderer::~MeshRenderer()
	{

	}

	void MeshRenderer::Initialize()
	{

		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);

		glGenBuffers(1, &this->m_VBO);

		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);

		std::vector<float> vertices;

		for (int i = 0; i < this->m_mesh.size(); i++)
		{
			Vector3 position = this->m_mesh[i].position;

			for (int j = 0; j < 3; j++)
			{
				switch (j)
				{
				case 0:
					vertices[i] = position.x;
					break;
				case 1:
					vertices[i] = position.y;
					break;
				case 2:
					vertices[i] = position.z;
					break;
				}
			}
		}

		glBufferData(GL_ARRAY_BUFFER, this->m_mesh.size() * 3 * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, this->m_mesh.size(), GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	}

	void MeshRenderer::Draw()
	{
		this->m_material->Bind();

		glBindVertexArray(this->m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);

		glDrawArrays(GL_TRIANGLES, 0, this->m_mesh.size());
	}
}