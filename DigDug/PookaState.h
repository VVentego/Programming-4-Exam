#include "PookaBehavior.h"
#ifndef POOKASTATE
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

		virtual void Update(PookaBehavior&) {};
	protected:
		virtual void OnEnter() {};
		virtual void OnExit() {};
	};

	class NormalState : public PookaState
	{
	public:
		NormalState() : m_IsGhost{ false } {};
		~NormalState() = default;

		void Update(PookaBehavior& pooka) override;
	private:
		void OnEnter() override;
		void OnExit() override;
	private:

		bool m_IsGhost{};
		TravelDirection m_TravelDirection{};
	};

	class GhostState : public PookaState
	{
	public:
		GhostState() = default;
		~GhostState() = default;

		void Update(PookaBehavior& pooka) override;
		void OnEnter() override;
		void OnExit() override;
	};
}
#define POOKASTATE
#endif // !POOKASTATE