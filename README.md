# Logic-Simulator
### A simple logic simulator that provides a mechanism to run and simulate logic circuits then find the desired outputs for different designs.

### Input Format
![gates](https://user-images.githubusercontent.com/81903080/192406733-f2eeaa70-a0ad-440d-9d4b-169f610beb34.png)

The input follows these formats:

#### gate type (such as AND/OR gate)
#### The inputs and output symbols
#### Write "SET" values to the inputs (either 0 or 1)
#### Write "SIM" to start simulation
#### Write "OUT" to view the output of a specific node or "OUT ALL" to view all nodes' values

### Sample Input 
#### AND A B D
#### OR C D E
#### SET A 1
#### SET B 0 
#### SET C 1
#### SIM 
#### OUT E
#### OUT ALL

### Sample Output 0
#### E: 1
#### A: 1
#### B: 0
#### D: 0
#### C: 1
#### E: 1
