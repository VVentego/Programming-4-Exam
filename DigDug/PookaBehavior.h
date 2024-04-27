#ifndef POOKA
#define POOKA
#include "../Minigin/Component.h"

namespace dae 
{
	class PookaBehavior : public Component
	{
	public:
		PookaBehavior(GameObject* pOwner);
		virtual ~PookaBehavior() = default;
		PookaBehavior(const PookaBehavior& other) = delete;
		PookaBehavior(PookaBehavior&& other) = delete;
		PookaBehavior& operator=(const PookaBehavior& other) = delete;
		PookaBehavior& operator=(PookaBehavior&& other) = delete;

		void CollisionEvent(GameObject* other) override;
	private:
		Facing m_FacingDirection{ Facing::right };
	};
}
#endif // !POOKA

