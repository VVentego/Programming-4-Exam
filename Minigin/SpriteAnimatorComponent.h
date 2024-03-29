#pragma once
#include "Component.h"

namespace dae
{
    class SpriteAnimatorComponent :
        public Component
    {
		SpriteAnimatorComponent(GameObject* owner);
		virtual ~SpriteAnimatorComponent() = default;
		SpriteAnimatorComponent(const SpriteAnimatorComponent& other) = delete;
		SpriteAnimatorComponent(SpriteAnimatorComponent&& other) = delete;
		SpriteAnimatorComponent& operator=(const SpriteAnimatorComponent& other) = delete;
		SpriteAnimatorComponent& operator=(SpriteAnimatorComponent&& other) = delete;
    };
}
