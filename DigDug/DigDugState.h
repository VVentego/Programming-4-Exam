#ifndef DIGDUGSTATE
#define DIGDUGSTATE
#include "DigDugController.h"
namespace dae
{
	class DigDugState
	{
	public:
		DigDugState() = default;
		virtual ~DigDugState() = default;
		DigDugState(const DigDugState& other) = delete;
		DigDugState(DigDugState&& other) = delete;
		DigDugState& operator=(const DigDugState& other) = delete;
		DigDugState& operator=(DigDugState&& other) = delete;

		virtual DigDugState* Update(DigDugController&, const double) { return nullptr; }

		virtual void OnEnter(DigDugController&) = 0;
		virtual void OnExit(DigDugController&) = 0;
		virtual void HandleInput(DigDugController&, Command*) = 0;
		virtual void HandleCollision(DigDugController&, GameObject*) = 0;
	};

	class DigDugNormalState final : public DigDugState
	{
	public:
		DigDugNormalState() = default;
		~DigDugNormalState() = default;
		DigDugNormalState(const DigDugNormalState& other) = delete;
		DigDugNormalState(DigDugNormalState&& other) = delete;
		DigDugNormalState& operator=(const DigDugNormalState& other) = delete;
		DigDugNormalState& operator=(DigDugNormalState&& other) = delete;

		DigDugState* Update(DigDugController&, const double deltaTime) override;

		void OnEnter(DigDugController& digDug) override;
		void OnExit(DigDugController& digDug) override;
		void HandleInput(DigDugController& digDug, Command* command) override;
		virtual void HandleCollision(DigDugController& digDug, GameObject* other) override;

	private:
		bool m_Dead{};
		float m_InvulnerabilityTimer{ 1.f };
	};

	class DigDugDigState final : public DigDugState
	{
	public:
		DigDugDigState() = default;
		~DigDugDigState() = default;
		DigDugDigState(const DigDugDigState& other) = delete;
		DigDugDigState(DigDugDigState&& other) = delete;
		DigDugDigState& operator=(const DigDugDigState& other) = delete;
		DigDugDigState& operator=(DigDugDigState&& other) = delete;

		DigDugState* Update(DigDugController&, const double deltaTime) override;

		void OnEnter(DigDugController& digDug) override;
		void OnExit(DigDugController& digDug) override;
		void HandleInput(DigDugController& digDug, Command* command) override;
		virtual void HandleCollision(DigDugController& digDug, GameObject* other) override;

	private:
		bool m_Dead{};
	};

	class DigDugDeathState final : public DigDugState
	{
	public:
		DigDugDeathState() = default;
		~DigDugDeathState() = default;
		DigDugDeathState(const DigDugDeathState& other) = delete;
		DigDugDeathState(DigDugDeathState&& other) = delete;
		DigDugDeathState& operator=(const DigDugDeathState& other) = delete;
		DigDugDeathState& operator=(DigDugDeathState&& other) = delete;

		DigDugState* Update(DigDugController&, const double deltaTime) override;

		void OnEnter(DigDugController&) override;
		void OnExit(DigDugController& digDug) override;
		void HandleInput(DigDugController&, Command*) override {};
		void HandleCollision(DigDugController&, GameObject*) override {};
	private:
		float m_DeathTimer{ 2.f };
	};
}
#endif //DIGDUGSTATE