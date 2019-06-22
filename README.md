# translators
My project-based attempt to learn about translators. 

## Use me! 
Build by typing `make`. 
You can run my test program at example/prog-v3.apas 

### Interactive Mode
`./calculator.out -i`

Prompts you with > and interprets every line of text as a program. 
Type `q` to quit. 

### Normal Mode 
`./calculator.out [< your-program-file]`

Normal mode takes input from stdin. You can either pass in a program file as input or type out your full program and then hit `Ctrl+D` to send an EOF to have your program interpreted. 

## Versions 
#### v1: 
A really basic arithmetic expression calculator

#### v2: 
An arithmetic expression calculator with operator and parenthesis precedence 

#### v3: 
A really basic interpreted pascal-like language with support for assignment statements in a global scope. At the end of successful execution the program displays the values of all the variables. 

