// ai_agent.cpp
#include "rviz-ai-panel/ai_agent.hpp"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>

AiAgent::AiAgent(const std::string& api_key) : api_key_(api_key) {}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

std::string AiAgent::getResponse(const std::string& prompt) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    if(curl) {
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + api_key_).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        nlohmann::json jsonData;
        jsonData["model"] = "gpt-4o-mini";
        jsonData["messages"] = nlohmann::json::array({
            { {"role", "user"}, {"content", prompt} }
        });
        jsonData["max_tokens"] = 1000;

        std::string jsonString = jsonData.dump();

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonString.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        if(res == CURLE_OK) {
            try {
                auto jsonResponse = nlohmann::json::parse(readBuffer);
                
                if(jsonResponse.contains("choices")) {
                    std::cout << jsonResponse["choices"][0]["message"]["content"] << std::endl;
                    return jsonResponse["choices"][0]["message"]["content"].get<std::string>();
                } else if(jsonResponse.contains("error")) {
                    std::cerr << "API Error: " << jsonResponse["error"]["message"] << std::endl;
                    return "Error from API: " + jsonResponse["error"]["message"].get<std::string>();
                } else {
                    std::cerr << "Unexpected JSON Structure: " << readBuffer << std::endl;
                    return "Unexpected response structure.";
                }
            } catch (nlohmann::json::exception& e) {
                std::cerr << "JSON Parsing Error: " << e.what() << "\nResponse: " << readBuffer << std::endl;
                return "Error parsing response.";
            }
        } else {
            std::cerr << "cURL Error: " << curl_easy_strerror(res) << std::endl;
            return "Error performing request.";
        }
    }
    return "cURL initialization failed.";
}