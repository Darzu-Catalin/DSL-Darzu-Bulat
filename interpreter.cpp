#include "parser.cpp"

class Interpreter{

  vector <pair<int,string>> integer;
  vector <pair<double,string>> decimal;
  int currentToken;
  queue <Token> tokens;
  
public:
  Interpreter(string inputExpression){  
    Lexer lexer(inputExpression);
  	Token token = lexer.getNextToken();
  	while (token.type != STOP) {
  	 	if(token.type == INVALID) cout<<"Invalid Syntax",exit(0);
    tokens.push(token);
    token = lexer.getNextToken();
  }
        tokens.push(token);
    	token = lexer.getNextToken();
 	  Token currentToken = tokens.front();
 	  //tokens.pop();
      nextOperationManager(currentToken);

  }
		bool isConvertibleToDouble(string str) {
  		istringstream iss(str);
    	double num;
   		 iss >> noskipws >> num;
    	return iss.eof() && !iss.fail();
		}
		bool checkVariable(Token var){
			for(int i=0;i<integer.size();i++){
				if(var.value == integer[i].second) return false;
			}
			for(int i=0;i<decimal.size();i++){
				if(var.value == decimal[i].second) return false;	
			}
			return true;
		}
		void decDeclare(Token current){
		try{
			tokens.pop();
			if(tokens.front().type == VARIABLE){
				Token variable = tokens.front();
				tokens.pop();
				if(!checkVariable(variable)){
					cout<<"This variable: "<< variable.value<< " already exists\n"; 
					throw 404;
				}
				if(tokens.front().type == ASSIGN_INT){
					cout<<"Assigned value is integer\n\n",throw 404;
				}
				
				
				if(tokens.front().type == ASSIGN_DEC){
					string intValue = tokens.front().value;
					intValue[0]=' ';
					intValue[1]=' ';
					//cout<<intValue<<endl;
   					double result = stod(intValue);
					decimal.push_back({result,variable.value});	
					tokens.pop();
				}
				
				else{
				decimal.push_back({0.00,variable.value});
				}
			}
			else{
				throw 404;
			}
		//cout<<currentToken;
	
		}catch(...){
		cout << "ERROR - DOUBLE declaration went wrong.\n";
		exit(0);
		}
		
		//cout<<"Decalred "<<decimal[0].first<<" "<<decimal[0].second;
				nextOperationManager(tokens.front());

	}
		void intDeclare(Token current){
		try{
			tokens.pop();
			if(tokens.front().type == VARIABLE){
				Token variable = tokens.front();
				tokens.pop();
				if(!checkVariable(variable)){
					cout<<"This variable: "<< variable.value<< " already exists\n"; 
					
					throw 404;
				}
				if(tokens.front().type == ASSIGN_INT){
					string intValue = tokens.front().value;
					intValue[0]=' ';
					intValue[1]=' ';
   					int result = stoi(intValue);
					integer.push_back({result,variable.value});
					tokens.pop();
				}
				else if(tokens.front().type == ASSIGN_DEC){
				cout << "Assigned value is decimal. \n";
				throw 404;
				}
				else{
				integer.push_back({0,variable.value});
				}
			}
			else{
				cout<<"Not a variable"<<endl;
				throw 404;
			}
		//cout<<currentToken;
	
		}catch(...){
		cout << "ERROR - INT declaration went wrong.\n";
		exit(0);
		}
		
		//cout<<"Decalred "<<integer[0].first<<" "<<integer[0].second;
		nextOperationManager(tokens.front());
	}
		void printVariable(Token current){
					try{
			tokens.pop();
			if(tokens.front().type == VARIABLE){
				Token variable = tokens.front();
				tokens.pop();
				
				for(int i=0;i<integer.size();i++){
					if(variable.value == integer[i].second) cout<<integer[i].first<<"\n";
				}
				for(int i=0;i<decimal.size();i++){
					if(variable.value == decimal[i].second) cout<<decimal[i].first<<"\n";	
				}
				
				
			}
			else{
				throw 404;
			}
	
		}catch(...){
		cout << "ERROR - PRINTING went wrong.\n";
		exit(0);
		}
		
		nextOperationManager(tokens.front());
		}
		void addVars(Token current){
			try{
			string valNumber="";
			tokens.pop();
			if(tokens.front().type == VARIABLE || tokens.front().type == INTEGER || tokens.front().type == DECIMAL){
				Token variable = tokens.front();
				tokens.pop();
				
				if(tokens.front().type == TO) tokens.pop();
				else cout<<"Syntax error!\n",throw 404;
				
				if(tokens.front().type == VARIABLE){
				Token variable2 = tokens.front();
				tokens.pop();
				int pos1=-1,pos2=-1,type2=-1,type1=-1;
				
				if(variable.type == INTEGER || variable.type == DECIMAL){
					valNumber = variable.value;
				}

				
				for(int i=0;i<integer.size();i++){
					if(variable.value == integer[i].second) pos1 =i,type1=0; 
					if(variable2.value == integer[i].second) pos2 =i,type2=0; 
				}
				for(int i=0;i<decimal.size();i++){
					if(variable.value == decimal[i].second) pos1 =i,type1=1;
					if(variable2.value == decimal[i].second) pos2 =i,type2=1;
				}
				


				if(variable.type == INTEGER || variable.type == DECIMAL){
				//cout<<valNumber<<endl;
				if( pos2==-1 || type2==-1 ) cout<<"Undeclared variable! \n\n",throw 404;

					if(type2 == 0){
						integer[pos2].first += stoi(valNumber);
						}
						else{	
						decimal[pos2].first += stod(valNumber);
						}
				}
				else{
				if(pos1 == -1 || pos2==-1 && type2==-1 || type1==-1) cout<<"Undeclared variable! \n\n",throw 404;
					if(type2 == 0){
						if(type1 == 0){
							integer[pos2].first += integer[pos1].first;
						}
						else{
							integer[pos2].first += decimal[pos1].first;
						}
					}
					else{
						 if(type1 == 0){
							decimal[pos2].first += integer[pos1].first;
						}
						else{
							decimal[pos2].first += decimal[pos1].first;
						}
					}
					
				}
			
			
			}
			}
			
			else{
				throw 404;
			}
	
		}catch(...){
		cout << "ERROR - ADD went wrong.\n";
		exit(0);
		}
		
		nextOperationManager(tokens.front());
		}
	    void minusVars(Token current){
			try{
			string valNumber="";
			tokens.pop();
			cout<<valNumber<<endl;
			if(tokens.front().type == VARIABLE || tokens.front().type == INTEGER || tokens.front().type == DECIMAL){
				Token variable = tokens.front();
				tokens.pop();
				

				if(tokens.front().type == FROM) tokens.pop();
				else cout<<"Syntax error!\n",throw 404;
				
				if(tokens.front().type == VARIABLE){
				Token variable2 = tokens.front();
				tokens.pop();
				int pos1=-1,pos2=-1,type2=-1,type1=-1;

				if(variable.type == INTEGER || variable.type == DECIMAL){
					valNumber = variable.value;

				}

				
				for(int i=0;i<integer.size();i++){
					if(variable.value == integer[i].second) pos1 =i,type1=0; 
					if(variable2.value == integer[i].second) pos2 =i,type2=0; 
				}
				for(int i=0;i<decimal.size();i++){
					if(variable.value == decimal[i].second) pos1 =i,type1=1;
					if(variable2.value == decimal[i].second) pos2 =i,type2=1;
				}
				//if(pos1 == -1 ||pos2==-1||type2==-1||type1==-1) cout<<"Undeclared variable! \n\n",throw 404;

				if(variable.type == INTEGER || variable.type == DECIMAL){
				if( pos2==-1 || type2==-1 ) cout<<"Undeclared variable! \n\n",throw 404;

					if(type2 == 0){
						integer[pos2].first -= stoi(valNumber);
						}
						else{	
						decimal[pos2].first -= stod(valNumber);
						}
				}
				else{
				if(pos1 == -1 || pos2==-1 && type2==-1 || type1==-1) cout<<"Undeclared variable! \n\n",throw 404;

					if(type2 == 0){
						if(type1 == 0){
							integer[pos2].first -= integer[pos1].first;
						}
						else{
							integer[pos2].first -= decimal[pos1].first;
						}
					}
					else{
						 if(type1 == 0){
							decimal[pos2].first -= integer[pos1].first;
						}
						else{
							decimal[pos2].first -= decimal[pos1].first;
						}
					}
					
				}
			
			
			}
			}
			
			else{
				throw 404;
			}
	
		}catch(...){
		cout << "ERROR - ADD went wrong.\n";
		exit(0);
		}
		
		nextOperationManager(tokens.front());
		}
		void divideVars(Token current){
			try{
			string valNumber="";
			tokens.pop();
			if(tokens.front().type == VARIABLE || tokens.front().type == INTEGER || tokens.front().type == DECIMAL){
				Token variable = tokens.front();
				tokens.pop();
				
				if(tokens.front().type == TO) tokens.pop();
				else cout<<"Syntax error!\n",throw 404;
				
				if(tokens.front().type == VARIABLE){
				Token variable2 = tokens.front();
				tokens.pop();
				int pos1=-1,pos2=-1,type2=-1,type1=-1;
				
				if(variable.type == INTEGER || variable.type == DECIMAL){
					valNumber = variable.value;

				}

				
				for(int i=0;i<integer.size();i++){
					if(variable.value == integer[i].second) pos1 =i,type1=0; 
					if(variable2.value == integer[i].second) pos2 =i,type2=0; 
				}
				for(int i=0;i<decimal.size();i++){
					if(variable.value == decimal[i].second) pos1 =i,type1=1;
					if(variable2.value == decimal[i].second) pos2 =i,type2=1;
				}
				
				//if(pos1 == -1 ||pos2==-1||type2==-1||type1==-1) cout<<"Undeclared variable! \n\n",throw 404;

				if(variable.type == INTEGER || variable.type == DECIMAL){
				//cout<<valNumber<<endl;
				if( pos2==-1 || type2==-1 ) cout<<"Undeclared variable! \n\n",throw 404;

					if(type2 == 0){
						integer[pos2].first /= stoi(valNumber);
					}
					else{	
						decimal[pos2].first /= stod(valNumber);
					}
				}
				else{
				if(pos1 == -1 || pos2==-1 && type2==-1 || type1==-1) cout<<"Undeclared variable! \n\n",throw 404;

					if(type2 == 0){
						if(type1 == 0){
							integer[pos2].first /= integer[pos1].first;
						}
						else{
							integer[pos2].first /= decimal[pos1].first;
						}
					}
					else{
						 if(type1 == 0){
							decimal[pos2].first /= integer[pos1].first;
						}
						else{
							decimal[pos2].first /= decimal[pos1].first;
						}
					}
					
				}
			
			
			}
			}
			
			else{
				throw 404;
			}
	
		}catch(...){
		cout << "ERROR - ADD went wrong.\n";
		exit(0);
		}
				nextOperationManager(tokens.front());
		
	}
		void multiplyVars(Token current){
			try{
			string valNumber="";
			tokens.pop();
			if(tokens.front().type == VARIABLE || tokens.front().type == INTEGER || tokens.front().type == DECIMAL){
				Token variable = tokens.front();
				tokens.pop();
				
				if(tokens.front().type == TO) tokens.pop();
				else cout<<"Syntax error!\n",throw 404;
				
				if(tokens.front().type == VARIABLE){
				Token variable2 = tokens.front();
				tokens.pop();
				int pos1=-1,pos2=-1,type2=-1,type1=-1;
				
				if(variable.type == INTEGER || variable.type == DECIMAL){
					valNumber = variable.value;

				}

				
				for(int i=0;i<integer.size();i++){
					if(variable.value == integer[i].second) pos1 =i,type1=0; 
					if(variable2.value == integer[i].second) pos2 =i,type2=0; 
				}
				for(int i=0;i<decimal.size();i++){
					if(variable.value == decimal[i].second) pos1 =i,type1=1;
					if(variable2.value == decimal[i].second) pos2 =i,type2=1;
				}
				
				//if(pos1 == -1 ||pos2==-1||type2==-1||type1==-1) cout<<"Undeclared variable! \n\n",throw 404;
				if(variable.type == INTEGER || variable.type == DECIMAL){
				//cout<<valNumber<<endl;
				if( pos2==-1 || type2==-1 ) cout<<"Undeclared variable! \n\n",throw 404;
					if(type2 == 0){
						integer[pos2].first *= stoi(valNumber);
						}
						else{	
						decimal[pos2].first *= stod(valNumber);
						}
				}
				else{
				
					if(pos1 == -1 || pos2==-1 && type2==-1 || type1==-1) cout<<"Undeclared variable! \n\n",throw 404;

					if(type2 == 0){
						if(type1 == 0){
							integer[pos2].first *= integer[pos1].first;
						}
						else{
							integer[pos2].first *= decimal[pos1].first;
						}
					}
					else{
						 if(type1 == 0){
							decimal[pos2].first *= integer[pos1].first;
						}
						else{
							decimal[pos2].first *= decimal[pos1].first;
						}
					}
					
				}
			
			
			}
			}
			
			else{
				throw 404;
			}
	
		}catch(...){
		cout << "ERROR - MULTIPLICATION went wrong.\n";
		exit(0);
		}
				nextOperationManager(tokens.front());
		
	}
		bool checkExpression(Token current){
			try{
				string expression = tokens.front().value;
				tokens.pop();
				expression[0] = '\0';
				expression [expression.length()-1] = '\0';

				string firstVar="";
				int j=0;
				while(expression[j] != '<' && expression[j] != '>' &&expression[j] != '='){
					if(expression[j] != ' ') firstVar+=expression[j];
					expression[j] = '\0';
					j++;
				}

				
				string equality;

				while(expression[j] == '<' || expression[j] == '>' || expression[j] == '='){
					if(expression[j] != ' '){
						if(expression[j] == '<'||expression[j] == '>'||expression[j] == '=') equality+=expression[j];
					}
					j++;
				}
				
				
				string secondVar = "";

				while(j < expression.length()){
					if(expression[j] != ' ') secondVar+=expression[j];
					expression[j] = '\0';
					j++;
				}
			
				firstVar.erase(std::remove(firstVar.begin(), firstVar.end(), '\0'), firstVar.end());
				secondVar.erase(std::remove(secondVar.begin(), secondVar.end(), '\0'), secondVar.end());
				
				
				for(int i=0;i<integer.size();i++){
					if(firstVar == integer[i].second) firstVar = to_string(integer[i].first); 
					if(secondVar == integer[i].second) secondVar =to_string(integer[i].first); 

				}
				for(int i=0;i<decimal.size();i++){
					if(firstVar == decimal[i].second) firstVar = to_string(decimal[i].first);
					if(secondVar == decimal[i].second) secondVar = to_string(decimal[i].first);
				}
				


				//cout<<firstVar<<" "<<equality<<" "<<secondVar<<endl;
				double first = stod(firstVar);
				//cout<<firstVar<<" "<<equality<<" "<<secondVar<<endl;
    			double second = stod(secondVar);



				if(equality == "<"){
					return first < second;
				}
				else if(equality == ">"){
					return first > second;
				}
				else if(equality == ">=" || equality == "=>"){
					return first >= second;
				}
				else if(equality == "<=" || equality == "=<"){
					//cout<<firstVar<<" "<<equality<<" "<<secondVar;
					return first <= second;
				}
				else if(equality == "=="){
					return first == second;
				}
				else throw 404;
				
				
			}catch(...){
				cout<<"Expression is invalid! \n";
				exit(0);
			}
		}
		void ifStatement(Token current){
			try{
			
			tokens.pop();
			if (tokens.front().type == LOGIC){
				
			   if(checkExpression(tokens.front())){
			   			//		   			
				}                  
				else{
						if(tokens.front().type == START){
							while(tokens.front().type != END){
								tokens.pop();
							}
						}
						else{
							while(tokens.front().type != VARIABLE &&
							tokens.front().type != ASSIGN_INT &&
							tokens.front().type != ASSIGN_DEC &&
							tokens.front().type != INTEGER &&
							tokens.front().type != DECIMAL
							){
							tokens.pop();	
							}
							tokens.pop();
							
						}	
				}
			   
			}
						   	
			else{
				throw 404;
			}
		
		}
		catch(...){
		cout << "ERROR - IF went wrong.\n";
		exit(0);
		}
		nextOperationManager(tokens.front());	
		}
		void whileOperation(Token current){
		try{
			tokens.pop();
			if (tokens.front().type == LOGIC){
				Token logicToken = tokens.front();
				queue<Token> tokensTMP;
			   	queue<Token> tokensCPY = tokens;
			   if(checkExpression(tokens.front())){
						 if(tokens.front().type == START){
							while(tokens.front().type != END){
								tokensTMP.push(tokens.front());
								tokens.pop();
							}
							tokensTMP.push(tokens.front());
							tokens.pop();
							tokensTMP.push(current);	
							//tokensTMP.push(logicToken);
							
							while(tokensCPY.size()>0){
								tokensTMP.push(tokensCPY.front());	
								tokensCPY.pop();
							}
							tokens = tokensTMP;
							
						 }
						 else{
							    throw 404;
							}
									
				}                  
				else{
						if(tokens.front().type == START){
							while(tokens.front().type != END){
								tokens.pop();
							}	
							tokens.pop();
						}
						else{
							throw 404;
							
						}	
				}
			   
			}
						   	
			else{
				throw 404;
			}
		
		}
		catch(...){
		cout << "ERROR - WHILE operation went wrong.\n";
		exit(0);
		}
		nextOperationManager(tokens.front());
		}
		void loopOperation(Token current){
		try{
			tokens.pop();
			if (tokens.front().type == INTEGER){
				int numberR = stoi(tokens.front().value);
				queue<Token> tokensTMP;
			   	queue<Token> tokensCPY = tokens;
				tokens.pop();
				if(tokens.front().type == START){
						 	vector <Token> vect;

							while(tokens.front().type != END){
								vect.push_back(tokens.front());
								tokens.pop();
							}
							tokens.pop();
							for(int j=0;j<numberR-1;j++)
							for(int i=0;i<vect.size();i++){
								tokensTMP.push(vect[i]);
							}
							tokensCPY.pop();
							while(tokensCPY.size()>0){
								tokensTMP.push(tokensCPY.front());	
								tokensCPY.pop();
							}
							tokens = tokensTMP;
							
						 }
						 else{
							    throw 404;
							}
							   		
		
		}
		else{
				throw 404;
			}	
		}
		catch(...){
		cout << "ERROR - LOOP operation went wrong.\n";
		exit(0);
		}
		nextOperationManager(tokens.front());
		}
		
		
		
		
	void nextOperationManager(Token type){
	switch(type.type){

  case START:{
  	tokens.pop();
  	nextOperationManager(tokens.front());
	break;
  }

  case END: {
  	tokens.pop();
  	nextOperationManager(tokens.front());
	break;
  }
  case PLUS:{
  	addVars(type);
	break;
  }
  	
  case INTDECALRE:
    intDeclare(type);
    break;
  case DECDECLARE:
    decDeclare(type);
    break;
  case MINUS:
     minusVars(type);
    break;
  case MULTIPLY:
    multiplyVars(type);
    break;
  case DIVIDE:
    divideVars(type);
    break;
  case LOOP:
    loopOperation(type);
    break;
  case WHILE:
    whileOperation(type);
    break;
  case IF:
    ifStatement(type);
    break;
  case INVALID:
        cout << "Syntax ERROR! (invalid symbols)" << endl,exit(0);
    break;
  case PRINT:
    printVariable(type);
    break;
  case STOP:
    cout<<"Program executed successfully!";exit(0);
    break;
  default:
    cout << "Syntax ERROR!" << endl,exit(0);
    break;
}

	
}
         

};


//int main() {
//    string inputExpression = "number a : 3 repeat 3 start print a end multiply a to a while [a < 10]  start add 1 to a  print a  end number b:10 stop ";
//	Parser parser(inputExpression);      
//                                                                          
//    return 0;
//}
                                                          