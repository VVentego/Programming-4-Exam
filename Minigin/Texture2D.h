#ifndef TEXTURE2D
#define TEXTURE2D
#include <glm/vec2.hpp>
#include <memory>

struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		glm::ivec2 GetSize() const;

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* m_texture;
	};

	class SpriteSheet final
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit SpriteSheet(SDL_Texture* spriteSheet, const int rows, const int columns);
		~SpriteSheet() = default;

		SpriteSheet(const SpriteSheet&) = delete;
		SpriteSheet(SpriteSheet&&) = delete;
		SpriteSheet& operator= (const SpriteSheet&) = delete;
		SpriteSheet& operator= (const SpriteSheet&&) = delete;

		const int m_Rows{ 1 };
		const int m_Columns{ 1 };
	private:
		std::unique_ptr<Texture2D> m_SpriteSheet;
	};
}
#endif // !TEXTURE2D