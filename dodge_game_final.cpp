#include "rlutil.h"
#include <iostream>
#include <vector>
#include <ctime>

struct Obstacle {
    int x, y;
};

int main() {
    srand(time(NULL));

    rlutil::saveDefaultColor();
    rlutil::hidecursor();
    
    int width = rlutil::tcols();
    int height = rlutil::trows();
    
    int px = 5, py = height / 2;
    std::vector<Obstacle> obs;
    int score = 0;

    rlutil::cls();

    while (true) {
        if (kbhit()) {
            rlutil::locate(px, py);
            std::cout << " ";
            
            char k = getch();
            if ((k == 'w' || k == 'W') && py > 1) py--;
            if ((k == 's' || k == 'S') && py < height - 1) py++;
            if (k == 27) break; 
        }

        if (rand() % 10 == 0) {
            obs.push_back({width, (rand() % (height - 1)) + 1});
        }

        for (int i = 0; i < (int)obs.size(); i++) {
            rlutil::locate(obs[i].x, obs[i].y);
            std::cout << " ";

            obs[i].x--;

            if (obs[i].x == px && obs[i].y == py) {
                rlutil::cls();
                rlutil::locate(width / 2 - 5, height / 2);
                rlutil::setColor(rlutil::RED);
                std::cout << "GAME OVER! Score: " << score << std::endl;
                rlutil::anykey();
                goto end;
            }

            if (obs[i].x > 1) {
                rlutil::locate(obs[i].x, obs[i].y);
                rlutil::setColor(rlutil::LIGHTRED);
                std::cout << "#";
            } else {
                obs.erase(obs.begin() + i);
                score++;
                i--; 
            }
        }

        rlutil::locate(px, py);
        rlutil::setColor(rlutil::CYAN);
        std::cout << "@";

        rlutil::locate(1, 1);
        rlutil::setColor(rlutil::YELLOW);
        std::cout << "Score: " << score;

        rlutil::msleep(50);
    }

end:
    rlutil::showcursor();
    rlutil::resetColor();
    rlutil::cls();
    return 0;
}
