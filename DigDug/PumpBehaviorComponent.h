#ifndef PUMPBEHAVIOR
#define PUMPBEHAVIOR
#include <Component.h>

namespace dae
{
	class TextureComponent;
	class Enemy;
	class PumpBehaviorComponent : public Component
	{
	public:
		PumpBehaviorComponent(GameObject* pOwner, const int playerIdx);
		virtual ~PumpBehaviorComponent() = default;
		PumpBehaviorComponent(const PumpBehaviorComponent& other) = delete;
		PumpBehaviorComponent(PumpBehaviorComponent&& other) = delete;
		PumpBehaviorComponent& operator=(const PumpBehaviorComponent& other) = delete;
		PumpBehaviorComponent& operator=(PumpBehaviorComponent&& other) = delete;

		void Update(const double deltaTime) override;
		void Fire(const Facing direction);

		bool IsActive() const { return m_Active; }
		void CollisionEvent(GameObject* other) override;
		void Reset();

		const int m_PlayerIdx{};
	private:
		const bool IsInTunnel() const;
		const float m_ShootDistance{ 20.f };
		const float m_Speed{ 40.f };
		float m_DistanceMoved{};
		glm::vec2 m_Velocity{};
		std::vector<std::shared_ptr<Texture2D>> m_Textures;
		Facing m_FacingDirection{};
		TextureComponent* m_TextureComponent{};
		bool m_Active{};
		bool m_Hit{};
		Enemy* m_AttachedEnemy{};

		float m_Timer{};
	};
}
#endif // !PUMPBEHAVIOR