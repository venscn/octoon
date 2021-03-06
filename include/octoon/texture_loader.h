#ifndef OCTOON_TEXTURE_LOADER_H_
#define OCTOON_TEXTURE_LOADER_H_

#include <octoon/hal/graphics_types.h>

namespace octoon
{
	class OCTOON_EXPORT TextureLoader final
	{
	public:
		static hal::GraphicsTexturePtr load(std::string_view path, bool generatorMipmap = false, bool cache = true) noexcept(false);
	};
}

#endif