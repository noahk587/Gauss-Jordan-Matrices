//
//  main.cpp
//  Guass-Jordan Method for Matrices
//
//
//  Student:    Noah Khan
//  netID:      nzk180000
//  Course:     CS 1337
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

/**
 This method is used to count the number of rows for the matrix.
 
 @par input The files to import the equations from
 @par rows The number of rows the matrix will have
 @par totalCount The character count for the .txt file.
 */
void RowCount(fstream &input, int &rows, long &totalCount){
    char indexValue = 'n'; //stores the character in the current index
    long indexCount = 0; //stores the current index count
    while (!(input.eof())) { //the loop continues until the file has reach the end
        input.seekg(indexCount, ios::beg); //sets the read position for the file to the current index count
        input.get(indexValue); //assigns the current index value to the char
        if (indexValue == '=') { //if the indexValue is an equal sign
            rows++; //adds one to the row count
        }
        indexCount++; //add one to the indexCount
    }
    //block of code to reset the file pointer to begining of the file
    totalCount = indexCount;
    input.clear();
    input.seekg(0, ios::beg);
    //end of block code
}

/**
 This method is used to fillout the matrix from the equations in the file
 
 @par input The files to import the equations from
 @par matrix The matrix to evaluate
 @par totalCount The character count for the .txt file.
 @par totalRows the number of rows for the matrix.
 */
void FIllMatrix(fstream &input, float ** &matrix, long totalCount, int totalRows){
    char indexValue = 'n'; //stores the character in the current index
    long indexCount = 0; //stores the current index count
    int row = 0; //stores the current row count
    int col = 0; //stores the current column count
    char num[10]; //stores the number for the index
    int num_string_count = 0; //index count for a c-string
    string numVal = ""; //store infomation from file
    while ((!(input.eof())) && (row < 4) ) { //the loop continues until the file has reach the end or above max rows
        input.seekg(indexCount, ios::beg); //sets the read position for the file to the current index count
        input.get(indexValue); //assigns the current index value to the char
        if ((indexValue != '+') && (indexValue != '=') && (indexValue != 'x') && (indexValue != 'y') && (indexValue != 'z') ) {// if the current char is not a math symbol or variable
            numVal = numVal + indexValue; //add the negative sign and/or digit/decimal to the numVal string
        }
        if (indexValue == 'x') { //if the x variable has been reached
            col = 0; //set the column to 0
            if (numVal == "-") { //if the numVal is just a negative sign
                *(*(matrix + row) + col) = -1; //set the entry to -1
            }
            if(numVal == ""){ //if there is no entry and only variable
                    *(*(matrix + row) + col) = 1; //set the entry to 1
                }
            else if (numVal != "-") { //if there is a value
                float xValue = stof(numVal); //conver the numValue to a float
                *(*(matrix + row) + col) = xValue; //assign the x value into the matrix
            }
            numVal = ""; //reset the numVal
        }
        
        if (indexValue == 'y') { //if the y variable has been reached
            col = 1; //set the column to 1
            if (numVal == "-") { //if the numVal is just a negative sign
                *(*(matrix + row) + col) = -1; //set the entry to -1
            }
            if(numVal == ""){ //if there is no entry and only variable
                    *(*(matrix + row) + col) = 1; //set the entry to 1
                }
            else if (numVal != "-") { //if there is a value
                float yValue = stof(numVal); //conver the numValue to a float
                *(*(matrix + row) + col) = yValue; //assign the y value into the matrix
            }
            numVal = ""; //reset the numVal
        }
        
        if (indexValue == 'z') { //if the z variable has been reached
            col = 2; //set the column to 2
            if (numVal == "-") { //if the numVal is just a negative sign
                *(*(matrix + row) + col) = -1; //set the entry to -1
            }
            if(numVal == ""){ //if there is no entry and only variable
                    *(*(matrix + row) + col) = 1; //set the entry to 1
                }
            else if (numVal != "-") { //if there is a value
                float zValue = stof(numVal); //conver the numValue to a float
                *(*(matrix + row) + col) = zValue; //assign the z value into the matrix
            }
            numVal = ""; //reset the numVal
        }
        
        if (indexValue == '=') { //if the indexValue is an equal sign
            col = 3; //sets the column index to 3
            string tempString = ""; //stores the equal sign entry into a string
            while ((indexValue != '\n') && (indexValue != '\0') && row < totalRows) {
                indexCount++; //add one to the indexCount
                input.seekg(indexCount, ios::beg); //sets the read position for the file to the current index count
                input.get(indexValue); //assigns the current index value to the char
                if (indexValue != '\n' && (indexValue != '\0') && (indexCount <= totalCount-2) ) { //checks if the current next is not a new line
                        num[num_string_count] = indexValue; //adds value to c-string
                        tempString = tempString + num[num_string_count];
                        num_string_count++; //adds one to the index value for the c-string
                }
                else{
                    num[num_string_count] = '\0';
                    float equalValue = stof(tempString); //conver the tempString to a float
                    *(*(matrix + row) + col) = equalValue; //assign the equal value into the matrix
                    num_string_count = 0; //reset the index count
                    row++; //move to next row
                }
            }
        }
       indexCount++; //add one to the indexCount
    }
}

