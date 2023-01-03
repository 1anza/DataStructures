#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

void pressAnyKeyToContinue();



vector<bool> destructTracker;
class DestructorTester {
public:
  DestructorTester() {
    index = destructTracker.size();
    destructTracker.push_back(false);
  }
  ~DestructorTester() {
    destructTracker[index] = true;
  }
private:
  int index{ -1 };
};


//These two base classes help the assignment compile and run without any changes.  
//Dot not modify these.  You will instead override the methods in the derived classes below.
template <typename T>
class BaseQueue {
public:
  BaseQueue() {}
  BaseQueue(const unsigned int capacity) {}
  void push_back(const T& item) {}                            //These methods just contain filler code to help the code compile on the initial run.
  void pop_front() {}
  void resize(const unsigned int newCapacity) {}
  T front() { T temp{}; return temp; }
  T back() { T temp{}; return temp; }
  const unsigned int size() const { return 0; }

  // This just disables the copy/move constructors/assignments
  BaseQueue(const BaseQueue<T>& objToCopy) = delete;
  const BaseQueue<T>& operator=(const BaseQueue<T>& objToCopy) = delete;
  BaseQueue(BaseQueue<T>&& objToCopy) = delete;
  BaseQueue<T>& operator=(BaseQueue<T>&& objToCopy) = delete;

protected:
  T* arr{ nullptr };

};

//**********************************
//Write your code below here
//**********************************
template <typename T>
class QueueForCS2420 : public BaseQueue<T> {
public:
  QueueForCS2420(const unsigned int capacity);
  ~QueueForCS2420();
  unsigned int size() const;
  void push_back(const T& item);
  void pop_front();
  T front();
  T back();
  void resize(const unsigned int newCapacity);
  

  // TODO: Complete methods, constructor, and destructor
private:
  // TODO: Supply the 4 needed data members
    unsigned int capacity = 0;
    unsigned int index = 0;
    unsigned int head = 0;
    unsigned int tail = 0;

};


template <typename T>
QueueForCS2420<T>::QueueForCS2420(const unsigned int capacity) {
  // TODO: Complete this
    this->arr = new T[capacity];
    this->capacity = capacity;
}


//**********************************
//Write your code above here
//**********************************

template <typename T>
QueueForCS2420<T>::~QueueForCS2420() {
    if (this->arr != nullptr) {
        delete[] this->arr;
    }
    if (this->arr == nullptr) {
        delete[] this->arr;
    }
}

template <typename T>
unsigned int QueueForCS2420<T>::size() const {
    return index;
}

template <typename T>
void QueueForCS2420<T>::push_back(const T& item) {
    if (capacity == size()) {
        cout << "Queue is full";
        return;
    }

    else if (tail >= capacity) {
        tail = 0;
        this->arr[tail] = item;
        
    }
    else {
        this->arr[tail] = item;
    }
        tail++;
        index++;

}

template <typename T>
void QueueForCS2420<T>::pop_front() {
    if (size() == 0) {
        cout << "Empty";
        return;
    }
    else {
        head++;
    }
    if (head >= capacity) {
        head = 0;
    }
        index--;
}

template <typename T>
T QueueForCS2420<T>::front() {
    if (size() == 0) {
        throw 1;
    }
    else {
        return this->arr[head];
    }
}

template <typename T>
T QueueForCS2420<T>::back() {
    if (size() == 0) {
        throw 1;
    }
    return this->arr[tail - 1];


}

template <typename T>
void QueueForCS2420<T>::resize(const unsigned int newCapacity) {
    
    QueueForCS2420<T> Queue(newCapacity);
    
    while (this->size() != 0) {
        Queue.push_back(this->front());
        this->pop_front();
    }

    delete[] this->arr;

    this->arr = Queue.arr;
    this->index = Queue.index;
    this->head = Queue.head;
    this->tail = Queue.tail;
    this->capacity = Queue.capacity;

    Queue.arr = nullptr;

}




//This helps with testing, do not modify.

//This helps with testing, comment it in when ready, but do not modify the code.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    if (whatItShouldBe == "") {
      cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been blank. " << endl;
    }
    else {
      cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    }
    exit(1);
    return false;
  }
}

