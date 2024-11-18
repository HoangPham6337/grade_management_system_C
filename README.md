# Overview
This repository hosts the source code for a GPA Management Program written in C. The program provides an interactive console-based user interface for managing academic courses and grades. Users can add, edit, or remove courses, calculate and predict GPA, and adjust their academic goals. The program ensures data persistence via file operations, making it a reliable tool for tracking and managing academic performance.

# Key Features
- Menu-Driven Interface:
    - Add new courses and corresponding marks.
    - Display all course information with calculated GPA and ECTS credits.
    - Edit or remove existing course details.
    - Predict GPA required to meet a targeted goal.
    - Update the targeted GPA.
    - Delete all stored data.
    - Exit with the option to save data.
- Data Handling:
    - Uses a linked list (List) to dynamically store course information.
    - Reads from and writes to a persistent data file (data.dat).
    - Supports sorting and GPA calculations for accurate academic tracking.
- Memory Management:
    - Allocates memory dynamically and cleans up resources to prevent memory leaks.
    - Handles failures gracefully, with error messages for allocation or file operation issues.

# How It Works
- **Initialization:**
    - On startup, the program attempts to load existing course data from data.dat.
    - If no data is found, a new course list is initialized with a default targeted GPA.
- **Interactive User Interface:**
    - The UILoop function handles the program's menu-driven workflow, allowing users to select and execute various operations.
- **Core Functionalities:**
    - Add new courses dynamically with marks and credits.
    - View all course details, including GPA and total ECTS credits.
    - Edit course details or delete specific courses by name.
    - Predict the required GPA to achieve a targeted GPA.
    - Change the targeted GPA based on user goals.
    - Optionally delete all course data.
- **Cleanup and Data Persistence:**
    - Before exiting, the program saves the updated course list back to data.dat unless explicitly deleted.
    - Frees dynamically allocated memory to ensure efficient resource usage.
- **File Structure:**
    - `bin/`: Contains compiled binaries for the program.
    - `data.dat`: Stores serialized course and GPA data for persistence.
    - `lib/`: Includes reusable libraries for modular code organization.
    - `obj/`: Contains intermediate object files generated during compilation.
    - `Makefile`: Automates the build process, simplifying compilation and linking.

# Build the program
Run `make` to build.

Run `make clean` to clear the object and executable files.
