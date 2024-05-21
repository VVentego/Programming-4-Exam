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

		virtual void OnEnter(PookaBehavior&) {};
		virtual void OnExit(PookaBehavior&) {};

	protected:
		float m_StateTimer{};
	};

	class NormalState : public PookaState
	{
	public:
		NormalState(){};
		~NormalState() = default;
		NormalState(const NormalState& other) = delete;
		NormalState(NormalState&& other) = delete;
		NormalState& operator=(const NormalState& other) = delete;
		NormalState& operator=(NormalState&& other) = delete;

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
		GhostState(const GhostState& other) = delete;
		GhostState(GhostState&& other) = delete;
		GhostState& operator=(const GhostState& other) = delete;
		GhostState& operator=(GhostState&& other) = delete;

		PookaState* Update(PookaBehavior& pooka, const double deltaTime) override;
		void OnEnter(PookaBehavior& pooka) override;
		void OnExit(PookaBehavior& pooka) override;

	private:
		const float m_GhostStateDuration{ 5.f };
	};

	class InflatedState : public PookaState
	{
	public:
		InflatedState() = default;
		~InflatedState() = default;
		InflatedState(const InflatedState& other) = delete;
		InflatedState(InflatedState&& other) = delete;
		InflatedState& operator=(const InflatedState& other) = delete;
		InflatedState& operator=(InflatedState&& other) = delete;

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