#ifndef TEXTURECOMPONENT
#define TEXTURECOMPONENT

#include "Transform.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Component.h"
#include <string>

namespace dae
{
	class TextureComponent :
		public Component
	{
	public:
		void Update(const double deltaTime) override;
		void Render() const override;
		void Start() override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		TextureComponent(GameObject* pOwner);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};
	};
}
#endif