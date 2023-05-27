#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<dirent.h>
#include<conio.h>
char ex[] = "./";
char users_ex[] = "./database/users/";
char students_ex[] = "./database/students/";
char subjects_ex[] = "./database/subjects/";
char proff_ex[] = "./database/profs/";
char courses_ex[] = "./database/courses/";
char admins_ex[] = "./database/admins/";
char notfcations_ex[] = "./database/notfcations/";
int calculas0 = 12006;
struct user
{
   int id;
   char password[255];
   char auth;
   int profile;
};


struct subject
{
    int id;
    char code[255];
    char name[255];
    int sub;
    int term;
    int is_it_n;
    int s;
    int pre;
    int hours;

};



struct student
{   
    int id;
    char name[255];
    int term;
    char group;
    int c0;
    float gpa;
    int not_able_to_reg;
    struct subs{
        int sub_id;
        int course_id;
        int w3;
        int w7;
        
        int final;
        int free;
        int att[14];
    }subs[7];

    struct done_couses{
        int subject_id;
        char sub_done_name[255];
        char code[255];
        int grade;
        int term;
    } done_couses[50];

};

struct doctor 
{
    int id;
    char name[255];
    int subs[30][2];
            
};


struct course
{
    int id;
    int doctor;
    int subject;  
    int students[100][2];  

};




void reset () {
  printf("\033[0m");
}


void faild (char x[]) {
  printf("\033[1;31m");
  printf("%s",x);
  reset();
}


void success (char x[]) {
  printf("\033[1;32m");
  printf("%s",x);
  reset();
}


void warning (char x[]) {
  printf("\033[1;33m");
  printf("%s",x);
  reset();
}


int is_file_exsist(char ex[]){
    FILE* file = fopen(ex,"r");
    if(file == NULL){
        fclose(file);
        return 0;
    }
    
    fclose(file);

    return 1;
}




int is_there_nofication(int id) {
  int count = 0;
  char filename[255];
  sprintf(filename,"%s%d.txt",notfcations_ex,id);
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    return 0;
  }

  // Count the number of lines in the file.
  char line[1000];
  while (fgets(line, sizeof(line), fp) != NULL) {
    count++;
  }

  fclose(fp);
  return count;
}

void print_notficaton_and_delete_file(int id) {
     char filename[255];
  sprintf(filename,"%s%d.txt",notfcations_ex,id);
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    return;
  }

  // Print all the lines in the file.
  char line[1000];
  while (fgets(line, sizeof(line), fp) != NULL) {
    printf("%s\n", line);
  }

  // Delete the file.
 

  fclose(fp);
  
   remove(filename);
}



void add_notfication(int id, char msg[255]){
    char filename[255];
    sprintf(filename,"%s%d.txt",notfcations_ex,id);
    if(!is_file_exsist(filename)){
        FILE* file = fopen(filename,"w");
        fclose(file);
    }

    FILE* file = fopen(filename,"a");
    fputs(msg,file);
    fclose(file);
    
}






int count_cours_students(struct course s){
    int counter = 0;
    for (int i = 0; i < sizeof(s.students); i++)
    {
        if(s.students[i][0]){
            counter++;
        }
    }
    return counter;
    
}


struct student get_student(int id){
    struct student s;
    char file_name[255];
    sprintf(file_name,"%s%d.bin",students_ex,id);
    if (is_file_exsist(file_name))
    {
        FILE* file = fopen(file_name,"rb");
        fread(&s,sizeof(struct student),1,file);
        

        fclose(file);
    }
    
return s;
}


struct user get_user(int id){
    struct user s;
    char file_name[255];
    sprintf(file_name,"%s%d.bin",users_ex,id);
    if (is_file_exsist(file_name))
    {
        FILE* file = fopen(file_name,"rb");
        fread(&s,sizeof(struct user),1,file);
        

        fclose(file);
    }
    
return s;
}


struct subject get_subject(int id){
    struct subject s;
    char file_name[255];
    sprintf(file_name,"%s%d.bin",subjects_ex,id);
    if (is_file_exsist(file_name))
    {
        FILE* file = fopen(file_name,"rb");
        fread(&s,sizeof(struct subject),1,file);
        

        fclose(file);
    }
    
return s;
}



struct doctor get_proffesor(int id){
    struct doctor s;
    char file_name[255];
    sprintf(file_name,"%s%d.bin",proff_ex,id);
    if (is_file_exsist(file_name))
    {
        FILE* file = fopen(file_name,"rb");
        fread(&s,sizeof(struct doctor),1,file);
        

        fclose(file);
    }
    
return s;
}



struct course get_course(int id){
    struct course s;
    char file_name[255];
    sprintf(file_name,"%s%d.bin",courses_ex,id);
    if (is_file_exsist(file_name))
    {
        FILE* file = fopen(file_name,"rb");
        fread(&s,sizeof(struct course),1,file);
        

        fclose(file);
    }
    
return s;
}



int empty_cours_students(struct course s){
    int counter = 0;
    for (int i = 0; i < sizeof(s.students); i++)
    {
        if(!(s.students[i][0])){
            counter = i;
            break;
        }
    }
    return counter;
    
}



