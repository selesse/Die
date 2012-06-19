#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BAD_ARGUMENTS 1
#define ILLEGAL_CHARACTER 2
#define ILLEGAL_ORDER 3
#define DEBUG 0

void printErrorMessage(int code);

int main (int argc, char *argv[]) {
  if (argc != 2) {
    printErrorMessage(BAD_ARGUMENTS);
    exit(BAD_ARGUMENTS);
  }

  if (!strcmp(argv[1], "abort")) {
    printf("Abort!\n");
    #ifdef __WIN32
    system("shutdown -a");
    #elif defined __unix__
    system("sudo shutdown -c");
    #else
    // mac -> need to figure this out
    system("sudo shutdown ");
    #endif
    return 0;
  }

  int hours = 0, minutes = 0, seconds = 0;
  char h,m,s;

  // count the number of chars passed, parse accordingly
  int charsInString = sscanf (argv[1], "%*d%c%*d%c%*d%c", &h,&m,&s);

  if (charsInString == 3) {
    // they have been passed in the correct order, assign them to their values
    if (h == 'h' && m == 'm' && s == 's') {
      sscanf (argv[1], "%d%*c%d%*c%d%*c", &hours, &minutes, &seconds);
    }
    else {
      printErrorMessage(ILLEGAL_ORDER);
      exit(ILLEGAL_ORDER);
    }
  }
  else if (charsInString == 2) {
    // three cases: {hours and minutes}, {minutes and seconds}, and {hours and seconds}
    if (h == 'h' && m == 'm') {
      sscanf (argv[1], "%d%*c%d%*c", &hours, &minutes);
    }
    else if (h == 'm' && m == 's') {
      sscanf (argv[1], "%d%*c%d%*c", &minutes, &seconds);
    }
    else if (h == 'h' && m == 's') {
      sscanf (argv[1], "%d%*c%d%*c", &hours, &seconds);
    }
    // well, they also may have used illegal chars
    else {
      printErrorMessage(ILLEGAL_CHARACTER);
      exit(ILLEGAL_CHARACTER);
    }
  }
  else if (charsInString == 1) {
    // three cases: {hours}, {minutes}, and {seconds}
    if (h == 'h') {
      sscanf (argv[1], "%d%*c", &hours);
    }
    else if (h == 'm') {
      sscanf (argv[1], "%d%*c", &minutes);
    }
    else if (h == 's') {
      sscanf (argv[1], "%d%*c", &seconds);
    }
    else {
      printErrorMessage(ILLEGAL_CHARACTER);
      exit(ILLEGAL_CHARACTER);
    }
  }
  else {
    printErrorMessage(ILLEGAL_ORDER);
    exit(ILLEGAL_ORDER);
  }

  printf ("shutting down in");

  if (hours) {
    printf("\n\t%d hour%s", hours, hours == 1 ? "" : "s");
  }
  if (minutes) {
    printf("\n\t%d minute%s", minutes, minutes == 1 ? "" : "s");
  }
  if (seconds) {
    printf("\n\t%d second%s", seconds, seconds == 1 ? "" : "s");

  }
  printf("\n");

  char number[10];
  char command[30];

  // convert the integer number into a string and append it to "shutdown -s -t"
  sprintf(number, "%d", (int)(hours*60*60 + minutes*60 + seconds));
  #ifdef __WIN32
  strcpy (command, "shutdown -s -t ");
  #elif defined __unix__
  strcpy(command, "sudo shutdown -H +");
  #else
  strcpy(command, "sudo shutdown -s +");
  #endif

  strcat(command, number);

  if (DEBUG) {
    printf("%s\n", command);
  }
  else {
    system(command);
  }

  return 0;
}

void printErrorMessage(int code) {
  switch (code) {
    case BAD_ARGUMENTS:
      printf("Error - must pass one argument.\n\tex:\tdie 40m\n");
      break;
    case ILLEGAL_CHARACTER:
      printf("Error - illegal character. Must use h, m, and/or s.\n");
      break;
    case ILLEGAL_ORDER:
      printf("Error - must format in decreasing order (h, m, then s) preceded by a number,\n\tex:\tdie 1h30m40s\n\t\tdie 30h25s\n\t\tdie 40s\n");
      break;
    default:
      printf("Error!");
  }
}
