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

		virtual DigDugState* Update(DigDugController&, const double deltaTime) { return nullptr; }

		virtual void OnEnter(DigDugController& digDug) {};
		virtual void OnExit(DigDugController& digDug) {};
		virtual void HandleInput(DigDugController& digDug) {};
	};

	class NormalState : public DigDugState
	{
		NormalState() = default;
		virtual ~NormalState() = default;
		NormalState(const NormalState& other) = delete;
		NormalState(NormalState&& other) = delete;
		NormalState& operator=(const NormalState& other) = delete;
		NormalState& operator=(NormalState&& other) = delete;

		NormalState* Update(DigDugController&, const double deltaTime);

		void OnEnter(DigDugController&);
		void OnExit(DigDugController& digDug);
		void HandleInput(DigDugController& digDug);
	};
}
#endif //DIGDUGSTATE