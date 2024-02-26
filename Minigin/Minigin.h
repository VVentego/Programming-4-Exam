#pragma once
#include <string>
#include <functional>

const int gWindowWidth{ 640 };
const int gWindowHeight{ 480 };

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
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);


		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
	};
}