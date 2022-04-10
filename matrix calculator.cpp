#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;


string& leftTrim(string& str, string& chars)
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

string& rightTrim(string& str, string& chars)
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

string& trimString(string& str, string& chars)
{
    return leftTrim(rightTrim(str, chars), chars);
}

int splitString(string s, string delimiter, string splittedStrings[101]) {
    size_t pos = 0;
    string token;
    int numOfOccurrence = 0;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);

        splittedStrings[numOfOccurrence] = token;
        s.erase(0, pos + delimiter.length());
        numOfOccurrence++;
    }
    splittedStrings[numOfOccurrence] = s;
    return numOfOccurrence;
}
int convertStringToMatrix(string s, int& row, int& col, float arr[101][101]) {
    if (s[0] != '[' || s[s.length() - 1] != ']')
        return 1;

    s = s.substr(1, (s.length() - 2));
    string splittedStrings[101];
    string trimmedChar = " ";

    int numOfOccurencesOfComma = splitString(s, ",", splittedStrings);
    row = numOfOccurencesOfComma;
    int unifiedNumOfCols = 0;
    for (int i = 0;i <= numOfOccurencesOfComma;i++) {
        string splittedStringsBySpace[101];
        //int rowLength = splittedStrings[i].length();
        if (i != 0) {
            //cout << "splittedStrings[i][rowLength - 1] " << splittedStrings[i][0] << endl;
            if (splittedStrings[i][0] != ' ') {
                return 1;
            }
        }
        
        trimString(splittedStrings[i], trimmedChar);
        int numOfOccurrenceOfSpace = splitString(splittedStrings[i], " ", splittedStringsBySpace);
        if (i == 0) {
            unifiedNumOfCols = numOfOccurrenceOfSpace;
        }
        else {
            if (unifiedNumOfCols != numOfOccurrenceOfSpace)
                return 1;
        }

        col = numOfOccurrenceOfSpace;
        for (int j = 0;j <= numOfOccurrenceOfSpace;j++) {
            if ((splittedStringsBySpace[j]).find_first_not_of("0123456789-.") != std::string::npos) {
                return 1;
            }


            arr[i][j] = stof(splittedStringsBySpace[j]);
            if (arr[i][j] < -10000 || arr[i][j] > 10000 || i >= 100 || j >= 100)
            {
                return 1;
            }


        }
    }
    return 0;

}

void printMatrix(float matrix[101][101], int row, int col) {
    //setprecision(2);
    cout << "[";
    for (int rowIndex = 0;rowIndex <= row;rowIndex++) {
        for (int colIndex = 0;colIndex <= col;colIndex++) {
            //cout << matrix[rowIndex][colIndex];
            //cout << (matrix[rowIndex][colIndex] * 100) / 100;

            float temp = ceil(matrix[rowIndex][colIndex] * 100) / 100;
            //cout << "temp" << temp << "     matrix[rowIndex][colIndex]"<< matrix[rowIndex][colIndex] <<"          ";
            if (temp - matrix[rowIndex][colIndex] == 0) {

                cout << setprecision(3) << matrix[rowIndex][colIndex];
            }
            else {
                //cout <<fixed<< setprecision(2) << matrix[rowIndex][colIndex];
                printf("%.2f", matrix[rowIndex][colIndex]);

            }
            //printf("%.2f", matrix[rowIndex][colIndex]);

            //cout << setprecision(3) << matrix[rowIndex][colIndex];
            if (colIndex < col)
                cout << " ";
        }

        //cout << matrix[rowIndex][colIndex] << " ";
        if (rowIndex < row)
            cout << ", ";
        //cout << endl;
    }
    cout << "]" << endl;
}


void calculateSubmatrix(float originalMatrix[101][101], float subMatrix[101][101], int row, int x, int y) {
    int subMatRowIndex = 0, subMatColIndex = 0;
    //cout << "row " << row << endl;
    for (int orginalMatRowIndex = 0; orginalMatRowIndex < row; orginalMatRowIndex++) {
        for (int orginalMatColIndex = 0; orginalMatColIndex < row; orginalMatColIndex++) {

            if (orginalMatRowIndex != x && orginalMatColIndex != y) {
                //cout << "sub x= " << x << ",y=" << y << endl;
                subMatrix[subMatRowIndex][subMatColIndex] = originalMatrix[orginalMatRowIndex][orginalMatColIndex];
                subMatColIndex++;

                if (subMatColIndex == row - 1) {
                    subMatColIndex = 0;
                    subMatRowIndex++;
                }
            }
        }
    }
}
float calculateMatrixDeterminant(int row, int col, int starting_x, int starting_y, float arr[101][101]) {
    //cout << "calc row=" << row << " ,col= " << col << endl;
    float determinantValue = 0.0;
    if (row == 1 && col == 1) {
        determinantValue = arr[0][0];
    }
    else if (row == 2 && col == 2) {
        determinantValue = arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
    }
    else {
        for (int i = 0;i < row;i++) {
            //0 2 4 +
            //1 3 5 -
            float subMatrix[101][101];
            calculateSubmatrix(arr, subMatrix, row, 0, i);
            if (i % 2 == 0) {
                determinantValue = determinantValue + arr[0][i] * calculateMatrixDeterminant(row - 1, col - 1, 0, 0, subMatrix);
            }
            else {
                determinantValue = determinantValue - arr[0][i] * calculateMatrixDeterminant(row - 1, col - 1, 0, 0, subMatrix);
            }

        }

    }
    //cout << "determinantValue : " << determinantValue << endl;
    return determinantValue;

}

