
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <playground.h>
#include <playground_backend_glfw.h>

#include "game.h"
#include "../tests/test_ascii.h"
#include "../tests/test_button.h"
#include "../tests/test_counter.h"

#define WIDTH 100
#define HEIGHT 50

int main(int argc, char* argv[])
{
    GLFWwindow* window;
    pg_backend_glfw_helper_init(&window, "Clicker", pg_config_simple(WIDTH, HEIGHT, "assets/DB_curses_12x12.png"));

    int testIndex = 0;

    Game game = {0};
    game_init(&game, WIDTH, HEIGHT);

    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        pg_backend_glfw_poll_events();
        pg_clear_all();

        switch (testIndex)
        {
            case 1: test_button_update(); break;
            case 2: test_counter_update(); break;
            case 3: test(); break;
            // Add other tests here
 
            default: game_update(&game);
        };


        pg_render();
        glfwSwapBuffers(window);
    }
    
    game_shutdown(&game);
    pg_shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
