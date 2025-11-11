/*
 * ===================================================================
 * POTENTIAL VIVA QUESTIONS & ANSWERS (Based on Assignments 1-10)
 * * This file contains expected questions an external examiner might ask
 * based on the provided C++ OOP assignment problem statements.
 * ===================================================================
 */

#include <iostream> // Standard library for I/O (relevant for most assignments)
#include <fstream>  // For file I/O (Assignment 6)
#include <vector>   // For STL (Assignment 10)
#include <string>   // For string manipulation
#include <algorithm> // For std::sort (Assignment 10)

// --- Assignment 1: Bank Account Management ---
// Concepts: Basic Class, Constructors (Default, Copy), Destructor, Member Functions

// Q: What is a constructor and why did you use it?
// A: A constructor is a special member function that initializes an object when it's created.
//    I used it to set initial values for account number, name, and balance.

// Q: What is the difference between the default constructor and the copy constructor?
// A: The default constructor is called with no arguments (e.g., BankAccount b;).
//    The copy constructor (e.g., BankAccount b2(b1);) creates a new object as a copy of an existing one.

// Q: What is the purpose of a destructor?
// A: A destructor is called automatically when an object is destroyed. It's used to
//    clean up resources, like freeing dynamically allocated memory.

// Q: How did you ensure a withdrawal is only possible if the balance is sufficient?
// A: Inside the withdraw() member function, I used an 'if' statement to check
//    if (withdrawal_amount <= balance) before proceeding.

// --- Assignment 2: Product Inventory Management ---
// Concepts: Static Members, Static Functions, Friend Functions, Inline Functions

// Q: What is a static member variable?
// A: It's a variable that is shared by all objects of the class. In this assignment,
//    'total_products' was static to keep one count for the whole class.

// Q: How is a static member function different from a regular one?
// A: A static function can only access static members. It can be called using the
//    class name (e.g., Product::get_total_count()) without needing an object.

// Q: What is a friend function and why did you use it?
// A: A friend function is a non-member function that can access the private
//    members of a class. It was used to compare the prices of two 'Product' objects.

// Q: What is the purpose of an inline function?
// A: It's a hint to the compiler to replace the function call with the function's
//    code. This can make small, frequently-called functions faster by avoiding
//    function call overhead. I used it for 'calculate_total_value'.

// --- Assignment 3: Vehicle Management System ---
// Concepts: Complex Inheritance, Nested Class, Friend Class, Multiple Inheritance, Virtual Base Class

// Q: What is a nested class and why use it?
// A: A class defined inside another class. It's used for encapsulation, to define a
//    class (like 'Registration') that is only used by the enclosing class ('Vehicle').

// Q: What problem does multiple inheritance solve, and what problems can it create?
// A: It lets a class inherit from multiple base classes (like 'Electric' and 'Vehicle'
//    to make 'ElectricVehicle'). The main problem it can create is the "diamond problem".

// Q: How does a virtual base class solve the "diamond problem"?
// A: It ensures that the derived class (at the bottom of the diamond) inherits
//    only one copy of the common base class. In this example, 'Engine' was likely a
//    virtual base to prevent ambiguity if multiple paths inherited from it.

// Q: What is a friend class?
// A: A class whose member functions can access the private and protected
//    members of another class, as if they were members of that class.

// --- Assignment 4: Employee Records ---
// Concepts: Polymorphism, Virtual Functions, Abstract Class, Virtual Destructor

// Q: What is runtime polymorphism?
// A: It's the ability for the program to decide which function to call at runtime.
//    This is achieved using a base class pointer (e.g., Employee*) pointing to a
//    derived class object (e.g., FullTimeEmployee) and calling a virtual function.

// Q: What is a pure virtual function?
// A: A virtual function with no implementation in the base class (e.g., virtual void
//    calculatePay() = 0;). It forces derived classes to provide their own implementation.

// Q: What is an abstract class?
// A: A class that has at least one pure virtual function. You cannot create an
//    object of an abstract class. 'Employee' was made abstract.

// Q: Why is it important to have a virtual destructor in the base class?
// A: To ensure that when you delete a derived class object using a base class
//    pointer, the correct derived class destructor is called first, followed by the
//    base class destructor. This prevents memory leaks.

// --- Assignment 5: Student Management System ---
// Concepts: Operator Overloading, Type Casting, `explicit`, `mutable`

// Q: What is operator overloading?
// A: It's defining what a C++ operator (like +, >, <<) does for your custom
//    class (like 'Student').

// Q: How did you overload the `<<` operator for printing?
// A: As a non-member (often friend) function that takes an `ostream&` as the
//    first parameter and a `const Student&` as the second.

// Q: What does the `explicit` keyword do for a constructor?
// A: It prevents the compiler from using that constructor for implicit type
//    conversions, which can avoid unexpected behavior.

