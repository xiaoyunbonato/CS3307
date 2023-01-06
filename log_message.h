// Xiaoyun Bonato
// Log Message Header
// 4 October 2022

#include <string>

class log_message
{
private:
    std::string timestamp;
    std::string message;

public:
    log_message(std::string timestampParam, std::string messageParam);
    ~log_message();
    std::string get_message();
    std::string get_timestamp();
};