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
int cont[maxn],usort[maxn],n,flag;
int tmp[maxn];
int gap[15],done[15],incan[15];
int thr_cnt;
int thr_run[8];
sem_t se[2],work,patch,que;
queue<int>can;
int fin;
int d;
void* dispatch(void* arg){
    sem_wait(&se[0]);
    d=0;
    for(int i=0;i<8;i++){
        can.push(i);
        sem_post(&work);
        incan[i]=1;
    }
    sem_post(&que);
    while(1){
        sem_wait(&patch);
        if(done[0]&&done[1]&&!incan[8]){
            incan[8]=1;
            can.push(8);
            sem_post(&work);
        }
        if(done[2]&&done[3]&&!incan[9]){
            incan[9]=1;
            can.push(9);
            sem_post(&work);
        }
        if(done[4]&&done[5]&&!incan[10]){
            incan[10]=1;
            can.push(10);
            sem_post(&work);
        }
        if(done[6]&&done[7]&&!incan[11]){
            incan[11]=1;
            can.push(11);
            sem_post(&work);
        }
        if(done[8]&&done[9]&&!incan[12]){
            incan[12]=1;
            can.push(12);
            sem_post(&work);
        }
        if(done[10]&&done[11]&&!incan[13]){
            incan[13]=1;
            can.push(13);
            sem_post(&work);
        }
        if(done[12]&&done[13]&&!incan[14]){
            incan[14]=1;
            can.push(14);
            sem_post(&work);
            break;
        }
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
    sem_post(&patch);
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
    sem_post(&patch);
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
    sem_post(&patch);
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
void* run(void* arg){
    while(1){
        sem_wait(&que);
        sem_wait(&work);
        int kk=can.front();
        can.pop();
        //cout<<kk<<endl;
        sem_post(&que);
        if(kk<8){
            bubblee(kk);
        }
        else if(kk<12){
            merge11(kk);
        }
        else if(kk<14){
            merge22(kk);
        }
        else{
            merge33(kk);
            sem_post(&se[1]);
        }
    }
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
        
        for(int j=0;j<2;j++){
            sem_init(&se[j],1,0);
        }
        sem_init(&work,1,0);
        sem_init(&patch,1,0);
        memset(done,0,sizeof(done));
        memset(incan,0,sizeof(incan));
        pthread_create(&dis, NULL , dispatch , NULL);
        for(int j=0;j<i;j++){
            int *k = (int*)malloc(sizeof(int));
            *k=j;
            pthread_create(&thread[j], NULL , run , (void *)k);
        }
        gettimeofday(&start, 0);
        sem_post(&se[0]);
        sem_wait(&se[1]);
        gettimeofday(&endd, 0);
        int sec = endd.tv_sec - start.tv_sec;
        int usec = endd.tv_usec - start.tv_usec;
        printf("Multi:%f ms\n", sec * 1000 + (usec / 1000.0));
        for(int j=0;j<n;j++){
            cont[j]=usort[j];
        }
        for(int i=0;i<2;i++){
            sem_destroy(&se[i]);
        }
        sem_destroy(&work);
    }

    
    return 0;
}
