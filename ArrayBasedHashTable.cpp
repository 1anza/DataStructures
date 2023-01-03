#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <memory>
#include <cstdio>
#include <algorithm>


using std::cout;
using std::endl;
using std::map;
using std::unique_ptr;
using std::make_unique;
using std::string;
using std::stringstream;
using std::pair;


//forward declarations
template <typename T> class HashTable;
template <typename T> class Iterator;
//************************************************************
//A quick and simple class that simulates a Product object.
//************************************************************
class Product {
public:
  void setCost(int cost);
  void setName(const string&);
  string getName();
  int getCost();
  string getAllInfo();
private:
  string name;
  int cost;
};
void Product::setCost(int cost) {
  this->cost = cost;
}
void Product::setName(const string& name) {
  this->name = name;
}
string Product::getName() {
  return name;
}
int Product::getCost() {
  return cost;
}
string Product::getAllInfo() {
  stringstream ss;
  ss << "Name: " << name << ", Cost: " << cost;
  return ss.str();
}

//************************************************************
//The Iterator class
//************************************************************
template <typename T>
class Iterator {
  friend class HashTable<T>;
public:

  // TODO: define these methods
  pair<string, T>& operator*();
  bool operator!=(const Iterator<T>& rhs) const;
  Iterator<T> operator++();

private:
  HashTable<T>* hashTable{ nullptr };
  unsigned int index{ 0 };
};




/*
Two data types
hashtable and index
begin at the begin, dont overthink it.
trickiest one is the ++, don't overthink it. Draw out a picture if it helps. 

HashTable has two, keyvalue and keystatus
keyvalue has an array of pairs. To access the key, you use first. value is the second. 

*/


//************************************************************
//The HashTable class
//************************************************************
template <typename T>
class HashTable
{
  friend class Iterator<T>;
public:
  unsigned int getNumBuckets() { return capacity; }
  unsigned int getTotalCount() const;
  unsigned int getWorstClump() const;

  // TODO: Create the array
  HashTable();
  // TODO: Add an operator= move method
  HashTable<T>& operator=(HashTable<T>&& obj) noexcept;

  HashTable(const HashTable<T>& obj) {
    cout << "Failed homework issue:  You hit the HashTable copy constructor.  That's bad!" << endl;
  }
  HashTable<T>& operator=(const HashTable& obj) {
    cout << "Failed homework issue:  You hit the HashTable copy assignment.  That's bad!" << endl;
    HashTable temp;
    return temp;
  }
  // We won't implement this move constructor for the homework
  HashTable(HashTable<T>&& obj);    // Move constructor

                           

  // TODO: supply these methods
  void create(const string& key, const T& item);// method for L - values
  void create(const string& key, T&& item);// method for R - values
  T retrieve(const string& key); // method(return by value, acts as a read only retrieve)
  T& operator[](const string& key); // method(return by reference which can allow for modification of values)
  bool exists(const string& key);//  method(returns a boolean)
  void remove(const string& key); //method
  Iterator<T> begin();
  Iterator<T> end();

private:

  // TODO: Implement a private constructor that sizes the arrays to customCapacity
  HashTable(const unsigned int customCapacity);

  unsigned int hash(const string& key) const;

  unsigned int capacity{ 20 };
  unsigned int count{ 0 };
  unique_ptr<int[]> status_arr;
  unique_ptr<pair<string, T>[]> keyValue_arr;

};// end class HashTable

//************************************************************
// Put HashTable consrtuctors and methods below here
//************************************************************


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Not quite complete Iterator Section

