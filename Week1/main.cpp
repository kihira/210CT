#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Matrix
{
public:
    const int rows;
    const int cols;
    string to_string()
    {
        stringstream ss;
        for (int row = 1; row <= rows; row++)
        {
            for (int col = 1; col <= cols; col++)
            {
                printf("%i\t", get(row, col)); // Use printf for formatting (force 3 digits)
            }
            cout << endl;
        }
        return ss.str();
    }
    virtual int get(int row, int col) = 0;
    Matrix(const int rows, const int cols) : rows(rows), cols(cols) {}
};

class DenseMatrix : public Matrix
{
public:
    vector<int> mMatrix;
    int index(int row, int col)
    {
        return row * cols + col;
    }
    int* operator[](int row)
    {
        return &mMatrix[cols * row]; // return pointer to int array from this position
    }
    int get(int row, int col)
    {
        return mMatrix[index(row, col)];
    }
    DenseMatrix operator+(const DenseMatrix& rhs)
    {
        if (mMatrix.size() != rhs.mMatrix.size())
        {
            throw range_error("Matrices are different sizes");
        }
        DenseMatrix output(rhs.rows, rhs.cols);
        for (int row = 0; row < output.rows; row++)
        {
            for (int col = 0; col < output.cols; col++)
            {
                output.mMatrix[index(row, col)] = mMatrix[index(row, col)] + rhs.mMatrix[index(row, col)];
            }
        }
        return output;
    }
    DenseMatrix operator-(const DenseMatrix& rhs)
    {
        if (mMatrix.size() != rhs.mMatrix.size())
        {
            throw range_error("Matrices are different sizes");
        }
        DenseMatrix output(rhs.rows, rhs.cols);
        for (int row = 0; row < output.rows; row++)
        {
            for (int col = 0; col < output.cols; col++)
            {
                output.mMatrix[index(row, col)] = mMatrix[index(row, col)] - rhs.mMatrix[index(row, col)];
            }
        }
        return output;
    }
    DenseMatrix operator*(const DenseMatrix& rhs)
    {
        if (cols != rhs.rows)
        {
            throw range_error("Column count on first matrix does not match row count on second matrix");
        }
        DenseMatrix output(rows, cols);

        for (int row = 0; row < rhs.rows; row++)
        {
            for (int colRHS = 0; colRHS < rhs.cols; colRHS++)
            {
                for (int col = 0; col < cols; col++)
                {
                     output.mMatrix[index(row, colRHS)] += mMatrix[index(row, col)] * rhs.mMatrix[index(col, colRHS)];
                }
            }
        }

        return output;
    }
    DenseMatrix(const int rows, const int cols) : Matrix(rows, cols), mMatrix(rows * cols, 0) {}
};

class SparseMatrix : public Matrix
{
public:
    vector<int> values;
    vector<int> row_indexes;
    vector<int> col_indexes;
    SparseMatrix operator+(SparseMatrix& rhs)
    {
        if (rows != rhs.rows || cols != rhs.cols)
        {
            throw range_error("Matrices are different sizes");
        }
        vector<int> values;
        vector<int> row_indexes;
        vector<int> col_indexes;
        for (int row = 1; row <= rows; row++)
        {
            for (int col = 1; col <= cols; col++)
            {
                int val = get(row, col) + rhs.get(row, col);
                if (val != 0)
                {
                    values.push_back(val);
                    row_indexes.push_back(row);
                    col_indexes.push_back(col);
                }
            }
        }
        SparseMatrix m(rows, cols, values, row_indexes, col_indexes);
        return m;
    }
    SparseMatrix operator-(SparseMatrix& rhs)
    {
        if (rows != rhs.rows || cols != rhs.cols)
        {
            throw range_error("Matrices are different sizes");
        }
        vector<int> values;
        vector<int> row_indexes;
        vector<int> col_indexes;
        for (int row = 1; row <= rows; row++)
        {
            for (int col = 1; col <= cols; col++)
            {
                int val = get(row, col) - rhs.get(row, col);
                if (val != 0)
                {
                    values.push_back(val);
                    row_indexes.push_back(row);
                    col_indexes.push_back(col);
                }
            }
        }
        SparseMatrix m(rows, cols, values, row_indexes, col_indexes);
        return m;
    }
//    SparseMatrix operator*(SparseMatrix& rhs)
//    {
//        if (rows != rhs.rows || cols != rhs.cols)
//        {
//            throw range_error("Matrices are different sizes");
//        }
//        vector<int> values;
//        vector<int> row_indexes;
//        vector<int> col_indexes;
//        for (int row = 1; row <= rhs.rows; row++)
//        {
//            for (int colRHS = 1; colRHS <= rhs.cols; colRHS++)
//            {
//                int total = 0;
//                for (int col = 1; col <= cols; col++)
//                {
//                    total += get(row, col) * get(col, colRHS);
//                }
//                if (total != 0)
//                {
//                    values.push_back(total);
//                    row_indexes.push_back(row);
//                    col_indexes.push_back(colRHS);
//                }
//            }
//        }
//        SparseMatrix m(rows, cols, values, row_indexes, col_indexes);
//        return m;
//    }
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
    SparseMatrix(const int rows, const int cols, vector<int> values, vector<int> row_indexes, vector<int> col_indexes) : Matrix(rows, cols), values(values), row_indexes(row_indexes), col_indexes(col_indexes) {}
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

    cout << "Matrix 1" << endl << m.to_string() << endl;
    cout << "Matrix 2" << endl << m2.to_string() << endl;
    cout << "Addition" << endl << (m + m2).to_string() << endl;
    cout << "Subtraction" << endl << (m - m2).to_string() << endl;
    cout << "Multiplication" << endl << (m * m2).to_string() << endl;
    return 0;
}
