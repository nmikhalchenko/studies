//Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <execinfo.h>

#include "student_database.h"

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(void)
{
    signal(SIGSEGV, handler);

    Student s1 =
    {{
        [StudentField_firstName] = "Ivan",
        [StudentField_lastName] = "Kovaliov",
        [StudentField_fatherName] = "Vasilyevich",
        [StudentField_groupName] = "TG-23",
        [StudentField_rating] = "2"
    }};

    Student s2 =
    {{
        [StudentField_firstName] = "Sergey",
        [StudentField_lastName] = "Kuznetsov",
        [StudentField_fatherName] = "Andreyevich",
        [StudentField_groupName] = "TG-22",
        [StudentField_rating] = "1"
    }};

    Student s3 =
    {{
        [StudentField_firstName] = "Panteleymon",
        [StudentField_lastName] = "Korystin",
        [StudentField_fatherName] = "Yefimovich",
        [StudentField_groupName] = "TG-23",
        [StudentField_rating] = "3"
    }};

    Students_Add(s1);
    Students_Add(s2);
    Students_Add(s3);
    Students_SortBy(StudentField_rating);
    Students_Print();

    return 0;
}