//template <typename T>
//Iterator<T> HashTable<T>::begin() {
//    // Create and iterator object
//    Iterator<T> retVal;
//    retVal.HashTable = this;
//    int count = 0;
//
//    while (count < this->capacity) {
//        if (this->status_arr[count] == 1) {
//            break;
//        }
//        count++;
//    }
//        retVal.index = count;
//        return retVal;
//}
//
//template <typename T>
//Iterator<T> HashTable<T>::end() {
//    // Create and iterator object
//    Iterator<T> retVal;
//    retVal.HashTable = this;
//    retVal.index = this->capacity;
//
//    return retVal;
//}
//
//template<typename T>
//pair<string, T>& Iterator<T>::operator*() {
//    return this->keyValue_arr->index;
//}
//
//template <typename T>
//bool Iterator<T>::operator!=(const Iterator<T>& rhs) const {
//    if (this->HashTable == rhs.HashTable && this->index == rhs.index)
//        return false;
//    else
//        return true;
//}
//
//template <typename T>
//Iterator<T> Iterator<T>::operator++() {
//
//    while (HashTable.status_arr[index] != 1) { 
//        if (index == (this->capacity - 1))
//            index = 0;
//        index++;
//    }
//    return *this;
//
//}

//End of not quite complete Iterator Section
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
Iterator<T> HashTable<T>::begin() {
    Iterator<T> retval;
    retval.hashTable = this;
    for (unsigned i = 0; i < this->capacity; i++) {
        if (this->status_arr[i] == 1) {
            retval.index = i;
            return retval;
        }
    }
    retval.index = this->capacity;
    return retval;
}

template<typename T>
Iterator<T> HashTable<T>::end() {
    Iterator<T> retval;
    retval.hashTable = this;
    retval.index = this->capacity;
    return retval;
}

template<typename T>
pair<string, T>& Iterator<T>::operator*() {
    return this->hashTable->keyValue_arr[this->index];
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T>& rhs) const { //not = return true, == return false
    return (!(this->hashTable == rhs.hashTable && this->index == rhs.index));


}

template<typename T>
Iterator<T> Iterator<T>::operator++() {
    while (this->index != this->hashTable->capacity) {
        this->index++;
        if (this->hashTable->status_arr[this->index] == 1) {
            return *this;
        }
    }
}


template <typename T>
HashTable<T>::HashTable() {
    status_arr = make_unique<int[]>(capacity);
    keyValue_arr = make_unique<pair<string, T>[]>(capacity);
    
    for (int i = 0; i < capacity; i++) {
        status_arr[i] = 0;
    }
}

template <typename T>
HashTable<T>::HashTable(const unsigned int customCapacity) {
    status_arr = make_unique<int[]>(customCapacity);
    keyValue_arr = make_unique<pair<string, T>[]>(customCapacity);

    for (int i = 0; i < capacity; i++) {
        status_arr[i] = 0;
    }

    capacity = customCapacity;
}

template <typename T>
HashTable<T>& HashTable<T>::operator=(HashTable<T>&& obj) noexcept {    //move assignment
    
    this->keyValue_arr = std::move(obj.keyValue_arr);
    this->status_arr = std::move(obj.status_arr);

    this->capacity = obj.capacity;
    this->count = obj.count;
    obj.count = 0;
    obj.capacity = 0;

    return *this;
}

template <typename T>
HashTable<T>::HashTable(HashTable<T>&& obj) {                           //move constructor

    this->keyValue_arr = std::move(obj.keyValue_arr);
    this->status_arr = std::move(obj.status_arr);

    this->capacity = obj.capacity;
    this->count = obj.count;
    obj.count = 0;
    obj.capacity = 0;
}

template <typename T>
void HashTable<T>::create(const string& key, const T& item) {           // L value

    int index = hash(key);

    if (((this->count + 1.0) / ((double)capacity)) >= 0.75) {
        HashTable temp(this->capacity * 2);

        for (int i = 0; i < this->capacity; i++) {
            if (status_arr[i] == 1) {
                temp.create(this->keyValue_arr[i].first, this->keyValue_arr[i].second);     
            }
        }
        *this = std::move(temp);
    }

    while (status_arr[index] == 1) { //status_arr[index] = 1, want to keep incrementing index. 
        if (index == (capacity - 1))
            index = 0;

        index++;
    }

    status_arr[index] = 1;
    this->keyValue_arr[index] = std::pair<string, T>(key, item); //exception found here
    this->count++;
}

