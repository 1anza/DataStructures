#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <sstream>
#include <memory>
#include <string>
#include <vector>

template <typename T> class DoublyLinkedList;

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::stringstream;
using std::iter_swap;
using std::make_shared;
using std::shared_ptr;
using std::vector;


//******************
//The Node class
//******************
template <typename T>
struct Node {
  T data{};
  shared_ptr<Node<T>> prev;
  shared_ptr<Node<T>> next;
};

//******************
//The Iterator class
//******************
template <typename T>
class Iterator {
  friend class DoublyLinkedList<T>;
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = int;
  using pointer = T*;
  using reference = T&;

  // TODO: Implement the following:
  //operator*
  //operator++ prefix  ends with return *this;
  //operator++ postfix  starts with auto temp = *this;  advances the "this"...;   return temp;
  //operator-- prefix
  //operator!=
  //operator==
  T& operator*() const;
  Iterator<T> operator++();
  Iterator<T> operator++(int);  //That int is a code saying it's postfix
  Iterator<T> operator--();
  bool operator!=(const Iterator<T>& rhs) const;
  bool operator==(const Iterator<T>& rhs) const;

private:

  // TODO: supply two data members
  //You need a shared pointer to a node
  //You need a boolean pastTheEnd, initialized to false. (see lecture video)
  shared_ptr<Node<T>> current{ nullptr };
  bool pastTheEnd{ false };

};

//***********************************
//The Iterator class methods
//***********************************

// TODO: code the definitions for all the iterator methods.
template <typename T>
T& Iterator<T>::operator*() const {
    return current->data;

}

template <typename T>
Iterator<T> Iterator<T>::operator++() {

    if (!current->next) {   //there is not a next node
        if (pastTheEnd == true) {
            return *this;
        }
        else {              //past the end is false, but there isn't a next node
            pastTheEnd = true;
            return *this;
        }
    }
    else {  //walk to the next node
        pastTheEnd = false;
        current = current->next;
        return *this;
    }
 
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
    shared_ptr<T> curr;
    auto copyOfItself = *this;

    if (!current->next) {   //there is not a next node
        if (pastTheEnd == true) {
            return copyOfItself;
        }
        else {              //past the end is false, but there isn't a next node
            pastTheEnd = true;
            return copyOfItself;
        }
    }
    else {  //walk to the next node
        pastTheEnd = false;
        current = current->next;
        return copyOfItself;
    }


}

//check here 

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& rhs) const {
    //this-> refers to the left hand operand
    //rhs. refers to the right hand operand
    if (this->current == rhs.current && this->pastTheEnd == rhs.pastTheEnd)
        return false;
    else
        return true;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& rhs) const {
    //this->refers to the left hand operand
    //rhs.refers to the right hand operand
        if (this->current == rhs.current && this->pastTheEnd == rhs.pastTheEnd)
            return true;
        else
            return false;
}

template <typename T>
Iterator<T> Iterator<T>::operator--() {
    
        if (pastTheEnd == true) {
                pastTheEnd = false;
                return *this;
            }

        if (current->prev) {
            current = current->prev;
            return *this;
        }


}

//****************************
//The DoublyLinkedList class
//****************************
template <typename T>
class DoublyLinkedList {

public:

  //public members of the DoublyLinkedList class
  DoublyLinkedList();
  ~DoublyLinkedList();
  string getStringFromList();

  void pushFront(const T&);
  void pushBack(const T&);
  // TODO: Implement a begin() and end() method.  They each return an Iterator<T> object
  Iterator<T> begin() const;
  Iterator<T> end() const;

protected:
  shared_ptr<Node<T>> first{ nullptr };
  shared_ptr<Node<T>> last{ nullptr };
  unsigned int count;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
  count = 0;
  first = nullptr;
  last = nullptr;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  while (first != last) {
    first = first->next;
    first->prev.reset();
  }
}

