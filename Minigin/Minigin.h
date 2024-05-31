#ifndef MINIGIN
#define MINIGIN

#include <string>
#include <functional>

const int gWindowWidth{ 448 };
const int gWindowHeight{ 576 };

namespace dae
{
	struct Vector2
	{
		float x{};
		float y{};
	};

	class Minigin
	{
	public:
		explicit Minigin(const char* dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		const int GetMonitorRefreshRate();
		const int m_RefreshRate{ 60 };
	};
}
#endif // !MINIGIN