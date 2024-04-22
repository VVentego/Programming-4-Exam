#ifndef TUNNELTEXTURECOMPONENT
#define TUNNELTEXTURECOMPONENT

#include "../Minigin/TextureComponent.h"
namespace dae
{
    class TunnelTextureComponent :
        public TextureComponent
    {
	public:
		void Render() const override;

		TunnelTextureComponent(GameObject* pOwner, std::vector<Rectf>* pTunnelVector);
		TunnelTextureComponent(GameObject* pOwner, const float width, const float height) = delete;
		virtual ~TunnelTextureComponent() = default;
		TunnelTextureComponent(const TunnelTextureComponent& other) = delete;
		TunnelTextureComponent(TunnelTextureComponent&& other) = delete;
		TunnelTextureComponent& operator=(const TunnelTextureComponent& other) = delete;
		TunnelTextureComponent& operator=(TunnelTextureComponent&& other) = delete;

	private:
		std::vector<Rectf>* m_pTunnels{};
    };
}
#endif // !TUNNELTEXTURECOMPONENT
