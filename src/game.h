#ifndef GUEMUD_GAME_H_
#define GUEMUD_GAME_H_

namespace guemud {
  class Game {
    public:
      Game();
      void ExecuteLoop();
      bool IsRunning();
    private:
      bool is_running_;
  };
}

#endif
