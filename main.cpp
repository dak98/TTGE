#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "num_range.hpp"
#include "parallel_call.hpp"

using row = std::vector<float>;
using matrix = std::vector<row>;

struct find
{
    matrix& m;
    int i, j;
    float operator()() const
    {
	float c = 0.0f;
	if (m[j][i] != 0)
	    c = m[j][i] / m[i][i];
	m[j][i] = 0.0f;
	return c;
    }
};

struct multiply
{
    matrix& m;
    int i, k;
    float c;
    float operator()() const
    {
	if (i == k)
	    return 0.0f;
	return m[i][k] * c;
    }
};

struct substract
{
    matrix& m;
    int j, k;
    float e;
    void operator()()
    {
	m[j][k] -= e;
    }
};

void gaussian_elimination(matrix& m, const int size)
{
    for (int i : num_range{0, size - 1})
    {
	const int curr_size = size - i;
	
	std::vector<find> finds;
	for (int j : num_range{0, curr_size - 1})
	    finds.push_back(find{m, i, i + j + 1});

	std::vector<float> coeffs = parallel_call(std::begin(finds),
						  std::end(finds));

	const int muls_count = curr_size * curr_size - 1;
	std::vector<multiply> muls;
	for (int j : num_range{0, curr_size - 1})
	    for (int k : num_range{i, size + 1})
		muls.push_back(multiply{m, i, k, coeffs[j]});

	std::vector<float> es = parallel_call(std::begin(muls),
			                      std::end(muls));

	std::vector<substract> subs;
	for (int j : num_range{0, curr_size - 1})
	    for (int k : num_range{0, curr_size + 1})
	    {
		float e = es[j * (curr_size + 1) + k];
		subs.push_back(substract{m, i + j + 1, i + k, e});
	    }

	parallel_call_void(std::begin(subs), std::end(subs));
    }

    for (int i : num_range{0, size})
    {
	for (int j : num_range{i + 1, size + 1})
	    m[i][j] /= m[i][i];
	m[i][i] = 1.0f;	
    }

    for (int i = size - 2; i >= 0; --i)
	for (int j = i + 1; j < size; ++j)
	{
	    m[i][size] -= (m[i][j] * m[j][size]);
	    m[i][j] = 0.0f;
	}
}

int main()
{
    int size;
    std::cin >> size;

    matrix m(size);
    for (int i : num_range{0, size})
	for (int j : num_range{0, size})
	{
	    float f;
	    std::cin >> f;
	    m[i].push_back(f);
	}

    for (int i : num_range{0, size})
    {
        float f;
        std::cin >> f;
        m[i].push_back(f);	
    }

    gaussian_elimination(m, size);    

    std::cout << size << std::endl;
    for (int i : num_range{0, size})
    {
	for (int j : num_range{0, size})
	    std::cout << m[i][j] << " ";
	std::cout << std::endl;
    }
    for (int i : num_range{0, size})
	std::cout << m[i][size] << " ";
    std::cout << std::endl;    
}
