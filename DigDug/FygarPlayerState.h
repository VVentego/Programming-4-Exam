#ifndef FYGARPLAYER
#define FYGARPLAYER
#include "FygarPlayerController.h"

namespace dae
{
	class FygarPlayerState
	{
	public:
		FygarPlayerState() = default;
		virtual ~FygarPlayerState() = default;
		FygarPlayerState(const FygarPlayerState& other) = delete;
		FygarPlayerState(FygarPlayerState&& other) = delete;
		FygarPlayerState& operator=(const FygarPlayerState& other) = delete;
		FygarPlayerState& operator=(FygarPlayerState&& other) = delete;

		virtual FygarPlayerState* Update(FygarPlayerController&, const double) { return nullptr; }

		virtual void OnEnter(FygarPlayerController&) = 0;
		virtual void OnExit(FygarPlayerController&) = 0;
		virtual void HandleInput(FygarPlayerController&, Command*) = 0;
	};
	class FygarPlayerNormalState final : public FygarPlayerState
	{
	public:
		FygarPlayerNormalState() = default;
		~FygarPlayerNormalState() = default;
		FygarPlayerNormalState(const FygarPlayerNormalState& other) = delete;
		FygarPlayerNormalState(FygarPlayerNormalState&& other) = delete;
		FygarPlayerNormalState& operator=(const FygarPlayerNormalState& other) = delete;
		FygarPlayerNormalState& operator=(FygarPlayerNormalState&& other) = delete;

		FygarPlayerState* Update(FygarPlayerController& fygar, const double deltaTime) override;
		void OnEnter(FygarPlayerController& fygar) override;
		void OnExit(FygarPlayerController& fygar) override;
		void HandleInput(FygarPlayerController&, Command* command) override;
	private:
		const float m_NormalStateDuration{ 60.f };
	};

	class FygarPlayerGhostState final : public FygarPlayerState
	{
	public:
		FygarPlayerGhostState() = default;
		~FygarPlayerGhostState() = default;
		FygarPlayerGhostState(const FygarPlayerGhostState& other) = delete;
		FygarPlayerGhostState(FygarPlayerGhostState&& other) = delete;
		FygarPlayerGhostState& operator=(const FygarPlayerGhostState& other) = delete;
		FygarPlayerGhostState& operator=(FygarPlayerGhostState&& other) = delete;

		FygarPlayerState* Update(FygarPlayerController& fygar, const double deltaTime) override;
		void OnEnter(FygarPlayerController& fygar) override;
		void OnExit(FygarPlayerController& fygar) override;
		void HandleInput(FygarPlayerController&, Command* command) override;
	};

	class FygarPlayerInflatedState final : public FygarPlayerState
	{
	public:
		FygarPlayerInflatedState() = default;
		~FygarPlayerInflatedState() = default;
		FygarPlayerInflatedState(const FygarPlayerInflatedState& other) = delete;
		FygarPlayerInflatedState(FygarPlayerInflatedState&& other) = delete;
		FygarPlayerInflatedState& operator=(const FygarPlayerInflatedState& other) = delete;
		FygarPlayerInflatedState& operator=(FygarPlayerInflatedState&& other) = delete;

		FygarPlayerState* Update(FygarPlayerController& fygar, const double deltaTime) override;
		void OnEnter(FygarPlayerController& fygar) override;
		void OnExit(FygarPlayerController& fygar) override;
		void HandleInput(FygarPlayerController&, Command*) override {};
	private:
		int m_CurrentInflationState{};
		const float m_TimeToDeflate{ 2.f };
		float m_DeflationTimer{};
		float m_DeathTimer{ .1f };
	};

	class FygarPlayerFlattenedState final : public FygarPlayerState
	{
	public:
		FygarPlayerFlattenedState() = default;
		~FygarPlayerFlattenedState() = default;
		FygarPlayerFlattenedState(const FygarPlayerFlattenedState& other) = delete;
		FygarPlayerFlattenedState(FygarPlayerFlattenedState&& other) = delete;
		FygarPlayerFlattenedState& operator=(const FygarPlayerFlattenedState& other) = delete;
		FygarPlayerFlattenedState& operator=(FygarPlayerFlattenedState&& other) = delete;

		FygarPlayerState* Update(FygarPlayerController& fygar, const double deltaTime) override;
		void OnEnter(FygarPlayerController& fygar) override;
		void OnExit(FygarPlayerController& fygar) override;
		void HandleInput(FygarPlayerController&, Command*) override {};
	private:
		float m_DeathTimer{ .1f };
	};

	class FygarPlayerFireBreathingState final : public FygarPlayerState
	{
	public:
		FygarPlayerFireBreathingState() = default;
		~FygarPlayerFireBreathingState() = default;
		FygarPlayerFireBreathingState(const FygarPlayerFireBreathingState& other) = delete;
		FygarPlayerFireBreathingState(FygarPlayerFireBreathingState&& other) = delete;
		FygarPlayerFireBreathingState& operator=(const FygarPlayerFireBreathingState& other) = delete;
		FygarPlayerFireBreathingState& operator=(FygarPlayerFireBreathingState&& other) = delete;

		FygarPlayerState* Update(FygarPlayerController& fygar, const double deltaTime) override;
		void OnEnter(FygarPlayerController& fygar) override;
		void OnExit(FygarPlayerController& fygar) override;
		void HandleInput(FygarPlayerController&, Command*) override {};
	private:
		float m_BreathTime{ .5f };
	};
}
#endif // !FYGARPLAYER

