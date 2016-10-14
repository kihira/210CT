#include <iostream>
#include <vector>
#include <stdio.h> // printf
#include <stdexcept>
#include <tuple>

using namespace std;

class Matrix
{
public:
    const int mRows;
    const int mColumns;
    vector<int> mMatrix;
    int index(int row, int col)
    {
        return row * this->mColumns + col;
    }
    void print()
    {
        for (int row = 0; row < this->mRows; row++)
        {
            for (int col = 0; col < this->mColumns; col++)
            {
                printf("%.3i   ", mMatrix[index(row, col)]); // Use printf for formatting (force 3 digits)
            }
            cout << endl;
        }
    }
    int* operator[](int row)
    {
        return &mMatrix[mColumns * row]; // return pointer to int array from this position
    }
    Matrix operator+(const Matrix& rhs)
    {
        if (this->mMatrix.size() != rhs.mMatrix.size())
        {
            throw range_error("Matrices are different sizes");
        }
        Matrix output(rhs.mRows, rhs.mColumns);
        for (int row = 0; row < output.mRows; row++)
        {
            for (int col = 0; col < output.mColumns; col++)
            {
                output.mMatrix[index(row, col)] = this->mMatrix[index(row, col)] + rhs.mMatrix[index(row, col)];
            }
        }
        return output;
    }
    Matrix operator-(const Matrix& rhs)
    {
        if (this->mMatrix.size() != rhs.mMatrix.size())
        {
            throw range_error("Matrices are different sizes");
        }
        Matrix output(rhs.mRows, rhs.mColumns);
        for (int row = 0; row < output.mRows; row++)
        {
            for (int col = 0; col < output.mColumns; col++)
            {
                output.mMatrix[index(row, col)] = this->mMatrix[index(row, col)] - rhs.mMatrix[index(row, col)];
            }
        }
        return output;
    }
    Matrix operator*(const Matrix& rhs)
    {
        if (this->mColumns != rhs.mRows)
        {
            throw range_error("Column count on first matrix does not match row count on second matrix");
        }
        Matrix output(this->mRows, rhs.mColumns);

        for (int row = 0; row < rhs.mRows; row++)
        {
            for (int colRHS = 0; colRHS < rhs.mColumns; colRHS++)
            {
                for (int col = 0; col < this->mColumns; col++)
                {
                     output.mMatrix[index(row, colRHS)] += this->mMatrix[index(row, col)] * rhs.mMatrix[index(col, colRHS)];
                }
            }
        }

        return output;
    }
    Matrix(const int rows, const int columns): mRows(rows), mColumns(columns), mMatrix(rows * columns, 0) {}
};

typedef tuple<int, int, int> COO;

class SparseMatrix
{
private:
    vector<int> values;
    vector<int> row_indexes;
    vector<int> col_indexes;
    int rows;
    int cols;
public:
    SparseMatrix(vector<int> values, vector<int> row_indexes, vector<int> col_indexes, int rows, int cols) : values(values), row_indexes(row_indexes), col_indexes(col_indexes), rows(rows), cols(cols) {}
    int get(int row, int col)
    {
        for (int index = 0; index < row_indexes.size(); index++)
        {
            if (row_indexes[index] == row && col_indexes[index] == col)
            {
                return values[index];
            }
        }
    }
};

int main()
{
    cout << "Advanced Task 1" << endl;
    int eggPerDay = 3;
    int eggHatchDays = 5;
    int days = 30;
    vector<int> eggsHatching(days + 100, 0); // A vector of what how many is hatching on what day. First day is day 0
    int alienCount = 1;

    for (int day = 0; day < days; day++)
    {
        alienCount += eggsHatching[day]; // Hatch eggs first
        eggsHatching[day + eggHatchDays - 1] = alienCount * eggPerDay; // -1 as we count the current day as a 1 day
    }

    cout << "Aliens count after " << days << " days: " << alienCount << endl << endl;

    cout << "Advanced Task 2" << endl;

    vector<int> values;
    vector<int> row_indexes;
    vector<int> col_indexes;
    SparseMatrix m(values, row_indexes, col_indexes, 3, 3);

    cout << m.get(1, 1);

        /*
    Matrix matrix(3, 3);
    int i = 0;
    for (int row = 0; row < matrix.mRows; row++)
    {
        for (int col = 0; col < matrix.mColumns; col++)
        {
            matrix[row][col] = i++;
        }
    }
    Matrix matrix2(3, 3);
    i = 0;
    for (int row = 0; row < matrix2.mRows; row++)
    {
        for (int col = 0; col < matrix2.mColumns; col++)
        {
            matrix2[matrix2.mRows-1-row][matrix2.mColumns-1-col] = i++;
        }
    }

    cout << "First Matrix: " << endl;
    matrix.print();
    cout << "Second Matrix: " << endl;
    matrix2.print();
    cout << "Addition: " << endl;
    Matrix out = matrix + matrix2;
    out.print();
    cout << "Subtraction: " << endl;
    Matrix out2 = matrix - matrix2;
    out2.print();
    cout << "Multiplication: " << endl;
    Matrix out3 = matrix * matrix2;
    out3.print();
    */

    return 0;
}
