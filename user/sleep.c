#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char * argv[]){
    if(argc < 2){
        fprintf(argc,"usage: sleep pid...\n");
        exit(1);
    }
    sleep(atoi(argv[1]));
    exit(0);
}