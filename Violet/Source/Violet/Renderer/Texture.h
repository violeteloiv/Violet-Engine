/////////////////
///
/// Texture.h
/// Violet McAllister
/// July 13th, 2022
/// Updated: July 16th, 2022
///
/// A texture is a collection of
/// data which can be uploaded to
/// the GPU and processed as an
/// image.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_TEXTURE_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_TEXTURE_H_INCLUDED__

#include <string>

#include "Violet/Core/Base.h"

namespace Violet
{
	/**
	 * @brief A texture is data which can be processed
	 * as an image.
	 */
	class Texture
	{
	public: // Deconstructors
		virtual ~Texture() = default;
	public: // Getters & Setters
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void SetData(void* p_Data, uint32_t p_Size) = 0;
	public: // Main Functionality
		virtual void Bind(uint32_t p_Slot = 0) const = 0;
	public: // Operator Overrides
		virtual bool operator==(const Texture& p_Other) const = 0;
	};

	/**
	 * @brief A 2D Texture is essentially an image. In
	 * 3D models using 2D textures, seaming issues are
	 * created.
	 */
	class Texture2D : public Texture
	{
	public: // Creator
		static Ref<Texture2D> Create(uint32_t p_Width, uint32_t p_Height);
		static Ref<Texture2D> Create(const std::string& p_Filepath);
	};
}

#endif // __VIOLET_ENGINE_RENDERER_TEXTURE_H_INCLUDED__