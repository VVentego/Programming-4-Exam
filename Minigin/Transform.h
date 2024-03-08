#ifndef TRANSFORM
#define TRANSFORM

#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		void SetWorldPosition(const float x, const float y, const float z);
		void SetWorldPosition(const glm::vec3& position);
		void UpdateWorldPosition();
		void SetLocalPosition(const float x, const float y, const float z);
		void SetLocalPosition(const glm::vec3& position);
		const glm::vec3 GetWorldPosition() const;
		const glm::vec3 GetLocalPosition() const;
		void SetParent(Transform* pParent);
	private:
		Transform* m_pParent{ nullptr };
		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};
	};
}
#endif // !TRANSFORM