template <typename T>
void HashTable<T>::create(const string& key, T&& item) {                // R Value

    int index = hash(key);

    if (((this->count + 1.0) / ((double)capacity)) >= 0.75) {
        //create new hash table object
        //size it to the current capacity, or invoking private constructor    
        HashTable temp(this->capacity * 2);

        //write a loop that iterates capacity times
        for (int i = 0; i < this->capacity; i++) {
            if (status_arr[i] == 1) {
                //call new hashtable create method
                //pass in the old hash table's key at this index
                //move in the old hash table's value at this index
                temp.create(this->keyValue_arr[i].first, std::move(this->keyValue_arr[i].second));
            }
        }
        //Once loop is finished, move the new hash table object back into *this.
        //*this.operator=(temp);
        *this = std::move(temp);    
    }

    while (status_arr[index] == 1) { 
        if (index == (capacity - 1))
            index = 0;

        index++;
    }  

    status_arr[index] = 1;
    this->keyValue_arr[index] = std::pair<string, T>(key, std::move(item));
    this->count++;
}

template <typename T>
T HashTable<T>::retrieve(const string& key) {
    int index = hash(key);
    int count = 0;

    while (count < capacity) {
        if (status_arr[index] == 1) {
            if (keyValue_arr[index].first == key) {
                return keyValue_arr[index].second;
            }

        }
        else if (status_arr[index] == 0) {
            throw 1;
        }

        if (index >= capacity) {
            index = 0;
        }

        index++;
        count++;
    }

    throw 1;
}

template <typename T>
T& HashTable<T>::operator[](const string& key) {
    int index = hash(key);
    int count = 0;

    while (count < capacity) {
        if (status_arr[index] == 1) {
            if (keyValue_arr[index].first == key) {
                return keyValue_arr[index].second;
            }
        }
        else if (status_arr[index] == 0) {
            throw 1;
        }

        index++;
        count++;

        if (index >= capacity) {
            index = 0;
        }
    }

    throw 1;
}

template <typename T>
bool HashTable<T>::exists(const string& key) {
    int index = hash(key);
    int count = 0;

    while (count < capacity) {
        if (status_arr[index] == 1) {
            if (keyValue_arr[index].first == key) {
                return true;
            }
           
        }
        else if (status_arr[index] == 0) {
            return false;
        }

        index++;
        count++;

        if (index >= capacity) {
            index = 0;
        }
    }

    return false;
}

template <typename T>
void HashTable<T>::remove(const string& key) {
    int index = hash(key);
    int count = 0;

    while (count < capacity) {
        if (status_arr[index] == 1) {
            if (keyValue_arr[index].first == key) {
                status_arr[index] = -1;
                return;
            }

        }
        else if (status_arr[index] == 0) {
            return;
        }

        index++;
        count++;

        if (index >= capacity) {
            index = 0;
        }
    }

    return;
}


//************************************************************
// Put HashTable consrtuctors and methods above here
//************************************************************
//Copyright 2021, Bradley Peterson, Weber State University, all rights reserved. (June 2021)

template <typename T>
unsigned int HashTable<T>::hash(const string& key) const {

  return std::hash<std::string>{}(key) % capacity;

}

template <typename T>
unsigned int HashTable<T>::getTotalCount() const {
  unsigned int count = 0;
  for (unsigned int i = 0; i < capacity; i++) {
    if (status_arr[i] == 1) {
      count++;
    }
  }
  return count;
}

template <typename T>
unsigned int HashTable<T>::getWorstClump() const {
  unsigned int clumpCount = 0;
  unsigned int maxClump = 0;
  for (unsigned int i = 0; i < capacity; i++) {
    if (status_arr[i] == 1) {
      clumpCount++;
    }
    else {
      if (clumpCount > maxClump) {
        maxClump = clumpCount;
        clumpCount = 0;
      }
    }
  }
  if (clumpCount > maxClump) {
    maxClump = clumpCount;
  }
  return maxClump;
}


//This helps with testing, do not modify.
template <typename T>
string NumberToString(T Number)
{
  stringstream ss;
  ss << Number;
  return ss.str();
}

//This helps with testing, do not modify.
bool checkEmpty(string testName, string whatItIs) {

  if (whatItIs != "") {
    cout << "Passed " << testName << ", the data was " << whatItIs << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << "   No data was found! " << endl;
    return false;
  }
}

