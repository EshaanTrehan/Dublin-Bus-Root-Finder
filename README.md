
# Dublin-Bus-Root-Finder 🚌

**Dublin-Bus-Root-Finder** is a C-based application that facilitates the identification of the shortest bus route between two specified stops within the Dublin Bus network. Using graph-based algorithms and structures, the project offers an intuitive way to navigate the intricate web of bus routes.

## 🚀 Features

- Representation of the Dublin Bus network as a graph, with stops as vertices and routes as edges.
- Efficient shortest-path calculations using Dijkstra's algorithm.
- Ability to load route and stop data from CSV files.
- Clear and concise output displaying the shortest route between specified bus stops.

## 📁 File Structure

- 📄 `edges.csv`: Data representing paths (or edges) between bus stops.
- 📄 `vertices.csv`: Data representing individual bus stops (or vertices).
- 📄 `t2.c`: Core implementation of the project's logic.
- 📄 `t2.h`: Header declarations associated with `t2.c`.
- 📄 `t2_test.c`: User interface and testing logic.
- 📜 `a.exe` & `t2.exe`: Pre-compiled executables.

## 🔧 Setup & Execution

1. Compile the source files using a C compiler. For instance:
   ```bash
   gcc t2.c t2_test.c -o bus_route_finder
   ```
2. Run the compiled executable:
   ```bash
   ./bus_route_finder vertices.csv edges.csv
   ```
3. Follow the on-screen prompts to input the starting and destination bus stop numbers.
4. The application will showcase the shortest route between the specified stops.

## 🧠 Core Concepts

- **Data Structures**: The bus network is represented as a graph. A matrix-based representation is used to store bus routes.
- **Algorithm**: Dijkstra's algorithm, known for its efficiency in pathfinding, is employed to determine the shortest route between two bus stops.

## 🧪 Testing

1. Compile the `t2_test.c` file separately for standalone tests.
2. Run the test executable, supplying the paths to `vertices.csv` and `edges.csv` as arguments.
3. Input the desired starting and destination bus stops as directed.
4. The test will validate the program's ability to correctly identify the shortest path.
5. 
