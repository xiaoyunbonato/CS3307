// Xiaoyun Bonato
// Log Message class
// 4 October 2022

#include "log_message.h"
using namespace std;

log_message::log_message(string timestampParam, string messageParam)
{
    timestamp = timestampParam;
    message = messageParam;
}
log_message::~log_message()
{
}

string log_message::get_message()
{
    return message;
}
string log_message::get_timestamp()
{
    return timestamp;
}