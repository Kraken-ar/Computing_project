#include<stdio.h>
#include<math.h>
#include<string.h>
#include <stdlib.h>
#include "funs.h"
//#include "Auth.h"



int main(){
	//creat_user();
	struct user User = auth();
	printLargeAAST();

	while (1)
	{
		char a = User.auth;// auth();
		switch (a)
		{
		case 'a':
			printf("\n1 for add New user[student-proffor-admin]\n");
			printf("2 for add New subject\n");
			printf("3 for add New group\n");
			printf("4 for get data [student-proffor-admin]\n");
			printf("5 for get all [student-proffor-admin]\n");
			printf("6 for get all [subject-course]\n");
			printf("7 for get data [subject-courses]\n");
			printf("8 for register for student [subject-courses]\n");
			int method;
			scanf("%d",&method);
			switch (method)
			{
			case 1:
				creat_user();
				break;

			case 2:
				creat_subject();
			break;
			
			
			case 3:
				creat_course();
			
			break;

			case 4:
			while (1)
			{
				char gm;
				printf("a => admin , p => professor , s => student , q for break : ");
				fflush(stdin);
				scanf("%c",&gm);
				if(gm == 'q')
				break;
				else if(gm == 's'){
				//printf("\n gelty\n");
				get_student_data(0);
				break;
				}
				else if(gm == 'p'){
				get_proffesor_data(0);
				break;
				}
				else
				faild("\nInvalid Input\n");
			}
			
				
			
			break;
			case 5:
				int m;
				printf("\n1 for students\n");
				printf("2 for professors\n");
				
				printf("any ather number for cancle : ");
				scanf("%d",&m);
				switch (m)
				{
				case 1:
					Print_all_students();
					break;
				case 2:
					Print_all_proffesors();
					break;
				


				default:
					break;
				}
				
			break;

			case 6:
				int m2;
				printf("\n1 for subjetcs\n");
				printf("2 for courses\n");
				
				printf("any ather number for cancle : ");
				scanf("%d",&m2);
				switch (m2)
				{
				case 1:
					int subject_term_filter = 0;
					printf("Choose subjects term [0 for all terms] : ");
					scanf("%d",&subject_term_filter);
					Print_all_subjects(subject_term_filter);
					break;
				case 2:
					int courses_term_filter = 0;
					int courses_subject_filter = 0;
					printf("If you want filter by subject Input subject id [0 for all subjects] : ");
					scanf("%d",&courses_subject_filter);
					printf("If you want filter by term Input term [0 for all terms] : ");
					scanf("%d",&courses_term_filter);
					Print_all_courses(courses_subject_filter,courses_term_filter);
					break;
				


				default:
					break;
				}
				
			break;


			case 7:
			printf("\n1 for subjetcs\n");
			printf("2 for courses\n : ");
			fflush(stdin);
			scanf("%d",&m);
			switch (m)
			{
			case 1:
			while (1)
			{
				
			int Subject_id ;
			printf("Input Subject Id : ");
			scanf("%d",&Subject_id);
			print_one_subject_data(Subject_id);
			printf("Do You Wanna search again [1 => yes / 0 => no]: ");
			fflush(stdin);

			scanf("%d",&Subject_id);
			if(!Subject_id)
			break;
			}
			
			case 2:

			while (1)
			{
				
			int course_id ;
			printf("Input course Id : ");
			scanf("%d",&course_id);
			print_one_course_data(course_id);
			printf("Do You Wanna search again [1 => yes / 0 => no]: ");
			scanf("%d",&course_id);
			if(!course_id)
			break;
			}

				break;
			
			default:
				break;
			}
		
				
			break;

			case 8:
				while (1)
				{
					int student_reg;
					printf("Input studnt Id: ");

					scanf("%d",&student_reg);
					if(is_student_exsist(student_reg)){
						registration(student_reg);
					}else{
						faild("\nWronge Id\n");
					}

					printf("Do You Wanna register for another [1 => yes / 0 => no]: ");

					scanf("%d",&student_reg);
					if(!student_reg)
						break;

				}
				
			break;
			default:
				
				break;
			}
			//printf("4 for add New user[student-proffor-admin]\n");
			break;
		

		case 's':

		struct student student = get_student(User.profile);
		
				printf("\n\t\tWELLCOM MR.%s\n\n",student.name);
					if(is_there_nofication(student.id)){
			printf("\t you have %d New notfications\n",is_there_nofication(student.id));
			print_notficaton_and_delete_file(student.id);
		}
				printf("\n1 for Get your data\n");
				printf("2 for your courses \n");
			
				printf("3 For registeration\n");
				printf("4 For your done courses\n");
				
		while (1)

		{
			
			int student_method;
			printf("Input Method Number : ");
			scanf("%d",&student_method);
			switch (student_method)
			{
			case 1:
			printf("\n---------YOUR DATA----------\n");
				get_student_data(student.id);
			printf("\n---------END OFYOUR DATA----------\n");

				break;
			
			case 2:
				printf("\n---------YOUR Couses----------\n");
				for(int i = 0;i<7;i++){
					if(!student.subs[i].free){
						struct course c = get_course(student.subs[i].course_id);
						 printf("\nID : %d\nSubject : %s\ndoctor : %s\n",c.id,get_subject(c.subject).name,get_proffesor(c.doctor).name);
					}
					
				}
				
				printf("\n---------END OF YOUR courses----------\n");
				break;

			case 3:
				registration(student.id);
			break;

			case 4:
				for (int i = 0; i < 50; i++)
				{
					if(student.done_couses[i].subject_id != 0){
						printf("\ncourse Name : %s\nGraid : %d\n-----------------\n",get_subject(student.done_couses[i].subject_id).name,student.done_couses[i].grade);
					}
				}
				
			break;
			default:
				break;
			}
			
			
		}
		
				
		break ;


		case 'p':
		struct doctor prof = get_proffesor(User.profile);
		printf("\n\t\tWELLCOM Dr.%s\n\n",prof.name);
		if(is_there_nofication(prof.id)){
			printf("\t you have %d New notfications\n",is_there_nofication(prof.id));
			print_notficaton_and_delete_file(prof.id);
		}
		int prof_method;
		
				printf("\n1 for Get your data\n");
				printf("2 for showing all your courses \n");
				printf("3 for get courses data\n");
				printf("4 for Put grades And Attindance\n");
				
			
				
		while (1)
		{
			printf("Input Method Number : ");
			scanf("%d",&prof_method);
			switch (prof_method)
			{
			case 1:

					printf("\n---------YOUR DATA----------\n");
					get_proffesor_data(prof.id);
					printf("\n---------END OFYOUR DATA----------\n");

				break;
			case 2:
					int prof_cours_term_filter;
					printf("\nterm filter [0 for all terms]: ");
					scanf("%d",&prof_cours_term_filter);

					printf("\n---------YOUR courses----------\n");
					
					Print_all_courses_for_proffessor(prof.id,prof_cours_term_filter);
					printf("\n---------END OFYOUR courses----------\n");
			break;

			case 3:
				int get_course_id;
				while (1)
				{
					printf("Input course ID : ");
					scanf("%d",&get_course_id);
					if (is_course_exsist(get_course_id) && get_course(get_course_id).doctor == prof.id)
					{
					printf("\n---------YOUR courses----------\n");


						print_one_course_data(get_course_id);
					
					printf("\n---------END OFYOUR courses----------\n");

					}else{
						faild("\nWrong ID\n");
						printf("Do you wanna Continue [1 => yes , 0 for => no]: ");
						scanf("%d",&get_course_id);
						if(!get_course_id)
						break;
					}
					
				}
				
				
			case 4:
			while (1)
			{
				int edit_course_id;
				printf("Input couse Id [0 for cancle] : ");
				scanf("%d",&edit_course_id);

				if(edit_course_id){
					if(is_course_exsist(edit_course_id) && get_course(edit_course_id).doctor == prof.id){
							struct course course = get_course(edit_course_id);
							for(int i = 0;i<100;i++){
								if(course.students[i][0])
								printf("ID : %d\nName : %s\n-------------\n",get_student(course.students[i][1]).id,get_student(course.students[i][1]).name);
							}

							while (1)
							{
								int student_id;
								printf("Input studdent Id [0 for cancle] : ");
								scanf("%d",&student_id);
								if(student_id){
									int sub_adress = is_subject_regestrated(student_id,course.subject);
									if(is_student_exsist(student_id) && sub_adress && get_student(student_id).subs[sub_adress-1].course_id == course.id){
											struct student st = get_student(student_id);
											put_graids(st.id,sub_adress-1);

											
											
									}else{
										faild("\nWronge ID\n");
									}
								}else
								break;

							}
							
					}else{
						faild("\nWrong Input\n");
					}
				}else
				break;
			}
			
			
			break;
			default:
				break;
			}
		}
		
		break;
		default:
	
			break;
		}
	}
	
}






