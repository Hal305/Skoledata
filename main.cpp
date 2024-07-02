#define CURL_STATICLIB
#include "URLTester.h"


int main(int argc, char* argv[])
{    
    //Call both global init and cleanup exactly once, before and after using libcurl, respectively
    curl_global_init(CURL_GLOBAL_ALL);
    if(!argv[1])
        URLTester urlTester("url.txt", "results.txt", 500);
    else
    {
        if (argc == 4)
        {
            std::string inputFile = argv[1], outputFile = argv[2], sleepTimer = argv[3];
            std::cout << inputFile << " " << outputFile << " " << sleepTimer << "\n";
            URLTester urlTester(inputFile, outputFile, stoi(sleepTimer));
        }
        else
            std::cout << "Invalid number of arguments. You entered " << argc << ". Please enter 4.\n";
    }

    curl_global_cleanup();
	return 0;
}