int is_doctor_exsist(int id){
    int res = 0;
    char filename[255];
    struct doctor d;
    //struct user u;
    sprintf(filename,"%s%d.bin",proff_ex,id);
    if(is_file_exsist(filename)){
      return 1;
    }else{
           

        return 0;
    }
    
    
}

int is_sub_exsist(int id){
    char ex[255];
    sprintf(ex,"%s%d.bin",subjects_ex,id);
    FILE* file = fopen(ex,"r");
    if(file == NULL){
        fclose(file);
        return 0;
    }
    fclose(file);

    return 1;
}


int is_course_exsist(int id){
    char ex[255];
    sprintf(ex,"%s%d.bin",courses_ex,id);
    FILE* file = fopen(ex,"r");
    if(file == NULL){
        fclose(file);
        return 0;
    }
    fclose(file);

    return 1;
}


int is_student_exsist(int id){
    char ex[255];
    sprintf(ex,"%s%d.bin",students_ex,id);
    FILE* file = fopen(ex,"r");
    if(file == NULL){
        fclose(file);
        return 0;
    }
    fclose(file);

    return 1;
}


int count_files(char path[]){
    DIR *d;
    struct dirent *dir;
    int counter = 0;
    d = opendir(path);

    if(d){
        while ((dir = readdir(d)) != NULL)
        {
           // printf("%s\n",dir->d_name);
            counter++;
        }
        closedir(d);
        
    }
    return counter;
}



int is_subject_has_course(int id){
    DIR *d;
    struct dirent *dir;
    struct course c;
    int counter = 0;
    d = opendir(courses_ex);

    if(d){
        while ((dir = readdir(d)) != NULL)
        {
            char filename[255];
            sprintf(filename,"%s%s",courses_ex,dir->d_name);
           FILE* file = fopen(filename,"r");
           fread(&c,sizeof(struct course),1,file);
           fclose(file);
           if(c.subject == id)
           return c.id;

            
        }
        closedir(d);
        
    }
    return 0;
}


void Print_all_subjects(int term){

 DIR *d;
    struct dirent *dir;
    int counter = 0;
    d = opendir(subjects_ex);

    if(d){
        while ((dir = readdir(d)) != NULL)
        {
              if(strcmp(".",dir->d_name) && strcmp("..",dir->d_name)){
            char file_name[255];
            sprintf(file_name,"%s%s",subjects_ex,dir->d_name);
            struct subject s;
            FILE* file = fopen(file_name,"r");
            fread(&s,sizeof(struct subject),1,file);
            fclose(file);
            if(term ){
                if( s.term == term)
            printf("\n\nID : %d\nCode : %s\nName : %s\nHours : %d\nPre-Name : %s\n______________\n",s.id,s.code,s.name,s.hours,get_subject(s.pre).name);
            
            }else
            printf("\n\nID : %d\nCode : %s\nName : %s\nHours : %d\nPre-Name : %s\n______________\n",s.id,s.code,s.name,s.hours,get_subject(s.pre).name);

            counter++;
              }
            
        }
        closedir(d);
         if(counter<1){
            warning("\n \t\tthere is no doctors added yet\n\n");
        }
        
    }
  


}



void Print_all_students(){

 DIR *d;
    struct dirent *dir;
    int counter = 0;
    d = opendir(students_ex);

    if(d){
        while ((dir = readdir(d)) != NULL)
        {
            if(strcmp(".",dir->d_name) && strcmp("..",dir->d_name)){
            char file_name[255];
            sprintf(file_name,"%s%s",students_ex,dir->d_name);
            struct student s;
            FILE* file = fopen(file_name,"r");
            fread(&s,sizeof(struct subject),1,file);
            fclose(file);
            printf("ID : %d\nName : %s\n______________\n",s.id,s.name);
            counter++;
            
        }
        }
        closedir(d);
        if(counter<1){
            warning("\n \t\tthere is no student added yet\n\n");
        }
    }
  


}



void Print_all_proffesors(){

 DIR *d;
    struct dirent *dir;
    int counter = 0;
    d = opendir(proff_ex);

    if(d){
        while ((dir = readdir(d)) != NULL)
        {
            if(strcmp(".",dir->d_name) && strcmp("..",dir->d_name)){
            char file_name[255];
            sprintf(file_name,"%s%s",proff_ex,dir->d_name);
            struct doctor s;
            FILE* file = fopen(file_name,"r");
            fread(&s,sizeof(struct doctor),1,file);
            fclose(file);
            printf("\nID : %d\nName : %s\n______________\n",s.id,s.name);
            counter++;
            
        }
        }
        closedir(d);
        if(counter<1){
            warning("\n \t\tthere is no doctors added yet\n\n");
        }
    }
  


}


