#include "log.h"

int main(int argc, char* argv[])
{
    try
    {
        Log::ReportingLevel() = Log::FromString("DEBUG");
		
		LOG(DEBUG) << "this is a debug ";
		LOG(INFO) << "this is a info ";
		LOG(ERROR) << "this is a error ";
		
        return 0;
    }
    catch(const std::exception& e)
    {
        LOG(ERROR) << e.what();
    }
    return -1;
}
