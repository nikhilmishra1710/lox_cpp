#include <bits/stdc++.h>
using namespace std;

class Token
{
public:
    string type;
    string lexeme;
    int line;
    string literal;
    string error;
    bool valid;

    Token(string type, string lexeme, int line, string literal = "null")
    {
        this->type = type;
        this->lexeme = lexeme;
        this->line = line;
        this->literal = literal;
        this->valid = true;
    }

    Token(string error, int line)
    {
        this->error = error;
        this->line = line;
        this->valid = false;
    }

    friend std::ostream &operator<<(std::ostream &out, const Token &token)
    {
        if (token.valid)
        {
            out << token.type << " " << token.lexeme << " " << token.literal << endl;
            return out;
        }
        else
        {
            out << "[line " << token.line  << "] " << token.error << endl;
        return out;
        }
    }
};


bool isChar(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isDigit(char c){
    return c >= '0' && c <= '9';
}

bool isUnderScore(char c){
    return c == '_';
}

vector<Token> generate_tokens(const string &file_contents)
{
    vector<Token> tokens;
    int line_number = 1;
    string type, lexeme, literal;
    stringstream converter;
    float temp;
    for (int i = 0; i < file_contents.length(); i++)
    {
        // cout<<file_contents[i]<<endl;
        lexeme = "", literal = "";
        switch (file_contents[i])
        {
        case '(':
            /* code */
            tokens.push_back(Token("LEFT_PAREN", "(", line_number));
            break;
        case ')':
            tokens.push_back(Token("RIGHT_PAREN", ")", line_number));
            break;
        case '{':
            tokens.push_back(Token("LEFT_BRACE", "{", line_number));
            break;
        case '}':
            tokens.push_back(Token("RIGHT_BRACE", "}", line_number));
            break;
        case ',':
            tokens.push_back(Token("COMMA", ",", line_number));
            break;
        case '.':
            tokens.push_back(Token("DOT", ".", line_number));
            break;
        case '+':
            tokens.push_back(Token("PLUS", "+", line_number));
            break;
        case '-':
            tokens.push_back(Token("MINUS", "-", line_number));
            break;
        case ';':
            tokens.push_back(Token("SEMICOLON", ";", line_number));
            break;
        case '*':
            tokens.push_back(Token("STAR", "*", line_number));
            break;
        case '=':
            if (file_contents[i + 1] == '=')
            {
                tokens.push_back(Token("EQUAL_EQUAL", "==", line_number));
                i++;
            }
            else
            {
                tokens.push_back(Token("EQUAL", "=", line_number));
            }
            break;
        case '!':
            if (file_contents[i + 1] == '=')
            {
                tokens.push_back(Token("BANG_EQUAL", "!=", line_number));
                i++;
            }
            else
            {
                tokens.push_back(Token("BANG", "!", line_number));
            }
            break;
        case '<':
            if (file_contents[i + 1] == '=')
            {
                tokens.push_back(Token("LESS_EQUAL", "<=", line_number));
                i++;
            }
            else
            {
                tokens.push_back(Token("LESS", "<", line_number));
            }
            break;
        case '>':
            if (file_contents[i + 1] == '=')
            {
                tokens.push_back(Token("GREATER_EQUAL", ">=", line_number));
                i++;
            }
            else
            {
                tokens.push_back(Token("GREATER", ">", line_number));
            }
            break;
        case '/':
            if (file_contents[i + 1] == '/')
            {
                while (i+1 < file_contents.length() && file_contents[i] != '\n')
                {
                    i++;
                }
                line_number++;
            }
            else
            {
                tokens.push_back(Token("SLASH", "/", line_number));
            }
            break;
        case '"':
            i++;
            // literal += "\"";
            while (i < file_contents.length() && file_contents[i] != '"')
            {
                literal += file_contents[i];
                i++;
            }
            if (file_contents[i] != '"' && i == file_contents.length())
            {
                tokens.push_back(Token("Error: Unterminated string.", line_number));
                break;
            }
            lexeme += "\"" + literal + "\"";
            tokens.push_back(Token("STRING", lexeme, line_number, literal));
            break;
        case '0' ... '9':
            while (i < file_contents.length() && isdigit(file_contents[i]))
            {
                lexeme += file_contents[i];
                i++;
            }
            if (file_contents[i] == '.' && isdigit(file_contents[i + 1]))
            {
                lexeme += file_contents[i];
                i++;
                while (i < file_contents.length() && isdigit(file_contents[i]))
                {
                    lexeme += file_contents[i];
                    i++;
                }
                
                temp = stod(lexeme);
                if(temp==static_cast<int>(temp))
                {
                    // cout<<"temp: "<<temp << " " << to_string(temp) <<endl;
                    literal = to_string(static_cast<int>(temp)) + ".0";
                }
                else{
                    literal =lexeme;
                }
                // cout<< "Lexeme: "<<lexeme << " Literal number: " << literal<<endl;
            }else{
                literal = lexeme + ".0";
            }
            
            
            tokens.push_back(Token("NUMBER", lexeme, line_number, literal));
            // cout<<file_contents[i]<<" "<<i<<endl;
            i--;
            break;
        case '\n':
            line_number++;
            break;
        case ' ':
            break;
        case '\t':
            break;
        default:
            if(isChar(file_contents[i]) || isUnderScore(file_contents[i])){
                while (i < file_contents.length() && (isChar(file_contents[i]) || isDigit(file_contents[i]) || isUnderScore(file_contents[i])))
                {
                    lexeme += file_contents[i];
                    i++;
                }
                i--;
                if (lexeme == "and")
                {
                    tokens.push_back(Token("AND", lexeme, line_number));
                }
                else if (lexeme == "class")
                {
                    tokens.push_back(Token("CLASS", lexeme, line_number));
                }
                else if (lexeme == "else")
                {
                    tokens.push_back(Token("ELSE", lexeme, line_number));
                }
                else if (lexeme == "false")
                {
                    tokens.push_back(Token("FALSE", lexeme, line_number));
                }
                else if (lexeme == "for")
                {
                    tokens.push_back(Token("FOR", lexeme, line_number));
                }
                else if (lexeme == "fun")
                {
                    tokens.push_back(Token("FUN", lexeme, line_number));
                }
                else if (lexeme == "if")
                {
                    tokens.push_back(Token("IF", lexeme, line_number));
                }
                else if (lexeme == "nil")
                {
                    tokens.push_back(Token("NIL", lexeme, line_number));
                }
                else if (lexeme == "or")
                {
                    tokens.push_back(Token("OR", lexeme, line_number));
                }
                else if (lexeme == "print")
                {
                    tokens.push_back(Token("PRINT", lexeme, line_number));
                }
                else if (lexeme == "return")
                {
                    tokens.push_back(Token("RETURN", lexeme, line_number));
                }
                else if (lexeme == "super")
                {
                    tokens.push_back(Token("SUPER", lexeme, line_number));
                }
                else if (lexeme == "this")
                {
                    tokens.push_back(Token("THIS", lexeme, line_number));
                }
                else if (lexeme == "true")
                {
                    tokens.push_back(Token("TRUE", lexeme, line_number));
                }
                else if (lexeme == "var")
                {
                    tokens.push_back(Token("VAR", lexeme, line_number));
                }
                else if (lexeme == "while")
                {
                    tokens.push_back(Token("WHILE", lexeme, line_number));
                }else{
                    tokens.push_back(Token("IDENTIFIER", lexeme, line_number));
                }
            }else{
                lexeme += file_contents[i];
                tokens.push_back(Token("Error: Unexpected character: " + lexeme, line_number));
            }
            // lexeme += "Error: Unexpected character: " + string(1,file_contents[i]);
            // cout<<lexeme<<endl;
            // // sprintf(lexeme, "Error: Unexpected character: %c",file_contents[i]);
            // tokens.push_back(Token(lexeme, line_number ));
            break;
        }
    }

    tokens.push_back(Token("EOF", "", line_number));
    return tokens;
}
