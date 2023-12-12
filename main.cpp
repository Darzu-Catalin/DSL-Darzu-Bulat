#include <conio.h>
#include "interpreter.cpp"


string readFromFile() {
	string txt="";
    system("cls");
    printf("Type name of the file: ");
    char a[100] = {};
    fgets(a, sizeof(a), stdin);

    a[strcspn(a, "\n")] = '\0';	

    strcat(a, ".txt");

    FILE* fo = fopen(a, "r");
    if (fo == NULL) {
        printf("Failed to open the file.\n");
        printf("(Press any key to continue)");
        getch();
        return " ";
    }

    int ch = fgetc(fo);
    while (ch != EOF) {
    	if( ch == char(10) ){
    		txt+=" ";
		}
        else txt+=ch;
        ch = fgetc(fo);
    }

    fclose(fo);
    printf("Loaded successfully!\n");
    printf("(Press any key to continue)");
    getch();
    return txt;
}


void printMenu(){
	printf("1. Load from file\n");
	printf("2. Compile\n");

	
}

int main(){
	char input;
	string txt;
	while(true){
		system("cls");
		printMenu();
	input = getch();

		switch(input){
			case 49 : {
				txt = readFromFile();
				break;
			}
			case 50 : {
				system("cls");
				Interpreter Interpreter(txt);
				printf("(Press any key to continue)");
    			getch();
				break;
			}

				
			case 27: {
				return 0;
			}
			
		}
	

	}
	
	return 0;
}