void Print_all_courses(int id,int term){

 DIR *d;
    struct dirent *dir;
    int counter = 0;
    d = opendir(courses_ex);

    if(d){
        while ((dir = readdir(d)) != NULL)
        {
            
            if(strcmp(".",dir->d_name) && strcmp("..",dir->d_name)){
            char file_name[255];
            sprintf(file_name,"%s%s",courses_ex,dir->d_name);
            struct course s;
            FILE* file = fopen(file_name,"r");
            fread(&s,sizeof(struct course),1,file);
            fclose(file);
            if(id && !term){
                if(s.subject == id )
            printf("\nID : %d\nSubject : %s\ndoctor : %s\n______________\n",s.id,get_subject(s.subject).name,get_proffesor(s.doctor).name);
            
            }else if(term && !id){
                 if(get_subject(s.subject).term == term)
            printf("\nID : %d\nSubject : %s\ndoctor : %s\n______________\n",s.id,get_subject(s.subject).name,get_proffesor(s.doctor).name);
             
            }else if(id && term){
                 if(get_subject(s.subject).term == term && s.subject == id )
            printf("\nID : %d\nSubject : %s\ndoctor : %s\n______________\n",s.id,get_subject(s.subject).name,get_proffesor(s.doctor).name);
             
            }else{
            printf("\nID : %d\nSubject : %s\ndoctor : %s\n______________\n",s.id,get_subject(s.subject).name,get_proffesor(s.doctor).name);
                
            }
            
        }
        counter++;
        }
        closedir(d);
        if(counter<1){
            warning("\n \t\tthere is no courses added yet\n\n");
        }
    }
  


}










void Print_all_courses_for_proffessor(int id,int term){

 DIR *d;
    struct dirent *dir;
    int counter = 0;
    d = opendir(courses_ex);

    if(d){
        while ((dir = readdir(d)) != NULL)
        {
            
            if(strcmp(".",dir->d_name) && strcmp("..",dir->d_name)){
            char file_name[255];
            sprintf(file_name,"%s%s",courses_ex,dir->d_name);
            struct course s;
            FILE* file = fopen(file_name,"r");
            fread(&s,sizeof(struct course),1,file);
            fclose(file);
            
            if(s.doctor == id && term){
                    if(term == get_subject(s.subject).term)
                    printf("\nID : %d\nSubject : %s\ndoctor : %s\n",s.id,get_subject(s.subject).name,get_proffesor(s.doctor).name);

            }else if(s.doctor == id)
                    printf("\nID : %d\nSubject : %s\ndoctor : %s\n",s.id,get_subject(s.subject).name,get_proffesor(s.doctor).name);

           
            
        }
        counter++;
        }
        closedir(d);
        if(counter<1){
            warning("\n \t\tthere is no courses added yet\n\n");
        }
    }
  


}









void creat_subject(){
    int id;
    char name;
    char code[255];

    while (1)
    {
        printf("\n Input Subject uniqe code : ");
        scanf("%s",code);
         DIR *d;
            struct dirent *dir;
        int counter = 0;
        d = opendir(subjects_ex);
        int is_in = 0;
        if(d){
            while ((dir = readdir(d)) != NULL)
                {
                    char temp_name[255];
                    sprintf(temp_name,"%s%s",subjects_ex,dir->d_name);
                    FILE* f = fopen(temp_name ,"r");
                    struct subject s;
                    fread(&s,sizeof(struct subject),1,f);
                       if(strcmp(s.code,code) == 0){
                            is_in = 1;
                       }

                 fclose(f);
                }
            closedir(d);

        
    }
    if (is_in)
    {
        faild("\nWronge code : ");

        warning("\n\t\tCode is already taken\n");

        continue;
    }else{
        break;
    }
    

    }

   

    id = count_files(subjects_ex)+12000+1;

    struct subject sub = {
        .id = id,
    };
   // char subject_buffer[255];
    printf("\n Input Subject name : ");
      fflush(stdin);
    fgets(sub.name,254 ,stdin);
    //sprintf(sub.name,"%s",subject_buffer);
   //scanf ("%[^\n]%*c", sub.name);
   // scanf("%[^\n]s",&sub.name);
     //   scanf("%s",&sub.name);
    
    printf("\n Input Subject Term [1-8]: ");
      fflush(stdin);
    scanf("%d",&sub.term);
    if (sub.name[strlen(sub.name) - 1] == '\n') {
    sub.name[strlen(sub.name) - 1] = '\0';
    }
    
    printf("\n Input Subject hours : ");
      fflush(stdin);
    scanf("%d",&sub.hours);

     while (1)
    {
       
        char pre;
        printf("doce this subject has a pre [y/n]: ");
        fflush(stdin);
        scanf("%c",&pre);
        if(pre == 'y'){
            while (1)
            {
                int id;
                char file_name[255];
                 printf("Input Subject id : ");
                scanf("%d",&id);
                sprintf(file_name,"%s%d.bin",subjects_ex,id);
                if(is_sub_exsist(id)){
                        sub.pre = id;
                        break;
                }else{
                     faild("\nwronge id\n");
                    warning("\t\t*subject dose not exist\n");
                }
            }
            
            break;
        }else if(pre == 'n'){
            sub.pre = 0;
            break;
        }else{
            faild("\nValid Input\n");
            warning("\t\t*please Anwser by y/n [y => yes , n => no]\n");
        }
    }

    sprintf(sub.code,"%s",code);
   // sprintf(sub.name,"%s",name);
    char file_name[255];
    sprintf(file_name,"%s%d.bin",subjects_ex,id);

    FILE* file = fopen(file_name,"w");
    fwrite(&sub,sizeof(struct subject),1,file);
    if(file != NULL){
    success("\nSubject Created\n");
     printf("ID : %d\nCode : %s\nName : %s\npre-Name : %s\n______________\n",sub.id,sub.code,sub.name,get_subject(sub.pre).name);
    }
    else
    faild("\nSubject Creat faild\n");

    fclose(file);
   

}


