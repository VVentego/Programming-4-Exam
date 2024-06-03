#ifndef POOKASTATE
#include "PookaBehavior.h"

namespace dae
{
	class PookaState
	{
	public:
		PookaState() = default;
		virtual ~PookaState() = default;
		PookaState(const PookaState& other) = delete;
		PookaState(PookaState&& other) = delete;
		PookaState& operator=(const PookaState& other) = delete;
		PookaState& operator=(PookaState&& other) = delete;

		virtual PookaState* Update(PookaBehavior&, const double) { return nullptr; }

		virtual void OnEnter(PookaBehavior&) = 0;
		virtual void OnExit(PookaBehavior&) = 0;

	protected:
		float m_StateTimer{};
	};

	class PookaNormalState final : public PookaState
	{
	public:
		PookaNormalState() = default;
		~PookaNormalState() = default;
		PookaNormalState(const PookaNormalState& other) = delete;
		PookaNormalState(PookaNormalState&& other) = delete;
		PookaNormalState& operator=(const PookaNormalState& other) = delete;
		PookaNormalState& operator=(PookaNormalState&& other) = delete;

		PookaState* Update(PookaBehavior& pooka, const double deltaTime) override;
		void OnEnter(PookaBehavior& pooka) override;
		void OnExit(PookaBehavior& pooka) override;

	private:
		const float m_NormalStateDuration{ 20.f };
	};

	class PookaGhostState final : public PookaState
	{
	public:
		PookaGhostState() = default;
		~PookaGhostState() = default;
		PookaGhostState(const PookaGhostState& other) = delete;
		PookaGhostState(PookaGhostState&& other) = delete;
		PookaGhostState& operator=(const PookaGhostState& other) = delete;
		PookaGhostState& operator=(PookaGhostState&& other) = delete;

		PookaState* Update(PookaBehavior& pooka, const double deltaTime) override;
		void OnEnter(PookaBehavior& pooka) override;
		void OnExit(PookaBehavior& pooka) override;

	private:
		const float m_GhostStateDuration{ 5.f };
	};

	class PookaInflatedState final : public PookaState
	{
	public:
		PookaInflatedState() = default;
		~PookaInflatedState() = default;
		PookaInflatedState(const PookaInflatedState& other) = delete;
		PookaInflatedState(PookaInflatedState&& other) = delete;
		PookaInflatedState& operator=(const PookaInflatedState& other) = delete;
		PookaInflatedState& operator=(PookaInflatedState&& other) = delete;

		PookaState* Update(PookaBehavior& pooka, const double deltaTime) override;
		void OnEnter(PookaBehavior& pooka) override;
		void OnExit(PookaBehavior& pooka) override;

		int m_CurrentInflationState{};
		const float m_TimeToDeflate{ 2.f };
		float m_DeflationTimer{};
		float m_DeathTimer{ .1f };
	};
}

#define POOKASTATE
#endif // !POOKASTATE