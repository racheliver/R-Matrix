#include <iostream>
#include "matrix.h"

using namespace std;

/*Program name and exercise number: Ex3*/

/*
Date: 15/12/2017
Author: Racheli Verechzon
Id:305710071
*/

/************A general explanation of what the program does***************************************
This is a class that represents a mathematical matrix. The matrix supports connecting, moving, and so on by using a number of basic services
**************************************************************************************************/

/****************Generate_Matrix*****************************************************************
This function creates a two-dimensional array in the stack memory, the function accepts values as rows and columns and returns a pointer to the matrix
*************************************************************************************************/
double ** Matrix::Generate_Matrix(int rows, int cols)
{
	if (rows > 0 && cols > 0)
	{
		double **temp = new double*[rows];
		for (int i = 0; i < rows; i++)
		{
			temp[i] = new double[cols];
		}
		return temp;
	}
	else {
		cout << "NA Exceeding the boundaries of the matrix and therefore the action was not carried out" << endl;
		exit(1);
	}
}
/*******************zero_Matrix************************************************
A function that aims to reset the matrix values that it received as input
*******************************************************************************/
void Matrix::zero_Matrix()
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			this->_array[i][j] = 0;
		}
	}
}
/***********************~Matrix************************************
Deals with the elimination and orderly release of the matrix memory
*******************************************************************/
Matrix::~Matrix()
{
	for (int i = 0; i < this->rows; i++)
	{
		delete[] this->_array[i];
	}
	delete[] this->_array;
}

/******************************isToepliz********************************
An auxiliary function for "isA" that checks whether the matrix is toplitz
************************************************************************/
bool Matrix::isToepliz()
{
	for (int i = 0; i < getNumRows() - 1; i++)
	{
		for (int j = 0; j < getNumCols() - 1; j++)
		{
			if (getElement(i, j) != getElement(i + 1, j + 1))
			{
				//	if ((getNumCols() != j - 1) && (getNumRows() != i - 1))
				{
					//	cout << "false";
					return false;
				}
			}
		}
	}
	//	cout << "true";
	return true;
}

/******************************colShift*********************************
Performs cyclic movement of the columns in the matrix
The function receives a shiftSize value from the receiver and we will then decide how much the matrix will move
************************************************************************/

void Matrix::colShift(const int shiftSize)
{

	int row = getNumRows(), col = getNumCols();
	if ((this->matType == "any" || (col == 2 && row == 2)))
	{
		double **temp = Generate_Matrix(row, col);
		int shiftSize_temp = shiftSize;
		while (shiftSize_temp < 0)
		{
			shiftSize_temp += col;
		}
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				double element = _array[i][j];
				temp[i][(j + shiftSize_temp) % (col)] = element;
			}
		}
		for (int i = 0; i < row; i++)
		{
			delete[] this->_array[i];
		}
		delete[] this->_array;
		this->_array = temp;
	}
	else
	{
		cout << "Operation not executed The program will continue as usual" << endl;
		return;
	}
}


/**************************rowShift*************************************
Performs cyclic movement of the rows in the matrix
The function receives a shiftSize value from the receiver and we will then decide how much the matrix will move
************************************************************************/
void Matrix::rowShift(const int shiftSize)
{

	int row = getNumRows(), col = getNumCols();
	if ((this->matType == "any" || (col == 2 && row == 2)))
	{
		int shiftSize_temp = shiftSize;
		double **temp = Generate_Matrix(row, col);
		while (shiftSize_temp < 0)
		{
			shiftSize_temp += row;
		}
		for (int i = 0; i < col; ++i)
		{
			for (int j = 0; j < row; ++j)
			{
				double element = _array[j][i];
				temp[(j + shiftSize_temp) % (row)][i] = element;
			}
		}
		for (int i = 0; i < row; i++)
		{
			delete[] this->_array[i];
		}
		delete[] this->_array;
		this->_array = temp;
	}
	else
	{
		cout << "Operation not executed The program will continue as usual";
		return;
	}
}

/*********************************setElement****************************
Gets index of row i and value j, index of column. The function inserts the assignment value data into the element (of the matrix i, j)
************************************************************************/