int creat_student(){
    int id = 220000+count_files(students_ex);
    char filename[255];
    while(1){
        sprintf(filename,"%s%d.bin",students_ex,id);
        if(is_file_exsist(filename) == 0){
            break;
        }else
        id++;
    }




    struct student s;

    s.id = id;
    printf("\n Input Student Name : ");
    scanf("%s",&s.name);

    while (1)
    {
        char pre;
        printf("\n Is the student pre [y/n]: ");

        scanf("%c ",&pre);
        if(pre == 'y'){
            s.c0 = 1;
            break;
        }else if(pre == 'n'){
            s.c0 = 0;
            break;
        }else{
            faild("\nValid Input\n");
            warning("\t\t*please Anwser by y/n [y => yes , n => no]\n");
        }
    }
    
    FILE *file = fopen(filename,"w");
    for(int i = 0;i < 7;i++){
        s.subs[i].free = 1;
    }
      for(int i = 0;i < 50;i++){
        s.done_couses[i].subject_id = 0;
    }
    s.term = 1;
    fwrite(&s,sizeof(struct student),1,file);
    if(file != NULL){
        success("\n Student created\n");
        fclose(file);
        return id;
    }else{
         faild("\n Student creating faild\n");
        fclose(file);
        return -1;
    }

}

void save_student(struct student s){
    char filename[255];
    sprintf(filename,"%s%d.bin",students_ex,s.id);
     FILE *file = fopen(filename,"w");
     
    fwrite(&s,sizeof(struct student),1,file);
    if(file != NULL){
       
        fclose(file);
        
    }else{
       
        fclose(file);
        
    }
}



int creat_proff(){
    int id = 51000+count_files(proff_ex);
    char filename[255];
    while(1){
        sprintf(filename,"%s%d.bin",proff_ex,id);
        if(is_file_exsist(filename) == 0){
            break;
        }else
        id++;
    }
    struct doctor d;

    d.id = id;
    printf("\n Input Proffesor Name : ");
    scanf("%s",&d.name);
    FILE *file = fopen(filename,"w");
    fwrite(&d,sizeof(struct doctor),1,file);
    if(file != NULL){
        success("\nProffesor  created\n");
        fclose(file);
        return id;
    }else{
         printf("\n Student created faild\n");
        fclose(file);
        return -1;
    }

}


void save_course(struct course s){
    char filename[255];
    sprintf(filename,"%s%d.bin",courses_ex,s.id);
     FILE *file = fopen(filename,"w");
    fwrite(&s,sizeof(struct course),1,file);
    if(file != NULL){
       
        fclose(file);
        
    }else{
        
        fclose(file);
        
    }
}


int get_user_by_profile(int profile){
        DIR *d;
    struct dirent *dir;
    int counter = 0;
    char file_name[255];
    d = opendir(users_ex);
    struct user User;

    if(d){
        while ((dir = readdir(d)) != NULL)
        {
           sprintf(file_name,"%s%s",users_ex,dir->d_name);
           FILE* file = fopen(file_name,"r");
           fread(&User,sizeof(struct user),1,file);
           fclose(file);
           if(User.profile == profile)
           return User.id;
        }
        closedir(d);
        
    }
    return 0;
 }


void get_student_data(int id){
    char con;
    int one_time = 0;
    if(id){
            one_time = 1;
    }

    while(1){
        if(!id){
        printf("\nInput Student ID [-1 for cancle]: ");
        fflush(stdin);
        scanf("%d",&id);
        }
        if(id == -1)
        break;
        else{
            if (is_student_exsist(id))
            {
               struct student s = get_student(id);
               printf("ID : %d\n",s.id);
            
               printf("Name : %s\n",s.name);
               printf("Term : %d\n",s.term);
               printf("Term : %f\n",s.gpa);
               printf("Login-id : %d\n",get_user(get_user_by_profile(s.id)).id);
               printf("Login_password : %s\n",get_user(get_user_by_profile(s.id)).password);
               printf("courses : \n");
               
               for(int i = 0;i<7;i++){
                if(!s.subs[i].free){
               printf("\t\tSubject Name : %s\n",get_subject(s.subs[i].sub_id).name);
               printf("\t\tSubject code : %s\n",get_subject(s.subs[i].sub_id).code);
               printf("\t\tcourse id : %d\n",s.subs[i].course_id);
               printf("\t\tdoctor Name : %s\n",get_proffesor(get_course(s.subs[i].course_id).doctor).name);
               printf("\n\t\t---------------------------\n");
                }

               }
                break;
              
                
            }else{
                faild("\nWronge ID\n");
                warning("\t\tStudent dose not exist\n");
            }
            
        }

        if(one_time)
        break;
        
    }
    
}


