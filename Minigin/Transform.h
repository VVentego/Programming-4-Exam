#ifndef TRANSFORM
#define TRANSFORM

#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		void SetWorldPosition(const float x, const float y);
		void SetWorldPosition(const glm::vec2& position);
		void UpdateWorldPosition();
		void SetLocalPosition(const float x, const float y);
		void SetLocalPosition(const glm::vec2& position);
		const glm::vec2 GetWorldPosition() const;
		const glm::vec2 GetLocalPosition() const;
		void SetParent(Transform* pParent);
	private:
		Transform* m_pParent{ nullptr };
		glm::vec2 m_WorldPosition{};
		glm::vec2 m_LocalPosition{};
	};
}
#endif // !TRANSFORM