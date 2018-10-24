#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <bits/stdc++.h>
using namespace std;
#define ui unsigned int
#define maxp 16
#define pb push_back
#define fr(i,j,k) for(int i=j;i<k;i++)
#define f(n) fr(i,0,n)
#define f1(n) fr(i,1,n+1)
#define ms(i) memset(i,0,sizeof(i));
struct table{
		ui cont[800][800];
}*x;
int main(){
	ios_base::sync_with_stdio(0);
	cout<<"Input the matrix dimension:";
	int id;
	id=shmget(0,3*(sizeof(struct table)),IPC_CREAT|0666);
	x=(struct table *) shmat(id,NULL,0);
    int sz;
    pid_t p1,p2;
    int f=0;
    cin>>sz;
    f(sz){
    	fr(j,0,sz){
    		x[0].cont[i][j]=(ui)(i*sz+j);
			x[1].cont[i][j]=(ui)(i*sz+j);
			x[2].cont[i][j]=0;
    	}
    }
    fr(cur,1,maxp+1){
    	struct timeval t1, t2;
    	gettimeofday(&t1, 0);
    	fr(cnt,0,cur){
    		int rows=sz/cur;
			 if ((p1 = fork()) == 0) {		
			 	int now_row = cnt*rows;
			 	for(int tmp=0;tmp<rows;tmp++){	
			 		for(int col=0;col<sz;col++){	
			 			ui tsum=0;
			 			int tmpo;
			 			for(tmpo=0;tmpo<sz;tmpo++){ 
			 				tsum+=x[0].cont[now_row][tmpo]*x[1].cont[tmpo][col];
			 			}
			 			x[2].cont[now_row][col]=tsum;
			 		}
			 	now_row++;
			 	}

			 	if(cnt==cur-1){		
			 		for(;now_row<sz;now_row++){
			 			for(int col=0;col<sz;col++){		
			 				ui tsum=0;
			 				int tmpo=0;
			 				for(tmpo=0;tmpo<sz;tmpo++){
			 					tsum+=x[0].cont[now_row][tmpo] * x[1].cont[tmpo][col];
			 				}
			 				x[2].cont[now_row][col]=tsum;
			 			}
			 		}
			 	}
			   exit(0);
			 }
			 else{	
			 	continue;
			 }
    	}
    	while ((p2 = wait(&f))>0); 
    	 gettimeofday(&t2,0);
    		ui checksum=0;
    		int sec,usec;
    		sec = t2.tv_sec - t1.tv_sec;
   			usec = t2.tv_usec - t1.tv_usec;
    	 for(int o=0;o<sz;o++){
    	 	for(int p=0;p<sz;p++){
    	 		checksum+=x[2].cont[o][p];
    	 	}
    	 }
    	 if(cur>=2)
    	 cout<<"Multiplying matrices using "<<cur<<" processes\n";
    	 else
    	 cout<<"Multiplying matrices using "<<cur<<" process\n";
    	 cout<<"Elapsed time: "<<(sec*1000 + (usec/1000.0))<<" ms,";
		 cout<<checksum<<endl;
    }
}
