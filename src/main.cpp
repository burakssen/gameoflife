#include <iostream>

#include "App/App.h"

int main()
{
    App &app = App::GetInstance();
    app.Init();
    app.Run();
    return EXIT_SUCCESS;
}