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
    int now=0;
    int add;
    //ios_base::sync_with_stdio(0);
    /*
    int sz[4]={128,256,512,1024};
    
    for(int fr=0;fr<1;fr++){
        struct timeval start,endd;
        gettimeofday(&start, 0);
        
        fstream fin;
        fin.open("sample.txt", ios::in);
        multiset<int>exist;
        map<int,int>pos;
        map<int,int>cont;
        int hit=0,miss=0;
        while(fin>>add){
            if(exist.find(add)==exist.end()){
                miss++;
                pos[add]=now;
                cont[now++]=add;
                exist.insert(add);
                while(exist.size()>sz[fr]){
                    int del=cont.begin()->second;
                    int mdel=cont.begin()->first;
                    cont.erase(cont.find(mdel));
                    exist.erase(exist.find(del));
                    pos.erase(pos.find(del));
                }

            }
            else{
                hit++;
                int del=pos[add];
                pos[add]=now;
                cont[now]=add;
                cont.erase(cont.find(del));
                now++;
            }
            
        }
        gettimeofday(&endd, 0);
        cout<<pos.size()<<' '<<cont.size()<<endl;
        cout<<hit<<' '<<miss<<endl;
        int sec = endd.tv_sec - start.tv_sec;
        int usec = endd.tv_usec - start.tv_usec;
        printf("Multi:%f ms\n", sec * 1000 + (usec / 1000.0));
    }*/
    multiset<t>st;
    for(int fr=0;fr<1;fr++){
        struct timeval start,endd;
        gettimeofday(&start, 0);
        int now=0;
        for(int i=0;i<10000;i++){
            cont[i].k=0;
            cont[i].idx=i;
            cont[i].time=0;
        }
        fstream fin;
        fin.open("sample.txt", ios::in);
        int hit=0,miss=0;
        set<int>exist;
        while(fin>>add){
            now++;
            if(exist.find(add)!=exist.end()){
                //cout<<"hit"<<endl;
                hit++;
                st.erase(st.find(cont[add]));
                cont[add].k++;
                cont[add].time=now;
                st.insert(cont[add]);
            }
            else{
                //cout<<"miss"<<endl;
                miss++;
                cont[add].k++;
                cont[add].time=now;
                if(st.size()<512){
                    //cout<<"insert"<<' '<<add<<endl;
                    st.insert(cont[add]);
                    exist.insert(add);
                }
                else if(st.size()>=512&&(*(--st.end())<cont[add])){
                    //cout<<"ggggggggg"<<endl;
                    exist.erase((*(--st.end())).idx);
                    st.erase(--st.end());
                    st.insert(cont[add]);
                    exist.insert(add);
                }
            }
            //cout<<st.size()<<endl;
            
        }
        cout<<hit<<' '<<miss<<endl;
    }
}
/*


int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m)){
        for(int i=1;i<=n;i++){
            cont[i].k=0;
            cont[i].p=0;
        }
        for(int i=0;i<m;i++){
            int add1,add2;
            cin>>add1>>add2;
            if(add1!=1){
                if(cont[add1]<cont[1]){
                    st.erase(st.find(cont[add1]));
                }
                cont[add1].k++;
                cont[add1].p+=add2;
                st.insert(cont[add1]);
            }
            else{
                cont[1].k++;
                cont[1].p+=add2;
            }
            //cout<<st.size()<<endl;
            while(!st.empty()&&!(*(--st.end())<cont[1])){
                //t nt=*(--st.end());
                //cout<<nt.k<<' '<<nt.p<<endl;
                st.erase(--st.end());
            }
            printf("%d\n",st.size()+1);
        }
    }
}*/
