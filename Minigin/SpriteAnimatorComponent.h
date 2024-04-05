#pragma once
#include "Component.h"
#include "Texture2D.h"

namespace dae
{
    class SpriteAnimatorComponent :
        public Component
    {
	public:
		SpriteAnimatorComponent(GameObject* owner);
		virtual ~SpriteAnimatorComponent() = default;
		SpriteAnimatorComponent(const SpriteAnimatorComponent& other) = delete;
		SpriteAnimatorComponent(SpriteAnimatorComponent&& other) = delete;
		SpriteAnimatorComponent& operator=(const SpriteAnimatorComponent& other) = delete;
		SpriteAnimatorComponent& operator=(SpriteAnimatorComponent&& other) = delete;

		void Update(const double) override;
		void FixedUpdate(const double fixedTimeStep) override;
		//void FlipSprite(const bool left) const;

		void AddSpriteSheet(const std::string& fileName, const int rows, const int columns);
		void AddSpriteSheet(SpriteSheet* spriteSheet);

		void Render() const override;
		const glm::vec2 GetSize() const;
		bool m_Looping{ true };
	private:
		int m_CurrentFrame{};
		int m_EndFrame{ 1 };
		double m_FrameTime{ 0.2 };
		double m_SpriteTimer{};
		std::vector<std::shared_ptr<SpriteSheet>> m_SpriteSheets;
		int m_CurrentSpriteSheet{};
		float m_Width{};
		float m_Height{};
    };
}
