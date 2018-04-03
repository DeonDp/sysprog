#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//int main(){

    int k,j;
    #define NUM_RANGE 8
    //global declaration of char * pointer variable address of player move enties
    char * pmv;
    //global declaration of char[][] variable to store letters for gameplay
    char ulcs[55][2];
    //global declaration of char[][] variable to store letters for start board
    char ch[10][2];
    //global declaration structure grid
    char * grid[NUM_RANGE][NUM_RANGE];

    void getNewBoard(){
        //creates a brand new blank board. Returns a pointer to the array 
        for (j = 0; j < NUM_RANGE; j++){
            for (k = 0; k < NUM_RANGE; k++){
                grid[k][j]="   ";
            }//Endfor
        }//Endfor
        return;
    }//EndFunction getNewBoard

    void drawBoard(){
        //This function prints out the board that was passed. Returns void
        char * const NLINE = "    1    2    3    4    5    6    7    8";
        char * const HLINE = "  +----+----+----+----+----+----+----+----+";
        char * const VLINE = "  |    |    |    |    |    |    |    |    |";

        printf("%s\n",NLINE);
        printf("%s\n",HLINE);
        for (j = 0; j < NUM_RANGE; j++){  

            printf("%s\n",VLINE);
            printf("%d ",j+1);
            for (k = 0; k < NUM_RANGE; k++){  
                if(strcmp(grid[k][j],"   ")==0){
                    printf("| %s",grid[k][j]);
                }
                else{
                    printf("| %s  ",grid[k][j]);
                }
            }
            printf("%s","|");
            printf("\n");
            printf("%s\n",VLINE);
            printf("%s\n",HLINE);
        }
        return;
    }//EndFunction drawBoard

       
    void makePlay(int x, int y, char* c){
       //Arrays are zero indexed but our grid starts at index 1
       grid[x-1][y-1]=c;
       return;
    }

    //currently suspecting that this function should not return void
    char *getPlayerMove(){
        /*This function ask the user for an input letter to play or
        the input 'quit' if they want to end the game. The function then get the x and y
        coordinates on the grid to place the letter in the form xy.*/
        char p_desc[7];
        char mv;
        char fp_desc[7];
        int x,y,coordinates;

        printf("Enter the letter you wish to play or type \"quit\" to end the game ");
        scanf("%s",p_desc);

        pmv=&p_desc[0];
        if (strlen(p_desc) ==1){
            mv=p_desc[0];
            printf("where do you want to place your chosen letter (%c) ",mv);
            scanf("%d",&coordinates);
            x=coordinates/10;
            y=coordinates%10;
            strcpy(fp_desc,p_desc);
            sprintf(pmv,"%d-%d-%s",x,y,fp_desc);
            //strcpy(pmv,p_desc);
            return pmv;
        }
        else if(strcmp(p_desc,"quit")==0){
            //jus add a goodbye msg
            //strcpy(pmv,p_desc);
            return pmv;
            //exit(0);
        }
    }

    int calculateScore(char * word){
        /*This function takes a word and calculates its
        score based on the dictionary like structure "SCRABBLE_LETTER_VALUES" 
        that holds 'letter:value' pairs and returns the score.*/
        char * clnstr;
        char valid_word[83670][20];
        char letter[3],strval[3];
        char SCRABBLE_LETTER_VALUES[30][10] = { "'A': 1","'B': 3", "'C': 3", "'D': 2", "'E': 1", "'F': 4",
        "'G': 2", "'H': 4", "'I': 1", "'J': 8", "'K': 5", "'L': 1", "'M': 3", "'N': 1", "'O': 1", "'P': 3",
        "'Q': 10", "'R': 1", "'S': 1", "'T': 1", "'U': 1", "'V': 4", "'W': 4", "'X': 8", "'Y': 4", "'Z': 10"
        };
        FILE *wpt;
        int i,c,s,l,value,score;
        
        wpt=fopen("words","r");
        i=0;
        value=0;

        while(fscanf(wpt,"%s",valid_word[i])!=-1) {
            printf("%s %s\n",valid_word[i],word);
            if(strcmp(word,valid_word[i])==0) {
                printf("here\n");
                for(s=0;s<strlen(word);++s){
                    printf("here now reading %c\n",word[s]);
                    for (l = 0; l < 26; ++l) {
                        printf("and now\n");
                        clnstr=strtok(SCRABBLE_LETTER_VALUES[l],":");
                        c=0;
                        while(clnstr!=NULL){
                            printf("%s %d\n",clnstr,c);
                            if(c%2==0){
                                strcpy(letter,clnstr);
                                c+=1;
                            }
                            else {
                                strcpy(strval,clnstr);
                                value= atoi(strval);
                            }
                            clnstr=strtok(NULL, ":");
                        }
                        printf("%c %c %d\n",letter[1],word[s],value);
                        if (word[s]==letter[1]) {
                            printf("and finally\n");
                            score+=value;
                            printf("score is->%d\n",score);
                            break;
                        }
                    }
                }
                break;
            }
            
            i+=1;
        } 
        printf("%d\n",score );
        return score;
    }

    int isOnBoard(int x, int y){
        /*
        This function take a x and y coordinate and
        return an integer to represent True if the coordinates are on the board or an integer to represent False if
        they are not.*/
        int r;
        if (x>=0 && y>=0 && x<8 && y<8 ) {
            if(strcmp(grid[x][y],"   ")!=0){
                r=1;
            }
            else {
                r=0;
            }
        }
        else{
            printf("Out of board range\n");
            r=0;
        }
        //1 represents True and 0 represennts False
        return r;
    }

    void startBoard(){
        /*This function uses the board to randomly position 10 letters on the
        board.*/
        time_t t;
        char letters[26][2]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p",
                        "q","r","s","t","u","v","w","x","y","z"};
        //char *cp;
        int x,y,c;

        getNewBoard();
        srand((unsigned) time(&t));
        c=0;

        while(c<10){
            x=rand() % 8; 
            y=rand() % 8; 
            x++;
            y++;
            //printf("<%d,%d> is %d board \n",x,y,isOnBoard(x-1,y-1)); 
            if(isOnBoard(x-1,y-1)==0){
                strcpy(ch[c],letters[rand() % 26]);
                //printf("%s\n",grid[x-1][y-1]);
                makePlay(x,y,ch[c]);
                //printf("%s\n",grid[x-1][y-1]);
                c++;
            }
            else {
                c=c;
            } 
            //printf("position %d added with letter %s\n",c,ch[c]);   
        }
        printf("New Game\n");
    }


    int getXcoordinate(char p_entry[7]) {

       int v;
       
       v=p_entry[0]-48;
       return v;
    }

    int getYcoordinate(char p_entry[7]) {

       int v;
       
       v=p_entry[2]-48;
       return v;
    }


    char * getuserL(char p_entry[7],int turn) {

       char v;
       char strver[3];
       
       v=p_entry[4];
       strver[0]=v;
       strver[1]=0;
       strcpy(ulcs[turn],strver);
       return ulcs[turn];
    }

   /* getNewBoard();
    //Displaying empty board
    printf("\n%s\n\n","Printing an empty board....");
    drawBoard();*/
    //making two plays
    /*makePlay(3,7,"a");    
    makePlay(4,5,"b"); 

    printf("\n%s\n\n","RePrinting board after plays....");
    //redrawing the board with plays shown
    drawBoard();
    
    getNewBoard();
    printf("\n%s\n\n","Printing new empty board....");
    drawBoard();*/
   // startBoard();
    //printf("\n%s\n\n","Printing board for new game....");
    //drawBoard();
    
    //calculateScore("zero");

    //return 0;

//}