void get_proffesor_data(int id){
    char con;
    int one_time = 0 ;
    if(id){
        one_time = 1;
    }

    while(1){
        if(!id){
        printf("\nInput proffesor ID [-1 for cancle]: ");
        scanf("%d",&id);
        }
      
        if(id == -1)
        break;
        else{
            if (is_doctor_exsist(id))
            {
               struct doctor s = get_proffesor(id);
               printf("ID : %d\n",s.id);
               printf("Name : %s\n",s.name);
               
              // printf("Term : %d\n",s.subs);
              
              break;  
            }else{
                faild("\nWronge ID\n");
                warning("\t\tdoctor dose not exist\n");
            }
            
        }
        if(one_time)
        break;
        
    }
    
}



void save_user(struct user u , char ex[]){
    
    FILE* file = fopen(ex,"w");
    fwrite(&u,sizeof(struct user),1,file);
    if(file != NULL){
        success("\n\t\tUser Created Successfuly\n");

    }else{
        faild("\n\t\tFaild to create User\n");

    }
    fclose(file);

}

void creat_user(){
    char file_name[255];
    char password[255];
    char id_s[255];
    int id;
    char auth;
    
    while (1)
    {
    printf("Input User Type\n\tp => professor\n\ts => student\n\ta => adminstrator : ");
    scanf("%c ",&auth);
    if(auth == 'a' || auth == 's' || auth == 'p')
    break;
    else
    faild("\nWronge input\n");
    }




     while (1)
    {
    printf("Input User id : ");
    scanf("%s",&id_s);
    id = atoi(id_s);
    sprintf(file_name,"%s%d.bin",users_ex,id);
    
    if(is_file_exsist(file_name) != 1)
    break;
    else{
    faild("\nsome thing is Wronge : ");
    warning("\n\t\tuser is already taken\n");
    }
    }




    while (1)
    {
    printf("\nInput User password : ");
    scanf("%s",&password);
    
    
    if(strlen(password) > 7)
    break;
    else
    faild("\nWronge password format : ");
    warning("\n\t\tPassword must be minimum 8 chars\n");

    }

    struct user u;
    u.auth = auth;
    sprintf(u.password,"%s",password);
    
    switch (auth)
    {
    case 's':
        int sprofile = creat_student();
        u.id = id;
        u.profile = sprofile;
        u.auth = 's';

        FILE* sfile = fopen(file_name,"w");
        fwrite(&u,sizeof(struct user),1,sfile);
        if(sfile != NULL && sprofile != -1){
            
            success("\nUser created succesfuly\n");
            fclose(sfile);
           
        }else{
              
            faild("\nfaild to creat\n");
            fclose(sfile);
            remove(file_name);
           
        }
        break;
    


    
    case 'p':
        int dprofile = creat_proff();
        u.profile = dprofile;
        u.id = id;

        u.auth = 'p';
        FILE* dfile = fopen(file_name,"w");
        fwrite(&u,sizeof(struct user),1,dfile);
        if(dfile != NULL && dprofile != -1){
          
            success("\nUser created succesfuly\n");
            fclose(dfile);
           
        }else{
              
            faild("\faild to creat\n");
            fclose(dfile);
            remove(file_name);

           
        }
        break;
    


       
    case 'a':
        
        u.auth = 'a';
        u.id = id;

        FILE* afile = fopen(file_name,"w");
        fwrite(&u,sizeof(struct user),1,afile);
        if(afile != NULL ){
          
            success("\nUser created succesfuly\n");
            fclose(afile);
           
        }else{
              
            faild("\faild to creat\n");
            fclose(afile);
            remove(file_name);

           
        }
        break;
    


    



    default:
        break;
    }


}


void creat_course(){
    int id = 13000+count_files(courses_ex);
    char file_name[255];
    
    
    while(1){
        sprintf(file_name,"%s%d.bin",courses_ex,id);
        if(is_file_exsist(file_name) == 0){
            break;
        }else
        id++;
    }

    struct course s = {
        .id = id,
    };
    
     while (1)
    {
        printf("\nInput subject id : ");
        scanf("%d",&s.subject);
        if(is_sub_exsist(s.subject))
        {
            break;
        }else{
             faild("\nWronge Subject Id : ");

             warning("\n\t\tSubject do Not exsist\n");
        }
    }
    

    while (1)
    {
        printf("\nInput Doctor id : ");
        scanf("%d",&s.doctor);
        if(is_doctor_exsist(s.doctor))
        {
            break;
        }else{
             faild("\nWronge proffesor Id : ");

             warning("\n\t\tDoctor do Not exsist\n");
        }
    }
    
;

            sprintf(file_name,"%s%d.bin",courses_ex,id);
            FILE* file = fopen(file_name,"wb");

            if(file == NULL){
             faild("\nFaild to create Cours\n");
                fclose(file);
            }else{
               
                fwrite(&s,sizeof(struct course),1,file);
             success("\ncours created successfuly\n");
             fclose(file);
             char msg[255];
             sprintf(msg,"The have new course %s\n",get_subject(s.subject).name);
             add_notfication(s.doctor,msg);

            }
    


}


