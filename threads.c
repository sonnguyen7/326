#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

static void *child(void *ignored){
while (1){ // this function allows infinite loops
   sleep(3);
   printf("Child is done sleeping 3 seconds.\n");
   }
   return NULL;
}

int main(int argc, char *argv[]){
   pthread_t child_thread;
   int code;
   code = pthread_create(&child_thread, NULL, child, NULL);
   if(code){
      fprintf(stderr, "pthread_create failed with code %d\n", code);
   }
   int input = getchar();
   if(input == '\n'){
       pthread_cancel(child_thread);
       printf("Child thread cancelled.\n");
   }

   sleep(5);
   printf("Parent is done sleeping 5 seconds.\n");
   return 0;
}
