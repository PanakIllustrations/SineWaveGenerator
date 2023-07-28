
#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <chrono> 
#include <iomanip> //std::setprecision
#include <numeric> //std::iota
#include <thread> 
#include <algorithm> //std::transform

#define yes response == 'Y' || response == 'y' 
#define no response == 'N' || response == 'n' 

std::string toLower( std::string& s )
{
	std::transform( s.begin( ), s.end( ), s.begin( ), std::tolower );
	return s;
}

void getInput( const std::string& prompt, float& i, float min, float max )
{
	bool valid = false;
	std::cout << prompt;
	do
	{
		std::cin >> i;		
		if ( std::cin.fail() )
		{
			std::cout << "\nERROR: Input must be a number.\n" << std::endl;
			std::cin.clear();
			std::cin.ignore( 10000, '\n' );
		}
		else if ( i < min || i > max )
		{
			std::cout << "\nError: Input must be a number between " << min << " and " << max << ".\n" << std::endl;
			std::cin.clear();
			std::cin.ignore( 10000, '\n' );
		}
		else
		{
			valid = true;
		}
	} while ( !valid );
}

int streamLength( const float seconds, const float frequency ) // 4. varriables
{
	return std::min(pow(2, 11), pow(2, ceil(log2((5 + seconds) * (5 + frequency)))));
	// returns 32, 64, 128 ... 2048 
}

void waveForm( int len, float seconds, float frequency, char response) // 1. Algorithms
{	

	#define M_PI 3.1415926535
	#define clock std::chrono::steady_clock

	std::vector<float> x( len ); // 5. Arrays (Kind of)
	std::iota(x.begin(), x.end(), 0 ); // fills elements in x with every integer up to result of len - 1
	std::vector<float> y;
	
	constexpr float TAU = M_PI * 2.0f;
	const clock::time_point begin = clock::now(); // Initial time of generator 
	float deltaTime;

	for ( unsigned int i = 0; i < x.size( ); ++i ) // 7. Iteration
	{
		x[i] = (x[i] * seconds) / (len - 1.f);

		clock::time_point now = clock::now( );
		deltaTime = std::chrono::duration<float, std::milli>( now - begin ).count( ); // ms since generator started

		y.push_back( sin( (deltaTime / 1000 - x[i]) * TAU * frequency ) ); 

		if ( no )
		{
			// print x, y: // 3b. Outputs
			std::cout << x[i] << "    ";
			if ( y[i] >= 0 ) std::cout << " ";
			std::cout << y[i] << std::endl;
		}
		else
		{
			std::ofstream myFile( "app_output.txt" ); 
			myFile << x[i] << '\t' << y[i] << std::endl;
		}

	}
	if (yes)
	{
		std::ofstream myFile( "app_output.txt" );
		myFile.close( );
	}
	

	clock::time_point now = clock::now( );
	deltaTime = std::chrono::duration<float, std::milli>( now - begin ).count( );
	std::cout	
		<< "\nGeneration of " << (len * 2) 
		<< " values took " << deltaTime 
		<< " milliseconds at " << (len * 2000) / (deltaTime) 
		<< " values per second.\n";
}

int main()
{
	char response;
	bool loop = false;

	float seconds = 0, frequency = 0, precision = 0;
	std::cout << "Are you using a file ?: Y/N\n\n"; // 8. Interaction
	do
	{
		std::cin >> response;
		std::cin.ignore( std::numeric_limits <std::streamsize> ::max( ), '\n' );

		if (yes)
		{
			std::cout << "\nEnter the filename: ";
			do
			{
				std::string fileName;
				std::cin >> fileName;
				toLower( fileName );
				if ( fileName.find_last_of( '.' ) == std::string::npos )
				{
					fileName.append( ".txt" );
				}
				std::ifstream inputFile( fileName.c_str( ) ); // 6a. File Input
				if ( fileName == "exit.txt" )
				{
					response = 'n';
					loop = true;
				}
				else if ( inputFile.fail( ) )
				{
					std::cout
						<< "\nERROR: Failed to open " << fileName << '\n'
						<< "try again or type 'EXIT' to manually enter parameters\n" << std::endl;
				}
				else
				{
					loop = true;
				}
			} while ( !loop );
		}

		if (no)
		{
			std::cout << "\nEnter the following paramaters:\n"; // 3a. Inputs

			getInput( "\nx axis duration (req: > 0.125, < 128 ): ", seconds, 0.125, 128 );
			getInput( "\nfrequency (Hz) (req: > 0.125, < 1024 ): ", frequency, 0.125, 1024 );
			getInput( "\nprecision (req: > 0, < 9 ): ", precision, 0, 9 );

			loop = true;
		}
	} while (!loop);

	std::cout << "\nOutput to file ?: Y/N\n\n";
	std::cin >> response;
	std::string fileName;

	if ( no )
	{
		// x , y headers :
		std::cout << std::fixed << "\nx:";
		for ( int i = 0; i < precision; i++ ) { std::cout << " "; }
		std::cout << "     y:" << std::endl;
		fileName = "null";
	}
	if ( yes )
	{
		std::cout << "\nGenerating...\n";
	}


	// genertates  x , y :
	std::cout.precision( precision );
	unsigned int len = streamLength( seconds, frequency );
	waveForm(len, seconds, frequency, response); 

	// file output :
	return 0;
}
