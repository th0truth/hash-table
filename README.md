# NanoKV

A high-performance, in-memory key-value data store implemented entirely from scratch in C++. 

NanoKV provides a robust implementation of a dynamically resizing hash table, utilizing open addressing with pluggable probing strategies for efficient collision resolution. Built without reliance on standard library container abstractions, this project serves as a foundational example of low-level data structure design, manual memory management, and algorithmic optimization in modern C++.

## Architecture & Capabilities

*   **Custom Hash Implementation:** Features a custom string hashing algorithm implementing Horner's method for efficient and uniform key distribution.
*   **Pluggable Probing Strategies (New!):** Supports multiple collision resolution techniques under Open Addressing. You can easily switch between them to observe their behavior under different load conditions:
    *   **Double Hashing (Default):** Uses a secondary hash function for the step size, virtually eliminating primary clustering and ensuring efficient probe sequences.
    *   **Linear Probing:** Checks sequential slots to resolve collisions. Simple, but can demonstrate primary clustering.
    *   **Quadratic Probing:** Uses a quadratic function to determine the step size, reducing primary clustering compared to linear probing.
*   **Dynamic Auto-Resizing:** Actively monitors the load factor and automatically resizes the underlying array (expanding at >70% load, shrinking at <10% load) to maintain optimal $O(1)$ amortized time complexity.
*   **Prime-Sized Buckets:** Automatically calculates and enforces prime number capacities for the bucket array, a mathematical requirement to guarantee that the probe sequences can visit every available slot.
*   **Complete CRUD Operations:** Supports fully functional Create, Read, Update, and Delete operations via an interactive shell.
*   **RAII Memory Management:** Leverages C++ class encapsulation and standard library strings to ensure safe memory allocation and prevent leaks during table destruction and resizing operations.

## Building and Installation

### Prerequisites
*   A C++11 compatible compiler (e.g., `g++`, `clang++`)
*   `make` build system

### Compilation
Clone the repository and compile the source code using the provided Makefile:

```bash
git clone https://github.com/th0truth/nanokv.git
cd nanokv

make clean
make
```

## Usage

NanoKV includes an interactive command-line interface, operating similarly to a lightweight Redis shell. 

To start the interface, execute the compiled binary:
```bash
./build/nanokv
```

### Interactive Shell Commands

```text
=== NanoKV ===
Commands: SET <key> <value> | GET <key> | DEL <key> | EXIT

db> SET user:1 Alice
OK
db> SET user:2 Bob
OK
db> GET user:1
"Alice"
db> DEL user:1
OK
db> GET user:1
(null)
db> EXIT
```

## Integration Example

NanoKV can also be integrated directly into other C++ projects by including the core data structure. You can optionally specify the probing strategy when initializing the database.

```cpp
#include <iostream>
#include <string>
#include "hash_table.h"

int main() {
  // Initialize the data store with the default strategy (DOUBLE_HASHING)
  HashTable db;
  
  // Alternatively, you can explicitly set the strategy:
  // HashTable db_linear(ProbingStrategy::LINEAR);
  // HashTable db_quadratic(ProbingStrategy::QUADRATIC);

  // Create records
  db.insert("service_status", "initializing");
  db.insert("max_connections", "100");

  // Update existing records
  db.insert("service_status", "running");

  // Retrieve records
  std::string* status = db.search("service_status");
  if (status) {
    std::cout << "Status: " << *status << std::endl; 
  }

  // Delete records
  db.remove("max_connections");

  return 0;
}
```
