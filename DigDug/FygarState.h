#ifndef FYGARSTATE
#define FYGARSTATE
#include "FygarBehavior.h"
namespace dae
{
	class FygarState
	{
	public:
		FygarState() = default;
		virtual ~FygarState() = default;
		FygarState(const FygarState& other) = delete;
		FygarState(FygarState&& other) = delete;
		FygarState& operator=(const FygarState& other) = delete;
		FygarState& operator=(FygarState&& other) = delete;

		virtual FygarState* Update(FygarBehavior&, const double) { return nullptr; }

		virtual void OnEnter(FygarBehavior&) = 0;
		virtual void OnExit(FygarBehavior&) = 0;

	protected:
		float m_StateTimer{};
	};

	class FygarNormalState final : public FygarState
	{
	public:
		FygarNormalState() = default;
		~FygarNormalState() = default;
		FygarNormalState(const FygarNormalState& other) = delete;
		FygarNormalState(FygarNormalState&& other) = delete;
		FygarNormalState& operator=(const FygarNormalState& other) = delete;
		FygarNormalState& operator=(FygarNormalState&& other) = delete;

		FygarState* Update(FygarBehavior& fygar, const double deltaTime) override;
		void OnEnter(FygarBehavior& fygar) override;
		void OnExit(FygarBehavior& fygar) override;

	private:
		const float m_NormalStateDuration{ 60.f };
	};

	class FygarGhostState final : public FygarState
	{
	public:
		FygarGhostState() = default;
		~FygarGhostState() = default;
		FygarGhostState(const FygarGhostState& other) = delete;
		FygarGhostState(FygarGhostState&& other) = delete;
		FygarGhostState& operator=(const FygarGhostState& other) = delete;
		FygarGhostState& operator=(FygarGhostState&& other) = delete;

		FygarState* Update(FygarBehavior& fygar, const double deltaTime) override;
		void OnEnter(FygarBehavior& fygar) override;
		void OnExit(FygarBehavior& fygar) override;

	private:
		const float m_GhostStateDuration{ 5.f };
	};

	class FygarInflatedState final : public FygarState
	{
	public:
		FygarInflatedState() = default;
		~FygarInflatedState() = default;
		FygarInflatedState(const FygarInflatedState& other) = delete;
		FygarInflatedState(FygarInflatedState&& other) = delete;
		FygarInflatedState& operator=(const FygarInflatedState& other) = delete;
		FygarInflatedState& operator=(FygarInflatedState&& other) = delete;

		FygarState* Update(FygarBehavior& fygar, const double deltaTime) override;
		void OnEnter(FygarBehavior& fygar) override;
		void OnExit(FygarBehavior& fygar) override;

	private:
		int m_CurrentInflationState{};
		const float m_TimeToDeflate{ 2.f };
		float m_DeflationTimer{};
		float m_DeathTimer{ .1f };
	};

	class FygarFlattenedState final : public FygarState
	{
	public:
		FygarFlattenedState() = default;
		~FygarFlattenedState() = default;
		FygarFlattenedState(const FygarFlattenedState& other) = delete;
		FygarFlattenedState(FygarFlattenedState&& other) = delete;
		FygarFlattenedState& operator=(const FygarFlattenedState& other) = delete;
		FygarFlattenedState& operator=(FygarFlattenedState&& other) = delete;

		FygarState* Update(FygarBehavior& fygar, const double deltaTime) override;
		void OnEnter(FygarBehavior& fygar) override;
		void OnExit(FygarBehavior& fygar) override;
	private:
		float m_DeathTimer{ .1f };
	};

	class FygarFireBreathingState final : public FygarState
	{
	public:
		FygarFireBreathingState() = default;
		~FygarFireBreathingState() = default;
		FygarFireBreathingState(const FygarFireBreathingState& other) = delete;
		FygarFireBreathingState(FygarFireBreathingState&& other) = delete;
		FygarFireBreathingState& operator=(const FygarFireBreathingState& other) = delete;
		FygarFireBreathingState& operator=(FygarFireBreathingState&& other) = delete;

		FygarState* Update(FygarBehavior& fygar, const double deltaTime) override;
		void OnEnter(FygarBehavior& fygar) override;
		void OnExit(FygarBehavior& fygar) override;
	private:
		float m_BreathTime{ .5f };
	};
}

#endif // !FYGARSTATE
