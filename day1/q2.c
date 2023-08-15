#include<stdio.h>
struct dob{
    int day,month,year;
};
typedef struct student_info{
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
}INFO;

void call_value(INFO ob){
    printf("The Students info are---\n");
    printf("roll no: %d\n",ob.roll_no);
    printf("name: %s\n",ob.name);
    printf("cgpa: %.2f\n",ob.CGPA);
    printf("dob: %d %d %d\n",ob.age.day,ob.age.month, ob.age.year);
}

void call_address(INFO *ob){
    printf("The Students info are---\n");
    printf("roll no: %d\n",ob->roll_no);
    printf("name: %s\n",ob->name);
    printf("cgpa: %.2f\n",ob->CGPA);
    printf("dob: %d %d %d\n",ob->age.day,ob->age.month,ob->age.year);
}
int main()
{
    INFO ob[2];    
    for(int i=0;i<2;i++){
        printf("Enter Student %d info: \n",i+1);
        printf("Name: ");
        scanf("%s",&ob[i].name);
        printf("roll: ");
        scanf("%d",&ob[i].roll_no);
        printf("cgpa: ");
        scanf("%f",&ob[i].CGPA);
        printf("dob day: ");
        scanf("%d",&ob[i].age.day);
        printf("dob month: ");
        scanf("%d",&ob[i].age.month);
        printf("dob year: ");
        scanf("%d",&ob[i].age.year);

    }
    printf("\n\nStudent details called by value...\n");
    call_value(ob[0]);
    printf("\n\nStudent details called by address...\n");

    call_address(&ob[1]);
}