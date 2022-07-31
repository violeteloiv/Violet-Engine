/////////////////
///
/// Renderer2D.cpp
/// Violet McAllister
/// July 14th, 2022
/// Updated: July 30th, 2022
///
/// Violet's main 2D Renderer which
/// handles drawing 2D shapes.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Violet/Renderer/RenderCommand.h"
#include "Violet/Renderer/Shader.h"
#include "Violet/Renderer/VertexArray.h"

namespace Violet
{
	/**
	 * @brief CPU definition of what a quad vertex is. 
	 */
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
		int EntityID;
	};

	/**
	 * @brief Contains data needed to render. 
	 */
	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = White Texture

		glm::vec4 QuadVertexPositions[4];

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_Data;

	/**
	 * @brief Initializes the renderer.
	 */
	void Renderer2D::Init()
	{
		VT_PROFILE_FUNCTION();

		// Initialize Data
		s_Data.QuadVertexArray = VertexArray::Create();
		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3,	"a_Position"		},
			{ ShaderDataType::Float4,	"a_Color"			},
			{ ShaderDataType::Float2,	"a_TexCoord"		},
			{ ShaderDataType::Float,	"a_TexIndex"		},
			{ ShaderDataType::Float,	"a_TilingFactor"	},
			{ ShaderDataType::Int,		"a_EntityID"		}
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		// Index Buffer
		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		// Create Default Texture
		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		// Initialize Sampler Array
		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		// Texture Shader
		s_Data.TextureShader = Shader::Create("Assets/Shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

		// Set First Texture Slot to 0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		// Initialize Position Vertices
		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	/**
	 * @brief Shuts down the renderer. 
	 */
	void Renderer2D::Shutdown()
	{
		VT_PROFILE_FUNCTION();

		delete[] s_Data.QuadVertexBufferBase;
	}

	/**
	 * @brief Begins the scene by updating the view projection.
	 * @param p_Camera The camera for the scene.
	 * @param p_Transform The transform to be used.
	 */
	void Renderer2D::BeginScene(const Camera& p_Camera, const glm::mat4& p_Transform)
	{
		VT_PROFILE_FUNCTION();

		glm::mat4 viewProj = p_Camera.GetProjection() * glm::inverse(p_Transform);

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", viewProj);

		StartBatch();
	}

	/**
	 * @brief Begins the scene by updating the view projection.
	 * @param p_Camera The editor camera for Violet Editor.
	 */
	void Renderer2D::BeginScene(const EditorCamera& p_Camera)
	{
		VT_PROFILE_FUNCTION();

		glm::mat4 viewProj = p_Camera.GetViewProjection();

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", viewProj);

		StartBatch();
	}

	/**
	 * @brief Begins the scene by updating view projections.
	 * @param p_Camera The camera view.
	 */
	void Renderer2D::BeginScene(const OrthographicCamera& p_Camera)
	{
		VT_PROFILE_FUNCTION();

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", p_Camera.GetViewProjectionMatrix());

		StartBatch();
	}

	/**
	 * @brief Ends the scene. 
	 */
	void Renderer2D::EndScene()
	{
		VT_PROFILE_FUNCTION();

		Flush();
	}

	/**
	 * @brief Starts a batch for the renderer. 
	 */
	void Renderer2D::StartBatch()
	{
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	/**
	 * @brief FLushes the buffers and draws what's currently indexed.
	 */
	void Renderer2D::Flush()
	{
		if (s_Data.QuadIndexCount == 0)
			return; // Nothing To Draw

		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		// Bind textures
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}

	/**
	 * @brief Resets to the next batch renderering. 
	 */
	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}

	/**
	 * @brief Draws a square at a position, with a size, and with a color.
	 * @param p_Position The 2D position.
	 * @param p_Size The size of the square.
	 * @param p_Color the color of the square.
	 */
	void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
	{
		DrawQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Color);
	}

	/**
	 * @brief Draws a square at a position, with a size, and with a color.
	 * @param p_Position The 3D position.
	 * @param p_Size The size of the square.
	 * @param p_Color the color of the square.
	 */
	void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
	{
		VT_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position)
			* glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });

		DrawQuad(transform, p_Color);
	}

	/**
	 * @brief Draws a square at a position, with a size, and with a texture.
	 * @param p_Position The 2D position.
	 * @param p_Size The size of the square.
	 * @param p_Texture The texture for the square.
	 * @param p_TilingFactor Optional setting to change how the image tiles.
	 * @param p_TintColor Option setting to change the tint color.
	 */
	void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		DrawQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Texture, p_TilingFactor, p_TintColor);
	}

	/**
	 * @brief Draws a square at a position, with a size, and with a texture.
	 * @param p_Position The 3D position.
	 * @param p_Size The size of the square.
	 * @param p_Texture The texture for the square.
	 * @param p_TilingFactor Optional setting to change how the image tiles.
	 * @param p_TintColor Option setting to change the tint color.
	 */
	void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		VT_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position)
			* glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });

		DrawQuad(transform, p_Texture, p_TilingFactor, p_TintColor);
	}

	/**
	 * @brief Draws a square with only a transform and color.
	 * @param p_Transform The transform of the square.
	 * @param p_Color The color of the square.
	 * @param p_EntityID Optional setting for the entity ID.
	 */
	void Renderer2D::DrawQuad(const glm::mat4& p_Transform, const glm::vec4& p_Color, int p_EntityID)
	{
		constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f; // White Texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = p_Transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = p_Color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr->EntityID = p_EntityID;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	/**
	 * @brief Draws a square at a position, with a size, and with a texture.
	 * @param p_Position The 3D position.
	 * @param p_Size The size of the square.
	 * @param p_Texture The texture for the square.
	 * @param p_TilingFactor Optional setting to change how the image tiles.
	 * @param p_TintColor Optional setting to change the tint color.
	 * @param p_EntityID Optional setting for the EntityID.
	 */
	void Renderer2D::DrawQuad(const glm::mat4& p_Transform, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor, int p_EntityID)
	{
		VT_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i] == *p_Texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				NextBatch();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = p_Texture;
			s_Data.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = p_Transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = p_TintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = p_TilingFactor;
			s_Data.QuadVertexBufferPtr->EntityID = p_EntityID;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	/**
	 * @brief Draws a rotated square at a position, with a size, and with a texture.
	 * @param p_Position The 2D position.
	 * @param p_Size The size of the square.
	 * @param p_Rotation The rotation of the square.
	 * @param p_Color The color of the square.
	 */
	void Renderer2D::DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color)
	{
		DrawRotatedQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Rotation, p_Color);
	}

	/**
	 * @brief Draws a rotated square at a position, with a size, and with a texture.
	 * @param p_Position The 3D position.
	 * @param p_Size The size of the square.
	 * @param p_Rotation The rotation of the square.
	 * @param p_Color The color of the square.
	 */
	void Renderer2D::DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color)
	{
		VT_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(p_Rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });

		DrawQuad(transform, p_Color);
	}

	/**
	 * @brief Draws a rotated square at a position, with a size, and with a texture.
	 * @param p_Position The 2D position.
	 * @param p_Size The size of the square.
	 * @param p_Rotation The rotation of the square.
	 * @param p_Texture The texture for the square.
	 * @param p_TilingFactor Optional setting to change how the image tiles.
	 * @param p_TintColor Option setting to change the tint color.
	 */
	void Renderer2D::DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		DrawRotatedQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Rotation, p_Texture, p_TilingFactor, p_TintColor);
	}

	/**
	 * @brief Draws a rotated square at a position, with a size, and with a texture.
	 * @param p_Position The 3D position.
	 * @param p_Size The size of the square.
	 * @param p_Rotation The rotation of the square.
	 * @param p_Texture The texture for the square.
	 * @param p_TilingFactor Optional setting to change how the image tiles.
	 * @param p_TintColor Option setting to change the tint color.
	 */
	void Renderer2D::DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		VT_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(p_Rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });

		DrawQuad(transform, p_Texture, p_TilingFactor, p_TintColor);
	}

	/**
	 * @brief Draws a sprite using it's SRC.
	 * @param p_Transform The transform of the spirte.
	 * @param p_SRC The Sprite Renderer Component of the sprite.
	 * @param p_EntityID The ID of the entity.
	 */
	void Renderer2D::DrawSprite(const glm::mat4& p_Transform, SpriteRendererComponent& p_SRC, int p_EntityID)
	{
		DrawQuad(p_Transform, p_SRC.Color, p_EntityID);
	}

	/**
	 * @brief Resets the Statistics for the renderer.
	 */
	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	/**
	 * @brief Gets the statistics data.
	 * @returns The statistics data.
	 */
	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}
}
