/*
Rico Cintron
Simple Neural Network from  "Code your Own Neural Network". Modified to take user input, produce a unique user experience, generating secret characters based off of selections.
5/24/2018
*/

#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include<iostream>
#include <thread>       


using namespace std;

//constants
const int NUMINPUTNODES = 2;   // Number of Input Nodes
const int NUMHIDDENNODES = 2;  //Number of Hidden Nodes
const int NUMOUTPUTNODES = 1;  //Number of Output Nodes
const int NUMNODES = NUMINPUTNODES + NUMHIDDENNODES + NUMOUTPUTNODES; //Sum of all nodes
const int ARRAYSIZE = NUMNODES + 1; //1 added for offset. Positions start at 0, so having a 1 added enables us to have "Node 1", Node 2, et cetra.
const int MAXITERATIONS = 500000; //Integer for maximum iterations.
const double E = 2.71828; //const double for value of 'E'.
const double LEARNINGRATE = 0.2; //const double for learning rate.

//Integer values, from user input, are stored here:
int v1A, v2A, evA = 0;
int v1B, v2B, evB = 0;
int v1C, v2C, evC = 0;
int secret1, secret2, secret3 = 0;

								 //Function Prototypes
void initialize(double[][ARRAYSIZE], double[], double[], double[]);
void connectNodes(double[][ARRAYSIZE], double[]);
void trainingExample(double[], double[]);
void activateNetwork(double[][ARRAYSIZE], double[], double[]);
double updateWeights(double[][ARRAYSIZE], double[], double[], double[]);
void displayNetwork(double[], double);
void introduction();
void userSelection();
void userValues();
void secretChars();



int main() {



	//Arrays for weight, values, expected values, and thresholds
	double weights[ARRAYSIZE][ARRAYSIZE];
	double values[ARRAYSIZE];
	double expectedValues[ARRAYSIZE];
	double thresholds[ARRAYSIZE];

	//Program introduction.
	introduction();

	//Function call to initiallize variables to 0.0 and connect nodes
	initialize(weights, values, expectedValues, thresholds);
	connectNodes(weights, thresholds);

	//Call function enabling user input.
	userSelection();

	//While loop, operates while counter is less than max iterations.
	int counter = 0;
	
	while (counter < MAXITERATIONS)
	{

		//Function calls and one assignment 
		trainingExample(values, expectedValues);
		activateNetwork(weights, values, thresholds);
		double sumOfSquaredErrors = updateWeights(weights, values, expectedValues, thresholds); //Populates sumOfSquaredErrors with return from updateWeights function
		counter++;//Increments counter variable.

		if (counter == (MAXITERATIONS - 3))//Simple if statement, displaying the users values, for verification.
		{
			userValues();//Call user value function.
			cout << endl;
			cout << "Here is what was 'learned' based off of your input..." << endl;
		}
		
		if (counter > (MAXITERATIONS-3)) //Another simple if statement. Allows only the last three results to be populated for the user.
		{
			
			displayNetwork(values, sumOfSquaredErrors);// Display network function call.
		}
	}
	secretChars(); //Function call, enabling user to view the "Secret Characters" Generated based off of their input and efficency of the Neural Network.
	

	system("pause");
	return 0;
}

//Initialize Function. Initalizes arrays with value of 0.0
void initialize(double weights[][ARRAYSIZE], double values[], double expectedValues[], double thresholds[])
{
	for (int x = 0; x <= NUMNODES; x++)
	{
		values[x] = 0.0; //values set to 0.0
		expectedValues[x] = 0.0; //expectedValues set to 0.0
		thresholds[x] = 0.0; //thresholds set to 0.0
		for (int y = 0; y <= NUMNODES; y++)
		{
			weights[x][y] = 0.0;//weights set to 0.0
		}
	}

}
//Initialize Function ends


//Connect Nodes Function. Populates weights and thresholds with random values.


void connectNodes(double weights[][ARRAYSIZE], double thresholds[])
{
	for (int x = 1; x <= NUMNODES; x++)
	{
		for (int y = 1; y <= NUMNODES; y++)
		{
			weights[x][y] = (rand() % 200) / 100.0;//Initiallizes weights to random genrated numbers with a value between 0.0 and 2.0
		}
	}
	//Thresholds set to random values between 0.0 and 2.0
	thresholds[3] = rand() / (double)rand();
	thresholds[4] = rand() / (double)rand();
	thresholds[5] = rand() / (double)rand();
	
}



