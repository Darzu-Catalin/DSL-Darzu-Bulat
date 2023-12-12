#include "lexer.cpp"


struct ASTNode {
  string type;  
  string value;
  vector<ASTNode> children;
};


class Parser {
public:
  Parser(vector<Token>& tokens) : tokens(tokens), currentTokenIndex(0) {}

  ASTNode parse() {
    ASTNode rootNode;
    while (currentTokenIndex < tokens.size()) {
      ASTNode statement = parseStatement();
      rootNode.children.push_back(statement);
    }
    return rootNode;
  }
  
  void printAST(const ASTNode& node, int depth = 0) {
    for (int i = 0; i < depth; ++i) {
      cout << "  ";
    }
    cout << node.value << endl;

    for (const auto& child : node.children) {
      printAST(child, depth + 1);
    }
  }

private:
  vector<Token>& tokens;
  size_t currentTokenIndex;

  ASTNode parseStatement() {
    Token token = getNextToken();
    switch (token.type) {
    	case END:
    	return	parseEndOperation();
      case INTEGER:
        return parseIntOperation();
      case DECIMAL:
        return parseDecimalOperation();
      case PLUS:
        return parsePlusOperation();
      case INTDECALRE:
        return parseIntDeclareOperation();
      case DECDECLARE:
        return parseDecDeclareOperation();
      case MINUS:
        return parseMinusOperation();
      case MULTIPLY:
        return parseMultiplyOperation();
      case DIVIDE:
        return parseDivideOperation();
      case LOOP:
        return parseLoopOperation();
      case WHILE:
        return parseWhileStatement();
      case IF:
        return parseIfStatement();
      case START:
        return parseStartStatement();
      case PRINT:
        return parsePrintStatement();
      case VARIABLE:
        return parseVariableDeclaration();
      case TO:
        return parseToOperation();
      case FROM:
        return parseFromOperation();
      case EQUALITY:
        return parseEqualityOperation();
      case LOGIC:
        return parseLogicOperation();
      case ASSIGN_INT:
        return parseAssignInt();
      case ASSIGN_DEC:
        return parseAssignDec();
      case SPACE:
        return parseSpaceOperation();
      case STOP:
        return parseStopOperation();
      default:
        cerr << "Error: Unexpected token " << tokenTypeToString(token.type) << " at position " << currentTokenIndex << endl;
        exit(1);
    }
  }

	ASTNode parseIntOperation() {
  ASTNode intNode;
  Token valueToken = getNextToken();
  intNode.value = valueToken.value;
  intNode.type = "integer";
  return intNode;
}

ASTNode parseDecimalOperation() {
  ASTNode decimalNode;
  Token valueToken = getNextToken();
  decimalNode.value = valueToken.value;
  decimalNode.type = "decimal";
  return decimalNode;
}

ASTNode parsePlusOperation() {
  ASTNode plusNode;
  plusNode.value = "+";
  plusNode.type = "operator";
  return plusNode;
}

ASTNode parseIntDeclareOperation() {
  ASTNode intDeclareNode;
  Token nameToken = getNextToken();
  intDeclareNode.value = nameToken.value;
  intDeclareNode.type = "int_declaration";
  return intDeclareNode;
}

ASTNode parseDecDeclareOperation() {
  ASTNode decDeclareNode;
  Token nameToken = getNextToken();
  decDeclareNode.value = nameToken.value;
  decDeclareNode.type = "dec_declaration";
  return decDeclareNode;
}

ASTNode parseMinusOperation() {
  ASTNode minusNode;
  minusNode.value = "-";
  minusNode.type = "operator";
  return minusNode;
}

ASTNode parseMultiplyOperation() {
  ASTNode multiplyNode;
  multiplyNode.value = "*";
  multiplyNode.type = "operator";
  return multiplyNode;
}

ASTNode parseDivideOperation() {
  ASTNode divideNode;
  divideNode.value = "/";
  divideNode.type = "operator";
  return divideNode;
}

ASTNode parseLoopOperation() {
  ASTNode loopNode;
  loopNode.value = "loop";
  loopNode.children.push_back(parseBlock());
  return loopNode;
}

ASTNode parseToOperation() {
  ASTNode toNode;
  Token valueToken = getNextToken();
  toNode.value = valueToken.value;
  toNode.type = "to";
  return toNode;
}

ASTNode parseFromOperation() {
  ASTNode fromNode;
  Token valueToken = getNextToken();
  fromNode.value = valueToken.value;
  fromNode.type = "from";
  return fromNode;
}

ASTNode parseEqualityOperation() {
  ASTNode equalityNode;
  equalityNode.value = "==";
  equalityNode.type = "operator";
  return equalityNode;
}

ASTNode parseLogicOperation() {
  ASTNode logicNode;
  Token valueToken = getNextToken();
  logicNode.value = valueToken.value;
  logicNode.type = "logic_operation";
  return logicNode;
}

ASTNode parseSpaceOperation() {
  ASTNode spaceNode;
  spaceNode.value = " ";
  spaceNode.type = "space";
  return spaceNode;
}

ASTNode parseStopOperation() {
  ASTNode stopNode;
  stopNode.value = "stop";
  stopNode.type = "stop";
  return stopNode;
}
ASTNode parseEndOperation() {
  ASTNode endNode;
  endNode.value = "end";
  endNode.type = "end";
  return endNode;
}



