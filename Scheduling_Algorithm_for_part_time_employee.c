#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct employee{
char initial;
int available[7];
int offer;
int priority;
int given;
}MOIM;
int array_sum(int*,int);
int lower_bound_cal(int*,MOIM*,int);
void BPB(MOIM*,int,int);
void MPB(MOIM*,int,int);
int col_index_of_smallest_or_random(MOIM*, int,int);
void day_array_extraction(MOIM*, MOIM*, int,int);
int main(){
    srand(time(NULL));
    printf("Hello world.\n");
    /*data for testing*/
    int allocated[7]={3,2,2,3,3,3,3};
    int num_employee=4;
    //MOIM current[7]={{'M',{1,1,1,1,1,1,1},5,1,0},{'N',{1,1,1,1,1,1,1},4,4,0},{'n',{1,1,1,1,1,1,1},4,4,0},{'C',{0,1,1,1,0,1,0},2,4,0},\
    {'O',{0,0,1,1,0,0,0},2,4,0},{'Y',{0,1,0,0,1,1,0},2,4,0},{'A',{1,1,0,0,1,0,1},2,4,0}};
    MOIM current[4]={{'M',{1,1,1,1,1,1,1},6,1,0},{'N',{1,1,1,1,1,1,1},5,4,0},{'O',{1,1,1,1,1,1,1},4,5,0},{'Y',{0,1,1,1,0,1,1},4,5,0}};
    /*testing data ends here*/
    const int global_lower_bound=lower_bound_cal(allocated,current,num_employee);
    if(global_lower_bound==0){
        printf("Error! The total number of employee exceed the available slots.\n");
        return 1;
    }
    MOIM two_dimensional[7][num_employee];
    char final_schedule[7][num_employee];
    for(int f_index=0;f_index<7;++f_index){
    day_array_extraction(two_dimensional[f_index],current,num_employee,f_index);
    MPB(two_dimensional[f_index],num_employee,global_lower_bound);
    BPB(two_dimensional[f_index],num_employee,global_lower_bound);
    int highest_or_random;
    for(int i=0;i<allocated[f_index];++i){
    highest_or_random=col_index_of_smallest_or_random(two_dimensional[f_index],num_employee,f_index);
    final_schedule[f_index][i]=two_dimensional[f_index][highest_or_random].initial;
    --(two_dimensional[f_index][highest_or_random].offer);
    two_dimensional[f_index][highest_or_random].available[f_index]=0;
    }
    for(int i=0;i<num_employee;++i){
        for(int j=0;j<allocated[f_index];++j){
            if(final_schedule[f_index][j]==current[i].initial)
            --current[i].offer;
            ++current[i].given;
            current[i].available[f_index]=0;
        }
    }
    }
    for(int day=0;day<7;++day){
        printf("%d",day);
        for(int employee=0;employee<allocated[day];++employee){
            printf("%c\n",final_schedule[day][employee]);
        }
    }
    return 0;
}
int lower_bound_cal(int* allocated,MOIM* offer,int num_employee){
    int total_allocated, total_offer=0,priority_1_tracker=0;
    total_allocated=array_sum(allocated,7);
    for(int i=0;i<num_employee;++i){
    if(offer[i].priority==1){
        total_allocated-=offer[i].offer;
        ++priority_1_tracker;
    }
    }
    int i=0;
    while((num_employee-priority_1_tracker)*i<=total_allocated){
        ++i;
    }
    if((num_employee-priority_1_tracker)*i>total_allocated){
        --i;
    }
    return i;
}
int array_sum(int* array, int size){
    int sum=0;
    for(int i=0;i<size;++i){
        sum+=array[i];
    }
    return sum;
}
void BPB(MOIM* waitor,int num_employee,int lower_bound){ /*Bounded priority boost*/
int i=0;
int temp_bound;
while((waitor[i].priority!=0)&&(i<num_employee)){
    if(waitor[i].offer<lower_bound){
        temp_bound=waitor[i].offer;
    }
    else{
        temp_bound=lower_bound;
    }
    if((array_sum(waitor[i].available,7)<= temp_bound)&&(waitor[i].priority!=1)&&(waitor[i].given<temp_bound)){
        waitor[i].priority=2;
    }
    ++i;
}
    return;
}
void MPB(MOIM* waitor,int num_employee,int lower_bound){/*Minimum priority boost*/
int i=0;
while((waitor[i].priority!=0)&&(i<num_employee)){
    if((waitor[i].offer<=lower_bound)&&(waitor[i].priority!=1)){
        waitor[i].priority=3;
    }
    ++i;
}
    return;
}
int col_index_of_smallest_or_random(MOIM* input,int size,int day_index){
    int same_value_tracker[size];
    int smallest=size+1;
    int index,i=0,j=0;
    while((input[i].priority!=0)&&(i<size)){
        if((input[i].priority<smallest)&&(input[i].available[day_index])&&(input[i].offer!=0)){
            smallest=input[i].priority;
            index=i;
        }
        ++i;
    }
    i=0;
    if(smallest!=(size+1)){
    while((input[i].priority!=0)&&(i<size)){
        if((input[i].priority==smallest)&&(input[i].available[day_index])&&(input[i].offer!=0)){
            same_value_tracker[j++]=i;
        }
        ++i;
    }
    }
    else{
        while((input[i].priority!=0)&&(i<size)){
            if(input[i].available[day_index]){
                index=i;
            }
            ++i;
        }
    }
    if(j==0){
        return index;
    }
    else{
        return(same_value_tracker[(rand()%j)]);
    }
}
void day_array_extraction(MOIM* day_array, MOIM* current, int num_employee,int day_index){
    int i,available_index=0;
    for(i=0;i<num_employee;++i){
        if(current[i].available[day_index]){
            day_array[available_index++]=current[i];
        }
    }
    if(available_index<num_employee){
    day_array[available_index].priority=0;
    }
    return;
}