// Our Training Example Function. We take input from user, utilizing for our training example.

void trainingExample(double values[], double expectedValues[])
{
	static int counter = 0;//Static integer enables retention of value for the life of the program.

	switch (counter % 3) // counter modulo 3 enables straight forward iteration.
	{


	case 0:	    
		values[1] = v1A;
		values[2] = v2A;
		expectedValues[5] = evA;
		break;
	case 1:		
		values[1] = v1B;
		values[2] = v2B;
		expectedValues[5] = evB;
		break;
	case 2:		
		values[1] = v1C;
		values[2] = v2C;
		expectedValues[5] = evC;
		break;
	}
	counter++;
}

void activateNetwork(double weights[][ARRAYSIZE], double values[], double thresholds[])
{

	//This for loop performs a calculation for each hidden node.
	for (int h = 1 + NUMINPUTNODES; h < 1 + NUMINPUTNODES + NUMHIDDENNODES; h++)
	{
		//Variable for weightedInput.
		double weightedInput = 0.0;
		//Perfom calculation to determine total weighted input
		for (int i = 1; i < 1 + NUMINPUTNODES; i++)
		{
			//Weighted Input calculated by multiplying weights and values from nodes.
			weightedInput += weights[i][h] * values[i];
		}
		//Threshold handling. We subtract the threshold value from the weighted input.
		weightedInput += (-1 * thresholds[h]);
		//Sigmoid Function. We apply the sigmoid function to obtain a useable value for the output node.
		values[h] = 1.0 / (1.0 + pow(E, -weightedInput));
	}

	//This for loop performs a calculation for each output node.
	for (int o = 1 + NUMINPUTNODES + NUMHIDDENNODES; o < 1 + NUMNODES; o++)
	{
		//Variable for weightedInput.
		double weightedInput = 0.0;
		//Perfom calculation to determine total weighted input
		for (int h = 1 + NUMINPUTNODES; h < 1 + NUMINPUTNODES + NUMHIDDENNODES; h++)
		{
			//Weighted Input calculated by multiplying weights and values from nodes.
			weightedInput += weights[h][o] * values[h];
		}
		//Threshold handling. We subtract the threshold value from the weighted input.
		weightedInput += (-1 * thresholds[o]);
		//Sigmoid Function. We apply the sigmoid function to output node.
		values[o] = 1.0 / (1.0 + pow(E, -weightedInput));
	}
}

double updateWeights(double weights[][ARRAYSIZE], double values[], double expectedValues[], double thresholds[])
{
	double sumOfSquaredErrors = 0.0; //Double variable for measuring overall  error in program.

									 //For loop performing calculations on each output node. We will calculate the following in this loop...
									 /*
									 Absolute Error: Expected error minus the value generated by our Neural Network.
									 Sum of Squared Error: Calculation for figuring out the error in our Neural Network.
									 Error Gradient: A slightly complex calculation, which helps us determing the severity of an error.
									 */

									 /*
									 Weights are updated with various calculations in the below for loops, using back propagation.
									 */

	for (int o = 1 + NUMINPUTNODES + NUMHIDDENNODES; o < 1 + NUMNODES; o++)
	{
		double absoluteerror = expectedValues[o] - values[o]; //Absolute Error calculation as mentioned above.
		sumOfSquaredErrors += pow(absoluteerror, 2);		  //Sum of Squared calculation.
		double outputErrorGradient = values[o] * (1.0 - values[o]) * absoluteerror; //Error Gradient.

																					//update each weighting from the hidden layer
		for (int h = 1 + NUMINPUTNODES; h <1 + NUMINPUTNODES + NUMHIDDENNODES; h++)
		{
			double delta = LEARNINGRATE*values[h] * outputErrorGradient; //double delta vairiable initalized by calculating LearningRate*Values*errorGradient
			weights[h][o] += delta; // Weights set with delta.
			double hiddenErrorGradient = values[h] * (1 - values[h])*outputErrorGradient*weights[h][o]; //Hidden Error Gradient initialized by this calculation
			for (int i = 1; i < 1 + NUMINPUTNODES; i++)
			{
				double delta = LEARNINGRATE*values[i] * hiddenErrorGradient; //Another variable initialization with calculation.
				weights[i][h] += delta; // weights [i][h] populated with delta values.
			}
			double thresholdDelta = LEARNINGRATE*-1 * hiddenErrorGradient; //Variable initalized with this calculation.
			thresholds[h] += thresholdDelta;//thresholds populated with thresholdDelta values.
		}

		//update each weighting for the theta
		double delta = LEARNINGRATE*-1 * outputErrorGradient;//Variable intialized with this calculation.
		thresholds[o] += delta;//Threshold popluated with delta values
	}
	return sumOfSquaredErrors;
}

