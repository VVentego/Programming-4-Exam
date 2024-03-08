#ifndef TEXTCOMPONENT
#define TEXTCOMPONENT

#include <string>
#include "Component.h"
#include "TextureComponent.h"
#include "Font.h"

namespace dae
{
	class Font;
	class TextComponent : 
		public Component
	{
	public:
		virtual void Update(const double deltaTime) override;
		virtual void Render() const override;

		virtual void SetText(const std::string& text);

		TextComponent(const std::string& text, std::shared_ptr<Font> font, GameObject* owner);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	protected:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::unique_ptr<dae::TextureComponent> m_pTextureComponent;
	};
}
#endif // !TEXTCOMPONENT

