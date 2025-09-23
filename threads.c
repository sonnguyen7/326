#include <pthread.h> // pthread library
#include <unistd.h> // for sleep()
#include <stdio.h> // for printf()

static void *child(void *ignored){ // the function for the separate child thread
while (1){ // this function allows infinite loops
   sleep(3); // sleep for 3 seconds
   printf("Child thread is done sleeping 3 seconds.\n"); // print this message after the 3 second pause
   }
   return NULL; // to avoid compiler warnings
}

int main(int argc, char *argv[]){
   printf("Press Enter to cancel the child thread.\n"); // notify the user to press enter if they want to terminate the child thread
   pthread_t child_thread; // create a pthread variable
   int code;
   code = pthread_create(&child_thread, NULL, child, NULL);
   if(code){
      fprintf(stderr, "pthread_create failed with code %d\n", code);
   }
   int input = getchar(); // get user input from keyboard(enter key)
   if(input == '\n'){ // if the user pressed enter key(newline character), kill the child thread
       pthread_cancel(child_thread); 
       printf("Child thread is now abandoned.\n"); // notify the user that the child thread has been terminated
   }

   sleep(5); // sleep for 5 seconds
   printf("Parent thread is done sleeping 5 seconds.\n"); // print this message after the 5 second pause
   printf("Ending program.\n"); // notify the user that the program is ending
   return 0;
}
