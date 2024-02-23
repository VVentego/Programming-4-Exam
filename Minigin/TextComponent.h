#pragma once
#include <string>
#include "Component.h"
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
		virtual void SetPosition(float x, float y);

		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	protected:
		bool m_needsUpdate;
		std::string m_text;
		Transform m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
