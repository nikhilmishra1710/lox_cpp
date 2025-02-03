#include <bits/stdc++.h>
#include "Tokeniser.hpp"
using namespace std;

string read_file_contents(const string &filename);

int main(int argc, char *argv[])
{
    // Disable output buffering
    cout << unitbuf;
    cerr << unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    // cerr << "Logs from your program will appear here!" << endl;
    int exit_code = 0;
    if (argc < 3)
    {
        cerr << "Usage: ./your_program tokenize <filename>" << endl;
        return 1;
    }

    const string command = argv[1];

    if (command == "tokenize")
    {
        string file_contents = read_file_contents(argv[2]);

        // Uncomment this block to pass the first stage

        if (!file_contents.empty())
        {
            vector<Token> tokens = generate_tokens(file_contents);
            for (const Token &token : tokens)
            {
                if (token.valid)
                {
                    cout << token;
                }
                else
                {
                    cerr << token;
                    exit_code = 65;
                }
            }
            // return 1;
        }
        else
        {
            cout << Token("EOF", "", 1);
        }
    }
    else
    {
        cerr << "Unknown command: " << command << endl;
        return 1;
    }

    return exit_code;
}

string read_file_contents(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error reading file: " << filename << endl;
        exit(1);
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