//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else if (whatItShouldBe == "") {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was '" << whatItIs << endl << "'     Output should have been blank" << endl;
    return false;

  }
  else {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
    return false;
  }
}

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
    return false;
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
  }
}

//This helps with testing, do not modify.
void testSimpleIntHash() {
  //cout << "|||### You need to comment in testSimpleIntHash() tests one-by-one###|||" << endl;

  HashTable<string> myHash;

  //Test #1, add "Monster Mash" into our hash with a key of 619238.  Try to retrieve it.
  string myString = "Monster Mash";

  myHash.create("619238", myString);
  checkTest("testSimpleIntHash #1", "Monster Mash", myHash.retrieve("619238"));

  //Test #2, attempt to get the Monster Mash using the operator[] code.
  checkTest("testSimpleIntHash #2", "Monster Mash", myHash["619238"]);

  //Test #3, attempt to change the value at this location:
  myHash["619238"] = "Graveyard Smash";

  checkTest("testSimpleIntHash #3", "Graveyard Smash", myHash["619238"]);

  //Test #4,
  //See if we can find it
  if (myHash.exists("619238")) {
    checkTest("testSimpleIntHash #4", "", "");
  }
  else {
    checkTest("testSimpleIntHash #4", "This test should have found an item with key \"619238\"", "This test did NOT find an item with key \"619238\"");
  }

  ////Test #5, see if we can find something that doesn't exist yet.
  if (myHash.exists("1234")) {
    checkTest("testSimpleIntHash #5", "This test should NOT have found an item with key \"1234\".", "This test found an item with key \"1234\"");
  }
  else {
    checkTest("testSimpleIntHash #5", "", "");
  }

  //Test #6, removing it from the hash
  myHash.remove("619238");
  if (myHash.exists("619238")) {
    checkTest("testSimpleIntHash #6", "This test should NOT have found an item with key \"619238\".", "This test found an item with key \"619238\"");
  }
  else {
    checkTest("testSimpleIntHash #6", "", "");
  }

  //Add add in "The Monster Hash" values.  
  myHash.create("13", "flash");
  myHash.create("25", "vampires feast");
  myHash.create("101", "humble abodes");
  myHash.create("77", "Transylvania Twist");
  myHash.create("12", "zombies");
  myHash.create("42", "Wolfman");
  myHash.create("97", "Dracula");
  myHash.create("123", "Dracula's son");
  myHash.create("500", "coffin-bangers");

  //Attempt to retrieve some
  checkTest("testSimpleIntHash #7", "zombies", myHash.retrieve("12"));
  checkTest("testSimpleIntHash #8", "Transylvania Twist", myHash.retrieve("77"));
  checkTest("testSimpleIntHash #9", "Dracula's son", myHash.retrieve("123"));

  //Now count up how many are in there
  checkTest("testSimpleIntHash #10", 9, myHash.getTotalCount());

  //Now just verify that they aren't clumping up badly.
  int worst = 0;
  worst = myHash.getWorstClump();
  if (worst > 7) {
    cout << "***Failed testSimpleIntHash #11!  There exists a clump of " << worst << " consecutive items, it shouldn't be worse than 7." << endl;
  }
  else {
    cout << "Passed testSimpleIntHash #11.  Your worst clump was " << worst << " items." << endl;
  }

}

