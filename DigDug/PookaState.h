#ifndef POOKASTATE
#include "PookaBehavior.h"
namespace dae
{
	enum class TravelDirection
	{
		up,
		right,
		left,
		down
	};

	class PookaState
	{
	public:
		PookaState() = default;
		virtual ~PookaState() = default;

		virtual PookaState* Update(PookaBehavior&, const double deltaTime) { return nullptr; }

		virtual void OnEnter(PookaBehavior&) {};
		virtual void OnExit(PookaBehavior& pooka) {};

	protected:
		float m_StateTimer{};
	};

	class NormalState : public PookaState
	{
	public:
		NormalState(){};
		~NormalState() = default;

		PookaState* Update(PookaBehavior& pooka, const double deltaTime) override;
		void OnEnter(PookaBehavior& pooka) override;
		void OnExit(PookaBehavior& pooka) override;

	private:
		const float m_NormalStateDuration{ 5.f };
	};

	class GhostState : public PookaState
	{
	public:
		GhostState() = default;
		~GhostState() = default;

		PookaState* Update(PookaBehavior& pooka, const double deltaTime) override;
		void OnEnter(PookaBehavior& pooka) override;
		void OnExit(PookaBehavior& pooka) override;

	private:
		const float m_GhostStateDuration{ 5.f };
	};
}
#define POOKASTATE
#endif // !POOKASTATE