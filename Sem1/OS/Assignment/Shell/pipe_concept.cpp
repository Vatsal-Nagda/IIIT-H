#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main(int argc, char** argv)
{
        int des_p[2];
        if(pipe(des_p) == -1) {
          //perror("Pipe failed");
          //exit(1);
        }
       int pid=fork();
        if(pid== 0)            //first fork
        {
            //close(1);  //closing stdout
            dup2(des_p[1],1);         //replacing stdout with pipe write 
           close(des_p[0]);       //closing pipe read
           // close(des_p[1]);

            char* prog1[] = { "ls", "-l",'\0'};
            execvp(prog1[0], prog1);
          //  perror("execvp of ls failed");
            //exit(1);
        }

        else         //creating 2nd child
        {
        //    close(0);   //closing stdin
            dup2(des_p[0],0);         //replacing stdin with pipe read
            close(des_p[1]);       //closing pipe write
            //close(des_p[0]);

            char* prog2[] = { "wc", "-l", '\0'};
            execvp(prog2[0], prog2);
         //   perror("execvp of wc failed");
           // exit(1);
        }

        close(des_p[0]);
        close(des_p[1]);
       
        return 0;
}