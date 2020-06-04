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

## Performance consequence of these containers for the search based algorithm

### std::list 

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



### std::map

Implementing the search-based algorithm using a map would mean inserting all the names into a list of string pairs, where the two names on each piece of paper represent one string pair in the list. Then it will proceed to choosing a starting name and extracting the correct westerly neighbour of that name and the following names, and then extracting the correct easterly neighbours of that same starting name. This is done using a sequential search in the list to find a name matching the 2nd element of the first pair for the westerly neighbour. As well as, finding a name matching the 1st element of the first pair for the easterly neighbour. 

Considering the following letters as names, an example is as follows: 
z, m 

m, b 

c, l 

b, x 

Where ‘b’ would be the westerly neighbour of ‘m’, and the easterly neighbour of ‘x’. 

Once the names are extracted, they will be contained in a map and stored in a BST. The names will be sorted in alphabetical order where the names on the most western side will be on the left side of 
the tree with their eastern neighbours to their right. Meaning if the names were represented as numbers, the most westerly name will have the lowest value, and the most easterly name will have the highest. 

Consider the 7 names, A-G. An example would be as follows: 

               D 
          B          F 
       A    C     E    G 
       
This process can be repeated until all the names have been restored to the correct order. 

Time-complexity of the algorithm:

Insertion: O(1) due to insertions taking the same amount of time regardless of the size of the data. 

Sorting: O (n log n) average case due to having to traverse tree to find the correct node to insert items alphabetically from list into the BST. 

Search: O(n) due to the function having to traverse the vector to find the westerly/easterly neighbour of the element in the list of pairs.

Time complexity of algorithm as a whole: O(n) as even if sorting is O(n log n) and insertion is constant, algorithm will still have a linear search complexity.

Space usage implications 

std::map has a linear space complexity with respect to the number of elements it contains. 


### std::unordered_map

Implementing the search-based algorithm using an unordered map would mean constructing a hash table that maps the first name element to the element directly after it, as well as, a reverse index hash to all the names that have predecessors. Each name will be given a unique mapped value using the hash function. The algorithm would then find a unique entry which has no predecessor, that would be the head name. Then it would start with the head name to look up all the other names succeeding it until the names have been restored to the correct order.  

Example: 

 -----------------A-------------------------------|-------------------------K--------------------|
 
Index = 01  Hash = #2KF94 (head)---------------Index = 02  Hash = 9DL16 (successor) 

This will allow for the names to be contained in the unordered map while still being able to identify the names’ respective westerly and easterly neighbours.

Time-complexity of the algorithm:

Insertion: O(1) due to insertions taking the same amount of time, regardless of the size of the data. 

Sorting: Due to the hash values and the indexing of elements, sorting can occur at O(1) constant time complexity. However, it can be O(n) in worst case if collisions occur. 

Search: O(n) due to the index being accessed in random order and having an unknown size. 

Time complexity of algorithm as a whole: O(n) as insertions and sorting can be ignored. 

Space usage implications:

std::unordered_map has a linear space complexity with respect to the number of elements it contains. 
