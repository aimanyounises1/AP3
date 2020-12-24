#ifndef __ALG_H__
#define __ALG_H__

#include <iterator>
#include <math.h>

// A utility function that returns true if x is perfect square 
static inline bool isPerfectSquare(size_t x) 
{ 
    size_t s = sqrt(x); 
    return (s*s == x);
} 
  
// Returns true if n is a Fibonacci Number, else false 
static inline bool isFibonacci(size_t n) 
{ 
    // n is Fibonacci if one of 5*n*n + 4 or 5*n*n - 4 or both 
    // is a perfect square 
    return isPerfectSquare(5*n*n + 4) || isPerfectSquare(5*n*n - 4);
}


template<typename T>
static size_t countElements(T b, T e) {
	size_t counter = 0lu;
	T itr = b;
	
	while (itr != e) {
		++counter;
		++itr;
	}
	
	return counter;
}


static bool areConsecutive(size_t first, size_t second) {
	if (!isFibonacci(first) || !isFibonacci(second)) return false;
	
	if (first >= second) return false;
	
	size_t itr = ++first;
	while (itr < second) {
		if (isFibonacci(itr)) return false;
		++itr;
	}
	
	return true;
}


/**
Modes of operation depending on container size:
Size == 1:	Check if the first element is a Fibonacci number.
Size == 2:	Check if the first and second elements are consecutive Fibonacci numbers,
			meaning, every number between the first and the second elements is NOT a Fibonacci number.
Size >= 3:	Check if the first number is a Fibonacci number, and the rest of the container satisfies the Fibonacci rule:
			e_(n-1) + e_n = e_(n+1) ; the expression following the underscore denotes the subscript of the element in the sequence.
*/
template<typename T>
bool Fib(T b, T e) {
	size_t num_elements = countElements(b, e);
		
	if (0 == num_elements) return true;
	
	if (1 == num_elements) return isFibonacci(*b);
	
	bool is_sub_series = true;
	if (num_elements > 1) {
		size_t first = *b;
		size_t second = *(std::next(b));
		
		is_sub_series = areConsecutive(first, second);
		
		if (false == is_sub_series) {
			return false;
		}
	}
	
	if (num_elements <= 2) {
		return is_sub_series;
	}
	
	// At this point we know that the first two elements
	// are a sub-sequence of the Fibonacci sequence;
	
	// Check the rest of the sequence
	T first_itr = b;
	T second_itr = std::next(first_itr);
	T third_itr = std::next(second_itr);

	while (third_itr != e) {
		size_t first = *first_itr;
		size_t second = *second_itr;
		size_t third = *third_itr;
		if ((first + second) != third) {
			return false;
		}
		
		first_itr = second_itr;
		second_itr = third_itr;
		third_itr = std::next(third_itr);
	}
	
	return true;
}


template<typename T>
static void mySwap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}


template<typename T>
T Transpose(T b, T e) {
	size_t num_elements = countElements(b, e);
	
	if (0 == num_elements || 1 == (num_elements % 2)) return b;
	
	T curr = b;
	T next = std::next(b);
	while (curr != e && next != e) {
		mySwap(*curr, *next);
		 	
		curr = std::next(next);
		next = std::next(next, 2);
	}
	
	return e;
}



template<typename SRC_ITR, typename DST_ITR, typename FUNC>
DST_ITR Transform2(SRC_ITR b, SRC_ITR e, DST_ITR b2, FUNC f) {	
	SRC_ITR curr = b;
	SRC_ITR next = std::next(b);
	DST_ITR dst = b2;
	
	while (curr != e && next != e) {
		*dst = f(*curr, *next);
		
		curr = std::next(next);
		next = std::next(next, 2);
		dst = std::next(dst);
	}
	
	return dst;
}

#endif // __ALG_H__
