#ifndef GAME_HPP
#define GAME_HPP

const int fps = 60;

namespace Playground {
    class Game {
      public:
        bool running;

        Game() : running(true) {
        }

        int run();
    };
} // namespace Playground

#endif
