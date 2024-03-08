#ifndef TEXTURECOMPONENT
#define TEXTURECOMPONENT

#include "Transform.h"
#include "ResourceManager.h"
#include "Component.h"
#include "Texture2D.h"
#include <string>

namespace dae
{
	class TextureComponent :
		public Component
	{
	public:
		void Render() const override;
		void Start() override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);
		TextureComponent(GameObject* pOwner);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
}
#endif