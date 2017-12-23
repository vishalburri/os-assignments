#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/types.h>
int main (int argc, char* argv[])
{
    char* path = argv[1];
    int rval;

    /* Check file existence. */
    rval = access (path, F_OK);
    if (rval == 0) 
        printf ("%s exists\n", path);
    else {
        if (errno == ENOENT) 
            printf ("%s does not exist\n", path);
        else if (errno == EACCES) 
            printf ("%s is not accessible\n", path);
        return 0;
    }

    /* Check read access. */
    rval = access (path, R_OK);
    if (rval == 0)
        printf ("%s is readable\n", path);
    else
        printf ("%s is not readable (access denied)\n", path);

    /* Check write access. */
    rval = access (path, W_OK);
    if (rval == 0)
        printf ("%s is writable\n", path);
    else if (errno == EACCES)
        printf ("%s is not writable (access denied)\n", path);
    else if (errno == EROFS)
        printf ("%s is not writable (read-only filesystem)\n", path);

    char file1[100]="test1";
    char file2[100]="test2";
    int in = open(file1,0400);
    int out = open(file2, 0400);
    char a,b;
    int count = 1;
    int flag=0;
    int f1 = lseek(in, (off_t) 0, SEEK_END);
    int f2 = lseek(out, (off_t) 0, SEEK_END);
    /*if(f1!=f2){
        printf("Filesize not same\n");
        printf("not same\n");
        return 0;
    }*/
    int i;
    for(i=0;i<f1-1;i++){
        count++;
        lseek(in,(off_t)(i),SEEK_SET);
        lseek(out,(off_t)(f2-count),SEEK_SET);
        int x = read(in,&a,1);
        x = read(out,&b,1);
        if(x!=1){
            flag = 1;
            printf("second file is shorter.not same\n");
            return 0;
        }
        //printf("%c%c%d\n",a,b,count); 
        if(a!=b){
            //printf("not same\n%c%c%d\n",a,b,count); 
            flag = 1;
            printf("comparision failed.not same\n");
            break;
        }
    }
    if(f2-count !=0 && !flag){
        printf("First file is shorter.not same\n");
        flag = 1;
    }
    if(!flag){
        printf("The second file is the reverse of the first one\n");
    }
    return 0;


}
