#include <pthread.h> // pthread library
#include <unistd.h> // for sleep()
#include <stdio.h> // for printf()

static void *child(void *ignored){ // the function for the separate child thread
while (1){ // this function allows infinite loops
   sleep(3); // sleep for 3 seconds
   printf("Child thread is done sleeping 3 seconds.\n"); // print this message after the 3 second pause
   }
   return NULL; // return Null due to void pointer
}

int main(int argc, char *argv[]){
   printf("Press Enter to cancel the child thread.\n"); // notify the user to press enter if they want to terminate the child thread
   pthread_t child_thread; // create a pthread variable
   int code; // set as an int variable
   code = pthread_create(&child_thread, NULL, child, NULL); // creating a thread that runs child and stores the ID in child_thread
   if(code){
      fprintf(stderr, "pthread_create failed with code %d\n", code); // error check if child thread creation fails
   }
   int input = getchar(); // get user input from keyboard(enter key)
   if(input == '\n'){ // if the user pressed enter key(newline character), kill the child thread with pthread_cancel
       pthread_cancel(child_thread);
       printf("Child thread is now abandoned.\n"); // notify the user that the child thread has been terminated
   }

   sleep(5); // sleep for 5 seconds
   printf("Parent thread is done sleeping 5 seconds.\n"); // print this message after the 5 second pause
   printf("Ending program.\n"); // notify the user that the program is ending
   return 0;
}

/* 
1. Explain what pthread is doing in this program. Be specific.
First to be able to use pthreads, we need to include the pthread.h library. From there, we use the function pthread_create to create a separate thread(child thread) from the main thread.
This allows us to implement an infinity loop in the child thread that sleeps for 3 seconds and prints out a message after every 3 seconds. Then in our main thread, it tells us to press enter
to cancel the child thread using getchar(). Then if the user presses enter, the child thread is cancelled using pthread_cancel function. The main thread then sleeps for 5 seconds and prints 
out a message stating the program is ending. 
2. Explain why the sleeping thread can print its periodic messages while the main thread is waiting for keyboard input.
Like the first answer stated, the sleeping thread(child thread) is part of of a separate thread that runs concurrently with the main thread. This means when the main thread runs, the child thread 
will run too when it is created in the main thread(using pthread_create). However, after the second thread is created, the main faces a block due to getchar()(meaning it cannot continue until the 
user keyboard input) while the child thread continues to run infinitely due to the while loop. This is why the sleeping thread can print its periodic messages while the main thread is waiting for 
keyboard input.
*/
