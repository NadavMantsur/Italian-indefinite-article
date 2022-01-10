/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*-------------------------------------------------------------------------
  Constants and definitions:
--------------------------------------------------------------------------*/

#define MASCULINE (1)
#define FEMININE (2)

#define UN (1)
#define UNO (2)
#define UNA (3)
#define UN_APOSTROPHE (4)


/* put your #defines and typedefs here*/
#define UN_ARTICLE "un "
#define UNO_ARTICLE "uno "
#define UNA_ARTICLE "una "
#define UN_APOSTROPHE_ARTICLE "un'"


#define Z_WHISTLE 'z'
#define X_WHISTLE 'x'
#define Y_WHISTLE 'y'
#define G_WHISTLE 'g'
#define P_WHISTLE 'p'
#define S_WHISTLE 's'
#define I_WHISTLE 'i'

#define A_VOWEL 'a'
#define E_VOWEL 'e'
#define I_VOWEL 'i'
#define O_VOWEL 'o'
#define U_VOWEL 'u'
#define H_VOWEL 'h'


int get_gender(char* noun);
int get_indefinite_article(char* noun);
int get_length_indefinite_article(char* noun);
void add_indefinite_article(char* noun, char* noun_with_article);
void handle_indefinite_article(int max_length);


/*-------------------------------------------------------------------------
  Your implementation of the functions (describe what each function does)
 -------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------
  The main program
 -------------------------------------------------------------------------*/

/**
 * main - reads two integers and calls handle_indefinite_article() accordingly.
 * 
 * @returns the status, for the operating system.
 */
int main() {
    int max_length, num_of_nouns;
    scanf("%d %d", &max_length, &num_of_nouns);
    for(int i = 0; i < num_of_nouns; i++) {
        handle_indefinite_article(max_length);
    }
    return 0;
}

//A
// returns 1 if the noun is MASCULINE or 2 if the noun is FEMININE
int get_gender(char* noun){
    char last_char = noun[(strlen(noun)-1)];
    if(last_char == 'o'){
        return 1;
    }
    else{
        return 2;
    }
}

//vowel letters: a, e, i, o, u, h*
//* h is vowel if it the first letter in the noun
//returns true if the second letter of the noun is vowel letter.
//not includes h.
bool isVowel(char c){//cases? capital letters?
    if(c == A_VOWEL || c == E_VOWEL || c == I_VOWEL || c == O_VOWEL || c == U_VOWEL || c == H_VOWEL){
        return true;
    }
    else{
        return false;
    }
}

//returns true if the noun begins with whistle letter
bool isWhistle(char* noun){ //cases? capital letters?
    char first_char = noun[0];
    char second_char = noun[1];
    if(first_char == Z_WHISTLE || first_char == X_WHISTLE || first_char == Y_WHISTLE){
        return true;
    }
    if(first_char == G_WHISTLE){
        if(second_char == 'n'){
            return true;
        }
    }
    if(first_char == P_WHISTLE){
        if(second_char == 's'){
            return true;
        }
    }
    if(first_char == S_WHISTLE){
        if(!isVowel(second_char)){
            return true;
        }
    }
    if(first_char == I_WHISTLE){
        if(isVowel(second_char) && second_char != 'h'){
            return true;
        }
    }
    return false;
}

//B
//returns the num's indefinite article that matches the noun
int get_indefinite_article(char* noun){
    int gender = get_gender(noun);
    if (gender == MASCULINE){
        if(isWhistle(noun)){
            return UNO;//(2)
        }
        else{
            return UN;//(1)
        }
    } else{
        if(isVowel(noun[0])){
            return UN_APOSTROPHE;//(4)
        } else{
            return UNA;//(3)
        }
    }
}

//C
//returns the length of the noun with his indefinite article
int get_length_indefinite_article(char* noun){
    int indefinite_article = get_indefinite_article(noun);

    if(indefinite_article == 1){
        return strlen(noun) + 3;
    }
    else{
        return strlen(noun) + 4;
    }
}

//D
//adds the correct indefinite article to the noun
void add_indefinite_article(char* noun, char* noun_with_article){    //cases?
    int article_num = get_indefinite_article(noun);
    if(article_num == 1){
        strcpy(noun_with_article, UN_ARTICLE);
    } else if (article_num == 2){
        strcpy(noun_with_article, UNO_ARTICLE);
    } else if (article_num == 3){
        strcpy(noun_with_article, UNA_ARTICLE);
    }else{
        strcpy(noun_with_article, UN_APOSTROPHE_ARTICLE);
    }

    strcat(noun_with_article, noun);
}

//E
//prints the noun with his indefinite article
void handle_indefinite_article(int max_length){
    //char noun[max_length + 1]; C90 forbids variable length array -> use malloc
    // or Declare a fixed-length array that can cope with the maximum string length you want to work with.
    char *noun = (char*)malloc(max_length + 1);
    if(noun == NULL) printf("error \n");
    scanf("%s", noun);

    int len = get_length_indefinite_article(noun);
    char *arr = (char*)malloc(len + 1);
    if(arr == NULL) printf("error \n");

    for(int i = 0; i < len + 1; i++){
        arr[i] = '\0';
    }

    add_indefinite_article(noun, arr);
    printf("%s\n",arr);

    free(noun);
    free(arr);
}


/*-------------------------------------------------------------------------
  Tests
 -------------------------------------------------------------------------*/

//male - ends with o
//starts with whistle letter (z,x,y,gn,ps,ia, ie,ii,io,iu,s-*)
//*consonant letter - not vowel
//needs to start with uno
/*
 8 1 zdlofono
 8 1 xilofono
 8 1 ydlofono
 8 1 gnlofono
 8 1 pslofono
 8 1 ialofono
 8 1 ielofono
 8 1 iilofono
 8 1 iolofono
 8 1 iulofono
 8 1 snlofono
*/

//male - ends with o
//doesnt start with whistle letter
//needs to start with un
/*
5 1 treno
*/

//female - ends with a
//starts with vowel letter (a,e,i,o,u,h)
//needs to start with un'
/*
 5 1 amica
 5 1 emica
 5 1 imica
 5 1 omica
 5 1 umica
 5 1 hmica
*/

//female - ends with a
//doesnt start with vowel letter
//needs to start with una
/*
 5 1 dmica
*/

//full test
/*
5 19 zdono
xiono
ydno
gnono
psono
iaono
ieono
iiono
ioono
iuono
snono
treno
amica
emica
imica
omica
umica
hmica
dmica
 */