#include<bits/stdc++.h>
#include<dirent.h>
#include<sys/stat.h>
using namespace std;

#define pb push_back
#define ll long long
#define maxn 1005
#define fr(i,j,k) for(int i=j;i<k;i++)
#define f(n) fr(i,0,n)
#define f1(n) fr(i,1,n+1)
#define ms(i) memset(i,0,sizeof(i));
char path[105],file[105];
ll node;
ll sz_max,sz_min;
void ls(char* cur ){
	DIR *d;
	struct dirent *dir;
	struct stat buf;
	d=opendir(path);
	if(d){
		while((dir=readdir(d))!=NULL){
			if(strcmp(dir->d_name,".")&&strcmp(dir->d_name,"..")){
				ll now_sz=buf.st_size*(1LL<<20);
				char find[105];
				strcpy(find,path);
				strcat(find,"/");
				strcat(find,dir->d_name);

				stat(find,&buf);
				if(dir->d_type==4){
					ls(find);
				}
				if(sz_min!=-1&&now_sz<sz_min){
					continue;
				}
				if(sz_max!=-1&&now_sz>sz_max){
					continue;
				}
				if(node!=-1&&node!=buf.st_ino){
					continue;
				}
				if(strcmp(file,"")&&strcmp(dir->d_name,file)){
					continue;
				}
				printf("%s %lld %lld",find,buf.st_ino,now_sz);
			}
		}
		closedir(d);
	}
}
int main(int argc, char* argv[]){
	strcpy(path,argv[1]);
	sz_min=sz_max=node=-1;
	for(int i=2;i<argc;i+=2){
		if(!strcmp(argv[i],"-inode")){
			node=(ll)atoi(argv[i+1]);
		}
		else if(!strcmp(argv[i],"-name")){
			strcpy(file,argv[i+1]);
		}
		else if(!strcmp(argv[i],"-size_min")){
			sz_min=(ll)atoi(argv[i+1]);
		}
		else if(!strcmp(argv[i],"-size_max")){
			sz_max=(ll)atoi(argv[i+1]);
		}
	}
	sz_min<<=20;
	sz_max<<=20;
	ls(path);
	
}