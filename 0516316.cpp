#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <bits/stdc++.h>
using namespace std;
#define ui unsigned int
#define fr(i,j,k) for(int i=j;i<k;i++)
#define f(n) fr(i,0,n)
#define f1(n) fr(i,1,n+1)
#define ms(i) memset(i,0,sizeof(i));
struct table{
	ui cont[805][805];
}*x;
int main(){
	int n,id;
	pid_t p1,p2;
	cout<<"Input the matrix dimension:";
	cin>>n;
	id=shmget(0,3*(sizeof(struct table)),IPC_CREAT|0666);
	x=(struct table *) shmat(id,NULL,0);
	f(n){
		fr(j,0,n){
			x[0].cont[i][j]=(ui)i*(ui)n+(ui)j;
			x[1].cont[i][j]=(ui)i*(ui)n+(ui)j;
			x[2].cont[i][j]=0;
		}
	}
	fr(cur,1,17){
		struct timeval t1, t2;
		gettimeofday(&t1, 0);
		fr(cnt,0,cur){
			int row=n/cur;
			if(!(p1=fork())){
			 	for(int now_row=cnt*row;now_row<(cnt==cur-1?n:(cnt+1)*row);now_row++){	
			 		for(int col=0;col<n;col++){	
			 			ui tsum=0;
			 			int tmpo;
			 			for(tmpo=0;tmpo<n;tmpo++){ 
			 				tsum+=x[0].cont[now_row][tmpo]*x[1].cont[tmpo][col];
			 			}
			 			x[2].cont[now_row][col]=tsum;
			 		}
			 	}
			 	exit(0);
			}
			else{
				continue;
			}
		}
		while ((p2 = wait(0))>0); 
		gettimeofday(&t2,0);
		ui checksum=0;
    	int sec,usec;
    	sec = t2.tv_sec - t1.tv_sec;
   		usec = t2.tv_usec - t1.tv_usec;
    	for(int o=0;o<n;o++){
    		for(int p=0;p<n;p++){
    	 		checksum+=x[2].cont[o][p];
    	 	}
    	}
    	if(cur>=2)
    	cout<<"Multiplying matrices using "<<cur<<" processes\n";
    	else
    	cout<<"Multiplying matrices using "<<cur<<" process\n";
    	cout<<"Elapsed time: "<<fixed<<setprecision(6)<<(sec*1000+(usec/(double)1000))/1000.0<<" sec,";
		cout<<checksum<<endl;
	}
}