#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HABITS 10 
#define MAX_DAYS 7

typedef struct {
    char name[50];
    int completed[MAX_DAYS];
}Habit ;

Habit habits[MAX_HABITS] ;
int habitcount =0 ;

void addHabit ();
void markHabit ();
void viewHabits();
void weeklyReport();
void saveHabits();
void loadHabits();

int main (){
    loadHabits(); //saved data 
    int choice ;
    while (1){
        printf("HABIT TRACKER\n");
        printf("1-> Add Habit\n");
        printf("2-> Mark Habit as Done\n");
        printf("3-> View Habits\n");
        printf("4-> Weekly REport\n");
        printf("5-> Save & Exit \n");
        printf("ENTER YOUR CHOICE\n");
        scanf("%d",&choice);

        switch(choice){
            case 1 : addHabit() ; 
            break ;
            case 2 : markHabit();
            break ;
            case 3 : viewHabits();
            break;
            case 4 : weeklyReport();
            break ;
            case 5 : saveHabits () ;
            printf("DATA SAVED , THANK YOU \n");
            return 0 ;
            default : printf("INVALID CHOICE\n");
        }
    }
    return 0 ;
}

void addHabit() {
    if (habitcount>=MAX_HABITS){
        printf("HABIT LIMIT REACHED\n");
        return ;
    }
    printf("ENTER YOUR HABIT NAME :\n");
    scanf(" %[^\n]",habits[habitcount].name);

    for (int i=0 ; i<MAX_DAYS ; i++){
        habits[habitcount].completed[i] = 0 ;
    }

    habitcount++ ;
    
    printf("HABIT SUCCESSFULLY ADDED\n");
}

void markHabit () {
    if (habitcount==0){
        printf("NO HABIT FOUND\n");
        return ;
    }

    printf("SELECT THE HABIT\n");
    for(int i=0 ; i<habitcount ; i++){
        printf("%d -> %s\n",i+1 , habits[i].name);
    }
    int selectedhabit ;
    int day ;

    scanf("%d",&selectedhabit);

    selectedhabit-- ;

    if (selectedhabit<0 || selectedhabit>=habitcount){
        printf("INVALID HABIT\n");
        return ;
    }
    printf("ENTER THE DAY TO MARK:\n");
    printf("0->Monday\n1->Tuesday\n2->Wednesday\n3->Thursday\n4->Friday\n5->Saturday\n6->Sunday\n");

    scanf("%d",&day);
    
    if(day<0 || day>=MAX_DAYS){
        printf("INVALID DAY\n");
        return ;
    }

    habits[selectedhabit].completed[day]=1 ;
    printf("MARKED AS DONE \n");
}

void viewHabits(){
    if(habitcount==0){
        printf("NO HABITS FOUND\n");
        return ;
    }

    for(int i=0 ; i<habitcount;i++){
        printf("%s: ",habits[i].name);
        for(int j=0 ;j<MAX_DAYS;j++){
            printf("%s ",habits[i].completed[j]?"[X]":"[ ]");
        }
        printf("\n");
    }
}

void weeklyReport(){
    if(habitcount==0){
        printf("HABIT NOT FOUND\n");
        return ;
    }
    for(int i=0 ; i<habitcount ;i++){
        int doneCount =0 ;
        for (int j=0 ; j<MAX_DAYS ;j++){
            if(habits[i].completed[j])doneCount++ ;
        }
        printf("%s : %d/7 days completed (%.2f%%)\n",habits[i].name,doneCount, (doneCount/7.0)*100);
    }
}

void saveHabits(){
    FILE *file = fopen("habits.txt","w");
    if(!file){
        printf("ERROR SAVING DATA\n");
        return ;
    }
    fprintf(file,"%d\n",habitcount);
    for(int i=0 ;i<habitcount;i++){
        fprintf(file,"%s\n",habits[i].name);
        for(int j=0 ; j<MAX_DAYS ;j++){
            fprintf(file,"%d ",habits[i].completed[j]);
        }
        fprintf(file,"\n");
    }
    fclose(file);
}

void loadHabits(){
    FILE *file = fopen("habits.txt","r");
    if(!file){
        return ;
    }
    fscanf(file,"%d\n",&habitcount);

    for(int i=0 ; i<habitcount ; i++){
        fgets(habits[i].name,sizeof(habits[i].name),file);
        habits[i].name[strcspn(habits[i].name ,"\n")]= 0 ;
        for(int j=0 ; j<MAX_DAYS ;j++){
            fscanf(file,"%d ",&habits[i].completed[j]);
        }
        fscanf(file,"\n");
    }
    fclose(file);
}