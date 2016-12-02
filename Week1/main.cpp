#include <iostream>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class SparseMatrix
{
public:
    const int rows;
    const int cols;
    vector<int> values;
    vector<int> row_indexes;
    vector<int> col_indexes;
    // O(n*2)
    SparseMatrix operator+(SparseMatrix& rhs)
    {
        if (rows != rhs.rows || cols != rhs.cols)
        {
            throw range_error("Matrices are different sizes");
        }
        for (int i = 0; i < rows * cols; i++)
        {
            int row = i / rows + 1;
            int col = i % cols + 1;
            int val = get(row, col) + rhs.get(row, col);
            if (val != 0)
            {
                values.push_back(val);
                row_indexes.push_back(row);
                col_indexes.push_back(col);
            }
        }
        return SparseMatrix(rows, cols, values, row_indexes, col_indexes);
    }
    // O(n*2)
    SparseMatrix operator-(SparseMatrix& rhs)
    {
        if (rows != rhs.rows || cols != rhs.cols)
        {
            throw range_error("Matrices are different sizes");
        }
        vector<int> values;
        vector<int> row_indexes;
        vector<int> col_indexes;
        for (int i = 0; i < rows * cols; i++)
        {
            int row = i / rows + 1;
            int col = i % cols + 1;
            int val = get(row, col) - rhs.get(row, col);
            if (val != 0)
            {
                values.push_back(val);
                row_indexes.push_back(row);
                col_indexes.push_back(col);
            }
        }
        return SparseMatrix(rows, cols, values, row_indexes, col_indexes);
    }
    SparseMatrix operator*(SparseMatrix& rhs)
    {
        if (cols != rhs.rows)
        {
            throw range_error("Column count on first matrix does not match row count on second matrix");
        }
        vector<int> values;
        vector<int> row_indexes;
        vector<int> col_indexes;
        for (int row = 1; row <= rhs.rows; row++)
        {
            for (int colRHS = 1; colRHS <= rhs.cols; colRHS++)
            {
                int total = 0;
                for (int col = 1; col <= cols; col++)
                {
                    total += get(row, col) * rhs.get(col, colRHS);
                }
                if (total != 0)
                {
                    values.push_back(total);
                    row_indexes.push_back(row);
                    col_indexes.push_back(colRHS);
                }
            }
        }
        return SparseMatrix(rhs.rows, cols, values, row_indexes, col_indexes);
    }
    int get(int row, int col)
    {
        if (row > rows || col > cols)
        {
            throw range_error("Index outside of matrix range");
        }
        for (int index = 0; index < row_indexes.size(); index++)
        {
            if (row_indexes[index] == row && col_indexes[index] == col)
            {
                return values[index];
            }
        }
        return 0;
    }
    void print_string()
    {
        stringstream ss;
        for (int row = 1; row <= rows; row++)
        {
            for (int col = 1; col <= cols; col++)
            {
                printf("%-5i", get(row, col)); // Use printf for formatting (pad to 5, left align, integers)
            }
            cout << endl;
        }
    }
    SparseMatrix(const int rows, const int cols, vector<int> values, vector<int> row_indexes, vector<int> col_indexes) : rows(rows), cols(cols), values(values), row_indexes(row_indexes), col_indexes(col_indexes) {}
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
        eggsHatching[day + eggHatchDays] = alienCount * eggPerDay;
    }

    cout << "Aliens count after " << days << " days: " << alienCount << endl << endl;

    cout << "Advanced Task 2" << endl;

    vector<int> values;
    vector<int> row_indexes;
    vector<int> col_indexes;
    for (int row = 1; row <= 3; row++)
    {
        for (int col = 1; col <= 3; col++)
        {
            values.push_back(rand() % 10);
            row_indexes.push_back(row);
            col_indexes.push_back(col);
        }
    }
    SparseMatrix m(3, 3, values, row_indexes, col_indexes);

    values.clear();
    row_indexes.clear();
    col_indexes.clear();
    for (int row = 1; row <= 3; row++)
    {
        for (int col = 1; col <= 3; col++)
        {
            values.push_back(rand() % 10);
            row_indexes.push_back(row);
            col_indexes.push_back(col);
        }
    }
    SparseMatrix m2(3, 3, values, row_indexes, col_indexes);

    cout << "Matrix 1" << endl;
    m.print_string();
    cout <<  "Matrix 2" << endl;
    m2.print_string();
    cout << "Addition" << endl;
    (m + m2).print_string();
    cout << "Subtraction" << endl;
    (m - m2).print_string();
    cout << "Multiplication" << endl;
    (m * m2).print_string();
    return 0;
}
