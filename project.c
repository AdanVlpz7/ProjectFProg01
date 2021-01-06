#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
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

//quiero que busques c en word y lo remplaces en answer sin quitar las x
char updateChar(char word[15], char answer[15],char rep){
    
    for(int i = 0; answer[i] != '\0'; i++){
        if (word[i] == rep){
            //printf("\n si es %c en: ",rep);
            //printf("%d",i);
            answer[i] = rep;
            //return answer[15];
        }

        //if(answer[i]!='x')
        //break;
            //answer[i] = 'x';
    }
    return answer[15];
}

void printCorrectAns(char word[15]){
    for(int i = 0; word[i]!= '\0'; i++)
    {
        
        //look for the character
        if (word[i] == 'x')
        {
            
            printf("_ ");
            //updateChecking(word,arr);
        }
        else
        {
            printf("%c",word[i]);
        } 
        
        //updateChecking(word,arr);
    }
}

int compareChar(char word[15],char answer[15]){
    int size = 0;
    int varBool = 0;
    int varCheck = 0;
    for(int i = 0; word[i]!='\0';i++){
        //size++;
    }
    for(int i = 0; i <= size; i++){
        if(word[i] == answer[i]){
            varBool = 1;
        }
    }
    //if(varCheck == size){
      //  varBool = 1;//si son iguales
    //}
    //else
      //  varBool = 0; //no son iguales aun
    return varBool;
}
//ACTUALIZAR-COMPARAR -> IMPRIMIR
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
        for(int i = 0; words[indexArr][i]!='\0'; i++)
        {
            //printf("_ ");
            answTemp[i] = 'x';
            wordTemp[i] = words[indexArr][i];
            printf("%c",wordTemp[i]);
            //funcion para imprimir answTemp como ("_ ")
        }
    }
    while(gameOn == 's'){
        //Funcionamiento del juego


        //para checar la palabra
        printCorrectAns(answTemp);
                                //comparacion de cadenas recurrente
        if (!(strcmp(wordTemp,answTemp))){
            printf("\n Felicidades, te salvaste... por ahora.\n");
            printf("\n ¿Quieres volver a jugar?(s/n)?");
            scanf("%d",gameOn);
            if(gameOn == 's'){
                srand((unsigned int)time(NULL));
                indexArr = (int)rand() % 15;
                mistakes = 0;
            }
        }

        printf("\n¿Cual letra crees que es parte de la palabra?\n");
        scanf("%c",&ans);

        if(mistakes < 10){
            int check;
            scanf("%c",&ans);
            check = checkAnswer(ans,wordTemp);
            updateChar(wordTemp,answTemp,ans);
            if(check == 0){
                    mistakes++;
                    //printf("'%c'",ans);
                    printf("\n Errores : %d \n",mistakes);
            }
            else{
                //ACTUALIZAR TEMPLATE
                //for(int i = 0; wordTemp[i]!= '\0';i++){
                //fgets(answTemp,15,stdin);
                //updateChar(wordTemp,answTemp,ans);
                

                printf("\n Errores : %d \n",mistakes);
            
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