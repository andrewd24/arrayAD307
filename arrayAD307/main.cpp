/*-----------------------------------------------------------------------------
Programmer:  Andrew Douglas

Program:     Arrays - Processes a binary wave data file by reading the file 
			 meta data for sea salinty, sea height, and sea temperature.

			 The binary file, data.in, is passed in via command line.

			 If 30 records for each are found, three output files will be 
			 generated: ex. seaSalinty.30.  

			 The program does not convert the binary data, it reads the binary 
			 file for records and sorts the records into their own files.

Class:       CSC 307 - Data Structures Using C++

Instructor:  Tom Rishel 

Semester:    Summer 2014
-----------------------------------------------------------------------------*/
  




#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
	
	int x;
	
	int has[4];
	
	int i = 0;



	/*----------------------------------------------------------------------------
	USAGE STATEMENT:  Informs command line user that they must provide a file to 
	run the program if one is not provided.
	----------------------------------------------------------------------------*/
	if (argc != 2)
	{
		cout << "Usage Statement: " << argv[0] << " You need to pass one file to the program to be opened.  Please try again.";
		
	}
	else {
	/*----------------------------------------------------------------------------
	Else, we try to open the file.

	If it is not open, report he file could not be opened, exit the program.

	Else, process the meta data of the file and covert it to integer values in 
	the has array.
	----------------------------------------------------------------------------*/
		
		ifstream myFile(argv[1], std::ios::binary);
		
		if (!myFile.is_open())
		{
			cout << "The file could not be opened";
			return 1;
		}
		
		else 
		{
			
			while (i < 4)
			{
				myFile.read((char*)&x, sizeof(int));

				has[i] = x;

				i++;
			}
					
		}
		
		//if all of the has elements listed return a 0, there is no data in the file
		
		if (has[0] == 0 && has[1] == 0 && has[2] == 0)
		{
			cout << "The file contains no data!  The program will exit." << endl;
			return 0;

		}
		
		//otherwise, 3 character arrays of capacity 999 are declared

		char seaSurfaceTemp[999];
		char seaSalinity[999];
		char seaSurfaceHeight[999];
		i = 0;
		
		int numOfEntries = has[3];
		
		/*---------------------------------------------------------------------
		This while counts the number of times each piece of data appears in the
		file.  The if statements check for which types of data are in the file,
		because each alternating byte is a different type of data.  The data is 
		stored in the array of the data type it represents.
		---------------------------------------------------------------------*/
		while (i < numOfEntries)
		{


			if (has[0] == 1 && has[1] == 1 && has[2] == 1)
			{
				myFile.get(seaSurfaceTemp[i]);
				myFile.get(seaSalinity[i]);
				myFile.get(seaSurfaceHeight[i]);
			}
			else if (has[0] == 1 && has[1] == 1 && has[2] == 0)
			{   
				myFile.get(seaSurfaceTemp[i]);
				myFile.get(seaSalinity[i]);
			}
			else if (has[0] == 1 && has[1] == 0 && has[2] == 0)
			{   
				myFile.get(seaSurfaceTemp[i]);
			}
			else if (has[0] == 1 && has[1] == 0 && has[2] == 1)
			{   
				myFile.get(seaSurfaceTemp[i]);
				myFile.get(seaSurfaceHeight[i]);
			}
			else if (has[0] == 0 && has[1] == 1 && has[2] == 1)
			{   
				myFile.get(seaSalinity[i]);
				myFile.get(seaSurfaceHeight[i]);
			}
			else if (has[0] == 0 && has[1] == 0 && has[2] == 1)
			{	
				myFile.get(seaSurfaceHeight[i]);
            }
			else if (has[0] == 0 && has[1] == 1 && has[2] == 0)
			{   
				myFile.get(seaSalinity[i]);
			}
			
			i++;
		}
		
		myFile.close();
		
		/*---------------------------------------------------------------------------
		This section converts the numOfEntries to a string that will be used for the 
		file extension.  Then, it reports which data was found in the file, creates
		new files, and writes that data to the correct files.
		---------------------------------------------------------------------------*/

		string fileExtension = to_string(numOfEntries);
		
		if (has[0] == 1)
		{   
			cout << "Sea surface temp data found. Writing to file" << endl;
			string tempFile;
			
			tempFile = "seaSurfaceTemperature." + fileExtension;
			
			ofstream seaTemp;
			
			seaTemp.open(tempFile.c_str());
			if (seaTemp.is_open())
			{
				for (i = 0; i < numOfEntries; i++)
				{
					seaTemp << seaSurfaceTemp[i];
				}
			}
			
			else 
			{
				cout << "Could not open the file to write sea temp data." << endl;
			}
		}
		
		if (has[1] == 1)
		{
			cout << "Sea salinity data found.  Writing to file." << endl;
			
			string salinityFile;
			
			salinityFile = "seaSalinity." + fileExtension;
			
			ofstream seaSalin;
			
			seaSalin.open(salinityFile.c_str());
			
			if (seaSalin.is_open())
			{

				for (i = 0; i < numOfEntries; i++)
				{
					seaSalin << seaSalinity[i];
				}
			}
			else 
			{
				cout << "Could not open the file to write sea salinity data." << endl;
		    }
		}
				
		        if (has[2] == 1)
				{
					
					cout << "Sea surface height data found. Writing to file" << endl;
					
					string heightFile;
					
					heightFile = "seaSurfaceHeight." + fileExtension;
					
					ofstream seaHeight;
					
					seaHeight.open(heightFile.c_str());
					
					if (seaHeight.is_open())
					{

						for (i = 0; i < numOfEntries; i++)
						{
							seaHeight << seaSurfaceHeight[i];
						}
					}
					else 
					{
						cout << "Could not open the file to write sea height data." << endl;
					}

				}
			
				cout << "The files have successfully been written. You may locate them in the visual studio" << +
					" project solution folder via the file explorer." << endl;
			
			}


			cin.get();
			return 0;

}
		
	
	