void Matrix::setElement(int i, int j, double data)
{
	if ((i < this->rows) && (j < this->cols))
	{
		double temp = getElement(i, j);
		if (this->getMatType() == "Arrowhead")
		{
			this->_array[i][j] = data;
			if (!isA("Arrowhead"))
			{
				this->_array[i][j] = 0;
				cout << "NA Exceeds the boundaries of the matType type and therefore the operation will not take place" << endl;
				return;
			}
		}
		else if (this->getMatType() == "Toeplitz")
		{
			if (i == 0 && j == (getNumCols() - 1) || j == 0 && i == (getNumRows() - 1))
			{
				this->_array[i][j] = data;
			}
			else {
				this->_array[i][j] = data;
				if (!isA("Toeplitz"))
				{
					this->_array[i][j] = temp;
					cout << "NA Exceeds the boundaries of the matType type and therefore the operation will not take place" << endl;
					return;
				}
			}
		}
		else
		{
			this->_array[i][j] = data;
		}
	}
	else
	{
		cout << "NA Exceeding the boundaries of the matrix_" << endl;
		return;
	}
}



/*****************************getElement********************************
Returns the value of the element  of matrix (i, j) in case the idanx exceeds the matrix size, we print "exit" and exit with NA for the screen
************************************************************************/
double Matrix::getElement(int i, int j)
{
	if ((i < this->rows) && (j < this->cols))
	{
		return (this->_array[i][j]);
	}
	else
	{
		cout << "NA Exceeding the boundaries of the matrix_" << endl;
		exit(1);
	}
}


/****************************add****************************************
The function accepts two references to matrices and makes a connection between the current and the other matrix and the result retains the result matrix
************************************************************************/
void Matrix::add(Matrix& other, Matrix& result)
{
	if ((this->rows != other.getNumRows()) || this->cols != other.getNumCols())
	{
		cout << "NA The size of the matrices other and this is different and therefore the action was not performed_1" << endl;
		return;
	}
	else if ((this->rows != result.getNumRows()) || this->cols != result.getNumCols())
	{
		cout << "NA The size of the matrices this and result is different and therefore the action was not performed_2" << endl;
		return;
	}
	else if ((other.getNumRows() != result.getNumRows()) || other.getNumCols() != result.getNumCols())
	{
		cout << "NA The size of the matrices other and result is different and therefore the action was not performed_3" << endl;
		return;
	}
	else if ((result.getMatType() == "Arrowhead"))
	{
		if ((other.getMatType() != "Arrowhead") || (this->getMatType() != "Arrowhead"))
		{
			cout << "NA The Type  of the matrices is different and therefore the action was not performed_Arrowhead" << endl;
			return;
		}
	}
	else if ((result.getMatType() == "Toeplitz"))
	{
		if ((other.getMatType() != "Toeplitz") || (this->getMatType() != "Toeplitz"))
		{
			cout << "NA The Type  of the matrices is different and therefore the action was not performed_Topepltz" << endl;
			return;
		}
	}
	else if ((result.getMatType() == "any"))
	{
		if ((other.getMatType() != "any") || (this->getMatType() != "any"))
		{
			cout << "NA The Type  of the matrices is different and therefore the action was not performed_any" << endl;
			return;
		}
	}
	double calculate = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			calculate = other.getElement(i, j) + (this->_array[i][j]);
			result._array[i][j] = calculate;

		}
	}
}



/********************************print***********************************
Prints the matrix in the following format: The matrix will be printed  Line by line - Each line in the matrix will start with a new row on the screen. When between the two members of the same line the character will appear only and without any space.

************************************************************************/
void Matrix::print()
{
	cout << endl;
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			cout << this->_array[i][j];
			if (j < this->cols - 1)
				cout << ",";
		}
		cout << endl;
	}
}

/****************************getters********************************************
************************************************************************/
int Matrix::getNumRows()
{
	return this->rows;
}
string Matrix::getMatType()
{
	return this->matType;
}

int Matrix::getNumCols()
{
	return this->cols;
}

/*******************************isA*************************************
matType of Matrix Can be one of the three values mentioned. If the matrix  true in the constructor
 This means that the function satisfies the conditions of the type on which it is registered
 ************************************************************************/
bool Matrix::isA(string matType)
{
	if (matType == "Arrowhead")
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				if ((j == 0 || i == 0) || (i == j))
				{
					//cout << "(" << i << "," << j << ")" << endl;

				}
				else
				{
					if (this->getElement(i, j) != 0)
					{
						// << "false" << endl;
						return false;
					}
				}
			}
		}
		//	cout << "true" << endl;
		return true;
	}
	else if (matType == "any")
	{
		//cout << "true" << endl;
		return true;
	}
	else if (matType == "Toeplitz")
	{
		return isToepliz();
	}
	else
	{
		//cout << "false__" << endl;
		return false;
	}
}
