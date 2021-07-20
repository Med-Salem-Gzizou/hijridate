
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "hijri.h"

#define PROG_NAME "hijridate"
#define PROG_VERSION "1.0"

char DEFAULT_OUTPUT_FORMAT[] = "+%HA %HD %HB(%HM) %HY / %GD %GB(%GM) %GY %h:%m:%s ";

/**
   Print out the command-line usage of this application
**/
void printHelp(int leave)
{
   char *pname = PROG_NAME;

   printf("Usage: %s [OPTION] [+FORMAT]\n", pname);
   fputs("Display the current date/time in the given FORMAT.\n\n", stdout);

   fputs("OPTION:\n\n", stdout);
   fputs("  -h, --help     display this help and exit\n", stdout);
   fputs("      --version  output version information and exit\n\n", stdout);

   fputs("FORMAT: controls the output.  Interpreted sequences are:\n", stdout);
   fputs("        must start with + \n\n", stdout);

   fputs("Hijri (Islamic):\n", stdout);
   fputs("  %%HY   hijri year\n", stdout);
   fputs("  %%HM   hijri month (01..12)\n", stdout);
   fputs("  %%HD   hijri day of month (e.g., 01)\n", stdout);
   fputs("  %%HA   locale's full weekday name (e.g., Ahad)\n", stdout);
   fputs("  %%HB   locale's full month name (e.g., Ramadan)\n", stdout);
   fputs("  %%Ha   locale's abbreviated weekday name (e.g., Ahd)\n", stdout);
   fputs("  %%Hb   locale's abbreviated month name (e.g., Ram)\n", stdout);
   fputs("Gregorian (Christian):\n", stdout);
   fputs("  %%GY   greforian year\n", stdout);
   fputs("  %%GM   greforian month (01..12)\n", stdout);
   fputs("  %%GD   greforian day of month (e.g., 01)\n", stdout);
   fputs("  %%GA   locale's full weekday name (e.g., Sunday)\n", stdout);
   fputs("  %%GB   locale's full month name (e.g., January)\n", stdout);
   fputs("  %%Ga   locale's abbreviated weekday name (e.g., Sun)\n", stdout);
   fputs("  %%Gb   locale's abbreviated month name (e.g., Jan)\n", stdout);
   fputs("Time:\n", stdout);
   fputs("  %%h    hour (00..23)\n", stdout);
   fputs("  %%m    minute (00..59)\n", stdout);
   fputs("  %%s    second (00..60)\n", stdout);
   fputs("\n", stdout);
   fputs("Examples:\n", stdout);
   printf("  $ %s '+%%HY %%HM %%HD %%h:%%m:%%s'\n", PROG_NAME);
   fputs("\n", stdout);

   if (leave)
      exit(0);
}

void printVersion(int leave)
{
   char *pname = PROG_NAME;
   char *pversion = PROG_VERSION;
   printf("%s: %s\n", pname, pversion);

   if (leave)
      exit(0);
}

void memError(){
   char *pname = PROG_NAME;
   printf("%s: Exiting, can't malloc/attain memory !\n", pname);
   exit(-1);
}

int main(int argc, char *argv[])
{
   int do_help = 0;
   int do_version = 0;

   for (int i = 1; i < argc; ++i)
   {
      if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
         do_help = 1;
      if (!strcmp(argv[i], "--version"))
         do_version = 1;
   }

   if (do_help)
      printHelp(1);
   if (do_version)
      printVersion(1);

   /* hijri code specifics */
   int day, month, year;
   sDate currentDate;
   int error_code = 0;
   int i;

   time_t ctime;        // Seconds since the Epoch.
   struct tm *time_ptr; // ISO C `broken-down time' structure.

   /* Get current dte structure */
   time(&ctime);
   time_ptr = localtime(&ctime);

   /* Set current time values */
   day = time_ptr->tm_mday;
   month = time_ptr->tm_mon + 1;
   year = time_ptr->tm_year + 1900;

   /* Convert using hijri code from meladi to hijri */
   error_code = h_date(&currentDate, day, month, year);
   if (error_code)
      return error_code;

   char *outputFormat;
   if (argv[argc - 1][0] == '+')
      outputFormat = argv[argc - 1];
   else
      outputFormat = DEFAULT_OUTPUT_FORMAT;
   
   char c;

   for (i = 1; outputFormat[i] != 0; i++)
   {
      if (outputFormat[i] == '%')
      {
         c = outputFormat[i + 1];
         /* Hijri Append */
         if (c == 'H')
         {
            c = outputFormat[i + 2];
            if (c == 'Y')
            {
               printf("%04d", currentDate.year);
               i += 2;
               continue;
            }
            else if (c == 'M')
            {
               printf("%02d", currentDate.month);
               i += 2;
               continue;
            }
            else if (c == 'D')
            {
               printf("%02d", currentDate.day);
               i += 2;
               continue;
            }
            else if (c == 'A')
            {
               fputs(currentDate.to_dname, stdout);
               i += 2;
               continue;
            }
            else if (c == 'B')
            {
               fputs(currentDate.to_mname, stdout);
               i += 2;
               continue;
            }
            else if (c == 'a')
            {
               fputs(currentDate.to_dname_sh, stdout);
               i += 2;
               continue;
            }
            else if (c == 'b')
            {
               fputs(currentDate.to_mname_sh, stdout);
               i += 2;
               continue;
            }
         }
         /* Gregorian Append */
         else if (c == 'G')
         {
            c = outputFormat[i + 2];
            if (c == 'Y')
            {
               printf("%04d", year);
               i += 2;
               continue;
            }
            else if (c == 'M')
            {
               printf("%02d", month);
               i += 2;
               continue;
            }
            else if (c == 'D')
            {
               printf("%02d", day);
               i += 2;
               continue;
            }
            else if (c == 'A')
            {
               fputs(currentDate.frm_dname, stdout);
               i += 2;
               continue;
            }
            else if (c == 'B')
            {
               fputs(currentDate.frm_mname, stdout);
               i += 2;
               continue;
            }
            else if (c == 'a')
            {
               fputs(currentDate.frm_dname_sh, stdout);
               i += 2;
               continue;
            }
            else if (c == 'b')
            {
               fputs(currentDate.frm_mname_sh, stdout);
               i += 2;
               continue;
            }
         }
         /* Time Append */
         else if (c == 'h')
         {
            printf("%02d", time_ptr->tm_hour);
            i++;
            continue;
         }
         else if (c == 'm')
         {
            printf("%02d", time_ptr->tm_min);
            i++;
            continue;
         }
         else if (c == 's')
         {
            printf("%02d", time_ptr->tm_sec);
            i++;
            continue;
         }
      }
      putchar(outputFormat[i]);
   }

   putchar('\n');
   return (0);
}
