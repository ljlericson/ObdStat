#include "ObdStat/ObdStat.hpp"

int main(int argc, char** argv) 
{
    try
    {
        ljl::ObdStat* app = new ljl::ObdStat{argc, argv};
        app->run();
        delete app;
    }
    catch(const std::exception& e)
    {
        std::cerr << "=======| OBDSTAT EXCEPTION OCCURED |========\\nn" << e.what() << '\n';
    }
    
    
}