template <typename T>
void DoublyLinkedList<T>::pushFront(const T& item) {
  shared_ptr<Node<T>> temp = make_shared<Node<T>>();

  temp->data = item;
  if (!first) {
    // Scenario: List is empty
    last = temp;
  }
  else {
    first->prev = temp;
    temp->next = first;
  }
  first = temp;
}

template <typename T>
void DoublyLinkedList<T>::pushBack(const T& item) {
  shared_ptr<Node<T>> temp = make_shared<Node<T>>();

  temp->data = item;
  if (!first) {
    // Scenario: List is empty
    first = temp;
  }
  else {
    last->next = temp;
    temp->prev = last;
  }
  last = temp;
}

//This method helps return a string representation of all nodes in the linked list
template <typename T>
string DoublyLinkedList<T>::getStringFromList() {
  stringstream ss;
  if (!first) {
    ss << "The list is empty.";
  }
  else {

    shared_ptr<Node<T>> currentNode{ first };
    ss << currentNode->data;
    currentNode = currentNode->forward;

    while (currentNode != nullptr) {
      ss << " " << currentNode->data;
      currentNode = currentNode->forward;
    }
  }
  return ss.str();
}

//***********************************
//The DoublyLinkedList class methods
//***********************************
// TODO: implement the  the definitions for the begin() and end() methods.  They each return an Iterator<T> object

template <typename T>
Iterator<T> DoublyLinkedList<T>::begin() const {
    // Create and iterator object
    Iterator<T> retVal; 
    retVal.current = this->first;
    

    if (!this->first) {
        retVal.pastTheEnd = true;
        return retVal;
    }
    else {
        retVal.pastTheEnd = false;
        return retVal;
    }
    //Make sure if empty, begin doesn't point to anything

}

template <typename T>
Iterator<T> DoublyLinkedList<T>::end() const {
    // Create and iterator object
    Iterator<T> retVal;
    retVal.current = this->last;
    
    
        retVal.pastTheEnd = true;
        return retVal;


}


//***********************************
// TODO: complete the assignmentReverse function.
// Note that begin and end here are are iterators (The T is just saying it can be any kind of iterator).
// Your tools are ***ONLY**: ++, --, !=, *, ==
// For example, these three lines do a swap:
// auto temp = *end;
// *end = *begin;
// *begin = temp;
// Also, this comes in handy: iter_swap(begin, end);  //Swaps the values pointed at by two iterators. 

template <typename T>
void assignmentReverse(T begin, T end) {
    /*

    Only have a begin and end. Must use these to reverse all values in the container. Don't have access to prev next first or last
    You can use ++,-- etc

    * lets you read and write

    auto temp = *end;
    *end = *begin;
    *begin = temp;
    also, this comes in handy: iter_swap(begin, end)

    ABCDE how many iterator states? = 6
    Should you iter swap when the last iterator (at 6) is nothing? = NO
    You must decrement end first --end; then use iter_swap(begin, end)
    Then we must move the iterators inward, then swap the values again
    then we must move the iterators inward again, swap values
    do it again
    do it again
    when the end matches the original beginning, you can say you're done - whala!

    Palindrom code can do this in a much more fashionable way.
    As you start moving in, you need to check to see if you're at the middle with == or !=
    once at the middle, you can stop; For even elements, the never have a middle, so check this with an if statement
    Need to find a way to find the length of the iterator. Conditional branching with a for loop? (He just threw this out there, not sure if it's relevant)

    while{ if this{ then that}}
    one while, two for's.  One liner == magic


    */
      // Get the container off its past-the-end state so its "pointing" at the last value in the container.  
    while (end != begin) {
        --end;
        iter_swap(end, begin);
        ++begin;
    }
    return;


}


//----------------------------------------------------------------------------------------------------------------------------------------
//Copyright 2021, Bradley Peterson, Weber State University, All rights reserved. (June 2021)
//This helps with testing, do not modify.
bool checkTest(string testName, const string whatItShouldBe, const string whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
    return false;
    exit(1);
  }
}