int main()
{

    string firstInput, secondInput;
    getline(cin, firstInput);
    char op;
    cin >> op;
    float outputMatrix[101][101];
    /*if (op == '+' || op == '-' || op == '*') {
        cin.ignore();
        getline(cin, secondInput);
        bool isTwoMatrixOp = true;


        float inputMatrix[101][101], scaler;
        int inputMatrixRow = 0, inputMatrixCol = 0;

        if (firstInput[0] != '[' && firstInput[firstInput.length() - 1] != ']' && op == '*')
        {

            isTwoMatrixOp = false;
            scaler = stof(firstInput);
            int inputMatrixUnifiedCol = convertStringToMatrix(secondInput, inputMatrixRow, inputMatrixCol, inputMatrix);
            if (inputMatrixUnifiedCol == 1) {
                cout << "ERROR!" << endl;
                return 0;
            }

        }
        else if (secondInput[0] != '[' && secondInput[secondInput.length() - 1] != ']' && op == '*')
        {
            isTwoMatrixOp = false;
            scaler = stof(secondInput);
            int inputMatrixUnifiedCol = convertStringToMatrix(firstInput, inputMatrixRow, inputMatrixCol, inputMatrix);
            if (inputMatrixUnifiedCol == 1) {
                cout << "ERROR!" << endl;
                return 0;
            }

        }
        else {
            float firstInputMatrix[101][101], secondInputMatrix[101][101];
            int firstInputMatrixRow = 0, firstInputMatrixCol = 0, secondInputMatrixRow = 0, secondInputMatrixCol = 0;
            int firstMatrixUnifiedCols = convertStringToMatrix(firstInput, firstInputMatrixRow, firstInputMatrixCol, firstInputMatrix);
            int secondMatrixUnifiedCols = convertStringToMatrix(secondInput, secondInputMatrixRow, secondInputMatrixCol, secondInputMatrix);
            if (firstMatrixUnifiedCols == 1 || secondMatrixUnifiedCols == 1) {
                cout << "ERROR!" << endl;
                return 0;
            }
            if (op == '+') {
                if (firstInputMatrixRow != secondInputMatrixRow || firstInputMatrixCol != secondInputMatrixCol) {
                    cout << "ERROR!" << endl;
                    return 0;
                }
                for (int i = 0;i <= firstInputMatrixRow;i++)
                {
                    for (int j = 0;j <= firstInputMatrixCol;j++)
                    {
                        outputMatrix[i][j] = firstInputMatrix[i][j] + secondInputMatrix[i][j];
                    }
                }

            }
            else if (op == '-') {
                if (firstInputMatrixRow != secondInputMatrixRow || firstInputMatrixCol != secondInputMatrixCol) {
                    cout << "ERROR!" << endl;
                    return 0;
                }
                for (int i = 0;i <= firstInputMatrixRow;i++)
                {
                    for (int j = 0;j <= firstInputMatrixCol;j++)
                    {
                        outputMatrix[i][j] = firstInputMatrix[i][j] - secondInputMatrix[i][j];
                    }
                }

            }
            else if (op == '*') {
                if (firstInputMatrixCol != secondInputMatrixRow) {
                    cout << "ERROR!" << endl;
                    return 0;
                }

                int outputElement = 0;
                for (int i = 0;i <= firstInputMatrixRow;i++)
                {
                    for (int j = 0;j <= secondInputMatrixCol;j++)
                    {
                        outputElement = 0;
                        for (int ir = 0;ir < firstInputMatrixCol;ir++) {
                            outputElement = outputElement + firstInputMatrix[i][ir] * secondInputMatrix[ir][j];
                        }
                        outputMatrix[i][j] = outputElement;

                    }
                }
            }
            else {
                cout << "ERROR!" << endl;
            }

            /*printMatrix(firstInputMatrix, firstInputMatrixRow, firstInputMatrixCol);
            cout << endl << endl;
            printMatrix(secondInputMatrix, secondInputMatrixRow, secondInputMatrixCol);
            cout << endl << endl;*/
            /*printMatrix(outputMatrix, firstInputMatrixRow, secondInputMatrixCol);


        }

        if (!isTwoMatrixOp) {
            for (int i = 0;i <= inputMatrixRow;i++)
            {
                for (int j = 0;j <= inputMatrixCol;j++)
                {
                    outputMatrix[i][j] = inputMatrix[i][j] * scaler;
                    if (outputMatrix[i][j] > 10000 || outputMatrix[i][j] < -10000)
                    {
                        cout << "ERROR!" << endl;
                        return 0;
                    }
                }
            }
            printMatrix(outputMatrix, inputMatrixRow, inputMatrixCol);
        }
    }
    else*/ if (op == 'T' || op == 'I' || op == 'D')
    {
        float firstInputMatrix[101][101];
        int firstInputMatrixRow = 0, firstInputMatrixCol = 0;
        int firstMatrixUnifiedCols = convertStringToMatrix(firstInput, firstInputMatrixRow, firstInputMatrixCol, firstInputMatrix);
        if (firstMatrixUnifiedCols == 1) {
            cout << "ERROR!" << endl;
            return 0;
        }
        if (op == 'T')
        {

            for (int i = 0;i <= firstInputMatrixCol;i++)
            {
                for (int j = 0;j <= firstInputMatrixRow;j++)
                {
                    outputMatrix[i][j] = firstInputMatrix[j][i];
                }

            }
            printMatrix(outputMatrix, firstInputMatrixCol, firstInputMatrixRow);

        }
        else if (op == 'I')
        {
            if (firstInputMatrixCol != firstInputMatrixRow) {
                cout << "ERROR!" << endl;
                return 0;
            }
            float determinant = calculateMatrixDeterminant(firstInputMatrixRow + 1, firstInputMatrixCol + 1, 0, 0, firstInputMatrix);
            //cout << "FULL MAT DET = " << determinant << endl;
            if (determinant == 0.0) {
                cout << "ERROR!" << endl;
                return 0;
            }
            float cofactorsMatrix[101][101];
            for (int i = 0;i <= firstInputMatrixRow;i++)
            {
                for (int j = 0;j <= firstInputMatrixCol;j++)
                {
                    //if (i != 0||j != 0)
                    //    break;
                    //cofactorsMatrix[i][j] = ((-1)^(i+j))*(calculateMatrixDeterminant(firstInputMatrixRow,firstInputMatrixCol,0,0,cofactorsMatrix)/determinant);
                    float subMatrix[101][101];
                    calculateSubmatrix(firstInputMatrix, subMatrix, firstInputMatrixRow + 1, i, j);
                    //cout << "i : " << i << "j : " << j<<endl;
                    //printMatrix(subMatrix, firstInputMatrixCol-1, firstInputMatrixRow-1);

                    float subDet = (pow((-1), (i + j)) * calculateMatrixDeterminant(firstInputMatrixRow, firstInputMatrixCol, 0, 0, subMatrix) / determinant);
                    //cout << "subDet : " << subDet << endl;
                    cofactorsMatrix[i][j] = subDet;
                    //cout << "-------------" << endl;
                }
                //if (i != 0)
                //    break;

            }
            for (int i = 0;i <= firstInputMatrixCol;i++)
            {
                for (int j = 0;j <= firstInputMatrixRow;j++)
                {
                    outputMatrix[i][j] = cofactorsMatrix[j][i];
                }

            }

            printMatrix(outputMatrix, firstInputMatrixCol, firstInputMatrixRow);

        }
        else if (op == 'D')
        {
            if (firstInputMatrixCol != firstInputMatrixRow) {
                cout << "ERROR!" << endl;
                return 0;
            }
            //printMatrix(firstInputMatrix, firstInputMatrixCol, firstInputMatrixRow);
            //cout << firstInputMatrixCol << firstInputMatrixRow << endl;
            float det = calculateMatrixDeterminant(firstInputMatrixRow + 1, firstInputMatrixCol + 1, 0, 0, firstInputMatrix);
            cout << det << endl;
            /*float temp = ceil(det * 1000) / 1000;
            //cout << "temp" << temp << "     matrix[rowIndex][colIndex]"<< matrix[rowIndex][colIndex] <<"          ";
            cout << temp << endl;
            if (temp ==det ) {

                cout <<"jj"<< setprecision(2) << det;
            }
            else {
                //cout <<fixed<< setprecision(2) << matrix[rowIndex][colIndex];
                printf("%.2f", det);

            }*/
        }
        else {
            cout << "ERROR!" << endl;
            return 0;
        }

    }

    return 0;
}