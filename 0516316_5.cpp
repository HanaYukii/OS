#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
struct t{
    int idx;
    int k;
    int time;
    //int p;
    bool operator<(const t &x)const{
        if(x.k!=k)
            return x.k<k;
        else{
            return x.time<time;
        }     
    }
}cont[10005];
int main(){
    int add;
    //ios_base::sync_with_stdio(0);
    string s;
    puts("input file name?");
    cin>>s;
    int sz[4]={128,256,512,1024};
    struct timeval start,endd;
    multiset<t>st;
    puts("LFU policy");
    puts("frame\thit\t\tmiss\t\tpage fault ratio");
    gettimeofday(&start, 0);
    for(int i=0;i<4;i++){
        st.clear();
        int now=0;
        for(int i=0;i<10000;i++){
            cont[i].k=0;
            cont[i].idx=i;
            cont[i].time=2e9;
        }
        fstream fin;
        fin.open(s.c_str(), ios::in);
        int hit=0,miss=0;
        multiset<int>exist;
        int f=0;
        while(fin>>add){
            now++;
            if(exist.find(add)!=exist.end()){
                hit++;
                st.erase(st.find(cont[add]));
                cont[add].k++;
                //cont[add].time=now;
                st.insert(cont[add]);
            }
            else{
                miss++;
                cont[add].k=1;
                cont[add].time=now;
                if(!f){
                    if((int)st.size()==sz[i]){
                        f=1;
                    }
                }
                if(!f){
                    st.insert(cont[add]);
                    exist.insert(add);
                }
                else{
                    exist.erase((*(--st.end())).idx);
                    st.erase(--st.end());
                    st.insert(cont[add]);
                    exist.insert(add);
                }
            }
        }
        printf("%d\t%d\t\t%d\t\t%.10f\n",sz[i],hit,miss,(double)miss/(miss+hit));
    }
    gettimeofday(&endd, 0);
    int sec = endd.tv_sec - start.tv_sec;
    int usec = endd.tv_usec - start.tv_usec;
    printf("Total elapsed time: %.4f sec\n", sec+(usec / 1000000.0));
    gettimeofday(&start, 0);
    puts("LRU policy");
    puts("frame\thit\t\tmiss\t\tpage fault ratio");
    for(int i=0;i<4;i++){
        st.clear();
        int now=0;
        for(int i=0;i<10000;i++){
            cont[i].k=0;
            cont[i].idx=i;
            cont[i].time=0;
        }
        fstream fin;
        fin.open(s.c_str(), ios::in);
        int hit=0,miss=0;
        multiset<int>exist;
        int f=0;
        while(fin>>add){
            now++;
            if(exist.find(add)!=exist.end()){
                hit++;
                st.erase(st.find(cont[add]));
                cont[add].time=now;
                st.insert(cont[add]);
            }
            else{
                miss++;
                cont[add].time=now;
                if(!f){
                    if((int)st.size()==sz[i]){
                        f=1;
                    }
                }
                if(!f){
                    st.insert(cont[add]);
                    exist.insert(add);
                }
                else{
                    exist.erase((*(--st.end())).idx);
                    st.erase(--st.end());
                    st.insert(cont[add]);
                    exist.insert(add);
                }
            }
            
            
        }
        printf("%d\t%d\t\t%d\t\t%.10f\n",sz[i],hit,miss,(double)miss/(miss+hit));
        
    }
    gettimeofday(&endd, 0);
    sec = endd.tv_sec - start.tv_sec;
    usec = endd.tv_usec - start.tv_usec;
    printf("Total elapsed time: %.4f sec\n", sec+(usec / 1000000.0));
    
    

}
