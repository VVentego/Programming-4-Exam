#ifndef FYGARBREATH
#define FYGARBREATH
#include <SpriteAnimatorComponent.h>

namespace dae
{
#include <Component.h>
    class FygarBreathComponent :
        public Component
    {
	public:
		FygarBreathComponent(GameObject* pOwner);
		~FygarBreathComponent() = default;
		FygarBreathComponent(const FygarBreathComponent& other) = delete;
		FygarBreathComponent(FygarBreathComponent&& other) = delete;
		FygarBreathComponent& operator=(const FygarBreathComponent& other) = delete;
		FygarBreathComponent& operator=(FygarBreathComponent&& other) = delete;

		void Update(const double deltaTime) override;
		void Toggle(const bool active, const bool facingRight);
		void SetLocalPosition(const glm::vec2 newPos);
		const bool IsActive() const { return m_Active; }
	private:
		void SetNewFrame(const int newFrame);

		SpriteAnimatorComponent* m_pSpriteAnimator;
		std::shared_ptr<SpriteSheet> m_pBreathSpriteRight1;
		std::shared_ptr<SpriteSheet> m_pBreathSpriteRight2;
		std::shared_ptr<SpriteSheet> m_pBreathSpriteRight3;
		std::shared_ptr<SpriteSheet> m_pBreathSpriteLeft1;
		std::shared_ptr<SpriteSheet> m_pBreathSpriteLeft2;
		std::shared_ptr<SpriteSheet> m_pBreathSpriteLeft3;
		const int m_MaxFrames{ 3 };
		float m_Width{};
		const float m_FrameDuration{ .2f };
		float m_FrameTime{};
		int m_CurrentFrame{ 0 };
		bool m_Active{};
		bool m_FacingRight{};
    };
}
#endif // !FYGARBREATH
