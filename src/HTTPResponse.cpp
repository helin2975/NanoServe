#include "HTTPResponse.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Helper function to tell the browser what kind of file we are sending
string HTTPResponse::determineContentType(const string& filePath) {
    if (filePath.find(".css") != string::npos) {
        return "text/css";
    }

    if (filePath.find(".json") != string::npos) {
        return "application/json";
    }

    if (filePath.find(".png") != string::npos) {
        return "image/png";
    }

    return "text/htmtl";
}

string HTTPResponse::buildResponse(const string& uri) {
    // 1. ROUTING LOGIC
    string filePath = "public" + uri;

    // If user just type localhost:8080/, default to index.html
    if (uri == "/") {
        filePath = "public/index.html";
    }

    // 2. READ THE FILE

    // Opens in binary mode so that images & non-text files are handled correctly
    ifstream file(filePath , ios::in | ios::binary);
    string body;
    string status_line;

    if (file.is_open()) {
        // File exists! Read the entire thing into our 'body' string
        ostringstream file_contents;
        file_contents << file.rdbuf();

        body = file_contents.str();

        status_line = "HTTP/1.1 200 OK\r\n";

        file.close();
        cout << "[INFO] Successfully loaded: " << filePath << "\n";
    }
    else {
        // File not found! Trigger a 404 Error
        cout << "[WARNING] File not found: " << filePath << "\n";
        status_line = "HTTP/1.1 404 Not Found\r\n";
        body = "<html><body><h1>404 - File Not Found</h1></body></html>";

        // Try to load a custom 404 file if it exists
        ifstream error_file("public/404.html");

        if (error_file.is_open()) {
            std::ostringstream error_contents;
            error_contents << error_file.rdbuf();

            body = error_contents.str();

            error_file.close();
        }
    }

    // 3. FORMAT THE FINAL HTTP STRING
    string content_type = "Content-Type: " + determineContentType(filePath) + "\r\n";
    string content_length = "Content-Length: " + std::to_string(body.size()) + "\r\n"; 

    string full_response = status_line + content_type + content_length + "\r\n" + body;

    return full_response;
}