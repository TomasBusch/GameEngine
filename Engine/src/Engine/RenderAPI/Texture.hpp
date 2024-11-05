#pragma once

namespace Engine {
	class Texture {
	public:
		Texture() = default;
		virtual ~Texture() = default;
	};

	class Texture2D : public Texture {
	public:
		Texture2D() = default;
		virtual ~Texture2D() = default;
	};

	class Texture3D : public Texture {
	public:
		Texture3D() = default;
		virtual ~Texture3D() = default;
	};

	class RectangleTexture : public Texture {
	public:
		RectangleTexture() = default;
		virtual ~RectangleTexture() = default;
	};

	class Cubemap : public Texture {
	public:
		Cubemap() = default;
		virtual ~Cubemap() = default;
	};
}