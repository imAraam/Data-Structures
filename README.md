## Assignment Description

#### Implementing Pointer-based Data Structures
Implement a dictionary as a C++ class, using a singly linked list as the internal data
structure. The dictionary should support keys and items of type std::string.

"dictionary.h" provides my answer

#### Basket of Names: Search-based Implementation

The Art of Computer Programming (1, page 9) by Donald Knuth presents the Basket of Names problem.

Implement the search-based algorithm for that problem using a chosen combination of
containers

"task3a.cpp" provides my answer


# The Search Based Algorithm

### Performance consequence of these containers for the search based algorithm

#### std::list 

Implementing the search based algorithm using a list would be accomplished by first inserting all the names as pairs into a vector. Which would be fast and efficient as all the names would be read from the file into the vector, to then be inserted into a list of names. The algorithm would then choose a random name as the starting point, it would then copy that name to be the first element in a new ordered list of names. It would then place the 2nd element (name) of that pair, as the first name’s westerly neighbour on the ordered list of names. It would then sequentially have to traverse the list of names to find a pair where the 2nd element in the first pair is the 1st element in another pair. And then copy that 2nd element on the other pair as the following westerly neighbour in the ordered list of names. 

Considering the following letters as names, an example is as follows: 

m, b 

c, l 

b, x

Where ‘b’ would be the westerly neighbour of ‘m’, and the easterly neighbour of ‘x’. 

Using recursion, that can be repeated until the most westerly name has been added to the ordered list of names. Then it would return to the name that was randomly chosen at first by accessing the head of the ordered list of names, and then identify that name’s easterly neighbours in the list of names. That would be done by traversing the list and finding a pair with the 2nd element matching the name, in that same pair the 1st element would be the easterly neighbour of the name. This process can also be repeated using recursion until the ordered list of names has the names restored to the correct order. 

Time-complexity of the algorithm:

Insertion: O(1) due to insertions taking the same amount of time regardless of the size of the data. 

Sorting: O(n) due to the search having to traverse the list to sort the element. 

Search: O(n^2) due to the function having to traverse the unordered list to find the westerly/easterly neighbour of the element in the list of pairs, and then repeat the process until all elements are found. 

Time complexity of algorithm as a whole: O(n^2) as insertion of constant time complexity can be ignored. Search uses recursion in a loop therefore O(n^2) is the time complexity of the algorithm as the O(n) of sort can be ignored. 

Space usage implications 
std::list has a linear space complexity with respect to the number of elements it contains. 



#### std::map


