//
// Created by ICTxi on 2019/8/16.
//

#include <fstream>
#include <iostream>
#include "configure.h"


configure::configure(std::string file): _file(std::move(file)) {
    this->_read_file();
    this->_tokenize();
    for(auto &t: this->_token_list) {
        std::cout << "[Token] text=" << t.text << "  type=" << t.type << std::endl;
    }
}

void configure::_read_file() {
    std::ifstream fs;
    fs.open(this->_file, std::ifstream::in);
    fs.seekg(0, std::ifstream::end);
    int length = fs.tellg();
    fs.seekg(0, std::ifstream::beg);
    std::vector<char> buffer;
    buffer.reserve(length);
    buffer.resize(length);
    fs.read(buffer.data(), length);
    this->_file_content = buffer.data();
    fs.close();
}

void configure::_tokenize() {
    this->_token_list.clear();
    int state = 0;
    int line = 0;
    char string_edge = '\"';
    std::string token_text;
    for (int i = 0; i < this->_file_content.length(); ++i) {
        char c = this->_file_content[i];
        switch (state) {
            case 0:
                if ('0' <= c && c <= '9') {
                    token_text += c;
                    state = 1;
                } else if (c == '_' || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
                    token_text += c;
                    state = 3;
                } else if (c == '\'' || c == '\"') {
                    string_edge = c;
                    state = 4;
                } else if (c == '#') {
                    state = 6;
                } else if (this->_mark_type.count(c)) {
                    token_text += c;
                    token t{token_text, this->_mark_type[c]};
                    this->_token_list.push_back(t);
                    token_text = "";
                } else if (c == '\n') {
                    line++;
                    continue;
                } else if (c == ' ' || c == '\t' || c == '\r') {
                    continue;
                } else {
                    // error
                    break;
                }
                continue;
            case 1:
                if (c == '.') {
                    token_text += c;
                    state = 2;
                } else if ('0' <= c && c <= '9') {
                    token_text += c;
                } else {
                    token t{token_text, t_integer};
                    this->_token_list.push_back(t);
                    state = 0;
                    token_text = "";
                    i--;
                }
                continue;
            case 2:
                if ('0' <= c && c <= '9') {
                    token_text += c;
                } else {
                    token t{token_text, t_float};
                    this->_token_list.push_back(t);
                    state = 0;
                    token_text = "";
                    i--;
                }
                continue;
            case 3:
                if (c == '_' || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9')) {
                    token_text += c;
                } else {
                    token t{token_text, t_symbol};
                    this->_token_list.push_back(t);
                    state = 0;
                    token_text = "";
                    i--;
                }
                continue;
            case 4:
                if (c == string_edge) {
                    token t{token_text, t_string};
                    this->_token_list.push_back(t);
                    state = 0;
                    token_text = "";
                } else if (c == '\\') {
                    state = 5;
                } else if (c == '\r' || c == '\n') {
                    // error
                    break;
                } else {
                    token_text += c;
                }
                continue;
            case 5:
                if (this->_escape.count(c)) {
                    token_text += this->_escape[c];
                } else if (c == '\r' || c == '\n') {
                    // error
                    break;
                } else {
                    token_text += c;
                }
                state = 4;
                continue;
            case 6:
                if (c == '\n') {
                    state = 0;
                }
                continue;
            default:
                break;
        }
    }
    if (state == 0) {
        // error handle
    }
}
