# Multicore Genome Sequencing

This project is a multicore implementation of genome sequencing. It utilizes multiple cores to speed up the sequencing process, making it efficient and scalable for large datasets.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Folder Structure](#folder-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction
Genome sequencing is a method used to determine the complete DNA sequence of an organism's genome. This project leverages multicore processing to enhance the performance of genome sequencing tasks. By distributing the workload across multiple cores, the sequencing process becomes significantly faster and more efficient.

## Features
- Multicore processing for enhanced performance
- Efficient scheduling of sequencing tasks
- Modular code structure for ease of maintenance and expansion

## Folder Structure
The project is organized into the following directories and files:

project_root/
├── include/
│ └── main.h
├── search/
│ ├── sequence.c
│ ├── sequence.h
│ ├── search.h
│ └── search.c
├── threading/
│ ├── scheduler.c
│ └── scheduler.h
└── main.c


- **include/main.h**: Header file for the main program.
- **search/sequence.c**: Implementation of sequence handling functions.
- **search/sequence.h**: Header file for sequence handling functions.
- **search/search.h**: Header file for search functions.
- **search/search.c**: Implementation of search functions.
- **threading/scheduler.c**: Implementation of the task scheduler.
- **threading/scheduler.h**: Header file for the task scheduler.
- **main.c**: Main program file.