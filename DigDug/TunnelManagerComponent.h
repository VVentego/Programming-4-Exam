#ifndef TUNNELMANAGER
#define TUNNELMANAGER
#include "../Minigin/Component.h"

namespace dae
{
    class TunnelTextureComponent;
    class TunnelManagerComponent :
        public Component
    {
    public:
        void Update(const double deltaTime) override;

        TunnelManagerComponent(GameObject* owner, const std::string& tunnelFileName, std::vector<Rectf> vTunnels = std::vector<Rectf>{});
        virtual ~TunnelManagerComponent() = default;
        TunnelManagerComponent(const TunnelManagerComponent& other) = delete;
        TunnelManagerComponent(TunnelManagerComponent&& other) = delete;
        TunnelManagerComponent& operator=(const TunnelManagerComponent& other) = delete;
        TunnelManagerComponent& operator=(TunnelManagerComponent&& other) = delete;

        bool InTunnel(const glm::vec2 positionToCheck);
        void DigTunnel(const glm::vec2 position);

    private:
        std::vector<Rectf> m_Tunnels{};

        TunnelTextureComponent* m_pTextureComponent{};
        float m_TunnelLength{};

        bool m_TextureNeedsUpdate{ true };
    };
}
#endif // !TUNNELMANAGER
