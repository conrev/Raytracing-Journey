#include "app.h"

int main()
{
    std::string app_title = "Raytracing Journey";
    app *running_app = new app(app_title, 1920, 1080);
    running_app->run();
    return 0;
}
