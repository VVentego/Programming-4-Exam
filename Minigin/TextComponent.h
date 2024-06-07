#ifndef TEXTCOMPONENT
#define TEXTCOMPONENT

#include <string>
#include "Component.h"
#include "TextureComponent.h"
#include "Font.h"

namespace dae
{
	class Font;
	class TextComponent final : 
		public Component
	{
	public:
		void Update(const double deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color color) { m_color = color; m_needsUpdate = true; }
		const glm::vec2 GetSize();
		TextComponent(const std::string& text, std::shared_ptr<Font> font, GameObject* owner);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	protected:
		void UpdateText();
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::unique_ptr<dae::TextureComponent> m_pTextureComponent;
		SDL_Color m_color { 255,255,255,255 }; // white text
	};
}
#endif // !TEXTCOMPONENT