/**
 This method will print the matrix.
 */
void PrintMatrix(int rows, const int cols, float **&matrix){
    cout << setprecision(2) << fixed; //set deciaml place to two
    cout << endl << "Equations:" << endl;
    for (int i = 0; i < rows; i++) { //populate the rows
        for (int j = 0; j < cols; j++) { //populate the columns
            if ( (*(*(matrix+ i) + j)) == -0) { //if there is a negative 0
                *(*(matrix+ i) + j) = 0; //correct the error
            }
           cout << *(*(matrix+ i) + j) << " "; //prints the entry
        }
        cout << endl;
    }
}

/**
 This method will swap two rows.
 
 @par rows The number of rows for the matrix.
 @par cols The numbe of columns for the matrix.
 @par matrix The matrix to evaluate.
 */
void SwapRows(int rows, const int cols, float **&matrix){
    int row1; //stores the first row to swap
    int row2; //stores the second row to swap
    bool solved; //stores info if the row is already sloved
    
    
    cout << "Enter the first row number to swap: ";
    cin >> row1; //user enters the first row to swap
    while ((row1 < 0) && (row1 > rows) ) { //if the input is invalid
        cout << "Invalid" << endl << "Enter the first row number to swap: ";
        cin >> row1; //user enters the first row to swap
    }
    
    cout << "Enter the second row number to swap: ";
    cin >> row2; //user inputs the second row to swap
    while ( (row2 < 0) || (row2 > rows) || (row1 == row2) ) { //if the input is invalid
        cout << "Invalid" << endl << "Enter the second row number to swap: ";
        cin >> row2; //user enters the second row to swap
    }
    
    if ((row1 == 1) || (row2 == 1)) { //if user wants to change row one
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 1) { //checking entry 1
                if ( (*(*(matrix+ (1)-1) + i) != 1)  ) { //if value is not 1
                    solved = false; //the row is not solved
                }
            }
            else if ( count > 1 && count < 4){ //checking entry 2-3
                if ( (*(*(matrix+ (1)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    else if ((row1 == 2) || (row2 == 2)) { //if user wants to change row two
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 2) { //checking entry 2
                if ( (*(*(matrix+ (2)-1) + i) != 1)  ) { //if value is not 1
                    solved = false; //the row is not solved
                }
            }
            else if ( (count == 1) || (count == 3)){ //checking entry 1/3
                if ( (*(*(matrix+ (2)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    else if ((row1 == 3) || (row2 == 3)) { //if user wants to change row 3
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 3) { //checking entry 3
                if ( (*(*(matrix+ (3)-1) + i) != 1)  ) { //if value is not 1
                    solved = false; //the row is not solved
                }
            }
            else if ( (count == 1) || (count == 2)){ //checking entry 1/2
                if ( (*(*(matrix+ (3)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    else if ((row1 == 4) || (row2 == 4)) { //if user wants to change row 4
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if ( (count == 1) || (count == 2) || (count ==3) || (count == 4)){ //checking row 4
                if ( (*(*(matrix+ (4)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    
    
    if(solved == false) { //continue row operations if the row is not solved
        float *tempRowVal = new float(4); //create a temporary dynamic array to store one row
    
        //block of code to set the temp array equal to row1
        for (int i = 0; i < cols; i++) {
        *(tempRowVal + i) = *(*(matrix+ (row1)-1) + i); //the index of temp array is set equal to index of row 1
        }
        //end of block code
    
        //block code to swap rows
        for (int i = 0; i < cols; i++) {
        *(*(matrix+ (row1)-1) + i) = *(*(matrix+ (row2)-1) + i); //index of row 1 is set equal to row2
        *(*(matrix+ (row2)-1) + i) = tempRowVal[i]; //index of row2 is equal to index of temp array
        }
        //end of block code
        }
}

/**
 This function will multiple a row values by a non-zero value.
 
 @par rows The number of rows for the matrix.
 @par cols The numbe of columns for the matrix.
 @par matrix The matrix to evaluate.
 */
void NonZeroMulti(int rows, const int cols, float **&matrix){
    int rowEdit; //stores the row number to multiply
    float multFactor; //stores the value to multiply the row by
    bool solved; //stores info if the row is already sloved
    
    cout << "Enter the row to modify: "; //user prompt
    cin >> rowEdit; //user enters the row to multiply
    while ((rowEdit < 0) && (rowEdit > rows) ) { //if the input is invalid
        cout << "Input not valid" << endl << "Enter the row to modify: "; //user prompt
        cin >> rowEdit; //user enters the first row to swap
    }
    if (rowEdit == 1) { //if user wants to change row one
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 1) { //checking entry 1
                if ( (*(*(matrix+ (1)-1) + i) != 1)  ) { //if value is not 1
                    solved = false; //the row is not solved
                }
            }
            else if ( count > 1 && count < 4){ //checking entry 2-3
                if ( (*(*(matrix+ (1)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    else if (rowEdit == 2) { //if user wants to change row two
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 2) { //checking entry 2
                if ( (*(*(matrix+ (2)-1) + i) != 1)  ) { //if value is not 1
                    solved = false; //the row is not solved
                }
            }
            else if ( (count == 1) || (count == 3)){ //checking entry 1/3
                if ( (*(*(matrix+ (2)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    else if (rowEdit == 3) { //if user wants to change row 3
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 3) { //checking entry 3
                if ( (*(*(matrix+ (3)-1) + i) != 1)  ) { //if value is not 1
                    solved = false; //the row is not solved
                }
            }
            else if ( (count == 1) || (count == 2)){ //checking entry 1/2
                if ( (*(*(matrix+ (3)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    else if (rowEdit == 4) { //if user wants to change row 4
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if ( (count == 1) || (count == 2) || (count ==3) || (count == 4)){ //checking row 4
                if ( (*(*(matrix+ (4)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    
    if(solved == false) { //continue row operations if the row is not solved
        cout << "Enter you multiplying factor: "; //user prompt
        cin >> multFactor; //user enters the value to use to multiply
        while (multFactor == 0) { //if the value is zero
            cout << "Invalid Input" << endl << "Enter you multiplying factor: "; //user prompt
            cin >> multFactor; //user enter a new value to use to multiply
        }
        for (int i = 0; i < cols; i++) { //gets the row user entered
        *(*(matrix+ (rowEdit)-1) + i) = (multFactor) * (*(*(matrix+ (rowEdit)-1) + i)); //multiply the entry within the row by the multFactor
        }
    }
    else{ //row already solved
        cout <<  "Row already solved" << endl;
    }
}

/**
 This method will perform row operations by scalar multiplication
 
 @par rows The number of rows for the matrix.
 @par cols The numbe of columns for the matrix.
 @par matrix The matrix to evaluate.
 */
void ScalarMulti(int rows, const int cols, float **&matrix){
    int rowAid;
    float multFactor; //stores the value to multiply the row by
    int rowEdit;
    bool solved; //stores info if the row is already sloved
    
    
    cout << "Enter the row to scalar multiply: "; //user prompt
    cin >> rowAid; //user enters the Row to use for multiplication
    while ((rowAid < 0) && (rowAid > rows) ) { //if the input is invalid
        cout << "Invalid Input" << endl << "Enter the row to scalar multiply: "; //user prompt
        cin >> rowAid; //user enters the Row to use for multiplication
    }
    
    cout << "Enter the multiplying factor: "; //user prompt
    cin >> multFactor; //user enters the value to use to multiply
    while (multFactor == 0) { //if the value is zero
        cout << "Invalid Input" << endl << "Enter the multiplying factor: "; //user prompt
        cin >> multFactor; //user enter a new value to use to multiply
    }
    
    cout << "Enter the row to edit: "; //user prompt
    cin >> rowEdit; //user inputs the row to edit
    while ((rowEdit < 0) && (rowEdit > rows) && (rowAid == rowEdit) ) { //if the input is invalid
        cout << "Invalid Input" << endl << "Enter the row to edit: "; //user prompt
        cin >> rowEdit; //user inputs the row to edit
    }
    
    if (rowEdit == 1) { //if user wants to change row one
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 1) { //checking entry 1
                if ( (*(*(matrix+ (1)-1) + i) != 1)  ) { //if value is not 1
                    solved = false; //the row is not solved
                }
            }
            else if ( count > 1 && count < 4){ //checking entry 2-3
                if ( (*(*(matrix+ (1)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    else if (rowEdit == 2) { //if user wants to change row two
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 2) { //checking entry 2
                if ( (*(*(matrix+ (2)-1) + i) != 1)  ) { //if value is not 1
                    solved = false; //the row is not solved
                }
            }
            else if ( (count == 1) || (count == 3)){ //checking entry 1/3
                if ( (*(*(matrix+ (2)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    else if (rowEdit == 3) { //if user wants to change row 3
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 3) { //checking entry 3
                if ( (*(*(matrix+ (3)-1) + i) != 1)  ) { //if value is not 1
                    solved = false; //the row is not solved
                }
            }
            else if ( (count == 1) || (count == 2)){ //checking entry 1/2
                if ( (*(*(matrix+ (3)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    else if (rowEdit == 4) { //if user wants to change row 4
        int count = 0;
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if ( (count == 1) || (count == 2) || (count ==3) || (count == 4)){ //checking row 4
                if ( (*(*(matrix+ (4)-1) + i) != 0)  ) {
                    solved = false; //the row is not solved
                }
            }
            else{
                solved = true; //the row is solved
            }
            }
        }
    
    
    if(solved == false) { //continue row operations if the row is not solved
        for (int i = 0; i < cols; i++) { //gets the row user entered
            *(*(matrix+ (rowEdit)-1) + i) = ((*(*(matrix+ (rowEdit)-1) + i)) + ( (multFactor) * (*(*(matrix+ (rowAid)-1) + i)) )); //performs the row operation
        }
    }
    else{ //row is solved
        cout << "Row is already solved" << endl;
    }
    
}

/**
 This method prints the menu option
 */
void PrintMenuOptions(){
    cout << endl << "Menu Options:" << endl;
    cout << "1 - Swap Rows" << endl;
    cout << "2 - Multply Row" << endl;
    cout << "3 - Scalar Multiplication" << endl;
    cout << "4 - Quit Program" << endl;
    cout << "Choose Option: ";
}

/**
 This method will check if the matrix has been reduced to echelon form.
 
 @par rows The number of rows for the matrix
 @par cols The numbrt of columns for the matrix
 @par matrix The matrix to evaluate
 @return true if matrrix is in echolon form
 @return false if matrix is in echolon form
 */
bool Echelon (int rows, const int cols, float **&matrix){
    int count = 0; //stores the count of index that has been checked
    cout << setprecision(2) << fixed; //set deciaml place to two
    if (rows == 2) { //if the matrix has 2 rows
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 1) { //checking entry 1
                if ( (*(*(matrix+ (1)-1) + i) != 1)  ) { //if value is not 1
                    return false;
                }
            }
            else if ( count > 1 && count < 4){ //checking entry 2-3
                if ( (*(*(matrix+ (1)-1) + i) != 0)  ) {
                    return false;
                }
            }
            else if ( (count == 5) || (count == 7) ){ //checking entry 5 and 7
                if ( (*(*(matrix+ (2)-1) + i) != 0)  ) {
                    return false;
                }
            }
            else if ( count == 6 ){ //checking entry 6
                if ( (*(*(matrix+ (2)-1) + i) != 1)  ) { //if value is not 1
                    return false;
                }
            }
        }
    }
    else if (rows == 3) { //if the matrix has 3 rows
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 1) { //checking entry 1
                if ( (*(*(matrix+ (1)-1) + i) != 1)  ) { //if value is not 1
                    return false;
                }
            }
            else if ( count > 1 && count < 4){ //checking entry 2-3
                if ( (*(*(matrix+ (1)-1) + i) != 0)  ) { //if value is not 0
                    return false;
                }
            }
            else if ( (count == 5) || (count == 7) ){ //checking entry 5 and 7
                if ( (*(*(matrix+ (2)-1) + i) != 0)  ) { //if value is not 0
                    return false;
                }
            }
            else if ( count == 6 ){ //checking entry 6
                if ( (*(*(matrix+ (2)-1) + i) != 1)  ) { //if value is not 1
                    return false;
                }
            }
            else if ( (count == 9) || (count == 10) ){ //checking entry 9 and 10
                if ( (*(*(matrix+ (3)-1) + i) != 0)  ) { //if value is not 0
                    return false;
                }
            }
            else if ( count == 11 ){ //checking entry 11
                if ( (*(*(matrix+ (3)-1) + i) != 1)  ) { //if value is not 1
                    return false;
                }
            }
        }
    }
    else if (rows == 4) { //if the matrix has 4 rows
        for (int i = 0; i < cols - 1; i++) { //gets the row user entered
            count++; //add one to the count
            if (count == 1) { //checking entry 1
                if ( (*(*(matrix+ (1)-1) + i) != 1)  ) { //if value is not 1
                    return false;
                }
            }
            else if ( count > 1 && count < 4){ //checking entry 2-3
                if ( (*(*(matrix+ (1)-1) + i) != 0)  ) { //if value is not 0
                    return false;
                }
            }
            else if ( (count == 5) || (count == 7) ){ //checking entry 5-7
                if ( (*(*(matrix+ (2)-1) + i) != 0)  ) { //if value is not 0
                    return false;
                }
            }
            else if ( count == 6 ){ //checking entry 6
                if ( (*(*(matrix+ (2)-1) + i) != 1)  ) { //if value is not 1
                    return false;
                }
            }
            else if ( (count == 9) || (count == 10) ){ //checking entry 9-10
                if ( (*(*(matrix+ (3)-1) + i) != 0)  ) { //if value is not 0
                    return false;
                }
            }
            else if ( count == 11 ){ //checking entry 11
                if ( (*(*(matrix+ (3)-1) + i) != 1)  ) { //if value is not 1
                    return false;
                }
            }
            else if ( (count == 13) || (count == 14) || (count == 15) || (count == 16) ){ //checking entry 13-16
                if ( (*(*(matrix+ (4)-1) + i) != 0)  ) { //if value is not 0
                    return false;
                }
            }
        }
    }

    if( (rows == 4) || (rows == 3)){ //if there are four or 3 rows
        if (rows == 4) { //second check of row 4
            for (int i = 0; i < cols - 1; i++) { //gets the row user entered
                if ( (*(*(matrix+ (4)-1) + i) != 0)  ) { //if value is not 0
                    return false;
                }
            }
        }
        else if (rows == 3){ //second check for row 3
            if ( (*(*(matrix+ (3)-1) + 0) != 0)  ) { //if value is not 0
                return false;
            }
            if ( (*(*(matrix+ (3)-1) + 1) != 0)  ) { //if value is not 0
                return false;
            }
            if ( (*(*(matrix+ (3)-1) + 2) != 1)  ) { //if value is not 0
                return false;
            }
        }
    //print out answers
    cout << "Solutions:" << endl;
    cout << "x = " << (*(*(matrix+ (1)-1) + 3)) << endl;
    cout << "y = " << (*(*(matrix+ (2)-1) + 3)) << endl;
    cout << "z = " << (*(*(matrix+ (3)-1) + 3));
        return true;
    //end of code block
    }
    else if( rows == 2){ //if there are two rows
    //print out answers
        cout << "Solutions:" << endl;
        cout << "x = " << (*(*(matrix+ (1)-1) + 3)) << endl;
        cout << "y = " << (*(*(matrix+ (2)-1) + 3));
        return true;;
    //end of code block
    }
   
    
    return true;
}

int main() {
    string fileName; //stores the name of the file containing the equations
    const string fileExtension = ".txt"; //stores the file extension of a text file
    const int matrixColumns = 4; //the number of columns in the matrix
    float defaultValue = 0;
    char menuInput; //stores the input option for the menu
    int matrixRows = 0; //stores the number of rows in the matrix
    long totalCount = 0;
    
    
    cout << "Enter the file name containing your equations: ";
    getline(cin, fileName); //gets the user input for the name of file containing the equations
    if ( (fileName.at(fileName.size()-1) != 't') && (fileName.at(fileName.size()-2) != 'x') && (fileName.at(fileName.size()-3) != 't') && (fileName.at(fileName.size()-4) != '.')) { //if there is no file extension
        fileName.append(fileExtension); //adds the file extension to the fileName string
    }
    fstream matrixFile (fileName, ios::in); //opens the file the user defined
    
    if(matrixFile.fail()){ //fail can't open
        cout << "Error: Could not open file" << endl;
        cout << "Program terminated" << endl;
        return 0;
    }
   
    RowCount(matrixFile, matrixRows, totalCount); //calls the RowCount function to calculate the number of rows for the matrix
   
    //block of code will create a 2D-Array that will store the matrix with zeros
    float **matrix;
    matrix = new float*[matrixRows];
    for (int i = 0; i < matrixRows; i++) {
        for (int j = 0; j < matrixColumns; j++) {
            matrix[i] = new float[matrixColumns];
        }
    }
    for (int i = 0; i < matrixRows; i++) {
        for (int j = 0; j < matrixColumns; j++) {
            *(*(matrix + i) + j) = defaultValue;
        }
    }
    //end of block
    FIllMatrix(matrixFile, matrix, totalCount, matrixRows); //call the FillMatrix function to fillout the matrix
    PrintMatrix(matrixRows, matrixColumns, matrix); //call the PrintMatrix function to print the matrix
    matrixFile.close(); //close the matrix file
    
    if( (Echelon(matrixRows, matrixColumns, matrix)) == true){  //checks if the matrix is reduced to Echelon form
        menuInput = 4;
        return 0;
    }
    else{
        PrintMenuOptions(); //print the menu
        cin >> menuInput; //user enters the menu option for operation
    }
    while ((menuInput != '4') && (Echelon(matrixRows, matrixColumns, matrix)) == false) { //while the user has not quit the program
        switch (menuInput) {
            case '1': //user wants to swap rows
                SwapRows(matrixRows, matrixColumns, matrix); //calls the swap row function to swap rows
                PrintMatrix(matrixRows, matrixColumns, matrix); //call the PrintMatrix function to print the matrix
                if ((Echelon(matrixRows, matrixColumns, matrix)) == true) { //checks if the matrix is reduced to Echelon form
                    menuInput = 4; //end progrma
                    return 0;
                }
                break;
            case '2': //user wants to multiply the row
                NonZeroMulti(matrixRows, matrixColumns, matrix); //calls the NonZeroMulti function to multiply row
                PrintMatrix(matrixRows, matrixColumns, matrix); //call the PrintMatrix function to print the matrix
                if ((Echelon(matrixRows, matrixColumns, matrix)) == true) { //checks if the matrix is reduced to Echelon form
                    menuInput = 4; //end progrma
                    return 0;
                }
                break;
            case '3': //user wants to perform scalar multiplication
                ScalarMulti(matrixRows, matrixColumns, matrix); //calls the ScalarMulti function to perform row operations
                PrintMatrix(matrixRows, matrixColumns, matrix); //call the PrintMatrix function to print the matrix
                if ((Echelon(matrixRows, matrixColumns, matrix)) == true) { //checks if the matrix is reduced to Echelon form
                    menuInput = 4; //end progrma
                    return 0;
                }
                break;
            default:
                break;
        }
        PrintMenuOptions(); //print the menu
        cin >> menuInput; //user inputs the next option
    }
    
    //free memory
    for (int i = 0; i < matrixRows; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;
    
    return 0;
}
