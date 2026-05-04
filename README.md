# NanoKV

NanoKV is a C++ command-line project for exploring fundamental data-structure implementations from first principles.

The repository centers on an in-memory key-value store backed by custom hash-table implementations, and also includes linked-list, stack, and queue modes exposed through a simple interactive REPL. The project is best understood as a compact systems-programming exercise focused on collision resolution, dynamic resizing, pointer-based structures, and basic container ergonomics.

## Highlights

- Open-addressing hash table with selectable probing strategies:
  - Double hashing
  - Linear probing
  - Quadratic probing
- Separate chaining hash table using `std::list`
- Tree-backed key-value modes:
  - Binary search tree (BST)
  - AVL tree
  - Trie
- Automatic resizing for the open-addressing table based on load factor
- Prime-sized table growth to support stable probing behavior
- Interactive CLI for insert, lookup, delete, and structure inspection
- Additional educational implementations for:
  - Singly linked list
  - Doubly linked list
  - Circular linked list
  - Stack
  - Queue

## Project Scope

NanoKV is an educational in-memory project, not a production database. It does not provide persistence, replication, concurrency control, durability guarantees, or a network protocol. Its value is in the implementation itself: understanding how core data structures behave under different design choices.

## Repository Layout

```text
.
├── include/    # Public headers
├── src/        # Implementations and entry point
├── build/      # Compiled binary output
├── Makefile
└── README.md
```

## Build

### Requirements

- A C++ compiler such as `g++` or `clang++`
- `make`

### Compile

```bash
make clean
make
```

The executable is produced at `./build/nanokv`.

## Running NanoKV

If no argument is provided, NanoKV starts in open-addressing mode with double hashing.

```bash
./build/nanokv
```

You can also select a specific mode explicitly:

| Command | Mode |
| :--- | :--- |
| `./build/nanokv DOUBLE` | Open addressing with double hashing |
| `./build/nanokv LINEAR` | Open addressing with linear probing |
| `./build/nanokv QUADRATIC` | Open addressing with quadratic probing |
| `./build/nanokv CHAINING` | Hash table with separate chaining |
| `./build/nanokv LIST` | Singly linked list |
| `./build/nanokv DOUBLE_LIST` | Doubly linked list |
| `./build/nanokv CIRCULAR_LIST` | Circular linked list |
| `./build/nanokv STACK` | Stack |
| `./build/nanokv QUEUE` | Queue |
| `./build/nanokv BST` | Binary search tree (KV store) |
| `./build/nanokv AVL` | AVL tree (KV store) |
| `./build/nanokv TRIE` | Trie (KV store) |

## CLI Usage

### Key-Value Modes

Available in:

- `DOUBLE`
- `LINEAR`
- `QUADRATIC`
- `CHAINING`
- `LIST`
- `DOUBLE_LIST`
- `CIRCULAR_LIST`
- `BST`
- `AVL`
- `TRIE`

Commands:

```text
SET <key> <value>
GET <key>
DEL <key>
DISPLAY
EXIT
```

Example:

```text
=== NanoKV ===
Commands: SET <key> <value> | GET <key> | DEL <key> | DISPLAY | EXIT

db> SET user:1 Alice
OK
db> SET user:2 Bob
OK
db> GET user:1
"Alice"
db> DISPLAY
Current State:
...
db> DEL user:2
OK
db> EXIT
```

`DISPLAY` prints a simple tree view for tree-backed modes (BST/AVL/TRIE), for example:

```text
db> DISPLAY
Current State:
\-- [30: a]
    |-- [20: b]
    |   \-- [10: d]
    \-- [40: c]
```

### Stack Mode

Commands:

```text
PUSH <value>
POP
TOP
SIZE
DISPLAY
EXIT
```

Example:

```text
=== NanoKV (Stack Mode) ===
Commands: PUSH <value> | POP | TOP | SIZE | DISPLAY | EXIT

stack> PUSH Hello
OK
stack> PUSH World
OK
stack> TOP
"World"
stack> DISPLAY
Current Stack State:
Stack (Top to Bottom):
  [1]: World <- TOP
  [0]: Hello
```

### Queue Mode

Commands:

```text
ENQUEUE <value>
DEQUEUE
FRONT
SIZE
DISPLAY
EXIT
```

Example:

```text
=== NanoKV (Queue Mode) ===
Commands: ENQUEUE <value> | DEQUEUE | FRONT | SIZE | DISPLAY | EXIT

queue> ENQUEUE Hello
OK
queue> ENQUEUE World
OK
queue> FRONT
"Hello"
queue> DISPLAY
Current Queue State:
Queue (Front to Back):
  [0]: Hello <- FRONT
  [1]: World <- BACK
```

## Implementation Notes

### Open Addressing

The open-addressing hash table stores items directly in the table array and resolves collisions through probe sequences. The implementation supports:

- load-factor-driven growth and shrink operations
- tombstone handling for deletions
- switchable probing strategies through `ProbingStrategy`

### Chaining

The chaining variant maps each bucket to a linked list of entries, which simplifies deletion semantics and handles collisions differently from the open-addressing implementation.

### Auxiliary Structures

The linked lists, stack, and queue are included as standalone implementations for comparison and practice. They are exposed through the same executable to keep the project easy to explore from a terminal.

## Example Integration

NanoKV’s components can also be used directly in C++ code.

```cpp
#include <string>
#include "hash_table.h"
#include "chaining_hash_table.h"
#include "stack.h"
#include "queue.h"

int main() {
  HashTable open_table(ProbingStrategy::DOUBLE_HASHING);
  open_table.insert("language", "C++");

  ChainingHashTable chained_table(50);
  chained_table.insert("mode", "chaining");

  Stack<std::string> stack(16);
  stack.push("alpha");

  Queue<std::string> queue(16);
  queue.enqueue("beta");

  return 0;
}
```

## Current Limitations

- No automated test suite yet
- No persistence layer or on-disk format
- No concurrency support
- No benchmarking harness
- Build configuration is intentionally minimal

## License

This project is available under the [MIT License](LICENSE).
