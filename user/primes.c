#include "kernel/types.h"
#include "user/user.h"
#define WR 1
#define RD 0
void select(int lp[2],int rp[2],int now){
    int x;
    while(read(lp[RD],&x,sizeof(int)) == sizeof(int)){
        if(x % now){
            write(rp[WR],&x,sizeof(int));
        }
    }
    close(lp[RD]);
    close(rp[WR]);
}
void solve(int p[2]){
    close(p[WR]);
    int now;
    if(read(p[RD],&now,sizeof(int)) == sizeof(int)){
        // 当前左管道有数
        printf("prime %d\n",now);
    }
    else{
        close(p[RD]);
        exit(0);
    }
    int rip[2];
    pipe(rip);
    select(p,rip,now);
    if(fork() == 0){
        solve(rip);
    }
    else{
        close(rip[RD]);
        wait(0);
    }
    exit(0);
}
int main(int argc,char const *argv[]){  
    int pip[2];
    pipe(pip);
    int exits = 0;
    if(pipe(pip) < 0){
        printf("error pipe\n");
        exits = 1;
    } 
    for(int i = 2;i <= 35;i++){
        write(pip[WR],&i,sizeof(int));
    }
    if(fork() == 0){
        solve(pip);
    }
    else{
        close(pip[WR]);
        close(pip[RD]);
        wait(0);
    }
    exit(exits);
}
