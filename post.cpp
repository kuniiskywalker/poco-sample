#include <string>
#include <iostream>
#include <sstream>
#include <Poco/URI.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Parser.h>
#include <Poco/StreamCopier.h>
// #include "Poco/Net/Context.h"
// #include "Poco/Net/SSLManager.h"
// #include "Poco/Net/AcceptCertificateHandler.h"
using namespace std;

using namespace Poco::Net;
using namespace Poco;

string ofPostRequest(string url, string body, map<string,string> headers) {
    try
    {
        // prepare session
        URI uri(url);
        HTTPClientSession session(uri.getHost(), uri.getPort());

        // prepare path
        string path(uri.getPathAndQuery());
        if (path.empty()) path = "/";

        // send request
        HTTPRequest req(HTTPRequest::HTTP_POST, path, HTTPMessage::HTTP_1_1);
        req.setContentType("application/x-www-form-urlencoded");

        // Set headers here
        for(map<string,string>::iterator it = headers.begin();
            it != headers.end(); it++) {
            req.set(it->first, it->second);
        }

        // Set the request body
        req.setContentLength( body.length() );

        // sends request, returns open stream
        std::ostream& os = session.sendRequest(req);
        os << body;  // sends the body
        //req.write(std::cout); // print out request

        // get response
        HTTPResponse res;
        cout << res.getStatus() << " " << res.getReason() << endl;

        istream &is = session.receiveResponse(res);
        stringstream ss;
        StreamCopier::copyStream(is, ss);

        return ss.str();
    }
    catch (Exception &ex)
    {
        cerr << ex.displayText() << endl;
        return "";
    }
}

int main(int argc, char **argv)
{
    int i;

    // printf("文字列の個数 %d\n",argc);
    // for(i=0;i<argc;i++)
    //   printf("%d 番目の文字列 %s\n",i,argv[i]);

    string id   = argv[1];
    string name = argv[2];

    string body = "{ \"id\":" + id + ", \"name\": \"" + name + "\" }";

    cout << body << endl;

    map<string,string> headers;
    headers["Content-Type"] = "application/json";
    ofPostRequest("http://host.docker.internal:3000/movies", body, headers);
}
