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
int gap[15],done[15];
int thr_cnt;
int thr_run[8];
sem_t free[16],s[2];
queue<int>can;
queue<int>empty;
int fin;
void* dispatch(void* arg){
     int k = *((int *) arg);
     sem_wait(&s[0]);
     while(fin<15){
        if(empty.size()){
            int now=empty.front();
            empty.pop();
            fin++;
            thr_run[now]=can.front();
            can.pop();
            sem_post(&free[now]);
        }
     }
     pthread_exit(NULL);
}
void* run(void* arg){
    int k = *((int *) arg);
    while(!flag){
        sem_wait(free[k]);
        if(k<8){
            bubblee(k);
        }
        else if(k<12){
            merge11(k);
        }
        else if(k<14){
            merge22(k);
        }
        else{
            merge33(k);
            sem_post(&s[1]);
            flag=1;
        }
        empty.push(k);
    }
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
     done[k]=1;
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
    done[k]=1;
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
    done[k]=1;
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
    done[k]=1;
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>cont[i];
        usort[i]=cont[i];
    }
    gap[0]=0;
    for(int i=1;i<=8;i++){
        gap[i]=n*i/8;
    }  
    pthread_t dis,thread[8];
    for(int i=1;i<=8;i++){
        struct timeval start,endd;
        thr_cnt=i;
        fin=0;
        for(int j=0;j<2;j++){
            sem_init(&s[j],1,0);
        }
        for(int j=0;j<2;j++){
            sem_init(&free[j],1,0);
        }
        /*int *k = (int*)malloc(sizeof(int));
        *k=i;*/
        pthread_create(&dis, NULL , dispatch , NULL);
        for(int j=0;j<thr_cnt;j++){
            int *k = (int*)malloc(sizeof(int));
            *k=j;
            pthread_create(&thread[j], NULL , run , (void *)k);
        }
        gettimeofday(&start, 0);
        sem_post(&s[0]);
        sem_wait(&s[1]);
        gettimeofday(&endd, 0);
        int sec = endd.tv_sec - start.tv_sec;
        int usec = endd.tv_usec - start.tv_usec;
        printf("Multi:%f ms\n", sec * 1000 + (usec / 1000.0));
        for(int i=0;i<n;i++){
            cont[i]=usort[i];
        }
    }

    for(int i=0;i<2;i++){
        sem_destroy(&s[i]);
    }
    for(int i=0;i<16;i++){
        sem_destroy(&free[i]);
    }
    return 0;
}