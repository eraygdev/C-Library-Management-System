📚 Library Management System (C-Archive)


💻 How to Run
This project is modular, so all source files must be compiled together.

Step 1: Download Files: Clone this repository or download it as a ZIP file.
Step 2: Prepare Compiler: Make sure you have a C compiler such as GCC or MinGW installed on your system.
Step 3: Running Options:

  * **VS Code**: Open the project folder with VS Code. Compile `main.c`, `functions.c`, and `library.c` through the Terminal. Tip: Make sure the C/C++ extension is installed.
  * **Code::Blocks**: Open the Library_System.cbp file. Click the Build and Run button in the top menu.

Terminal / CMD: You can compile all files at once by typing this command:
  `gcc main.c functions.c library.c -o library_system`
  `./library_system`

🛠️ Core Capabilities
Smart Search Logic: User-friendly search engine that ignores uppercase and lowercase differences.
Binary Persistence: Backend structure that saves data in `.dat` format (binary) for fast and secure reading and writing.
Safe Memory Handling: A solid foundation built on memory management and buffer safety.

📂 Project Structure
This project is developed in a modular structure following software architecture discipline:
Main File: `main.c` is the entry point and main loop of the program.
Backend Logic: `functions.c` and `library.c` are where backend logic and library operations are managed.
Header File: `library.h` forms the skeleton of the entire system.

🚀 Roadmap (Future Plans)
Advanced Sorting: Listing books by year or page count.
Borrowing System: Book borrowing and return tracking mechanism.
Authorization: Admin login panel and security layer.
