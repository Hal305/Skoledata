#define CURL_STATICLIB
#include <iostream>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include <Windows.h>

const std::string dataFile = "url.txt";
const std::string results = "results.txt";

void readAndWriteURLFile()
{
    std::ifstream in;
    std::ofstream out;
    std::string url;

    in.open(dataFile.c_str());
    out.open(results.c_str());

    if (in.is_open())
    {
        //Start the count on 1 to match the line numbers
        int num = 1;
        CURLcode res;

        //Do while loop ensures that the file's first line is read
        do
        {
            //Pauses and breaks up requests to avoid spamming the server
            if (num > 1)
                Sleep(500);

            //Init for every iteration
            CURL* curl = curl_easy_init();
            //Reads url from current line and redeclares URL string
            in >> url;
            //std::cout << url << "\n";
            //Triggers at the end of the file
            if (url.empty())
                break;

            //curl options setup. Fetches header data without retrieving the body
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HEADER, 0);
            curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
            res = curl_easy_perform(curl);

            long responseCode = 0;

            // Checks URL validity
            if (res == CURLE_OK)
            {
                // Checks for response code, 200 for success, 404 for not found
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
                if (responseCode == 404) //Prints out error responses
                    std::cout << num << " \n" << responseCode << ": " << url << " not found\n";
                out << url << ": " << responseCode << "\n";
            }
            else
            {
                std::cout << num << " \n" << url << "\n";
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
                out << "Invalid URL: " << url << "\n";
            }

            //Clean up every time
            curl_easy_cleanup(curl);
            //Increment number at the end
            num++;
        }//getline iterates through input file, moving to the next line on line breaks or blank spaces
        while (std::getline(in, url));
    }
    //Close files once they're done being used
    in.close();
    out.close();
}

int main(void)
{
    //Call both global init and cleanup exactly once, before and after using libcurl, respectively
    curl_global_init(CURL_GLOBAL_ALL);
    readAndWriteURLFile();
    curl_global_cleanup();
	return 0;
}