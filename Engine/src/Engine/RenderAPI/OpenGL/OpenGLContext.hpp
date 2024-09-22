#include "Engine/RenderAPI/Context.hpp"

namespace Engine::RenderAPI {
	class OpenGLContext : public Context {
	public:
		OpenGLContext();
		virtual ~OpenGLContext();

		void Init() override;
	};
}