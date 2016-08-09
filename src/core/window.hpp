/**
 *    > Author:   UncP
 *    > Mail:     770778010@qq.com
 *    > Github:   https://www.github.com/UncP/Mini_Ray_Tracer
 *    > Description:
 *
 *    > Created Time: 2016-06-24 15:48:13
**/

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <png.h>
#include <fstream>
#include <chrono>

#include "scene.hpp"
#include "../math/ray.hpp"
#include "camera.hpp"
#include "pathTracer.hpp"

class Window
{
	public:
		Window() = default;
		Window(const std::string &title, const int width, const int height)
			:title_(title), width_(width), height_(height), pixels_(new Vector3d[width_ * height_]) {
			if (!pixels_) {
				std::cerr << "颜色初始化失败 :(\n";
				exit(-1);
			}

			if (SDL_Init(SDL_INIT_VIDEO)) {
				std::cerr << "SDL_Init failed :(\n";
				exit(-1);
			}

			screen_ = SDL_SetVideoMode(width_, height_, 32, SDL_SWSURFACE);
			if (!screen_) {
				SDL_Quit();
				std::cerr << "SDL_SetVideoMode failed :(\n";
				exit(-1);
			}
			canvas_ = static_cast<uint32_t *>(screen_->pixels);

			SDL_WM_SetCaption(title_.c_str(), NULL);
		}

		void render(const Scene &, const int &);

		void show() const;
		void save_ppm() const;
		bool save_png() const;

		Window& operator=(const Window &) = delete;

		~Window() { delete [] pixels_; }

	private:
		std::string  title_;
		int 				 width_;
		int					 height_;
		Vector3d		*pixels_;
		uint32_t		*canvas_;
		SDL_Surface *screen_;
};

#endif /* _WINDOW_H_ */