# 🚌 Urban Transport Network Simulator

This project simulates a simplified public transportation network for a city using C++. It uses graphs to model stations and lines, allowing users to compute shortest paths, analyze connectivity, and explore the transport system structure.

![image](https://github.com/user-attachments/assets/573a298a-1ba7-4728-a320-12e3462b4bb1)


---

## 📌 Overview

### 🎯 Goal
To develop a C++ application that models a public transport network and allows users to:
- Load stations and lines from input files.
- Find optimal paths between stations.
- Analyze the structure and connectivity of the network.

### 🧭 Scope
The application supports:
- Parsing input files defining stations and lines.
- Constructing a directed graph for the network.
- Performing BFS and DFS for route-finding.
- Generating output reports with optimal paths and line transitions.
- Handling errors in input files and reporting issues.

---

## 🛠️ Building and Running

### Prerequisites
- C++ compiler (supporting C++11 or later)
- CMake (optional but recommended)

## 📂 Input File Format

- stajalista.txt: Defines stations  
154 Aleksandra Karadjordjevica
578 Bulevar oslobodjenja
23 Cetinjska
1024 Despota Stefana
103 Evgenija Onjegina
123 Faradejeva
422 Gornji grad
  
- linije.txt: Defines transport lines  
12 [05:30-23:30#15] 154 578 123 422 3112 99 12 1221 1212  
MINI [06:30-22:00#30] 154 578 23 1024 111 1221 1212  
81L [06:30-22:00#20] 154 578 23 1024 103 123 422 3112 219 1 312

## 🧪 Example Usage

Sample query: "Find best route from `154` to `422`"
Optimal route:
Line 12: 154 → 578 → 123 → 422
Estimated travel time: 15 minutes