// Q: What is the purpose of the `mutable` keyword?
// A: 'mutable' allows a member variable to be modified even inside a 'const'
//    member function (which normally isn't allowed).

// --- Assignment 6: File Stream Operations ---
// Concepts: `ofstream`, `ifstream`, `fstream`, File I/O

// Q: What is the difference between `ofstream`, `ifstream`, and `fstream`?
// A: `ofstream` (output) is for writing to files.
//    `ifstream` (input) is for reading from files.
//    `fstream` (file) is for both reading and writing.

// Q: Why do you need to `close()` a file?
// A: Closing a file ensures that all data in the buffer is "flushed" (written)
//    to the disk, and it releases the file handle for the operating system.

// Q: How did you check if the file was opened successfully?
// A: By checking the stream object in an 'if' statement (e.g., `if (!myFile)`
//    or `if (myFile.is_open())`).

// Q: How did you write "formatted" data?
// A: By using the `<<` operator with spaces, tabs, or newlines (`\n`) to
//    structure the data, just like writing to `cout`.

// --- Assignment 7: Publication Hierarchy ---
// Concepts: Inheritance, Exception Handling (`try`, `catch`, `throw`)

// Q: What is exception handling?
// A: It's a mechanism to handle runtime errors (exceptions) in a structured
//    way. It uses `try`, `catch`, and `throw`.

// Q: What code goes in the `try` block?
// A: The code that might cause an error, like reading user input that
//    could be an invalid data type (e.g., "abc" for an integer price).

// Q: What does the `catch` block do?
// A: It "catches" the exception thrown by the `try` block. It contains the
//    code to handle the error, like printing an error message and setting
//    data members to zero.

// Q: How did you handle different types of exceptions?
// A: You can use multiple `catch` blocks for different data types, or
//    use a generic `catch(...)` to catch all types of exceptions.

// --- Assignment 8: Selection Sort Function Template ---
// Concepts: Function Templates

// Q: What is a function template?
// A: A blueprint for creating a function. It allows you to write one function
//    that can work with different data types (like `int`, `float`, `double`).

// Q: How did you define the template for `selection_sort`?
// A: With the line `template <typename T>` or `template <class T>` before
//    the function definition. The function then uses 'T' as the generic data type.

// Q: How does the selection sort algorithm work?
// A: It works by repeatedly finding the minimum element from the unsorted
//    part of the array and swapping it with the first element of the unsorted part.

// Q: Did you need to change the function to call it for floats and then for ints?
// A: No. The compiler automatically creates (instantiates) a version of the
//    function for `int` and another for `float` based on the arguments I passed.

// --- Assignment 9: Library System with Pointers ---
// Concepts: Dynamic Memory (`new`/`delete`), Pointers, Function Pointers

// Q: Why did you use `new` and `delete`?
// A: To dynamically allocate memory on the heap for the book's title and
//    author. This is useful when you don't know the size at compile time.

// Q: What is a pointer to a pointer (e.g., `Book**`)?
// A: It's a variable that stores the memory address of another pointer. It might be
//    used to create a dynamic array of 'Book*' pointers or to modify a
//    pointer variable inside a function.

// Q: What is a function pointer?
// A: A variable that stores the memory address of a function. It's useful
//    for passing a function as an argument to another function, like
//    passing a sorting criteria (e.g., 'sortByTitle') to a 'sort' function.

// Q: What is the risk of using `new`?
// A: Forgetting to call `delete`. This creates a memory leak, where memory is
//    allocated but never freed, and the program consumes more and more memory.

// --- Assignment 10: Item Records with STL ---
// Concepts: STL `vector`, Iterators, Algorithms (`std::sort`)

// Q: What is the C++ STL?
// A: The Standard Template Library. It's a collection of powerful, pre-built
//    template classes and functions for containers, iterators, and algorithms.

// Q: Why use an
// A: A 'vector' is a dynamic array from the STL. It's easier and safer
//    than managing memory manually with `new` and `delete`. It can grow
//    and shrink automatically.

// Q: How did you sort the vector of 'Item' objects?
// A: By using the `std::sort` algorithm. To sort on different criteria
//    (like cost or name), I passed a custom comparison function (or a lambda)
//    as the third argument to `std::sort`.

// Q: How did you search for an item?
// A: I could have used `std::find` or `std::find_if` from the `<algorithm>`
//    library, or simply iterated through the vector with a 'for' loop.

// ===================================================================
// Main function (placeholder to make it a valid C++ file)
// ===================================================================

int main() {
    // This file is for study/viva purposes.
    // The C++ code for the assignments would go here.
    
    std::cout << "Viva/Oral Exam Preparation Questions" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "See the comments in this file for Q&A." << std::endl;
    
    return 0;
}