//
// Created by ICTxi on 2019/8/16.
//

#ifndef LOONG_CONFIGURE_H
#define LOONG_CONFIGURE_H

#include <vector>
#include <unordered_map>


enum token_type {
    t_symbol,
    t_string,
    t_integer,
    t_float,
    t_assign,
    t_brace_l,
    t_brace_r,
};

struct token {
    std::string text;
    token_type type;
};

class configure {
public:
    explicit configure(std::string file);

private:
    std::string _file;
    std::string _file_content;
    std::vector<token> _token_list;
    void _read_file();
    void _tokenize();

    std::unordered_map<char, char> _escape = {
            {'a', '\a'},
            {'b', '\b'},
            {'f', '\f'},
            {'n', '\n'},
            {'r', '\r'},
            {'t', '\t'},
            {'v', '\v'},
            {'0', '\0'},
    };

    std::unordered_map<char, token_type> _mark_type = {
            {'=', t_assign},
            {'{', t_brace_l},
            {'}', t_brace_r},
    };
};


#endif //LOONG_CONFIGURE_H
