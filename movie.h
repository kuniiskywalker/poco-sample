#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <Poco/JSON/Parser.h>

class Movie{
public:
    Poco::JSON::Object::Ptr get(std::string endpoint);
    std::string post(std::string url, std::string body, std::map<std::string, std::string> headers);
};

#endif // _MOVIE_H_