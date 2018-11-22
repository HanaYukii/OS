#include <bits/stdc++.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
using namespace std;
#define maxn 1000005
int cont[maxn],usort[maxn],n;
int tmp[maxn];
int gap[15];
sem_t se[31];
void* bubble(void* arg){
	 int k = *((int *) arg);
	 sem_wait(&se[k+15]);
     for(int i=gap[k];i<gap[k+1];i++){
     	for(int j=i+1;j<gap[k+1];j++){
     		if(cont[i]>cont[j]){
     			swap(cont[i],cont[j]);
     		}
     	}
     }
     sem_post(&se[k]);
     pthread_exit(NULL);
}
void* merge(void* arg){
	int k = *((int *) arg);
	sem_wait(&se[k+15]);
	sem_post(&se[((k-8)<<1)+15]);
	sem_post(&se[(((k-8)<<1)|1)+15]);
	sem_wait(&se[(k-8)<<1]);
	sem_wait(&se[((k-8)<<1)|1]);
	int p1=gap[(k-8)<<1],p2=gap[((k-8)<<1)|1],now=gap[(k-8)<<1];
	while(p1<gap[((k-8)<<1)|1]&&p2<gap[((k-8)<<1)+2]){
		if(cont[p1]<cont[p2]){
			tmp[now++]=cont[p1++];
		}
		else{
			tmp[now++]=cont[p2++];
		}
	}
	while(p1<gap[((k-8)<<1)|1]){
		tmp[now++]=cont[p1++];
	}
	while(p2<gap[((k-8)<<1)+2]){
		tmp[now++]=cont[p2++];
	}
	for(int i=gap[((k-8)<<1)];i<gap[((k-8)<<1)+2];i++){
		cont[i]=tmp[i];
	}
	sem_post(&se[k]);
	pthread_exit(NULL);
	//cout<<k<<endl;
}

void* merge2(void* arg){
	int k = *((int *) arg);
	sem_wait(&se[k+15]);
	sem_post(&se[((k-12)<<1)+8]+15);
	sem_post(&se[((k-12)<<1)+9]+15);
	sem_wait(&se[((k-12)<<1)+8]);
	sem_wait(&se[((k-12)<<1)+9]);
	int p1=gap[(k-12)<<2],p2=gap[((k-12)<<2)+2],now=gap[((k-12)<<2)];
	while(p1<gap[(((k-12)<<2))+2]&&p2<gap[((k-12)<<2)+4]){
		if(cont[p1]<cont[p2]){
			tmp[now++]=cont[p1++];
		}
		else{
			tmp[now++]=cont[p2++];
		}
	}
	while(p1<gap[(((k-12)<<2))+2]){
		tmp[now++]=cont[p1++];
	}
	while(p2<gap[((k-12)<<2)+4]){
		tmp[now++]=cont[p2++];
	}
	for(int i=gap[((k-12)<<2)];i<gap[((k-12)<<2)+4];i++){
		cont[i]=tmp[i];
	}
	sem_post(&se[k]);
	pthread_exit(NULL);
}
void* merge3(void* arg){
	int k = *((int *) arg);
	sem_wait(&se[29]);
	sem_post(&se[28]);
	sem_post(&se[27]);
	sem_wait(&se[12]);
	sem_wait(&se[13]);
	int p1=gap[0],p2=gap[4],now=gap[0];
	while(p1<gap[4]&&p2<gap[8]){
		if(cont[p1]<cont[p2]){
			tmp[now++]=cont[p1++];
		}
		else{
			tmp[now++]=cont[p2++];
		}
	}
	while(p1<gap[4]){
		tmp[now++]=cont[p1++];
	}
	while(p2<gap[8]){
		tmp[now++]=cont[p2++];
	}
	for(int i=0;i<gap[8];i++){
		cont[i]=tmp[i];
	}
	fstream fout1;
	fout1.open("output1.txt", ios::out);
	for(int i=0;i<n;i++){
     	fout1<<cont[i]<<' ';
    }
    fout1<<endl;
    fout1.close();
	sem_post(&se[k]);
	pthread_exit(NULL);
}
void bubblee(int arg){
	 int k = arg;
     for(int i=gap[k];i<gap[k+1];i++){
     	for(int j=i+1;j<gap[k+1];j++){
     		if(cont[i]>cont[j]){
     			swap(cont[i],cont[j]);
     		}
     	}
     }
}

void merge11(int arg){
	int k = arg;
	int p1=gap[(k-8)<<1],p2=gap[((k-8)<<1)|1],now=gap[(k-8)<<1];
	while(p1<gap[((k-8)<<1)|1]&&p2<gap[((k-8)<<1)+2]){
		if(cont[p1]<cont[p2]){
			tmp[now++]=cont[p1++];
		}
		else{
			tmp[now++]=cont[p2++];
		}
	}
	while(p1<gap[((k-8)<<1)|1]){
		tmp[now++]=cont[p1++];
	}
	while(p2<gap[((k-8)<<1)+2]){
		tmp[now++]=cont[p2++];
	}
	for(int i=gap[((k-8)<<1)];i<gap[((k-8)<<1)+2];i++){
		cont[i]=tmp[i];
	}
}

