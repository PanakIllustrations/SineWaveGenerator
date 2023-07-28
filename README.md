# Sine Wave Generator Program Documentation

## Introduction

The Sine Wave Generator program is designed to produce a sine wave and output the generated coordinates to the console or a file. The program allows users to specify the duration of the wave (in seconds) and its frequency (in Hz) as inputs. The program then calculates and generates the corresponding x and y coordinates of the sine wave.

## Features

- Generates a sine wave based on user-defined parameters: duration (seconds) and frequency (Hz).
- Provides the option to output the generated coordinates to the console or a file.
- Offers precision control for the displayed y-values.
- Validates user inputs to ensure valid parameter ranges.

## Usage

### Input Parameters

Upon running the program, the user will be prompted with the following questions:

1. "Are you using a file ?: Y/N" - This question asks the user if they want to output the coordinates to a file or not. If "Y" is selected, the user will be prompted to enter a filename. If "N" is selected, the user will be asked to input the following parameters manually.

   - "x axis duration (req: > 0.125, < 128 ): " - The duration of the sine wave in seconds. It should be a value between 0.125 and 128.
   - "frequency (Hz) (req: > 0.125, < 1024 ): " - The frequency of the sine wave in Hz. It should be a value between 0.125 and 1024.
   - "precision (req: > 0, < 9 ): " - The precision of the displayed y-values. It should be a value between 0 and 9.

### Console Output

If the user chooses to display the coordinates on the console, the program will generate and print the x and y coordinates of the sine wave. The output will be displayed in tabular format, with columns for the x-values and y-values. This can be pasted into any spreadsheet software for defining data points for graphic visualization. 

### File Output (WIP)

If the user chooses to output the coordinates to a file, the program will create a file named "app_output.txt" and write the x and y coordinates to it. The file will contain two columns: the x-values and the corresponding y-values. 

## Dependencies

The program uses the following standard C++ libraries:

- `<iostream>` - For input/output operations.
- `<fstream>` - Work-in-progress (WIP) library for file input/output operations.
- `<vector>` - To handle dynamic arrays.
- `<string>` - For string manipulation.
- `<chrono>` - To measure time.
- `<iomanip>` - To set precision for output formatting.
- `<numeric>` - To perform operations on ranges of elements.
- `<thread>` - To work with threads for multi-threaded applications.
- `<algorithm>` - For various algorithms like transforming elements.

## Implementation Details

### Algorithms

The main algorithm in this program is used to generate the sine wave coordinates. It follows these steps:

1. Calculate the length of the stream based on the duration and frequency of the sine wave.
2. Initialize an array `x` with values from 0 to `(length - 1)` to represent the x-coordinates of the wave.
3. Iterate over each element in the `x` array, calculate the corresponding y-value of the sine wave, and store it in a vector `y`.
4. Output the generated coordinates to the console or a file, based on user preference.

### Functions

- `toLower`: Converts a given string to lowercase, used for error handling.
- `getInput`: Prompts the user for input and validates it to ensure it falls within specified ranges.
- `streamLength`: Calculates the length of the stream based on the duration and frequency of the sine wave.
- `waveForm`: Generates the sine wave coordinates and outputs them to the console or a file.

## Known Issues

Fstream has not yet been implemented. 

## Feedback

The Sine Wave Generator program is the first program I have made. It does not use object-oriented formatting I have used in more recent projects, but I would still appreciate any feedback.
