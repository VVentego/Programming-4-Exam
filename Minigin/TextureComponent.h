#ifndef TEXTURECOMPONENT
#define TEXTURECOMPONENT
#include "Component.h"
#include "Texture2D.h"
#include <string>

namespace dae
{
	class TextureComponent :
		public Component
	{
	public:
		virtual void Render() const override;
		virtual void Start() override;

		virtual void SetTexture(const std::string& filename);
		virtual void SetTexture(std::shared_ptr<Texture2D> texture);
		TextureComponent(GameObject* pOwner);
		TextureComponent(GameObject* pOwner, const float width, const float height);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		const glm::vec2 GetSize() const;
		void SetSize(const glm::vec2& newSize);
		void SetSize(const float x, const float y);
		bool m_ShouldRender{ true };
	protected:
		std::shared_ptr<Texture2D> m_texture{};
		float m_Width{};
		float m_Height{};
	};
}
#endif