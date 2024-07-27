#pragma once

namespace Engine::Components {
	struct TagComponent {
		char Tag[256];

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag_string) {
			strncpy(Tag, tag_string.c_str(), 255);
			Tag[255] = '\0';
		};

		//operator const char* () const { return Tag; };
		//operator char* () { return Tag; };

	};
}

