#include<stdio.h>
#include<stdlib.h>
int allocated[3][3]={0},max[3][3]={0},needed[3][3]={0},available[3]={0}, 
alloc[3][3]={{0,0,1},{3,2,0},{2,1,1}},
need[3][3]={{8,4,3},{6,2,0},{3,3,3}},
avail[3]={3,2,2},
safe_sequence[3];
void check(){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		max[i][j]=need[i][j];
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		allocated[i][j]=alloc[i][j];
	}
	for(i=0;i<3;i++)
	available[i]=avail[i];
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		needed[i][j]=max[i][j]-allocated[i][j];
	}
}
void print_status(){
	int i,j,k=0,check,need[3][3],avail[3],alloc[3][3];
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		need[i][j]=needed[i][j];
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		alloc[i][j]=allocated[i][j];
	}
	for(i=0;i<3;i++)
	avail[i]=available[i];
	for(i=0;i<3;i++){
		if(need[i][0]==0 &&need[i][1]==0 &&need[i][2]==0){
			safe_sequence[k]=i+1;k++;
			avail[0]+=alloc[i][0];
			avail[1]+=alloc[i][1];
			avail[2]+=alloc[i][2];
		}
	}
	while(1){
		check=1;
		for(i=0;i<3;i++){
			int tt=need[i][0]+need[i][1]+need[i][2];
			if(tt>0&&need[i][0]<=avail[0]&&need[i][1]<=avail[1]&&need[i][2]<=avail[2]){
				avail[0]+=alloc[i][0];
				avail[1]+=alloc[i][1];
				avail[2]+=alloc[i][2];
				safe_sequence[k]=i+1;k++;
				check=0;
				need[i][0]=need[i][1]=need[i][2]=0;
			}
		}
		if(check)
		break;
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		if(need[i][j]>0)
		check=2;
	}
	if(check==2)
	printf("\nSYSTEM IN UNSAFE STATE\n");
	else
	printf("\nSYSTEM IN SAFE STATE\nSAFE SEQUENCE WILL BE P->%d P->%d P->%d\n",safe_sequence[0],safe_sequence[1],safe_sequence[2]);
}

int main(){
	int i,j,choice,a,b,c,process_num,temp[3];
	printf("\n\n");
	for(i=0;i<60;i++)
	printf("*");
	printf(" OPRATING SYSTEM PROJECT IN C (BANKER`S ALGORITHM) " );
	for(i=0;i<55;i++)
	printf("*");
	check();//updating all the values of table
	printf("\n\n");
	print_status();//printing that system in safe or unsafe state,if safe then also printing safe sequence
	printf("PLEASE CHOOSE ONE OF THE FOLLOWING OPTIONS\n");
	while(1){
		printf("1 ADD NEW REQUEST\t\t2 EXIT\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("CHOOSE ONE PROCESS\n1 P1\t2 P2\t2 P3\n");
				scanf("%d",&process_num);
				process_num--;
				if(process_num<0||process_num>2)
				printf("INVALID PROCESS CHOOSEN\n");
				else{
					printf("ENTER RESOUCES NEEDED A B C\n");
					scanf("%d %d %d",&temp[0],&temp[1],&temp[2]);
					for(i=0;i<3;i++){
						allocated[process_num][i]+=temp[i];
						available[i]-=temp[i];
						needed[process_num][i]-=temp[i];
					}
					print_status();
					check();
				}
				break;
			case 2:
				exit(0);
			default:
				printf("INVALID CHOICE\n");
		}
	}
	
}

