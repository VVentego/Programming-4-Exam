#pragma once
#include "TextComponent.h"

namespace dae
{
    class FpsCounterComponent :
        public TextComponent
    {
	public:
		virtual void Update(const double deltaTime) override;
		void FixedUpdate(const double fixedDeltaTime) override;
		virtual void Render() const override;

		virtual void SetText(const std::string& text);
		virtual void SetPosition(float x, float y);

		FpsCounterComponent(std::shared_ptr<Font> font);
		virtual ~FpsCounterComponent() = default;
		FpsCounterComponent(const FpsCounterComponent& other) = delete;
		FpsCounterComponent(FpsCounterComponent&& other) = delete;
		FpsCounterComponent& operator=(const FpsCounterComponent& other) = delete;
		FpsCounterComponent& operator=(FpsCounterComponent&& other) = delete;
    };
}

