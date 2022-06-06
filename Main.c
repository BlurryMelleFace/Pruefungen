#include <stdio.h>
#include <stdlib.h>

typedef struct FarbMenge
{
	float Rot;
	float Gruen;
	float Blau;

}FarbMenge;

FarbMenge CalculateCapacityAndValidateData(int array[]) {

	struct FarbMenge FarbMenge;

	//Calculate Capacities and And Store it in a Struct Datatype
	int Sollfüllmenge = array[0];
	int Sollfüllmenge1 = array[1];
	float S1 = Sollfüllmenge1 * 0.01;
	int Sollfüllmenge2 = array[2];
	float S2 = Sollfüllmenge2 * 0.01;
	int Sollfüllmenge3 = array[3];
	float S3 = Sollfüllmenge3 * 0.01;

	FarbMenge.Rot = Sollfüllmenge * S1;
	FarbMenge.Gruen = Sollfüllmenge * S2;
	FarbMenge.Blau = Sollfüllmenge * S3;

	//Validate Data 
	if ((array[0]) > (array[4])) {

		FarbMenge.Rot = 0;
		FarbMenge.Gruen = 0;
		FarbMenge.Blau = 0;

	}

	return FarbMenge;

}

int ReadFileInAnArray() {

	FILE* file;
	fopen_s(&file, "Scannerdatei.txt", "r+");

	FILE* write;
	fopen_s(&write, "Zieldatei.txt", "w");

	//Local Variables
	int i = 0;
	int ii = 0;

	char Datensatzsegment[100];
	int Datensatz[100];

	char c = fgetc(file);
	//Local Variables

	//As long as it is not the End of he File 
	//--> Go Through While Loop
	while (c != EOF) {

		ii = 0;

		//As long as it is not the End of the Line 
		//--> Go Through While Loop
		while (c != '\n') {

			i = 0;

			//As long as it is not recognising a semicolon
			//--> Go Through While Loop

			while (c != ';') {

				//if the end of the line is Reached c will be \n and we need to break out of the loop
				if (c == '\n') break;

				//write char in array
				Datensatzsegment[i] = c;

				i++;

				c = fgetc(file);

				//##The programm is in the middle of the Segment loop as the File ends, so we need 
				//##to exit the loop and write into the targe File
				if (c == EOF) break;
			}

			//Arry is NullTerminating
			Datensatzsegment[i] = 0;

			//Converting Char Arry to Integer
			int Wert = atoi(Datensatzsegment);

			Datensatz[ii] = Wert;

			printf("%i\n", Datensatz[ii]);							//Testing on Console

			ii++;

			//##The programm is in the middle of the Segment loop as the File ends, so we need 
			//##to exit the loop and write into the targe File
			if (c == EOF) break;

			//because at the end of the line the c Variable is \n, we do not want to go to the next char or else
			//We will not break out of this loop and wont be able to write the integer array into a File. 
			if (c != '\n') {
				c = fgetc(file);
			}

		}

		//Function to calculate the capacity needed at each fillstation
		//Function used to check wether the Data concerning the Capacity of each Bucket is Valid
		FarbMenge FarbMenge = CalculateCapacityAndValidateData(Datensatz);

		//Print Float Numbers to Console
		printf("Rot: %.2f\nGruen: %.2f\nBlau: %.2f \n\n", FarbMenge.Rot, FarbMenge.Gruen, FarbMenge.Blau);


		//Write Float Numbers Seperated by semicolons to a target file
		fprintf(write, "%.2f;%.2f;%.2f", FarbMenge.Rot, FarbMenge.Gruen, FarbMenge.Blau);

		//If it is the end of the File we dont need another Linebreak
		if (c != EOF) fprintf(write, "\n");

		//The programm is in the middle of the Segment loop as the File ends, so we need 
		//to exit the Programm Now 
		if (c == EOF) exit(0);

		c = fgetc(file);

		//While Loop to Account for Linebreaks
		while (c == '\n') {
			c = fgetc(file);
			//Wites Linebreaks in to the target File!
			fprintf(write, "\n");
			if (c != '\n') break;
		}

	}


}

int main() {

	ReadFileInAnArray();

}