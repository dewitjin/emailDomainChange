#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


/**

Objective : The purpose of this assignment is to work with sequential text files.
Write a program that reads a text file, modifies some of the data, and writes the modified data back to another text file.
In the program, prompt for and collect an email domain. Open and read the data from dataIn.txt and write back to a file named dataOut.txt.
Update the domain in each email address to the one collected.
Increase the age of each person by one year.

**/

int main() {

	char firstName[30];									//start varaibles that will store data from dataIn.txt
	char lastName[30];
	char email[120];
	int age;
	double balance;

	char divider[] = "---------------------------------------------------------------------";//could be define as a constant prior to main()

	char newEmailDomain[80];								//user input for new email domain, without the '@' symbol
	char newEmail[120];									//stores new converted email with '@' appended again

	char *pToken;										//use for strtok function
	char emailSymbol[120] = "@";								//strtok function uses it to break down original email, will append new domain to this variable (needs to be big enough to hold the new content)

	FILE *fpClient;
	FILE *fpOutput;

	if ((fpClient = fopen("dataIn.txt", "r")) == NULL) {

		printf("File (dataIn.txt) could not be opened\n");
	}
	else {

		printf("Enter new email domain: ");
		fgets(newEmailDomain, 50, stdin);

		char *pNewEmailDomain = newEmailDomain;

		while (*pNewEmailDomain != '\0') {						//remember the asterik
			pNewEmailDomain++;
		}

		*(pNewEmailDomain - 1) = '\0';							//Note NOT [pNewEmailDomain - 1], assign null in order to get rid of '\n' that gets inserted by using fgets - good habit

		strcat(emailSymbol, newEmailDomain);						//append the '@' to the new email domain again, because user will not append the '@' before the user input
									
		printf("\n%-13s %-13s %-20s %3s %10s\n", "FirstName", "LastName", "Email Address", "Age", "Balance"); //start printing header
		printf("%s\n", divider);

		if ((fpOutput = fopen("dataOut.txt", "w")) == NULL) {
			printf("Output File (dataOut.txt) could not be opened\n");
		}
		else {
			
			while (!feof(fpClient)) {
				fscanf(fpClient, "%s %s %s %d %lf", firstName, lastName, email, &age, &balance); 
				strcpy(newEmail, email);															//should copy so we don't change original email from file because strtok will change the original email
				pToken = strtok(newEmail, "@");														//gets the email string prior to '@' symbol (remember: tokenizing changes the original email string) so i.e. jerry
				strcat(pToken, emailSymbol);														//append the first part of dataIn.txt email input (jerry) with new email domain (and the new email domain has the '@' infront of it already from line 57)
				age++;																				//add one to all the age - just to show this can be done
				printf("%-13s %-13s %-20s %3d %10.2lf\n", firstName, lastName, pToken, age, balance);//output the modified data to the console 
				fprintf(fpOutput, "%s %s %s %d %0.2lf\n", firstName, lastName, pToken, age, balance);//write to new file
			}


			/* the above code works, but sometimes you have to scan one line prior to the while loop 
			and put the print statments right after the while loop to prevent the last line in the dataIn.txt from being printing out

			like this:

			fscanf(fpClient, "%s %s %s %d %lf", firstName, lastName, email, &age, &balance);

			while (!feof(fpClient)) {

			printf("%-13s %-13s %-20s %3d %10.2lf\n", firstName, lastName, pToken, age, balance);
			fprintf(fpOutput, "%s %s %s %d %0.2lf\n", firstName, lastName, pToken, age, balance);

			strcpy(newEmail, email);
			pToken = strtok(newEmail, "@");
			strcat(pToken, emailSymbol);
			age++;

			}

			*/
		}
	}

	rewind(fpClient); //remember to rewind pointer to top - good habit
	fclose(fpClient); //always close file after
	fclose(fpOutput);

	system("pause");
}