//Function for displaying network. Pretty self explanitory.
void displayNetwork(double values[], double sumOfSquaredErrors)
{
	
	static int counter = 0; //int variable with program lifecycle retention (static).
	if ((counter % 3) == 0)
	
	cout << "--------------------------------------" << endl;
	cout << "Input 1: " << values[1] << "| ";
	cout << "Input 2: " << values[2] << "| ";
	cout << "Output: " << values[5] << "| ";
	cout << endl;
	
	//If,else if, else statments for generating "Secret Characters".
	if (counter == 0)
	{
		secret1 = values[5] + ((rand() / 1000) + 30);
	}
	else if (counter == 1)
	{
		secret2 = values[5] + ((rand() / 1000) + 30);
	}
	else
	{
		secret3 = values[5] + ((rand() / 1000) + 30);
	}

	counter++; //counter post increment
}

void introduction() { //Function enabling basic user interface/instructions.


	cout << "Welcome to LogiGate!" << endl;
	cout << endl;
	cout << "You will create 3 of your own virtual Logic Gates. Data you provide will be 'learned' by a Neural Network." << endl;
	cout << "Each gate has two binary inputs (1 or 0), and one binary output." << endl;
	cout << endl;
	cout << "Here is how it works for each gate:" << endl;
	cout << "1.Select input for Input A." << endl;
	cout << "2.Select input for Input B." << endl;
	cout << "3.Select desired Output." << endl;
	cout << endl;
}