template <typename T, typename U>
bool checkTest(string testName, T whatItShouldBe, U whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
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
    cout << "***Failed test " << testName << " *** " << endl << ".  ";
    cout << "You are manually managing " << whatItIs << " bytes in memory, but it should be " << whatItShouldBe << " bytes." << endl;
    return false;
    exit(1);
  }
}

//Copyright 2021, Bradley Peterson, Weber State University, All rights reserved. (May 2021)

void testQueueForCS2420() {

  string result;
  string caughtError;
  {
    QueueForCS2420<string> pQueue(5);

    // Tests push_back
    string item = "penny";
    pQueue.push_back(item);
    item = "nickel";
    pQueue.push_back(item);
    item = "dime";
    pQueue.push_back(item);
    item = "quarter";
    pQueue.push_back(item);

    checkTest("testQueueForCS2420 #1", 4, pQueue.size());

    checkTest("testQueueForCS2420 #2", "penny", pQueue.front());
    checkTest("testQueueForCS2420 #3", "quarter", pQueue.back());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #4", 3, pQueue.size());

    checkTest("testQueueForCS2420 #5", "nickel", pQueue.front());
    checkTest("testQueueForCS2420 #6", "quarter", pQueue.back());

    pQueue.pop_front();
    checkTest("testQueueForCS2420 #7", "dime", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #8", "quarter", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #9", 0, pQueue.size());

    caughtError = "not caught";
    try {
      result = pQueue.front();
    }
    catch (int) {
      caughtError = "caught";
    }
    checkTest("testQueueForCS2420 #10", "caught", caughtError);

    caughtError = "not caught";
    try {
      result = pQueue.back();
    }
    catch (int) {
      caughtError = "caught";
    }
    checkTest("testQueueForCS2420 #11", "caught", caughtError);

    checkTest("testQueueForCS2420 #12", 0, pQueue.size());

    item = "penny";
    pQueue.push_back(item);
    checkTest("testQueueForCS2420 #13", "penny", pQueue.front());
    pQueue.push_back("nickel");
    pQueue.push_back("dime");
    pQueue.push_back("quarter");

    checkTest("testQueueForCS2420 #14", "penny", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("half dollar");
    pQueue.push_back("silver dollar");

    // It should be full, no more room to add more.
    pQueue.push_back("million dollar bill");

    // Because of so many tests, pause for a bit on the screen.
    pressAnyKeyToContinue();

    // Take a look at what is coming next.
    checkTest("testQueueForCS2420 #15", "nickel", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #16", "dime", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #17", "quarter", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #18", "half dollar", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #19", "silver dollar", pQueue.front());
    pQueue.pop_front();
    caughtError = "not caught";
    try {
      result = pQueue.front();
    }
    catch (int) {
      caughtError = "caught";
    }
    checkTest("testQueueForCS2420 #20", "caught", caughtError);

    // Test adding and removing back and forth
    pQueue.push_back("penny");
    checkTest("testQueueForCS2420 #21", "penny", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("nickel");
    checkTest("testQueueForCS2420 #22", "nickel", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("dime");
    checkTest("testQueueForCS2420 #23", "dime", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("quarter");
    checkTest("testQueueForCS2420 #24", "quarter", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("half dollar");
    checkTest("testQueueForCS2420 #25", "half dollar", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("silver dollar");
    checkTest("testQueueForCS2420 #26", 1, pQueue.size());

    checkTest("testQueueForCS2420 #27", "silver dollar", pQueue.front());
    pQueue.pop_front();
    caughtError = "not caught";
    try {
      result = pQueue.front();
    }
    catch (int) {
      caughtError = "caught";
    }
    checkTest("testQueueForCS2420 #28", "caught", caughtError);
  }
  {
    QueueForCS2420<int> iQueue(3); // A queue of 3 items

    iQueue.push_back(1);
    iQueue.push_back(2);
    iQueue.pop_front();
    iQueue.push_back(3);
    iQueue.pop_front();
    checkTest("testQueueForCS2420 #29", 3, iQueue.front());
    checkTest("testQueueForCS2420 #30", 3, iQueue.back());
    iQueue.push_back(4);
    iQueue.push_back(5);
    checkTest("testQueueForCS2420 #31", 3, iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueForCS2420 #32", 4, iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueForCS2420 #33", 5, iQueue.front());
  }

}

void testQueueResize() {

  string result;
  string caughtError;


  {
    QueueForCS2420<int> iQueue(5);
    iQueue.push_back(10);
    iQueue.push_back(20);
    iQueue.push_back(30);
    iQueue.push_back(40);
    iQueue.push_back(50);
    checkTest("testQueueResize #1", 5, iQueue.size());
    iQueue.push_back(666);
    checkTest("testQueueResize #2", 5, iQueue.size());

    iQueue.resize(10);
    iQueue.push_back(60);
    checkTest("testQueueResize #3", 6, iQueue.size());
    checkTest("testQueueResize #4", 10, iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #5", 20, iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #6", 30, iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #7", 40, iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #8", 50, iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #9", 60, iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #10", 0, iQueue.size());
  }

  {
    QueueForCS2420<char> iQueue(3);
    iQueue.push_back('a');
    iQueue.push_back('b');
    iQueue.push_back('c');
    checkTest("testQueueResize #11", 3, iQueue.size());
    iQueue.push_back('x');
    checkTest("testQueueResize #12", 3, iQueue.size());
    iQueue.pop_front(); // Get rid of the 'a'
    iQueue.pop_front(); // Get rid of the 'b'
    iQueue.resize(8);
    checkTest("testQueueResize #12", 1, iQueue.size());
    checkTest("testQueueResize #13", 'c', iQueue.front());
    iQueue.push_back('d');
    iQueue.push_back('e');
    iQueue.push_back('f');
    iQueue.push_back('g');
    iQueue.push_back('h');
    iQueue.push_back('i');
    iQueue.push_back('j');
    checkTest("testQueueResize #14", 8, iQueue.size());
    iQueue.push_back('x');
    checkTest("testQueueResize #15", 8, iQueue.size());
    checkTest("testQueueResize #16", 'c', iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #17", 'd', iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #18", 'e', iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #19", 'f', iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #20", 'g', iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #21", 'h', iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #22", 'i', iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueResize #23", 'j', iQueue.front());
    iQueue.pop_front();


  }


}

void testDestructor() {

  // Test that it destroys everything 
  // (It's a queue of DestructorTestor objects.  Each time a Destructor tester object is created
  // it will append a new false value to a global destructTracker vector.  Each time a Destructor object is
  // destructed, it will set its corresponding false value to true.)

  {
    QueueForCS2420< DestructorTester > dQueue(5);
  }  // <--- Destructor should invoke here.

  bool everythingDestructed{ true };
  if (destructTracker.size() != 5) {
    everythingDestructed = false;
  }
  else {
    for (int i = 0; i < 5; i++) {
      if (!destructTracker[i]) {
        everythingDestructed = false;
      }
    }
  }
  if (everythingDestructed) {
    cout << "Passed testDestructor #1" << endl;
  }
  else {
    cout << "***Failed test testDestructor #1 *** " << endl << "   You are missing a destructor, or your destructor didn't work. " << endl;
  }

  destructTracker.clear();

  {
    QueueForCS2420< DestructorTester > dQueue(3);
    dQueue.resize(5);
  }  // <--- Destructor should invoke here.

  everythingDestructed = true;
  if (destructTracker.size() != 8) {
    everythingDestructed = false;
  }
  else {
    for (auto destructed : destructTracker) {
      if (!destructed) {
        everythingDestructed = false;
      }
    }
  }

  // If this test fails, then your resize() method likely didn't call delete[] on the original this->arr.  
  if (everythingDestructed) {
    cout << "Passed testDestructor #2" << endl;
  }
  else {
    cout << "***Failed test testDestructor #2 *** " << endl << "   You are missing a destructor, or your destructor didn't work. " << endl;
  }

  destructTracker.clear();

}


void pressAnyKeyToContinue() {
  cout << "Press enter to continue...";

  //Linux and Mac users with g++ don't need this
  //But everyone else will see this message.
  cin.get();

}

int main() {

  {
    testQueueForCS2420();
    pressAnyKeyToContinue();
    testQueueResize();
    pressAnyKeyToContinue();
    testDestructor();
    pressAnyKeyToContinue();
  }
  cout << "Shutting down the program" << endl;
  return 0;
}
*/