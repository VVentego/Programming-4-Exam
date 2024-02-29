#pragma once
#include "TextComponent.h"

namespace dae
{
    class FpsCounterComponent :
        public Component
    {
	public:
		void Update(const double deltaTime) override;
		double GetFps() const { return m_Fps; }

		FpsCounterComponent(GameObject* pOwner);
		virtual ~FpsCounterComponent() = default;
		FpsCounterComponent(const FpsCounterComponent& other) = delete;
		FpsCounterComponent(FpsCounterComponent&& other) = delete;
		FpsCounterComponent& operator=(const FpsCounterComponent& other) = delete;
		FpsCounterComponent& operator=(FpsCounterComponent&& other) = delete;

	private:
		double m_Fps{};
		std::shared_ptr<dae::TextComponent> m_pTextComponent;
    };
}

