#pragma once
#include "GameObject.h"
#include "TextComponent.h"
namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent;
	class TextObject final : public GameObject
	{
	public:
		void Update(const double deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		TextObject(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

	private:
		std::string m_text;
		Transform m_transform{};
		std::shared_ptr<Font> m_font;
		//std::shared_ptr<Texture2D> m_textTexture;
		std::shared_ptr<TextComponent> m_TextComponent;
	};
}