void testRehashing() {
  //cout << "|||### You need to comment in testRehashing() tests one-by-one###|||" << endl;

  HashTable<string> myHash;
  
  string stringToMove = "Invisible man";
  myHash.create("11111", std::move(stringToMove));
  checkTest("testRehashing #1", "", stringToMove);
  checkTest("testRehashing #2", "Invisible man", myHash["11111"]);
  myHash.remove("11111");
  checkTest("testRehashing #3", 0, myHash.getTotalCount());

  //Throw in more items.
  int key = 0;
  stringstream out;
  for (unsigned int i = 0; i < 10000; i++) {

    //this next part just helps create some variation in generated W#s...
    if (i % 2 == 0) {
      key += 17;
    }
    else if (i % 3 == 0) {
      key += 23;
    }
    else if (i % 5 == 0) {
      key += 51;
    }
    else if (i % 7 == 0) {
      key += 13;
    }
    else {
      key += 71;
    }
    //convert an int to a string via help from the stringstream class
    out.str("");
    out << key;
    string temp = out.str();

    out.str("");
    out << "a-" << i;
    string value = out.str();
    myHash.create(temp, value); //Just add a bunch of letter a's
  }

  //Make sure they all go in there. 
  checkTest("testRehashing #4", 10000, myHash.getTotalCount());

  //Make sure the capacity is large enough
  checkTest("testRehashing #5", 20480, myHash.getNumBuckets());

  //Verify one of the values in the hash table.
  checkTest("testRehashing #6", "a-2345", myHash.retrieve("76154"));

  int worst = myHash.getWorstClump();
  if (worst > 1000) {
    cout << "Failed testRehashing #7!  There exists a clump of " << worst << " consecutive items, it shouldn't be worse than 1000." << endl;
  }
  else {
    cout << "Passed testRehashing #7.  Your worst clump was " << worst << " items." << endl;
  }

  //Remove the key "184275".
  myHash.remove("184275");
  if (myHash.exists("184275")) {
    checkTest("testRehashing #8", "This test should NOT have found an item with key \"184275\".", "This test found an item with key \"184275\"");
  }
  else {
    checkTest("testRehashing #8", "", "");
  }
  //There should be one less value now
  checkTest("testRehashing #9", 9999, myHash.getTotalCount());

}

void testHashOfObjects() {
  //cout << "|||### You need to comment in testHashOfObjects() tests one-by-one###|||" << endl;

  //Create a HashTable. We want this to be a hash table with int keys, string object values,
  //And we also supply the hash function we want to use for integers..

  HashTable<Product> myHash;

  //Test #1, add in a studentObject.  Try to retrive it.
  Product tempProduct;
  tempProduct.setCost(5);
  tempProduct.setName("Silly string");
  myHash.create("12341-51231", tempProduct);
  checkTest("testHashOfObjects #1", "Silly string", myHash.retrieve("12341-51231").getName());

  //Test #2, attempt to get the product using its ID code
  checkTest("testHashOfObjects #2", "Silly string", myHash["12341-51231"].getName());

  //Test #3, see what happens if two products have the same ID code.  This should overwrite the former.
  tempProduct.setCost(18);
  tempProduct.setName("Novelty foam hat");
  myHash["12341-51231"] = tempProduct;
  checkTest("testHashOfObjects #3", "Novelty foam hat", myHash["12341-51231"].getName());

  //Test #4,
  //See if we can find it
  if (myHash.exists("12341-51231")) {
    checkTest("testHashOfObjects #4", "", "");
  }
  else {
    checkTest("testHashOfObjects #4", "This test should have found an item with key 12341-51231", "This test did NOT find an item with key 12341-51231");
  }

  //Test #5, see if we can find something that doesn't exist yet.
  if (myHash.exists("56756-75675")) {
    checkTest("testHashOfObjects #5", "This test should NOT have found an item with key 56756-75675.", "This test found an item with key56756-75675");
  }
  else {
    checkTest("testHashOfObjects #5", "", "");
  }

  //Test #6, removing it from the hash
  myHash.remove("12341-51231");
  if (myHash.exists("12341-51231")) {
    checkTest("testHashOfObjects #6", "This test should NOT have found an item with key 12341-51231.", "This test found an item with key 12341-51231");
  }
  else {
    checkTest("testHashOfObjects #6", "", "");
  }

}


