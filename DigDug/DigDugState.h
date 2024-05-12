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

		virtual void OnEnter(DigDugController&) {};
		virtual void OnExit(DigDugController& pooka) {};
	};
}
#endif //DIGDUGSTATE