template <typename T>
bool checkTest(string testName, const T whatItShouldBe, const T whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
    return false;
    exit(1);
  }
}


//This helps with testing, do not modify.
bool checkTestMemory(string testName, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << "  There are " << whatItIs << " bytes of memory yet to be reclaimed!" << endl;
    return false;
    exit(1);
  }
}


//This helps with testing, do not modify.
void testIteratorFundamentals() {
  //cout << "|||### You need to comment in testIteratorIncrement() when it's ready and remove this ###|||" << endl;
  //cout << "|||### I strongly advise commenting in tests one at a time and testing those.  It's harder to try and do all tests at once.###|||" << endl;

  DoublyLinkedList<int> d;

  //Our test data should have all even numbers from 2 to 20
  for (int i = 2; i <= 20; i += 2) {
    d.pushBack(i);
  }

  ////Get an iterator which points at the beginning of the list
  Iterator<int> iter = d.begin();

  ////Test the operator* operator
  checkTest("testIteratorFundamentals #1", 2, *iter);

  //Test the ++ prefix increment opreator
  ++iter;
  checkTest("testIteratorFundamentals #2", 4, *iter);

  ////Test the != operator
  ////reset them back to the start
  iter = d.begin();
  Iterator<int> anotherIter = d.begin();
  if (iter != anotherIter) {
    cout << "****** Failed testIteratorFundamentals #3 ****** " << endl << "     The two iteraters held the same data." << endl;
  }
  else {
    cout << "Passed testIteratorFundamentals #3" << endl;
  }

  //Again test the != operator
  ++iter;
  if (iter != anotherIter) {
    cout << "Passed testIteratorFundamentals #4" << endl;
  }
  else {
    cout << "****** Failed testIteratorFundamentals #4 ****** " << endl << "     The two iteraters held different data." << endl;
  }

  //Test the ++postfix increment
  iter = d.begin(); //reset it back to the start
  anotherIter = iter++;  //anotherIter should be at the data 2

  checkTest("testIteratorFundamentals #5", 4, *iter);
  checkTest("testIteratorFundamentals #6", 2, *anotherIter);

  // TODO:
  // We have !=, *, ++, and .begin() tested by this point.  Now test .end().  Do that with a for loop.  
  stringstream ss;
  cout << "testIteratorFundamentals test #7, this should display 2 4 6 8 10 12 14 16 18 20." << endl;
  for (auto item : d) {
    cout << item << " ";
    ss << item << " ";
  }
  cout << endl;


  //checkTest("testIteratorFundamentals test #7", "2 4 6 8 10 12 14 16 18 20 ", ss.str());
  //ss.str("");
}

//This helps with testing, do not modify.
void testIteratorIncrement() {
  //cout << "|||### You need to comment in testIteratorIncrement() when it's ready and remove this ###|||" << endl;
  DoublyLinkedList<int>* d = new DoublyLinkedList<int>;

  //Our test data should have all even numbers from 2 to 20
  for (int i = 2; i <= 20; i += 2) {
    d->pushBack(i);
  }

  //Get an iterator which points at the beginning of the list
  Iterator<int> iter = d->begin();

  //Test that it does point to the first
  checkTest("testIteratorsIncrement #1", 2, *iter);

  //Test that our Iterator can move forward;
  ++iter;
  checkTest("testIteratorsIncrement #2", 4, *iter);


  //Test that our Iterator can move forward again;
  ++iter;
  checkTest("testIteratorsIncrement #3", 6, *iter);

  //move it some more
  for (int i = 0; i < 6; i++) {
    ++iter;
  }
  checkTest("testIteratorsIncrement #4", 18, *iter);

  //Hit the end
  ++iter;
  checkTest("testIteratorsIncrement #5", 20, *iter);

  ////Verify we move the iterator past the end without crashing
  ++iter;
  string didntCrash = "did not crash";
  checkTest("testIteratorsIncrement #6", didntCrash, didntCrash);


  delete d;
}