struct user auth(){
    int id[255];
    char password[255];
    printf("Input Username : ");
    scanf("%s",&id);
    printf("Input Passwort : ");
    scanf("%s",&password);

    char file_name[255];
    sprintf(file_name,"%s%s.bin",users_ex,id);
    if(is_file_exsist(file_name)){
        FILE *file = fopen(file_name,"r");
        struct user u;
        fread(&u,sizeof(struct user),1,file);
        fclose(file);
        if (strcmp(password,u.password) == 0)
        {
           
            return u;
        }else{
            
        faild("\t\tWronge User Or ID 1\n");
        return auth();
        }
        
         
    }else{
        faild("\t\tWronge User Or ID \n");

        return auth();
    }


}


int is_subject_regestrated(int student_id , int subject_id){

   struct student st = get_student(student_id);
   struct subject sub = get_subject(subject_id);
   int max = 7;
   
   
   for (int i = 0; i < 7; i++)
   {
   
    if(st.subs[i].sub_id == subject_id && !(st.subs[i].free))
    return i+1;
    
   }
   
   return 0;

}



int is_subject_done(int student_id , int subject_id){

   struct student st = get_student(student_id);
   struct subject sub = get_subject(subject_id);
   
   
   
   for (int i = 0; i < 50; i++)
   {
    if(st.done_couses[i].subject_id == subject_id || strcmp(st.done_couses[i].code,get_subject(subject_id).code)  == 0)
    return 1;
    
   }
   
   return 0;

}


void print_one_subject_data(int id){
    if(is_sub_exsist(id)){
        struct subject s = get_subject(id);
         printf("ID : %d\nCode : %s\nName : %s\nHours : %d\nPre-Name : %s\n______________\n",s.id,s.code,s.name,s.hours,get_subject(s.pre).name);
    }else
    faild("\nWronge Id\n");
}


void print_one_course_data(int id){
    if(is_course_exsist(id)){
        struct course s = get_course(id);
          printf("\nID : %d\nSubject : %s\ndoctor : %s\n",s.id,get_subject(s.subject).name,get_proffesor(s.doctor).name);
          printf("group Students : \n\n");
          for(int i = 0;i<100;i++){
            if(s.students[i][0]){
                
                 printf("id : %d\nName : %s\n--------\n",s.students[i][1],get_student(s.students[i][1]).name);

            }
          }
    }else
    faild("\nWronge Id\n");
}


int finde_free_space_to_register(int student_id){
   struct student st = get_student(student_id);

    for (int i = 0; i < 7; i++)
    {
     if(st.subs[i].free)
     return i;
     

    }
return -1;    
}


int count_registerd_courses(int student_id){
   struct student st = get_student(student_id);
    int counter = 0;
    for (int i = 0; i < 7; i++)
    {
     if(st.subs[i].free == 0)
     counter++;
     

    }
return counter++;    
}


int count_free_courses(int student_id){
   struct student st = get_student(student_id);
    int counter = 0;
    for (int i = 0; i < 7; i++)
    {
     if(st.subs[i].free == 1)
     counter++;
     

    }
return counter;    
}

int finde_free_space_into_done_courses(int student_id){
   struct student st = get_student(student_id);

    for (int i = 0; i < 5; i++)
    {
     if(!st.done_couses[i].subject_id)
     return i;
     

    }
return -1;    
}



int finde_free_space_into_course_to_student(int course_id){
   struct course course = get_course(course_id);

    for (int i = 0; i < 100; i++)
    {
     if(!course.students[i][0])
     return i+=1;
     

    }
return 0;    
}




int counte_free_spaces_into_course(int course_id){
   struct course course = get_course(course_id);
    int counter = 0;
    for (int i = 0; i < 100; i++)
    {
     if(!course.students[i][0])
      counter++;
     

    }
return counter;    
}

float calculate_points(int grade){
    if(grade<= 100 && grade >= 94)
    return 4.0;
    else if (grade <= 93 && grade >= 90)
    return 3.7;
    else if (grade <= 89 && grade >= 87)
    return 3.3;
    else if (grade <= 86 && grade >= 83)
    return 3.0;
    else if (grade <= 83 && grade >= 80)
    return 3.7;
    else if (grade <= 79 && grade >= 77)
    return 2.3;
    else if (grade <= 76 && grade >= 73)
    return 2.0;
    else if (grade <= 72 && grade >= 70)
    return 1.7;
    else if (grade <= 79 && grade >= 67)
    return 1.3;
    else if (grade <= 66 && grade >= 60)
    return 1.0;
    else if (grade <= 59 && grade >= 0)
    return 1.3;
    

    

}

float gpa_calculator(struct student student){
    float total_hours = 0;
    float upper_part = 0;
    float gpa;
    for(int i = 0 ;i<50;i++){
        if(student.done_couses[i].subject_id){
            total_hours += get_subject(student.done_couses[i].subject_id).hours;
        }
    }

     for(int i = 0 ;i<50;i++){
        if(student.done_couses[i].subject_id){
            upper_part += get_subject(student.done_couses[i].subject_id).hours * calculate_points(student.done_couses[i].grade);
        }
    }

    return upper_part/total_hours;    
}