void userSelection()//This function enables user input, while reducing chance for user error.
{

	
	static int selection;
	while (selection < 3)
	{

		//Switch/Case menu enabling user input/selection.
		switch (selection % 3)
		{
		case 0:
			cout << ("GATE 1: ") << endl;
			cout << "Please enter input value A: (0 OR 1 ONLY) " << endl;
			if (!(cin >> v1A))//Allow and test user input. If unacceptable
			{
				cin.clear();//Clear cin
				cin.ignore();//Ignore cin
				cout << "Incorrect entry. Try again: " << endl;
				cin >> v1A;//Allow another attempt
			}
			
			else if (v1A == 0 || v1A == 1)
			{
				//cout << "Good answer!" << endl;
			}
			else if (v1A != 0 || v1A != 1)
			{
			cout << "Incorrect entry.. Try again: " << endl;
			cin >> v1A;
			}

			

			cout << "Please enter input value A: (0 OR 1 ONLY) " << endl;
			if (!(cin >> v2A))
			{
				cin.clear();
				cin.ignore();
				cout << "Incorrect entry. Try again: " << endl;
				cin >> v2A;
			}

			else if (v2A == 0 || v2A == 1)
			{
				//cout << "Good answer!" << endl;
			}
			else if (v2A != 0 || v2A != 1)
			{
				cout << "Incorrect entry.. Try again: " << endl;
				cin >> v2A;
			}


			cout << "Please enter desired output value: (0 OR 1 ONLY) " << endl;
			if (!(cin >> evA))
			{
				cin.clear();
				cin.ignore();
				cout << "Incorrect entry. Try again: " << endl;
				cin >> evA;
			}

			else if (evA == 0 || evA == 1)
			{
				//cout << "Good answer!" << endl;
			}
			else if (evA != 0 || evA != 1)
			{
				cout << "Incorrect entry.. Try again: " << endl;
				cin >> evA ;
			}
			system("cls");
			break;

		case 1:
			cout << ("GATE 2: ") << endl;
			cout << "Please enter input value A: (0 OR 1 ONLY) " << endl;
			if (!(cin >> v1B))
			{
				cin.clear();
				cin.ignore();
				cout << "Incorrect entry. Try again: " << endl;
				cin >> v1B;
			}

			else if (v1B == 0 || v1B == 1)
			{
				//cout << "Good answer!" << endl;
			}
			else if (v1B != 0 || v1B != 1)
			{
				cout << "Incorrect entry.. Try again: " << endl;
				cin >> v1B;
			}



			cout << "Please enter input value A: (0 OR 1 ONLY) " << endl;
			if (!(cin >> v2B))
			{
				cin.clear();
				cin.ignore();
				cout << "Incorrect entry. Try again: " << endl;
				cin >> v2B;
			}

			else if (v2B == 0 || v2B == 1)
			{
				//cout << "Good answer!" << endl;
			}
			else if (v2B != 0 || v2B != 1)
			{
				cout << "Incorrect entry.. Try again: " << endl;
				cin >> v2B;
			}


			cout << "Please enter desired output value: (0 OR 1 ONLY) " << endl;
			if (!(cin >> evB))
			{
				cin.clear();
				cin.ignore();
				cout << "Incorrect entry. Try again: " << endl;
				cin >> evB;
			}

			else if (evB == 0 || evB == 1)
			{
				//cout << "Good answer!" << endl;
			}
			else if (evB != 0 || evB != 1)
			{
				cout << "Incorrect entry.. Try again: " << endl;
				cin >> evB;
			}
			system("cls");
			break;

		case 2:
			cout << ("GATE 3: ") << endl;
			cout << "Please enter input value A: (0 OR 1 ONLY) " << endl;
			if (!(cin >> v1C))
			{
				cin.clear();
				cin.ignore();
				cout << "Incorrect entry. Try again: " << endl;
				cin >> v1C;
			}

			else if (v1C == 0 || v1C == 1)
			{
				//cout << "Good answer!" << endl;
			}
			else if (v1C != 0 || v1C != 1)
			{
				cout << "Incorrect entry.. Try again: " << endl;
				cin >> v1C;
			}



			cout << "Please enter input value A: (0 OR 1 ONLY) " << endl;
			if (!(cin >> v2C))
			{
				cin.clear();
				cin.ignore();
				cout << "Incorrect entry. Try again: " << endl;
				cin >> v2C;
			}

			else if (v2C == 0 || v2C == 1)
			{
				//cout << "Good answer!" << endl;
			}
			else if (v2C != 0 || v2C != 1)
			{
				cout << "Incorrect entry.. Try again: " << endl;
				cin >> v2C;
			}


			cout << "Please enter desired output value: (0 OR 1 ONLY) " << endl;
			if (!(cin >> evC))
			{
				cin.clear();
				cin.ignore();
				cout << "Incorrect entry. Try again: " << endl;
				cin >> evC;
			}

			else if (evC == 0 || evC == 1)
			{
				//cout << "Good answer!" << endl;
			}
			else if (evC != 0 || evC != 1)
			{
				cout << "Incorrect entry.. Try again: " << endl;
				cin >> evC;
			}
			system("cls");
			break;
			
		}

		selection++;
	}
}


void userValues() //Function call for showing user choices, for verification.
{



	cout << "--------------------------------------" << endl;
	cout << "Values you entered: " << endl;
	cout << "(Gate 1) ";
	cout << "Input A: " << v1A << "| ";
	cout << "Input B: " << v2A << "| ";
	cout << "Output: " << evA << endl;
	cout << "(Gate 2) ";
	cout << "Input A: " << v1B << "| ";
	cout << "Input B: " << v2B << "| ";
	cout << "Output: " << evB << endl;
	cout << "(Gate 3) ";
	cout << "Input A: " << v1C << "| ";
	cout << "Input B: " << v2C << "| ";
	cout << "Output: " << evC << endl;



}

void secretChars() //Function call enabling "Secret Characters" to be displayed.
{
	cout << endl;
	cout << "As an added bonus, here are some secret characters!" << endl;
	cout << "These are based off of your input and the efficency of the Neural Network." << endl;
	cout << "Secret Character 1: " << (char)secret1 << endl;
	cout << "Secret Character 2: " << (char)secret2 << endl;
	cout << "Secret Character 3: " << (char)secret3 << endl;



}