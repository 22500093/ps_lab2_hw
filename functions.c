#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

char kname[2][10] = {"A+~F", "P/F"};    /// 실제 정의

int loadData(struct st_class* c[]){
	int count=0;
	FILE* file;

	file=fopen("classes.txt", "r");
	while(!feof(file)){
		c[count] = (struct st_class*)malloc(sizeof(struct st_class));
		int r = fscanf(file, "%d %s %d %d", &(c[count]->code),c[count]->name, &(c[count]->unit), &(c[count]->grading));
		if(r < 4) break;
		count++;
	}
	fclose(file);
	return count;
}

void printAllClasses(struct st_class* c[], int csize){
	for(int i=0; i<csize; i++){
		printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
	}
}

void saveAllClasses(struct st_class* c[], int csize){
	FILE* file;
	file = fopen("classes.txt", "w");
	for(int i=0; i<csize; i++){
		fprintf(file, "%d %s %d %d\n",c[i]->code, c[i]->name, c[i]->unit, c[i]->grading);
	}
	fclose(file);	
}

void findClasses(char* name, struct st_class* c[], int csize){
	int count = 0;

	printf("Searching (keyword : %s)\n", name);
	for(int i=0; i<csize; i++){
		if(strstr(c[i]->name, name)){
			printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
			count++;
		}
	}
	printf("%d classes found.\n", count);
}

// You must complete these functions.
int addNewClass(struct st_class* c[], int csize){
// You must complete this function.

	struct st_class* p = (struct st_class*)malloc(sizeof(struct st_class));

    while(1){
        int i;

        printf(">> code number > ");
        scanf("%d", &(p->code));

        for(i=0; i<csize; i++){
            if(p->code == c[i]->code){
                printf(">> Code duplicated! Retry.\n");
                break;
            }
        }
        if(i == csize) break;
    }

	printf(">> class name > ");
	scanf("%s", p->name);
	printf(">> credits > ");
	scanf("%d", &(p->unit));
	printf(">> grading (1: A+~F, 2: P/F) > ");
	scanf("%d", &(p->grading));

	c[csize] = p;
	return csize+1;
}

void editClass(struct st_class* c[], int csize){
	struct st_class* p;
	int code;

    while(1){
        int i;

        printf(">> Enter a code of class > ");
	    scanf("%d", &code);

        for(i=0; i<csize; i++){
            if(code == c[i]->code){
                p = c[i];
                break;
            }
        }
        if(i == csize) printf("> No such class.\n");
        else break;
    }
	
	printf("> Current: [%d] %s [credits %d - %s]\n",p->code, p->name, p->unit, kname[p->grading-1]);
	printf("> Enter new class name > ");
	scanf("%s", p->name);
	printf("> Enter new credits > ");
	scanf("%d", &(p->unit));
	printf("> Enter new grading(1:Grade, 2: P/F) > ");
	scanf("%d", &(p->grading));

	printf("> Modified.\n");

}


// You must make all these functions.

int applyMyClasses(int my[], int msize, struct st_class* c[], int csize){
                    // my[] : 내가 신청한 과목코드 배열
    int i, num, code;
    struct st_class* p ;    // 메모리 할당 없이 포인터변수에 입력받기 불가능.

    while(1){
        printf(">> Enter a class code > ");
	    scanf("%d", &code);

        for(i=0; i<csize; i++){
            if(code == c[i]->code){
                break;
            }
        }
        if(i == csize){
            printf(">> No such code of class.\n");
            continue;
        } 
        else {
            p = c[i];
            printf(">> [%d] %s [credits %d - %s]\n",p->code, p->name, p->unit, kname[p->grading-1]);
            my[msize] = p->code;  // 신청한 과목코드를 넣기!!
            msize ++;
        } 

        printf(">> Add more?(1:Yes 2:No) > ");
        scanf("%d", &num);

        if(num == 2) break;
    }
		
	return msize;
}

void printMyClasses(int my[], int msize, struct st_class* c[], int csize){

    int all_credits=0;

    for(int i=0; i<msize; i++){
        for(int j=0; j<csize; j++){
            if( my[i] == c[j]->code ){
                printf("%d. [%d] %s [credits %d - %s]\n", i+1, c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading-1]);
                all_credits += c[j]->unit;
                break;
            }
        }
    }

    printf("All : %d credits\n", all_credits);
}

void saveMyClass(int my[], int msize, struct st_class* c[], int csize){

    FILE* file;
    file = fopen("my_classes.txt", "w");

    //if(file != NULL){     // 조건 필수!!

        fprintf(file, "My Classes\n");

        int all_credits=0;
        int first=0, second=0;

        for(int i=0; i<msize; i++){
            for(int j=0; j<csize; j++){
                if( my[i] == c[j]->code ){
                    fprintf(file, "%d. [%d] %s [credits %d - %s]\n", i+1, c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading-1]);
                    
                    all_credits += c[j]->unit;
                    if(c[j]->grading == 1) first += c[j]->unit;
                    else second += c[j]->unit;

                    break;
                }
            }
        }

        fprintf(file, "All : %d classes, %d credits (A+~F %d credits, P/F %d credits)\n", msize, all_credits, first, second);
    //}
	fclose(file);		
}