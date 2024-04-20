#ifndef PUMPBEHAVIOR
#define PUMPBEHAVIOR
#include "Component.h"

namespace dae
{
	class TextureComponent;
	class PumpBehaviorComponent : public Component
	{
	public:
		PumpBehaviorComponent(GameObject* pOwner, std::vector<std::shared_ptr<Texture2D>> textures);
		virtual ~PumpBehaviorComponent() = default;
		PumpBehaviorComponent(const PumpBehaviorComponent& other) = delete;
		PumpBehaviorComponent(PumpBehaviorComponent&& other) = delete;
		PumpBehaviorComponent& operator=(const PumpBehaviorComponent& other) = delete;
		PumpBehaviorComponent& operator=(PumpBehaviorComponent&& other) = delete;

		void Update(const double deltaTime) override;
		void Fire(const Facing direction);

		bool IsActive() const { return m_Active; }
	private:
		const float m_ShootDistance{ 20.f };
		const float m_Speed{ 20.f };
		float m_DistanceMoved{};
		glm::vec2 m_Velocity{};
		std::vector<std::shared_ptr<Texture2D>> m_Textures;
		Facing m_FacingDirection{};
		TextureComponent* m_TextureComponent{};
		bool m_Active{};
		bool m_Hit{};

		float m_Timer{};
	};
}
#endif // !PUMPBEHAVIOR