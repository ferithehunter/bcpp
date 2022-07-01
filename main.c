#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send();
void editMsg();
void editPass();
void viewAllMessage();

void loadData();
void saveData();

int lastUsrID = 0, lastMsgID = 0, usrID = 0;
char Allmsg[100][200];

struct usr{
    char usrName[50];
    char usrPass[50];
    int msgID[1001];
}usrArr[20];

int main(){
    for(int i = 0; i <= 19; i++){usrArr[i].msgID[0] = 0;}
    loadData();


    while(1){

    while(1){// login system
        char inputPass[50], inputUsr[50], skip = 0;
        int findUsr = 0, findPass = 0, inp;

        printf("Enter username:\n");
        scanf("%s", inputUsr);
        printf("Enter password:\n");
        scanf("%s", inputPass);
        printf("1.Login\n2.Register\nEnter the number of the action: ");
        scanf("%d", &inp);

        if(inp == 1){//login
            for(int i = 1; i <= lastUsrID; i++){
                if(strcmp(usrArr[i].usrName, inputUsr) == 0){
                    findUsr = 1;
                    usrID = i;
                    if(strcmp(usrArr[i].usrPass, inputPass) == 0){findPass = 1; break;}
                }
            }
        }
        if(inp == 2){//register
            for(int i = 1; i <= lastUsrID; i++){
                if(strcmp(usrArr[i].usrName, inputUsr) == 0){
                    printf("Username %s already exist!\n", inputUsr);
                    skip = 1;
                    break;
                }
            }
            if(skip == 0){
                lastUsrID++;
                usrID = lastUsrID;
                strcpy(usrArr[usrID].usrName, inputUsr);
                strcpy(usrArr[usrID].usrPass, inputPass);
                printf("New account created!\n", usrArr[usrID].usrName);
                break;
            }
        }

        if(skip == 0){
            if(findUsr == 0){
                printf("no username matches %s\n", inputUsr);
            }
            if(findUsr == 1 && findPass == 0){
                printf("username and password do not match!\n");
            }
            if(findUsr == 1 && findPass == 1){
                printf("Welcome %s\n", inputUsr);
                break;
            }
        }


    }

    saveData();

    while(1){//main menu
    printf("       ==========================================");
    printf("\n\n1.send message \n2.edit message \n3.view all message \n4.change passeord \n5.exit \nenter number of menu:");

    int menuNum;
    scanf("%d", &menuNum);

    if(menuNum == 1){send(); saveData();}
    if(menuNum == 2){editMsg(); saveData();}
    if(menuNum == 3){viewAllMessage();}
    if(menuNum == 4){editPass(); saveData();}
    if(menuNum == 5){
        saveData();
        break;
    }

    }




}
    return 0;
}

void send(){
    printf("       ==========================================\n");
    printf("send message menu: \n1.send message \n2.exit\n");
    int inp;
    scanf("%d", &inp);
    if(inp == 2){return;}
    lastMsgID++;

    char str[200];
    gets(str);
    printf("%s", str);

    printf("enter the message:");
    char input[200];
    gets(input);

    strcpy(Allmsg[lastMsgID], input);

    usrArr[usrID].msgID[usrArr[usrID].msgID[0] + 1] = lastMsgID;
    usrArr[usrID].msgID[0]++;
    return;
}


void editMsg(){
    printf("       ==========================================\n");
    printf("edit message menu: \n1.edit message \n2.exit\n");
    int inp;
    scanf("%d", &inp);
    if(inp == 2){return;}
    else{printf("enter the message ID:");}
    scanf("%d", &inp);
    if(usrArr[usrID].msgID[0] == 0){printf("wrong message ID\n"); return;}

    for(int i = 1; i <= usrArr[usrID].msgID[0]; i++){//messageID check
        if(inp == usrArr[usrID].msgID[i]){break;}
        if(i == usrArr[usrID].msgID[0]){printf("wrong message ID\n"); return;}

    }

    printf("%s\n", Allmsg[inp]);

    char str[200];
    gets(str);
    printf("%s", str);

    printf("enter the new message:");
    char input[200];
    gets(input);

    strcpy(Allmsg[inp], input);
    return;
}

void viewAllMessage(){
    printf("       ==========================================\n");
    for(int i = 1; i <= lastMsgID; i++){
        printf("%d --> %s\n", i, Allmsg[i]);
    }

    return;
}

void editPass(){
    printf("       ==========================================\n");
    printf("edit password menu: \n1.edit pasword \n2.exit\n");
    int inp;
    scanf("%d", &inp);
    if(inp == 2){return;}
    else{printf("enter the new password:");}
    char input[50];
    scanf("%s", input);
    strcpy(usrArr[usrID].usrPass, input);
    return;

}

void saveData(){
    FILE *fp;
    remove("savedData.txt");
    fp = fopen("savedData.txt", "w");

    fprintf(fp, "%d\n", lastUsrID);
    fprintf(fp, "%d\n", lastMsgID);

    for(int i = 1; i <= lastUsrID; i++){//saving usrs
        fprintf(fp, "%s\n", usrArr[i].usrName);
        fprintf(fp, "%s\n", usrArr[i].usrPass);
        fprintf(fp, "%d ", usrArr[i].msgID[0]);
        for(int j = 1; j <= usrArr[i].msgID[0]; j++){
            fprintf(fp, "%d ", usrArr[i].msgID[j]);
        }
        fprintf(fp, "\n");
    }

    for(int i = 1; i <= lastMsgID; i++){
        fprintf(fp, "%s\n", Allmsg[i]);
    }

    fclose(fp);
}

void loadData(){
    if(fopen("savedData.txt", "r") == NULL){
        return;// agar file vojood nadasht
    }

    FILE *fp;
    fp = fopen("savedData.txt", "r");
    int inp;
    char input[200];

    fscanf(fp, "%d", &lastUsrID);
    fscanf(fp, "%d", &lastMsgID);

    for(int i = 1; i <= lastUsrID; i++){// load krdn user
        fscanf(fp, "%s", input);
        strcpy(usrArr[i].usrName, input);
        fscanf(fp, "%s", input);
        strcpy(usrArr[i].usrPass, input);

        fscanf(fp, "%d", &inp);
        usrArr[i].msgID[0] = inp;
        for(int  j = 1; j <= usrArr[i].msgID[0]; j++){// load krdn msgID
            fscanf(fp, "%d", &inp);
            usrArr[i].msgID[j] = inp;
        }
    }

    for(int i = 1; i <= lastMsgID + 1; i++){
        fgets(input, 200, fp);
        //fscanf(fp, "%[^\n]s", input);
        strcpy(Allmsg[i - 1], input);
    }

    fclose(fp);
}





