#include <iostream>
#include <fstream>
#include <stdexcept>
#include <type_traits>
#include <vector>

using namespace std;

//----------------------------------------------------------------------------------------------------
class Matrix
{
private:
	int num_rws;
	int num_clms;

	std::vector<std::vector<int>> elemnts;
public:
	Matrix() 
	{ 
		num_rws = 0; 
		num_clms = 0; 	
	}
	
	Matrix(int num_rows, int num_columns)
	{
		Reset(num_rows, num_columns);
	}
	
	void Reset(int num_rows, int num_columns)
	{
		if (num_rows < 0)
		{
			throw std::out_of_range("num_rows must be >= 0");
		}

		if (num_columns < 0)
		{
			throw std::out_of_range("num_columns must be >= 0");
		}

		if (num_rows == 0 || num_columns == 0)
		{
			num_rows = num_columns = 0;
		}

		num_rws = num_rows;
		num_clms = num_columns;
		elemnts.assign(num_rows, std::vector<int>(num_columns));
	}

	int & At(int num_rows, int num_columns)
	{
		return elemnts.at(num_rows).at(num_columns);
	}

	int At(int num_rows, int num_columns) const
	{
		return elemnts.at(num_rows).at(num_columns);
	}

	int GetNumRows() const
	{
		return num_rws;
	}

	int GetNumColumns() const
	{
		return num_clms;
	}
};
//----------------------------------------------------------------------------------------------------
bool operator == (const Matrix & one, const Matrix & two)
{
	if (one.GetNumRows() != two.GetNumRows())
	{
		return false;
	}

	if (one.GetNumColumns() != two.GetNumColumns())
	{
		return false;
	}

	for (size_t row = 0; row < one.GetNumRows(); ++row)
	{
		for (size_t col = 0; col < one.GetNumColumns(); ++col)
		{
			if (one.At(row, col) != two.At(row, col))
			{
				return false;
			}
		}
	}
	return true;
}
//----------------------------------------------------------------------------------------------------
Matrix operator + (const Matrix & one, const Matrix & two)
{
	if (one.GetNumRows() != two.GetNumRows())
	{
		throw std::invalid_argument("Mismatched number of rows");
	}

	if (one.GetNumColumns() != two.GetNumColumns())
	{
		throw std::invalid_argument("Mismatched number of columns");
	}

	Matrix temp(one.GetNumRows(), one.GetNumColumns());

	for (size_t row = 0; row < one.GetNumRows(); ++row)
	{
		for (size_t col = 0; col < one.GetNumColumns(); ++col)
		{
			temp.At(row, col) = one.At(row, col) + two.At(row, col);
		}
	}
	return temp;
}
//----------------------------------------------------------------------------------------------------
std::istream & operator >> (std::istream & in, Matrix & matrix)
{
	int num_rws = 0;
	int num_clms = 0;

	in >> num_rws >> num_clms;

	matrix.Reset(num_rws, num_clms);

	for (size_t row = 0; row < num_rws; ++row)
	{
		for (size_t col = 0; col < num_clms; ++col)
		{
			in >> matrix.At(row, col);
		}
	}
	return in;
}
//----------------------------------------------------------------------------------------------------
std::ostream & operator << (std::ostream & out, const Matrix & matrix)
{
	out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << std::endl;

	for (size_t row = 0; row < matrix.GetNumRows(); ++row)
	{
		for (size_t col = 0; col < matrix.GetNumColumns(); ++col)
		{
			if (col > 0)
			{
				out << " ";
			}
			out << matrix.At(row, col);
		}
		out << std::endl;
	}
	return out;
}
//----------------------------------------------------------------------------------------------------
int main()
{
	Matrix one;
	Matrix two;

	std::cin >> one >> two;
	std::cout << std::endl;
	std::cout << one + two << std::endl;

	return 0;
}
//----------------------------------------------------------------------------------------------------