//This helps with testing, do not modify.
void testIteratorDecrement() {
  //cout << "|||### You need to comment in testIteratorDecrement() when it's ready and remove this###|||" << endl;

  DoublyLinkedList<int>* d = new DoublyLinkedList<int>;

  //Our test data should have all even numbers from 2 to 20
  for (int i = 2; i <= 20; i += 2) {
    d->pushBack(i);
  }

  //Get an Iterator which points at the end of the list    (Not on the last item, but on the "end" state)
  Iterator<int> iter = d->end();

  --iter;  // We have to do a decrement otherwise the iterator is in the past-the-end state and isn't pointing at a value
           // Don't comment out this line, even if it makes your test #2 pass.  It will make later tests fail.
           // If you comment out this line and later contact me for help, then I will drive up to your residence, ring your doorbell, and stare at you angrily.  

       //Test that it does point to the first
  checkTest("testIteratorsDecrement #1", 20, *iter);

  //Test that our Iterator can move forward;
  --iter;
  checkTest("testIteratorsDecrement #2", 18, *iter);

  //move it some more
  for (int i = 0; i < 7; i++) {
    --iter;
  }
  checkTest("testIteratorsDecrement #3", 4, *iter);

  //Hit the end
  --iter;
  checkTest("testIteratorsDecrement #4", 2, *iter);

  //Now go back forward
  ++iter;
  checkTest("testIteratorsDecrement #5", 4, *iter);

  delete d;
}

//This helps with testing, do not modify.
void testIterationTricky() {

  //cout << "|||### You need to comment in testIterationTricky() when it's ready and remove this###|||" << endl;

  DoublyLinkedList<int> myListOneNode;

  myListOneNode.pushBack(42);
  cout << "TestIterationTricky test #1, the next line should display 42" << endl;
  stringstream ss;
  //see if we can just iterator through one item.
  for (auto i : myListOneNode) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("TestIterationTricky test #1", "42 ", ss.str());
  ss.str("");

  DoublyLinkedList<int> myListEmpty;
  cout << "TestIterationTricky test #2, the next line shouldn't display anything" << endl;
  //see if we can just iterator through one item.
  for (auto i : myListEmpty) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("TestIterationTricky test #2", "", ss.str());
  ss.str("");
}



