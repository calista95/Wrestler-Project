# Wrestler-Project

# Description: 

This program reads from a user-input file which contains a number of wrestlers, a list of wrestler names, a number of pairings, and the pairings between rival wrestlers. It will use a bread-first search to determine whether the specified rivalries are compatible. If compatible, it will display a list of potential Babyfaces (good guys) and Heels (bad guys). 

# Example:  

Sample input file: 
```
5   
Ace   
Duke   
Jax   
Biggs  
Stone   
6   
Ace Duke   
Ace Biggs 
Jax Duke 
Stone Biggs 
Stone Duke 
Biggs Jax 
```
Sample result: 
```
Yes  
Babyfaces: Ace Jax Stone   
Heels: Biggs Duke 
```

# How to compile:
```
g++ wrestler.cpp

```

# How to run: 
```
a.out
```
