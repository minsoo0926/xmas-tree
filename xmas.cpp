#include <iostream>
// #include <unistd.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h> // ioctl()
    #include <unistd.h>    // STDOUT_FILENO
#endif
#define HEIGHT 7
#define WIDTH 4
#define INTERVAL 1
#define GAP 4

using namespace std;

struct TerminalSize {
    int rows;
    int cols;
};

TerminalSize getTerminalSize() {
    int rows = 0;
    int cols = 0;

#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != -1) {
        cols = w.ws_col;
        rows = w.ws_row;
    }
#endif
    return {rows, cols};
}

int main() {
    int count = 0;
    int MARGIN = getTerminalSize().cols / 2 - 2 * WIDTH - HEIGHT;
    
    while (++count) {
        cout.flush();
        system("clear");
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                cout << string(MARGIN, ' ');
                for (int k = 0; k < (HEIGHT - i - j) + WIDTH; ++k) {
                    cout << " ";
                }
                for (int k = 0; k < 2 * (i + j) + 1; ++k) {
                    if (k % GAP == 1 and (count + j + k / 2) % 3 == 0) {
                        cout << "\033[31m●\033[0m";
                    } else if (k % GAP == 1 and (count + j + k / 2) % 3 != 0) {
                        cout << "\033[31m○\033[0m";
                    } else {
                        cout << "\033[32m@\033[0m";
                    }
                }
                cout << endl;
            }
        }
        for (int i = 0; i < HEIGHT; ++i) {
            cout << string(MARGIN + HEIGHT + WIDTH - 2, ' ') << "\033[33m|   |\033[0m" << endl;
        }

        cout << endl << string(MARGIN + WIDTH, ' ') << "Merry Christmas!" << endl;
        #ifdef _WIN32
            Sleep(INTERVAL * 1000);
        #else
            usleep(1e6 * INTERVAL);
        #endif
    }
    return 0;
}