//This helps with testing, do not modify.
void testAlgorithms() {
  //cout << "|||### You need to comment in testAlgorithms() when it's ready and remove this###|||" << endl;

  DoublyLinkedList<int> myList;

  //Our test data should have all even numbers from 2 to 20
  for (int i = 2; i <= 6; i += 2) {
    myList.pushBack(i);
  }
  myList.pushBack(100);
  for (int i = 8; i <= 12; i += 2) {
    myList.pushBack(i);
  }
  myList.pushBack(100);
  for (int i = 14; i <= 20; i += 2) {
    myList.pushBack(i);
  }
  stringstream ss;
  cout << "testAlgorithms test #1, this should display 2 4 6 100 8 10 12 100 14 16 18 20." << endl;
  for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #1", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
  ss.str("");

  //Test the STL reverse algorithm on our iterator
  cout << "testAlgorithms test #2, this should display 20 18 16 14 100 12 10 8 100 6 4 2." << endl;
  std::reverse(myList.begin(), myList.end());
  for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #2", "20 18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
  ss.str("");

  //Get it back in ascending order using the STL reverse algorithm
  std::reverse(myList.begin(), myList.end());
  for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #3", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
  ss.str("");

  // Try a custom assignmentReverse function

  assignmentReverse(myList.begin(), myList.end());
  for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #4", "20 18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
  ss.str("");

  //Get it back in ascending order using the STL reverse algorithm
  assignmentReverse(myList.begin(), myList.end());
  for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;

  checkTest("testAlgorithms test #5", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
  ss.str("");

  // Test assignmentReverse on an STL container:


  list<int> stlList;

  //Our test data should have all even numbers from 2 to 20
  for (int i = 2; i <= 6; i += 2) {
    stlList.push_back(i);
  }
  stlList.push_back(100);
  for (int i = 8; i <= 12; i += 2) {
    stlList.push_back(i);
  }
  stlList.push_back(100);
  for (int i = 14; i <= 20; i += 2) {
    stlList.push_back(i);
  }
  for (auto i : stlList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #6", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
  ss.str("");

  // Try a custom assignmentReverse function

  assignmentReverse(stlList.begin(), stlList.end());
  for (auto i : stlList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #7", "20 18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
  ss.str("");


}



//This helps with testing, do not modify.
void testLambda() {
  cout << "|||### You need to comment in testLambda() when it's ready and remove this###|||" << endl;

  DoublyLinkedList<string> myWords;

  myWords.pushBack("bob");
  myWords.pushBack("racecar");
  myWords.pushBack("peep");
  myWords.pushBack("redder");
  myWords.pushBack("sells");
  myWords.pushBack("pneumonoultramicroscopicsilicovolcanoconiosis");
  myWords.pushBack("Was it a car or a cat I saw?");
  myWords.pushBack("Madam, in Eden, I’m Adam");
  myWords.pushBack("A nut for a jar of tuna");
  myWords.pushBack("Borrow or rob?");
  myWords.pushBack("This is a palindrome!");
  
  
  // Lets search for only palindromes

  // Prepare a container to hold output.  
  vector<string> output(11);
  
  // TODO:

  // Utilize an STL algorithm std::copy_if with a lambda expression to filter out all palindromes into the vector called output
  // The lambda expression captures nothing
  // The lambda expression needs a single parameter, a const string reference.  
  // The code body of the lambda expression needs to return a boolean.  True if the string is a palindrome, false if not.
  // Note that you must remove all non-letter characters and then turn all upper-case to lower-case.  After that you
  //   can easily test if the string is a palindrome

  auto it = std::copy_if(myWords.begin(), 
                         myWords.end(), 
                         output.begin(), 
  //                        TODO: put lambda here 
  //                            it shoul manually go through and loop all items. If it works correctly it 
  //                            gets resized down to a new end below (output.resize). Could write a function
  //                            above and call the name of it down here. Could use a functor, or use a lambda 
  //                            - which is easiest, quick and dirty on the fly right here. Functions within functions
                              [output](const string& someWord){ 
  //                            [] is the capture part (capture something into scope)
  //                            () the parameter part, how many things are  being passed in
  //                            {} The code body, put all your logic here
                                    string temp = "";
                                    for (int i = 0; i < someWord.length(); i++) {
                                        if ((someWord[i] >= 'a' && someWord[i] <= 'z') || (someWord[i] >= 'A' && someWord[i] <= 'Z')) {
                                            temp = temp + someWord[i];
                                        }
                                    }
                                    
                                    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                                    
                                    if (temp == string(temp.rbegin(), temp.rend())) {
                                        return true;
                                    }
                                    return false;
                              }
                        );
  
  output.resize(std::distance(output.begin(), it));  // Shrinkg output to new size
  std::stringstream ss;
  for (auto& str : output) {
    ss << str << "|";
  }
  checkTest("testLambda test #1", "bob|racecar|peep|redder|Was it a car or a cat I saw?|Madam, in Eden, I’m Adam|A nut for a jar of tuna|Borrow or rob?|", ss.str());

}

void pressAnyKeyToContinue() {
  cout << "Press enter to continue...";
  cin.get();
}

int main() {

  cout << "This first test can run forever until you get operators *, != and ++ implemented." << endl;
  pressAnyKeyToContinue();

  testIteratorFundamentals();
  pressAnyKeyToContinue();

  testIteratorIncrement();
  pressAnyKeyToContinue();

  testIteratorDecrement();
  pressAnyKeyToContinue();

  testIterationTricky();
  pressAnyKeyToContinue();

  testAlgorithms();
  pressAnyKeyToContinue();

  testLambda();
  pressAnyKeyToContinue();

  return 0;
}