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
    if (cont != 0) 
        varBool = 1;
    if (cont == 0)
        varBool = 0;
    return varBool;
}

void printCorrectAns(char c, char word[15]){
    for(int i = 0; word[i]!= '\0'; i++)
    {
        //look for the character
        if (c == word[i])
        {
            printf("%c ",c);
        }
        else{
            printf("_ ");
            
        }
    }
}
int main(){

    char words[15][15] = {"coronavirus","mazatlan","relampago","relojeria","delantero",
                          "venezuela","internacional","enamorados","regueton","lenguaje",
                          "elefante","teorema","calzones","velocidad","gravedad"};
    char gameOn = 's';
    char wordTemp[15];
    int mistakes;
    int answer; //bool que simboliza si la respuesta fue correcta o incorrecta 
    int indexArr = 0;
    do{
        //Introducción al juego
        printf("!Bienvenido al juego tradicional de Ahorcado!");
        printf("** Nota: \n"
               "Se elegira una palabra al azar, dicha palabra estara incompleta \n"
               "y necesitara que adivines que letras faltan, si no, !te ahogaras!\n"
               "...y dicen que es una muerte dolorosa**\n");
        printf("Presiona cualquier letra para comenzar!\n");
        getch();
        
        //Funcionamiento del juego

        indexArr = 0;
        srand((unsigned int)time(NULL));
        indexArr = (int)rand() % 15;
        //printf("%d",&indexArr); //Para checar el index aleatorio

                    printf("\nLa palabra es mas o menos asi: \n");
        for(int i = 0; words[indexArr][i]!='\0'; i++)
        {
            printf("_ ");
            wordTemp[i] = words[indexArr][i];
        }

        //para checar la palabra
        for(int i = 0; wordTemp[i]!='\0'; i++){
            printf("%c", wordTemp[i]);
        }
        getch();
        mistakes = 0;
        while(mistakes < 5){
            printf("¿Cual letra crees que es parte de la palabra?\n");
            char ans;
            scanf("%c",&ans);
            printCorrectAns(ans,wordTemp);

            //si no se encuentra, sumar a mistakes
            if(checkAnswer(ans,wordTemp) == 0){
                mistakes++;
            }
        }

        if (mistakes == 5){
            //G A M E   O V E R
            printf("\n\n¿Quieres volver a jugar?(s/n)");
        }
    }while(gameOn == 's');
    
    return 0;
}