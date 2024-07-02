#define CURL_STATICLIB
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <Windows.h>

const std::string dataFile = "url.txt";
const std::string results = "results.txt";

void readAndWriteURLFile(std::string dataFile)
{
    std::ifstream in;
    std::ofstream out;
    std::string url;

    in.open(dataFile.c_str());
    out.open(results.c_str());

    if (in.is_open())
    {
        struct curl_header* type;
        int num = 0;
        in >> num;
        CURLcode res;

        for (int i = 0; i<num; i++)
        {
            if (i != 0)
                Sleep(1000);
            CURL* curl = curl_easy_init();
            in >> url;
                
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            //std::cout << url << "\n";
            curl_easy_setopt(curl, CURLOPT_HEADER, 0);
            curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
            res = curl_easy_perform(curl);


            long responseCode = 0;

            if (res == CURLE_OK)
            {
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
                if (responseCode == 404)
                    std::cout << i << " \n" << responseCode << ": " << url << " not found\n";
            }
            else
            {
                std::cout << i << " \n" << url << "\n";
                i--;
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            }

            out << url << ": " << responseCode << "\n";

            curl_easy_cleanup(curl);
        }
    }
    in.close();
    out.close();
}

int main(void)
{

    curl_global_init(CURL_GLOBAL_ALL);
    readAndWriteURLFile(dataFile);
    curl_global_cleanup();
	return 0;
}