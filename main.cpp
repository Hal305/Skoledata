#define CURL_STATICLIB
#include "URLTester.h"


int main(void)
{
    //Call both global init and cleanup exactly once, before and after using libcurl, respectively
    curl_global_init(CURL_GLOBAL_ALL);
    URLTester urlTester("url.txt", "results.txt", 500);
    curl_global_cleanup();
	return 0;
}