void merge22(int arg){
	int k = arg;
	int p1=gap[(k-12)<<2],p2=gap[((k-12)<<2)+2],now=gap[((k-12)<<2)];
	while(p1<gap[(((k-12)<<2))+2]&&p2<gap[((k-12)<<2)+4]){
		if(cont[p1]<cont[p2]){
			tmp[now++]=cont[p1++];
		}
		else{
			tmp[now++]=cont[p2++];
		}
	}
	while(p1<gap[(((k-12)<<2))+2]){
		tmp[now++]=cont[p1++];
	}
	while(p2<gap[((k-12)<<2)+4]){
		tmp[now++]=cont[p2++];
	}
	for(int i=gap[((k-12)<<2)];i<gap[((k-12)<<2)+4];i++){
		cont[i]=tmp[i];
	}
}
void merge33(int arg){
	int k = arg;
	int p1=gap[0],p2=gap[4],now=gap[0];
	while(p1<gap[4]&&p2<gap[8]){
		if(cont[p1]<cont[p2]){
			tmp[now++]=cont[p1++];
		}
		else{
			tmp[now++]=cont[p2++];
		}
	}
	while(p1<gap[4]){
		tmp[now++]=cont[p1++];
	}
	while(p2<gap[8]){
		tmp[now++]=cont[p2++];
	}
	for(int i=0;i<gap[8];i++){
		cont[i]=tmp[i];
	}
}
void *single(void* arg){
	sem_wait(&se[0]);
	for(int i=0;i<15;i++){
   		if(i<8){
   			bubblee(i);
   		}
   		else if(i<12){
   			merge11(i);
   		}
   		else if(i<14){
   			merge22(i);
   		}
   		else{
   			merge33(i);
   		}
	}
	fstream fout2;
	fout2.open("output2.txt", ios::out);
	for(int i=0;i<n;i++){
     	fout2<<cont[i]<<' ';
    }
    fout2<<endl;
    fout2.close();
	sem_post(&se[1]);
	pthread_exit(NULL);
}
int main(){
	fstream fin;// fout1, fout2;
	string input;
	cout << "Please enter file name:\n";
	cin >> input;
	fin.open(input.c_str(), ios::in);
	//fout1.open("output1.txt", ios::out);
	//fout2.open("output2.txt", ios::out);
	fin>>n;
	for(int i=0;i<n;i++){
		fin>>cont[i];
		usort[i]=cont[i];
	}
	fin.close();
	gap[0]=0;
	for(int i=1;i<=8;i++){
		gap[i]=n*i/8;
	}
	for(int i=0;i<30;i++){
		sem_init(&se[i],1,0);
	}
	
   	pthread_t thread[15],sig;
	for(int i=0;i<15;i++){
		int *k = (int*)malloc(sizeof(int));
   		*k=i;
   		if(i<8){
   			pthread_create(&thread[i], NULL , bubble , (void *)k);
   		}
   		else if(i<12){
   			pthread_create(&thread[i], NULL , merge , (void *)k);
   		}
   		else if(i<14){
   			pthread_create(&thread[i], NULL , merge2 , (void *)k);
   		}
   		else{
   			pthread_create(&thread[i], NULL , merge3 , (void *)k);
   		}
	}
	struct timeval start,endd;
   	gettimeofday(&start, 0);
   	sem_post(&se[29]);
	sem_wait(&se[14]);
	gettimeofday(&endd, 0);
	int sec = endd.tv_sec - start.tv_sec;
	int usec = endd.tv_usec - start.tv_usec;
	printf("Multi:%f ms\n", sec * 1000 + (usec / 1000.0));
    /*for(int i=0;i<n;i++){
     	fout1<<cont[i]<<' ';
    }
    fout1<<endl;*/
    for(int i=0;i<n;i++){
    	cont[i]=usort[i];
    }
    for(int i=0;i<2;i++){
		sem_init(&se[i],1,0);
	}
	pthread_create(&sig, NULL , single , NULL);
	gettimeofday(&start, 0);
   	sem_post(&se[0]);
	sem_wait(&se[1]);
	gettimeofday(&endd, 0);
	sec = endd.tv_sec - start.tv_sec;
	usec = endd.tv_usec - start.tv_usec;
	printf("Single:%f ms\n", sec * 1000 + (usec / 1000.0));
	for(int i=0;i<30;i++){
		sem_destroy(&se[i]);
	}
    /*for(int i=0;i<n;i++){
     	fout2<<cont[i]<<' ';
    }
    fout2<<endl;
    fout1.close();
    fout2.close();*/
   	return 0;
}
