#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
//#include <conio.h> ONLY WINDOWS

char getch(){
       #include <unistd.h>   //_getch*/
       #include <termios.h>  //_getch*/
       char buf=0;
       struct termios old={0};
       fflush(stdout);
       if(tcgetattr(0, &old)<0)
           perror("tcsetattr()");
       old.c_lflag&=~ICANON;
       old.c_lflag&=~ECHO;
       old.c_cc[VMIN]=1;
       old.c_cc[VTIME]=0;
       if(tcsetattr(0, TCSANOW, &old)<0)
           perror("tcsetattr ICANON");
       if(read(0,&buf,1)<0)
           perror("read()");
       old.c_lflag|=ICANON;
       old.c_lflag|=ECHO;
       if(tcsetattr(0, TCSADRAIN, &old)<0)
           perror ("tcsetattr ~ICANON");
       printf("%c\n",buf);
       return buf;
}

int checkAnswer(char c, char word[15]){
    int varBool = 0;//bool
    int cont = 0;
    for(int i = 0; word[i]!= '\0'; i++)
    {
        //look for the character
        if (c == word[i])
        {
            cont++;
        }
        
    }
    if (cont != 0){
        //printf("si esta la letra");
        varBool = 1;
    }
    if (cont == 0){
        //printf("no esta la letra");
        varBool = 0;
    }
    return varBool;
}

char updateChar(char c, char word[15], char answer[15]){
    char updChar[15];
    for(int i = 0; word[i]!= '\0'; i++){
        if (c == word[i] && answer[i] == 'x'){
            updChar[i] = c;
            return updChar[i];
        }
    }
}

int updateChecking(char original[15],char answer[15]){
    int varBool;
    char template[15];
    for(int i = 0; answer[i]!= '\0'; i++){
        if ((answer[i] >= 65  && answer[i] <= 90) || (answer[i] >= 97  && answer[i] <= 122))
        {
            template[i] = answer[i];
            printf("%c ",template[i]);
        }
        else{
            printf("%c ", answer[i]);
        }
    }
    
    return varBool;
}
void printCorrectAns(char c, char word[15], char wrong){
    char arr[15];
    for(int i = 0; word[i]!= '\0'; i++)
    {
        //look for the character
        if (c == word[i])
        {
            arr[i] = c;
            //updateChecking(word,arr);
        }
        else 
        {
            arr[i] = 00;
        } 
        //updateChecking(word,arr);
    }
    
    for(int i = 0; arr[i]!= '\0'; i++)
    {
        if (arr[i]!= '0') 
            printf("%c", arr[i]);
        if(arr[i] == '0') 
            printf("_ ");
    }
}


int main(){

    char words[15][15] = {"coronavirus","mazatlan","relampago","relojeria","delantero",
                          "venezuela","internacional","enamorados","regueton","lenguaje",
                          "elefante","teorema","calzones","velocidad","gravedad"};
    char gameOn = 'n';
    char wrong = 'x';
    char ans;
    char wordTemp[15]; //la palabra a adivinar
    char answTemp[15];
    int mistakes = 0;
    int answer; //bool que simboliza si la respuesta fue correcta o incorrecta 
    int indexArr = 0;
    //Introducción al juego
    printf("!Bienvenido al juego tradicional de Ahorcado!");
    printf("\n **** Nota: \n"
               "Se elegira una palabra al azar, dicha palabra estara incompleta \n"
               "y necesitara que adivines que letras faltan, si no, !te ahogaras!\n"
               "...y dicen que es una muerte dolorosa ****\n"
               "TIENES 10 INTENTOS\n");
    printf("Listo? (s/n) \n");
    scanf("%c",&gameOn);
    if(gameOn == 's'){
        srand((unsigned int)time(NULL));
        indexArr = (int)rand() % 15;
        printf(" * La palabra es mas o menos asi: \n");
        ans = 0;
    }
    while(gameOn == 's'){
        //Funcionamiento del juego

        for(int i = 0; words[indexArr][i]!='\0'; i++)
        {
            printf("_ ");
            answTemp[i] = 'x';
            wordTemp[i] = words[indexArr][i];
        }

        //para checar la palabra
        for(int i = 0; wordTemp[i]!='\0'; i++){
            printf(" '%c' ", wordTemp[i]);
        }

        printf("\n¿Cual letra crees que es parte de la palabra?\n");
        scanf("%c",&ans);
            //printf("\n Confirma que crees que %c es una respuesta con cualquier tecla \n",ans);
            //getch();
        //WORKBENCH
        if(mistakes < 10){
            int check;
            scanf("%c",&ans);
            check = checkAnswer(ans,wordTemp);
            if(check == 0 && ans!= '\0'){
                    mistakes++;
                    //printf("'%c'",ans);
                    printf("\n Errores : %d \n",mistakes);
            }
            else{
                printf("\n Errores : %d \n",mistakes);
            }
            for(int i = 0; answTemp[i]!= '\0';i++){ 
                //answTemp[i] = updateChar(ans,wordTemp,answTemp);
                //printf("%c",answTemp[i]);
            }            
        }

        if (mistakes == 10){
            //G A M E   O V E R
            printf("\n\n¿Quieres volver a jugar?(s/n)\n");
            scanf("%c",&gameOn);
            if(gameOn == 's'){
                srand((unsigned int)time(NULL));
                indexArr = (int)rand() % 15;
                mistakes = 0;
            }
        }
    };
    
    return 0;
}