  ASTNode parseWhileStatement() {
    ASTNode whileNode;
    whileNode.value = "while";
    whileNode.children.push_back(parseLogicExpression());
    whileNode.children.push_back(parseBlock());
    return whileNode;
  }

  ASTNode parseIfStatement() {
    ASTNode ifNode;
    ifNode.value = "if";
    ifNode.children.push_back(parseLogicExpression());
    ifNode.children.push_back(parseBlock());
    return ifNode;
  }

  ASTNode parseStartStatement() {
    ASTNode startNode;
    startNode.value = "start";
    startNode.children.push_back(parseBlock());
    return startNode;
  }

ASTNode parsePrintStatement() {
  ASTNode printNode;
  printNode.value = "print";
  
  Token variableToken = getNextToken();
  ASTNode variableChild;
  variableChild.value = variableToken.value;
  printNode.children.push_back(variableChild);
  
  return printNode;
}


// Update parseVariableDeclaration, parseAssignInt, parseAssignDec, and parseLogicExpression functions

ASTNode parseVariableDeclaration() {
    ASTNode varDeclNode;
    varDeclNode.type = "variable_declaration";
    Token typeToken = getNextToken();
    Token nameToken = getNextToken();

    ASTNode childNode;
    childNode.type = typeToken.value;  // Store the type in value or use a separate member
    childNode.value = nameToken.value;
    varDeclNode.children.push_back(childNode);

    return varDeclNode;
}

ASTNode parseAssignInt() {
    ASTNode assignNode;
    assignNode.type = "assign_int";
    Token variableToken = getNextToken();
    Token valueToken = getNextToken();

    ASTNode variableChild, valueChild;
    variableChild.type = "variable";
    variableChild.value = variableToken.value;

    valueChild.type = "assign_int";
    valueChild.value = valueToken.value;

    assignNode.children.push_back(variableChild);
    assignNode.children.push_back(valueChild);

    return assignNode;
}

ASTNode parseAssignDec() {
    ASTNode assignNode;
    assignNode.type = "assign_dec";
    Token variableToken = getNextToken();
    Token valueToken = getNextToken();

    ASTNode variableChild, valueChild;
    variableChild.type = "variable";
    variableChild.value = variableToken.value;

    valueChild.type = "assign_dec";
    valueChild.value = valueToken.value;

    assignNode.children.push_back(variableChild);
    assignNode.children.push_back(valueChild);

    return assignNode;
}

ASTNode parseLogicExpression() {
    ASTNode logicNode;
    logicNode.type = "logic_expression";
    Token logicToken = getNextToken();

    ASTNode logicChild;
    logicChild.type = "logic";
    logicChild.value = logicToken.value;

    logicNode.children.push_back(logicChild);

    return logicNode;
}


ASTNode parseBlock() {
  ASTNode blockNode;
  blockNode.value = "block";
  while (currentTokenIndex < tokens.size() && tokens[currentTokenIndex].type != END) {
    ASTNode statement = parseStatement();
    blockNode.children.push_back(statement);
  }
  // Assuming END is used to mark the end of a block
  if (currentTokenIndex < tokens.size() && tokens[currentTokenIndex].type == END) {
    blockNode.children.push_back(parseEndOperation());
  }
  return blockNode;
}


  Token getNextToken() {
    if (currentTokenIndex < tokens.size()) {
      return tokens[currentTokenIndex++];
    } else {
      return {END, ""};
    }
  }
};
       
	   
//	   int main() {
//  string inputExpression = "start print a while [a > b] start print a add b to c end   stop";
//  Lexer lexer(inputExpression);
//
//  vector<Token> tokens;
//
//  Token token = lexer.getNextToken();
//  while (token.type != STOP) {
//    tokens.push_back(token);
//    token = lexer.getNextToken();
//  }
//
//  Parser parser(tokens);
//  ASTNode rootNode = parser.parse();
//  
//  
//  parser.printAST(rootNode);
//
//  return 0;
//}                                  