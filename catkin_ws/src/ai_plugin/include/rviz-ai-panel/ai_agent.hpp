#ifndef AI_AGENT_HPP
#define AI_AGENT_HPP

#include <string>

class AiAgent {
public:
    AiAgent(const std::string& api_key);
    std::string getResponse(const std::string& prompt);
private:
    std::string api_key_;
};

#endif // AI_AGENT_HPP