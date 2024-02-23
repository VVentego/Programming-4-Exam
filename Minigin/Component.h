#pragma once
#include <memory>
#include "Transform.h"
#include "Renderer.h"
#include "Texture2D.h"

namespace dae
{
	class Renderer;
	class Texture2D;
	class Component
	{
	public:
		virtual void Update(const double deltaTime);
		virtual void FixedUpdate(const double fixedTimeStep);
		virtual void Start();
		virtual void Render() const;

		virtual void SetPosition(float x, float y);


		Component() = default;
		virtual ~Component();
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	protected:
		Transform m_transform{};
	};
}

