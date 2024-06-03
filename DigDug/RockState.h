#ifndef ROCKSTATE
#define ROCKSTATE
#include "RockBehavior.h"
namespace dae
{
	class RockState
	{
	public:
		RockState() = default;
		virtual ~RockState() = default;
		RockState(const RockState& other) = delete;
		RockState(RockState&& other) = delete;
		RockState& operator=(const RockState& other) = delete;
		RockState& operator=(RockState&& other) = delete;

		virtual RockState* Update(RockBehavior&, const double) { return nullptr; }

		virtual void OnEnter(RockBehavior&) = 0;
		virtual void OnExit(RockBehavior&) = 0;
	};

	class RockIdleState final : public RockState
	{
	public:
		RockIdleState() = default;
		virtual ~RockIdleState() = default;
		RockIdleState(const RockIdleState& other) = delete;
		RockIdleState(RockIdleState&& other) = delete;
		RockIdleState& operator=(const RockIdleState& other) = delete;
		RockIdleState& operator=(RockIdleState&& other) = delete;

		RockState* Update(RockBehavior& rock, const double deltaTime) override;

		void OnEnter(RockBehavior& rock) override;
		void OnExit(RockBehavior& rock) override;
	};

	class RockFallingState final : public RockState
	{
	public:
		RockFallingState() = default;
		virtual ~RockFallingState() = default;
		RockFallingState(const RockFallingState& other) = delete;
		RockFallingState(RockFallingState&& other) = delete;
		RockFallingState& operator=(const RockFallingState& other) = delete;
		RockFallingState& operator=(RockFallingState&& other) = delete;

		RockState* Update(RockBehavior& rock, const double deltaTime) override;

		void OnEnter(RockBehavior& rock) override;
		void OnExit(RockBehavior& rock) override;
	};

	class RockBreakState final : public RockState
	{
	public:
		RockBreakState() = default;
		virtual ~RockBreakState() = default;
		RockBreakState(const RockBreakState& other) = delete;
		RockBreakState(RockBreakState&& other) = delete;
		RockBreakState& operator=(const RockBreakState& other) = delete;
		RockBreakState& operator=(RockBreakState&& other) = delete;

		RockState* Update(RockBehavior& rock, const double deltaTime) override;

		void OnEnter(RockBehavior& rock) override;
		void OnExit(RockBehavior& rock) override;
	};
}
#endif // !ROCKSTATE