//This helps with testing, do not modify.
void testIteration() {

  cout << "         |||### You need to comment in testIteration() tests one-by-one###|||" << endl;
  cout << " ||||||| I didn't fully test my iterators, so this section remains incomplete |||||||" << endl;

  HashTable<int> someHash;
  someHash.create("1", 1);
  someHash.create("2", 4);
  someHash.create("3", 9);
  someHash.create("4", 16);
  someHash.create("5", 25);
  someHash.create("6", 36);
  someHash.create("7", 49);

  Iterator<int> iter = someHash.begin();

  cout << "The first item.  key: " << (*iter).first << " value " << (*iter).second << endl;

  // Now test operator!=
  auto anotherIter = someHash.begin();

  if (iter != anotherIter) {
    cout << "****** Failed testIteration #1 ****** " << endl << "   The two iteraters held the same data." << endl;
  }
  else {
    cout << "Passed testIteration #1" << endl;
  }
  ++iter; //move it to the second item

  if (iter != anotherIter) {
    cout << "Passed testIteration #2" << endl;
  }
  else {
    cout << "****** Failed testIteration #2 ****** " << endl << "     The two iteraters held different data." << endl;
  }

  cout << "The second item.  key: " << (*iter).first << " value " << (*iter).second << endl;

  for (int i = 2; i < 7; i++) {
    ++iter;
  }

  // Display the last item
  cout << "The last item.  key: " << (*iter).first << " value " << (*iter).second << endl;

  // Go to the "past the end"
  ++iter;

  auto endIter = someHash.end();
  if (iter != endIter) {
    cout << "****** Failed testIteration #3 ****** " << endl << "   The two iteraters are the same, and != should have returned false." << endl;
  }
  else {
    cout << "Passed testIteration #3" << endl;
  }

  int arr[7];
  int i = 0;

  for (auto& somePair : someHash) {
    cout << "key: " << somePair.first << " value " << somePair.second << " ";
    arr[i] = somePair.second;
    i++;
  }



  cout << endl;
  std::sort(&arr[0], &arr[7]);
  if (arr[0] == 1 && arr[1] == 4 && arr[2] == 9 && arr[3] == 16 && arr[4] == 25 && arr[5] == 36 && arr[6] == 49) {
    cout << "Passed testIteration #4" << endl;
  }
  else {
    cout << "****** Failed testIteration #4 ****** " << endl << "   The hashtable iteration didn't find all values." << endl;
  }
  cout << endl;

}

//This helps with testing, do not modify.
void testHashofHashes() {
  //cout << "|||### You need to comment in testHashofHashes() tests one-by-one###|||" << endl;

  HashTable< HashTable<int> > studentAssignments;
  studentAssignments.create("Alice", HashTable<int>());

  HashTable<int> tempHash2;
  studentAssignments.create("Bob", HashTable<int>());

  HashTable<int> tempHash3;
  studentAssignments.create("Karl", HashTable<int>());

  //Give alice some assignment scores
  studentAssignments["Alice"].create("1", 73);
  studentAssignments["Alice"].create("2", 65);
  studentAssignments["Alice"].create("4", 91);
  //Ensure it went in
  checkTest("testHashofHashes #1", 65, studentAssignments["Alice"]["2"]);

  //And Bob
  studentAssignments["Bob"].create("1", 90);
  studentAssignments["Bob"].create("3", 84);
  studentAssignments["Bob"].create("4", 99);

  //And Karl
  studentAssignments["Karl"].create("1", 92);
  studentAssignments["Karl"].create("2", 92);
  studentAssignments["Karl"].create("3", 87);
  studentAssignments["Karl"].create("4", 10);

  //Now find the average of assignment 4 scores
  int average = (studentAssignments["Alice"]["4"] + studentAssignments["Bob"]["4"] + studentAssignments["Karl"]["4"]) / 3;
  checkTest("testHashofHashes #2", 66, average);

  //int scores = 0;
  //for (auto& student : studentAssignments) {
  //  for (auto& assignmentScore : student.second) {
  //    scores += assignmentScore.second;
  //    cout << assignmentScore.second << " ";
  //  }
  //}
  //cout << endl;
  //if (scores != 783) {
  //  cout << "Failed testHashofHashes #3!  Tried iterating and counting all the scores of all values.  Got " << scores << " instead of 783" << endl;
  //}
  //else {
  //  cout << "Passed testHashofHashes #3." << endl;
  //}
}

void pressEnterToContinue() {
  cout << "Press any key to continue...";

  cout << endl;
}

int main() {

  testSimpleIntHash();
  //pressEnterToContinue();

  testRehashing();
  //pressEnterToContinue();

  testHashOfObjects();
  //pressEnterToContinue();

  testIteration();
  //pressEnterToContinue();

  testHashofHashes();
  // pressEnterToContinue();



  pressEnterToContinue();
  return 0;
}
