#include "ObdStat/ObdStat.hpp"

int main() 
{
    ljl::ObdStat* app = new ljl::ObdStat{};
    app->run();
    delete app;
}