void registration(int student_id){
    int notf = 0;
  if(!student_id){
    while (1)
    {
    printf("Input student Id : ");
    scanf("%d",&student_id);
    notf = 1;
    if(is_student_exsist(student_id)){
        break;
    }else{
        faild("\nWronge id :<\n");
        warning("\t\t student may not be exist\n");
    }
    }
    
   
  }

struct student student = get_student(student_id);

    
   
int couses_abilable;
if(student.term == 1){
couses_abilable = 7;
}else{
    if(student.gpa >= 2.0){
couses_abilable = 7;

    }else{
couses_abilable = 4;

    }
}



    if(!student.not_able_to_reg){
    warning("\n\t\tyou can register ");
    printf("%d",count_free_courses(student.id));
    warning(" courses \n");
    }else{
              warning("\n\t\tyou can\'t register antel the new term\n");
              return ;

    }
  


if(student.c0 &&!is_subject_regestrated(student.id,calculas0) && !is_subject_done(student.id,calculas0) && count_free_courses(student.id) > 0){
    int calculas_course_id;
    warning("\n\t\tBecouse you are scince student you will take calculas0 forcly \n");
    Print_all_courses(calculas0,0);
    while (1)
    {
        printf("\nPlease chose on of these groups[id] : ");
        scanf("%d",&calculas_course_id);
        if(is_course_exsist(calculas_course_id) && get_course(calculas_course_id).subject == calculas0){
            break;
        }else{
            faild("\nsomething Wronge :<\n");
            warning("\n\t\t may be you enterd wronge course Id\n");
            
        }
    }

    int registeration_adress = finde_free_space_to_register(student.id);
    student.subs[registeration_adress].course_id = calculas_course_id;
    student.subs[registeration_adress].sub_id = calculas0;
    student.subs[registeration_adress].free = 0;
    save_student(student);
    struct course cal_course = get_course(calculas_course_id);
    int free_space_into_course = finde_free_space_into_course_to_student(cal_course.id);
    cal_course.students[free_space_into_course][1] = student.id;
    cal_course.students[free_space_into_course][0] = 1;
      if(!(7 - count_free_courses(student.id) < couses_abilable)){
        student.not_able_to_reg = 1;
        }
    save_course(cal_course);
    if(notf){
            char msg[255];
            sprintf(msg,"The have new course registerd by admin %s\n",get_subject(calculas0).name);
             add_notfication(student.id,msg);
    }
    success("\n\t\t Calculas course rigesterd successfuly\n");
}// end of claculas0 register



int con = 1;
int subject_id;
int course_id;
while (con && count_free_courses(student.id)&& count_registerd_courses(student.id) < couses_abilable)
{
int pre = 1;

    Print_all_subjects(student.term);
    printf("Please choose One of these subjects [0 for cancle]:\n");
    scanf("%d",&subject_id);
    if(subject_id){
            if(!is_subject_regestrated(student.id,subject_id) && is_sub_exsist(subject_id)&& !is_subject_done(student.id,subject_id) && get_subject(subject_id).term == student.term){
                    if(get_subject(subject_id).pre ){
                        if(is_subject_done(student.id,get_subject(subject_id).pre))
                        pre = 1;
                        else
                        pre = 0;
                    }
                    if(pre){
                        if (is_subject_has_course(subject_id))
                        {
                           Print_all_courses(subject_id,0);
                                while (1)
                                {
                                           
                           printf("Input course Id : ");
                           scanf("%d",&course_id);
                           if(is_course_exsist(course_id) && get_course(course_id).subject == subject_id){
                            int free_space = finde_free_space_into_course_to_student(course_id);
                            if(free_space){
                                 int registeration_adress2 = finde_free_space_to_register(student.id);
                                   student.subs[registeration_adress2].course_id = course_id;
                                   student.subs[registeration_adress2].sub_id = subject_id;
                                   student.subs[registeration_adress2].free = 0;
                                   if(!(7 - count_free_courses(student.id) < couses_abilable)){
                                    student.not_able_to_reg = 1;
                                   }
                                   save_student(student);
                                   
                                     struct course cal_course = get_course(course_id);
                                   
                                     cal_course.students[free_space][1] = student.id;
                                     cal_course.students[free_space][0] = 1;
                                        save_course(cal_course);
                                         if(notf){
                                         char msg[255];
                                         sprintf(msg,"The have new course registerd by admin %s whith proffesor %s\n",get_subject(cal_course.subject).name,get_proffesor(cal_course.doctor).name);
                                         add_notfication(student.id,msg);

                                        }
                            success("\n\t\tcourse rigesterd successfuly\n");
                                    break;


                            }else{
                                 warning("\n\t\tThere is No free space In this group please chose anthor group or wait antile new groups added\n");
                            printf("Do you wanna continue [yes => 1/no => 0] %d: ",free_space);
                                scanf("%d",&con);

                            }

                           }else{
                             warning("\n\t\tyou probebly enterd Wronge Id\n");
                     printf("Do you wanna continue [yes => 1/no => 0] : ");
                        scanf("%d",&con);
                           }

                                }
                         
                        }else{
                    warning("\n\t\tthis subject has no courses yet\n");
                     printf("Do you wanna continue [yes => 1/no => 0] : ");
                        scanf("%d",&con);
                        }
                    //Print_all_courses(subject_id,0);




                    }else{
                        warning("\n\t\t You must take ");
                        printf("%s",get_subject(get_subject(subject_id).pre).name);
                        warning(" first\n");
                        printf("Do you wanna continue [yes => 1/no => 0] : ");
                        scanf("%d",&con);

                    }
            }else{
                  faild("\nsomething Wronge :<\n");
                  if( !is_sub_exsist(subject_id))
                    warning("\n\t\t subject may not exsist\n");
                 
                else  if(is_subject_regestrated(student.id,subject_id))
                    warning("\n\t\t subject Is allready registerd\n");
                else if(is_subject_done(student.id,subject_id) )
                    warning("\n\t\t you already taked this subject\n");
                else if( get_subject(subject_id).term != student.term )
                    warning("\n\t\t this subject is not your term\n");

                     printf("Do you wanna continue [yes => 1/no => 0] : ");
                        scanf("%d",&con);
            }
    }else
    break;
}



1;






}




