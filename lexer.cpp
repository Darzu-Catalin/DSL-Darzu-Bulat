#include <bits/stdc++.h>

#include <regex>

using namespace std;

enum TokenType {
  //tokens and they're values as integer 
  INTEGER,//0
  DECIMAL,//1
  PLUS,//2
  INTDECALRE,//3
  DECDECLARE,//4
  MINUS,//5
  MULTIPLY,//6
  DIVIDE,//7
  LOOP,//8
  WHILE,//9
  IF,//10
  START,//11
  END,//12
  VARIABLE,//13
  TO,//14
  FROM,//15
  EQUALITY,//16
  LOGIC,//17
  ASSIGN_INT,//18
  ASSIGN_DEC,//19
  SPACE,//20
  STOP,//21
  PRINT,//22
  INVALID//23
};

struct Token {
  TokenType type;
  string value;
};

class Lexer {
  public: Lexer( string & input): input(input),
  pos(0) {

    tokenPatterns.push_back({
      EQUALITY,
      R"(==|!=|>|<|>=|<=)"
    });
    tokenPatterns.push_back({
      ASSIGN_DEC,
      ":=\\s*-?\\d+\\.\\d+"
    });

    tokenPatterns.push_back({
      DECIMAL,
      R"(-?\d+\.\d+)"
    }); 

    tokenPatterns.push_back({
      ASSIGN_INT,
      ":=\\s*-?\\d+"
    });
    tokenPatterns.push_back({
      INTEGER,
      R"(-?\d+)"
    });

    tokenPatterns.push_back({
      PLUS,
      "plus"
    });
    tokenPatterns.push_back({
      MINUS,
      "substract"
    });
    tokenPatterns.push_back({
      MULTIPLY,
      "multiply"
    });
    tokenPatterns.push_back({
      DIVIDE,
      "divide"
    });
    tokenPatterns.push_back({
      LOOP,
      "repeat"
    });
    tokenPatterns.push_back({
      WHILE,
      "while"
    });
    tokenPatterns.push_back({
      IF,
      "if"
    });
    tokenPatterns.push_back({
      START,
      "start"
    });
    tokenPatterns.push_back({
      END,
      "end"
    });
    tokenPatterns.push_back({
      TO,
      "to"
    });
    tokenPatterns.push_back({
      STOP,
      "exit"
    });
    tokenPatterns.push_back({
      FROM,
      "from"
    });
    tokenPatterns.push_back({
      DECDECLARE,
      "decNumber"
    });
    tokenPatterns.push_back({
      PRINT,
      "print"
    });
    tokenPatterns.push_back({
      INTDECALRE,
      "intNumber"
    });
    tokenPatterns.push_back({
      VARIABLE,
      R"([_a-zA-Z][_a-zA-Z0-9]*)"
    });
    tokenPatterns.push_back({
      LOGIC,
      R"(\[(-?[a-zA-Z0-9]+(?:\.\d+)?\s*(==|!=|>|<|>=|<=)\s*-?[a-zA-Z0-9]+(?:\.\d+)?)\])"
    });

    tokenPatterns.push_back({
      SPACE,
      "\\s+"
    });

    combinedPattern = "(";
    for (const auto & pattern: tokenPatterns) {
      if (pattern.first != SPACE) {
        combinedPattern += pattern.second + ")|(";
      }
    }
    combinedPattern.pop_back();
    combinedPattern += "(\\s+)";
    tokenRegex = regex(combinedPattern);
  }

  Token getNextToken() {
    if (pos >= input.size()) {
      return {
        END,
        ""
      };
    }
    smatch match;
    string remainder = input.substr(pos);
    if (regex_search(remainder, match, tokenRegex)) {
      for (size_t i = 1; i <= tokenPatterns.size(); i++) {
        if (match[i].length() > 0) {
          pos += match.position() + match.length();
          return {
            tokenPatterns[i - 1].first,
            match[i].str()
          };
        }
      }
      pos += match.position() + match.length();
    } else {
      pos++;
    }
    if (tokenPatterns.back().first == SPACE) {
      return getNextToken();
    }
    return {
      INVALID,
      ""
    };
  }


  private: string input;
  size_t pos;
  vector < pair < TokenType,
  string >> tokenPatterns;
  string combinedPattern;
  regex tokenRegex;
};

string tokenTypeToString(TokenType type) {
  switch (type) {
  case INTEGER:
    return "INTEGER";
  case DECIMAL:
    return "DECIMAL";
  case PLUS:
    return "PLUS";
  case INTDECALRE:
    return "INTDECALRE";
  case DECDECLARE:
    return "DECDECLARE";
  case MINUS:
    return "MINUS";
  case MULTIPLY:
    return "MULTIPLY";
  case DIVIDE:
    return "DIVIDE";
  case LOOP:
    return "LOOP";
  case WHILE:
    return "WHILE";
  case IF:
    return "IF";
  case START:
    return "START";
  case END:
    return "END";
  case VARIABLE:
    return "VARIABLE";
  case TO:
    return "TO";
  case FROM:
    return "FROM";
  case EQUALITY:
    return "EQUALITY";
  case LOGIC:
    return "LOGIC";
  case SPACE:
    return "SPACE";
  case INVALID:
    return "INVALID";
  case ASSIGN_INT:
    return "ASSIGN_INT";
  case ASSIGN_DEC:
    return "ASSIGN_DEC";
  case PRINT:
  	return "PRINT";
  case STOP:
  	return "STOP";
  default:
    return "UNKNOWN";
  }
}

//int main() {
//  string inputExpression = "intNumber a := 4 decNumber b := 4.56 if [a < b] start print a end while (a < b) start plus a to b divide a to b end exit";
//  Lexer lexer(inputExpression);
//  vector < Token > tokens;
//  Token token = lexer.getNextToken();
//  while (token.type != STOP) {
//  	
//    tokens.push_back(token);
//    token = lexer.getNextToken();
//  }
//  int i = 1;
//  for (const Token & t: tokens) {
//  	if(i < 10){
//  		cout<<i<<". " << "Token Type: " << tokenTypeToString(t.type) << "\n   Token Value: " << t.value << endl;
//	}
//	else {
//		cout<<i<<". " << "Token Type: " << tokenTypeToString(t.type) << "\n    Token Value: " << t.value << endl;
//	}
//    
//    i++;
//  }
//  return 0;
//}
