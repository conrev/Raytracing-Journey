#include "app.h"

int main()
{
    std::string app_title = "Raytracing Journey";
    std::unique_ptr<app> running_app = std::make_unique<app>(app_title, 1920, 1080);
    running_app->run();
    return 0;
}
