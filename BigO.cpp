#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::unique_ptr;
using std::make_unique;
using std::string;

template <typename T>
class BaseSort {
public:
    BaseSort(const string& sortName, const unsigned int capacity);
    string getName() { return sortName; }
    void loadRandomValues();
    void printValues() const;
    void verifySort() const;
    virtual void runSort() = 0; // Pure virtual function.  It makes BaseSort **abstract**                              
protected:
    string sortName;
    unique_ptr<T[]> arr;
    unsigned int capacity{ 0 };
};

template <typename T>
BaseSort<T>::BaseSort(const string& sortName, const unsigned int capacity) {
    this->sortName = sortName;
    this->capacity = capacity;
    this->arr = make_unique<T[]>(capacity);
}

template <typename T>
void BaseSort<T>::loadRandomValues() {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, UINT32_MAX);

    for (unsigned int i = 0; i < capacity; ++i) {
        this->arr[i] = distrib(gen);
    }
}

template <typename T>
void BaseSort<T>::printValues() const {
    if (capacity < 50) {
        for (unsigned int i = 0; i < capacity; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}

template <typename T>
void BaseSort<T>::verifySort() const {
    for (unsigned int i = 0; i < capacity - 1; i++) {
        if (arr[i + 1] < arr[i]) {
            cout << "Not sorted at index: " << (i + 1) << endl;
            return;
        }
    }
    cout << "Sorted!" << endl;
}

template <typename T>
class Bubble : public BaseSort<T> {
public:
    Bubble(const unsigned int capacity) : BaseSort<T>("Bubble", capacity) {};
    void runSort();
private:
};

template <typename T>
void Bubble<T>::runSort() {

    for (unsigned int round = 0; round < this->capacity - 1; round++) {
        for (unsigned int i = 0; i < this->capacity - 1 - round; i++) {
            if (this->arr[i + 1] < this->arr[i]) {
                T temp = this->arr[i];
                this->arr[i] = this->arr[i + 1];
                this->arr[i + 1] = temp;
            }
        }
    }
}

template <typename T>
class Selection : public BaseSort<T> {
public:
    Selection(const unsigned int capacity) : BaseSort<T>("Selection", capacity) {};
    void runSort();
private:
};

template <typename T>
void Selection<T>::runSort() {
    // The outer loop's job is to...
    // Each time the outer loop iterators, it works with the leftmost/unsorted index value
    for (unsigned int i = 0; i < this->capacity - 1; i++) {
        // The inner loop's job is to...  
        // Compare the current index to the rest of the unsorted region
        for (unsigned int j = i + 1; j < this->capacity; j++) {
            // We have an i (the index we hope to sort) and a j (a candidate to check)
            if (this->arr[j] < this->arr[i]) {
                T temp = this->arr[i];
                this->arr[i] = this->arr[j];
                this->arr[j] = temp;
            }
        }
    }
};

template <typename T>
class Insertion : public BaseSort<T> {
public:
    Insertion(const unsigned int capacity) : BaseSort<T>("Insertion", capacity) {};
    void runSort();
private:
};

template <typename T>
void Insertion<T>::runSort() {
    // The outer loop's job is to...
    // Obtain the leftmost unsorted value, iterates one index to the right each round.  Starts at 1
    for (unsigned int i = 1; i < this->capacity; i++) {
        // The inner loop's job is to...  
        // Take the leftmost unsorted value, walk to the left (back to index 0), swapping along the way until
        // no swaps are needed, or until we get to index 0.      
        unsigned int j = i;
        while (j > 0 && this->arr[j] < this->arr[j - 1]) {
            T temp = this->arr[j];
            this->arr[j] = this->arr[j - 1];
            this->arr[j - 1] = temp;
            j--;
        }
    }
};

template <typename T>
void runMySort(BaseSort<T>&& sortObj) {
    cout << "Running sort: " << sortObj.getName() << endl;
    sortObj.loadRandomValues();
    sortObj.printValues();

    auto t1 = std::chrono::high_resolution_clock::now();
    sortObj.runSort();
    auto t2 = std::chrono::high_resolution_clock::now();

    sortObj.printValues();
    sortObj.verifySort();
    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
    std::cout << "Sort completed in " << fp_ms.count() << " milliseconds" << endl;


}

int main() {
    runMySort(Bubble<int>(50000));
    runMySort(Selection<int>(50000));
    runMySort(Insertion<int>(50000));

    cin.get();
    return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <thread>
#include <chrono>
#include <random>

using std::thread;
using std::cout;
using std::cin;
using std::endl;

uint8_t* arr{ nullptr };
unsigned int N{ 0 };
unsigned int numBuckets{ 0 };
unsigned int count{ 0 };

void loadArray() {
    arr = new uint8_t[N];
}

void loadRandomNumbers() {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<unsigned int> distrib(0, 9);

    for (unsigned int i = 0; i < N; ++i) {
        arr[i] = distrib(gen);
    }
}
void countSixes() {
    for (unsigned int i = 0; i < N; i++) {
        if (arr[i] == 6) {
            count++;
        }
    }
}

int main() {

    N = 100'000'000;

    loadArray();
    loadRandomNumbers();

    auto t1 = std::chrono::high_resolution_clock::now();
    // Create thread tracking objects. These are NOT threads themselves. They just track the threads
    thread* threads = new thread[numThreads];

    //Fork to create numThreads threads starting their life in countSixes();
    threads[0] = thread(countSixes);
    for (unsigned int i = 0; i < numThreads; i++) {
        threads[i] = thread(countSixes);
    }

    //Join the child threads back to main
    for (unsigned int i = 0;)

    countSixes();
    delete[] threads;
    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
    std::cout << "Sort completed in " << fp_ms.count() << " milliseconds" << endl;


    cout << "Counted " << count << " sixes" << endl;

    cin.get();
    return 0;
}

/*
* Get single thread working befor attempting this. 
* 
* 
thread go to bucket number and push back in that value
Big(0n)

2 
loop for every bucket
for each bucket sort through one vector
Parrallelized?
every thread sorts a bucket.
Use ticketing system to solve 12 threads only for x amount of buckets problem
Should all be inside step 2 (just like sixes) 
Copy almost all we've done already in here
Must do a fork and join in step2(); under voidBucketSort
Must also use thread tracker objects and delete in highlighted step 2
There is a currBucket, that could be your master ticket number
Want to declare variables use threadLocalBucket
Count has no relation to homework, don't bring it in.
Obtain currentWorkBucket
incrementing currentWorkBucket
Don't use start or end index
Simply call sortOneVector and pass in the relevant bucket. Sort for you, ticketing system will while around. 

3 
take each bucket and write val back out to output array


test code against a high performance server once done
Go to icarus, or use a VPN,

Has a 64 code machine. Copy code onto the server and see how fast it will run. Provide screenshots that you got it working 
on the server, with times included. 


*/