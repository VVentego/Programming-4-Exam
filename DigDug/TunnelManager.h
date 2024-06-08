#ifndef TUNNELMANAGER
#define TUNNELMANAGER
#include "../Minigin/Singleton.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>
#include "../Minigin/Component.h"

namespace dae
{
    class TunnelTextureComponent;
    class Component;
    class GameObject;
    struct Rectf;

    class TunnelManager :
        public Singleton<TunnelManager>
    {
    public:
        static TunnelManager& GetInstance()
        {
            static TunnelManager instance;
            return instance;
        }

        void Init(const std::string& tunnelFileName, std::vector<glm::vec2> tunnels);
        virtual ~TunnelManager() = default;
        TunnelManager(const TunnelManager& other) = delete;
        TunnelManager(TunnelManager&& other) = delete;
        TunnelManager& operator=(const TunnelManager& other) = delete;
        TunnelManager& operator=(TunnelManager&& other) = delete;
        glm::vec2 FindNearestTunnel(const glm::vec2 position) const;
        bool InTunnel(const glm::vec2 position);
        void DigTunnel(const glm::vec2 position);
        void ReplaceTunnels(std::vector<glm::vec2> tunnels);

        GameObject* GetTunnelManagerObject() { return m_TunnelManagerObject; }
        class TunnelComponent;
    private:
        void AdjustTunnelPositions();
        TunnelManager() = default;
        TunnelComponent* m_pTunnelComponent{};
        GameObject* m_TunnelManagerObject{};

    };

    class TunnelManager::TunnelComponent : public Component
    {
    public:
        TunnelComponent(GameObject* pOwner, const std::string& tunnelFileName, std::vector<glm::vec2> tunnels);
        virtual ~TunnelComponent() = default;
        TunnelComponent(const TunnelComponent& other) = delete;
        TunnelComponent(TunnelComponent&& other) = delete;
        TunnelComponent& operator=(const TunnelComponent& other) = delete;
        TunnelComponent& operator=(TunnelComponent&& other) = delete;

        bool InTunnel(const glm::vec2 positionToCheck);
        glm::vec2 FindNearestTunnel(const glm::vec2 position) const;
        void DigTunnel(const glm::vec2 position);
        void SetTunnelLength(const float tunnelLength) { m_TunnelLength = tunnelLength; }
        void AdjustTunnelPositions();
        void ReplaceTunnels(std::vector<glm::vec2> newTunnels);
    private:
        TunnelTextureComponent* m_pTextureComponent{};
        float m_TunnelLength{};
        std::vector<glm::vec2> m_Tunnels{};
        bool m_TextureNeedsUpdate{ true };
    };
}
#endif // !TUNNELMANAGER