void put_graids(int student_id,int course_address){
    struct student student = get_student(student_id);
    struct course course = get_course(student.subs[course_address].course_id);
    int student_addrees;
    for(int i = 0;i<100;i++){
        if(course.students[i][1] == student.id && course.students[i][0]){
            student_addrees = i;
        }
    }
    int w3,w7,final;
    
    while (1)
    {
    printf("Input The grade out of 100 [-1 for cancle]: ");
    fflush(stdin);
    scanf("%d",&final);
    if(final == -1){
        return;
    }else if(final > 100 || final < 0)
       warning("\nPlease grade must be out of 100\n");
    else
        break;
    }
  
        int done_adrees = finde_free_space_into_done_courses(student.id);

        if(final < 50){
            faild("\nStudent coudent pass the course\n");
            student.subs[course_address].free = 1;
             course.students[student_addrees][0] = 0;
            course.students[student_addrees][1] = 0;
              if(count_registerd_courses(student.id) == 0){
            student.gpa = gpa_calculator(student);
            student.term++;
           }
            save_course(course);
            save_student(student);
             char msg[255];
             sprintf(msg,"You faild %s course becous your grade is %d\n",get_subject(course.subject).name,final);
             add_notfication(student.id,msg);
            
        }else {
            success("\nStudentt passed the course\n");
            student.subs[course_address].free = 1;
            student.done_couses[done_adrees].grade = final;
            student.done_couses[done_adrees].subject_id = course.subject;
           // student.done_couses[done_adrees].sub_done_name = get_subject(course.subject).name;
           if(count_registerd_courses(student.id) == 0){
            student.gpa = gpa_calculator(student);
            student.term++;

           }
            save_student(student);
            course.students[student_addrees][0] = 0;
            course.students[student_addrees][1] = 0;
            save_course(course);
             char msg[255];
             sprintf(msg,"You successd to pass %s course becous your grade is %d\n",get_subject(course.subject).name,final);
             add_notfication(student.id,msg);
        }
}





// int main(){
    
// //creat_user();
// //creat_subject();
// Print_all_subjects();
// //Print_all_proffesors();
// //Print_all_courses();
// //Print_all_students();
// //creat_course();
// //creat_user();
// //printf("%d",is_doctor_exsist(51003));
// // struct student s = get_student(220002);
// // printf("\n%d\n",s.id);
// // struct doctor d = get_proffesor(51002);
// // printf("\n%s\n",d.name);
// //struct subject s = get_subject(12003);
// //printf("\n%s\n",s.code);
//  //struct doctor c =get_proffesor(get_course(13002).doctor);
// // printf("\n%s\n",c.name);
// //Print_all_students();
// }






























void printLargeAAST() {
    int i;

    // ANSI color escape sequences
    char* color_red = "\x1b[36m";
    char* color_reset = "\x1b[0m";

    char largeAAST[11][100] = {
        "    AAAAA       AAAAA      SSSSSS  TTTTTTTTTTTTTTTT",
        "   AAAAAAA     AAAAAAA    SSSSSSSS TTTTTTTTTTTTTTTT",
        "  AAA   AAA   AAA   AAA  SSS              TTT      ",
        " AAA     AAA AAA     AAA SSS              TTT      ",
        " AAA     AAA AAA     AAA  SSSSSS          TTT      ",
        " AAAAAAAAAAA AAAAAAAAAAA    SSSSSS        TTT      ",
        " AAAAAAAAAAA AAAAAAAAAAA      SSSSS       TTT      ",
        " AAA     AAA AAA     AAA         SSS      TTT      ",
        " AAA     AAA AAA     AAA          SSS     TTT      ",
        " AAA     AAA AAA     AAA  SSSSSSSSSS      TTT      ",
        " AAA     AAA AAA     AAA   SSSSSSSS       TTT      "
    };
printf("\n\n");
    for (i = 0; i < 11; i++) {
        // Set color based on row index
        if (i % 2 == 0) {
            printf("%s%s%s\n", color_red, largeAAST[i], color_reset);
        } else {
            printf("%s%s%s\n", color_red, largeAAST[i], color_reset);
        }
    }
}

