#include <octoon/material/mesh_standard_material.h>

namespace octoon::material
{
	OctoonImplementSubClass(MeshStandardMaterial, Material, "MeshStandardMaterial");

	MeshStandardMaterial::MeshStandardMaterial() noexcept
		: MeshStandardMaterial(math::float3::One)
	{
	}

	MeshStandardMaterial::MeshStandardMaterial(const math::float3& color) noexcept
		: opacity_(1.0f)
	{
#if defined(OCTOON_BUILD_PLATFORM_EMSCRIPTEN) || defined(OCTOON_BUILD_PLATFORM_ANDROID)
		const char* vert = R"(
			precision mediump float;
			uniform mat4 proj;
			uniform mat4 model;

			attribute vec4 POSITION0;
			attribute vec4 NORMAL0;

			varying vec3 oTexcoord0;

			void main()
			{
				oTexcoord0 = NORMAL0;
				gl_Position = proj * model * (POSITION0 * vec4(1,1,1,1));
			})";

		const char* frag = R"(
			precision mediump float;

			uniform sampler2D decal;
			uniform vec4 color;
			uniform bool hasTexture;

			varying vec2 oTexcoord0;
			void main()
			{
				fragColor = color;
				if (hasTexture) fragColor *= pow(texture(decal, oTexcoord0), vec4(2.2));
				fragColor = pow(fragColor, vec4(1.0 / 2.2));
			})";
#else
		const char* vert = R"(#version 330
			uniform mat4 proj;
			uniform mat4 model;

			layout(location  = 0) in vec4 POSITION0;
			layout(location  = 1) in vec2 TEXCOORD0;

			out vec2 oTexcoord0;

			void main()
			{
				oTexcoord0 = TEXCOORD0;
				gl_Position = proj * model * (POSITION0 * vec4(1,1,1,1));
			})";

		const char* frag = R"(#version 330
			layout(location  = 0) out vec4 fragColor;

			uniform sampler2D decal;
			uniform vec4 color;
			uniform bool hasTexture;

			in vec2 oTexcoord0;

			void main()
			{
				fragColor = color;
				if (hasTexture) fragColor *= pow(texture(decal, oTexcoord0), vec4(2.2));
				fragColor = pow(fragColor, vec4(1.0 / 2.2));
			})";
#endif

		this->setColor(color);
		this->setOpacity(1.0f);
		this->setShader(std::make_shared<Shader>(vert, frag));
	}

	MeshStandardMaterial::~MeshStandardMaterial() noexcept
	{
	}

	void
	MeshStandardMaterial::setColor(const math::float3& color) noexcept
	{
		this->color_ = color;
		this->set("color", math::float4(this->color_, this->opacity_));
	}

	const math::float3&
	MeshStandardMaterial::getColor() const noexcept
	{
		return this->color_;
	}

	void
	MeshStandardMaterial::setColorTexture(const hal::GraphicsTexturePtr& map) noexcept
	{
		this->colorTexture_ = map;
		this->set("decal", map);
		this->set("hasTexture", map ? true : false);
	}

	const hal::GraphicsTexturePtr&
	MeshStandardMaterial::getColorTexture() const noexcept
	{
		return this->colorTexture_;
	}

	void
	MeshStandardMaterial::setOpacity(float opacity) noexcept
	{
		this->opacity_ = opacity;
		this->set("color", math::float4(this->color_, this->opacity_));
	}

	float
	MeshStandardMaterial::getOpacity() const noexcept
	{
		return opacity_;
	}

	std::shared_ptr<Material>
	MeshStandardMaterial::clone() const noexcept
	{
		auto instance = std::make_shared<MeshStandardMaterial>();
		instance->setColor(this->getColor());

		return instance;
	}
}