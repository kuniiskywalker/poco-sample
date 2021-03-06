#include "movie.h"

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char **argv)
{
    string id   = argv[1];
    string name = argv[2];

    string body = "{ \"id\":" + id + ", \"name\": \"" + name + "\" }";

    map<string,string> headers;
    headers["Content-Type"] = "application/json";
    Movie::post("http://host.docker.internal:3000/movies", body, headers);
}
