# ft_ls
42 school project

## Description

Classical 42 school project aiming at reproducing the 'ls' command.  
  
Available options reproduced are '-alrRt'  
  
You can find the original subject of the project [here](https://github.com/bpopovic42/ft_ls/blob/master/resources/subject.en.pdf)

### How to

#### Recommended way (Requires Docker)
You can try it out by building and running the provided Dockerfile as follows :
```
./bin/dev/build && ./bin/dev/bash
```
And once inside the container :
```
make -C ft_ls && ./ft_ls/ft_ls
```
Allowing you to test it out in the intended containerized environment

#### Not recommended
Otherwise you should be able to try it out under a typical Unix distribution, provided that you have the proper dependencies installed by simply running :
```
make -C ft_ls && ./ft_ls/ft_ls
```

### Specificities
I handled the memory in a uncommon way for this project,  
Reducing the amount of malloc calls by regrouping them into single memory blocks for all data inside linked-list nodes.
  
This ls version is pretty slow that being said, as I reused my sub-optimal printf version in order to handle the display.  
I did not try to implement any sort of output bufferization as it seemed to me as quite a time consuming task for a very minor ROI.

### Testing framework
The provided testing framework is located under [/testing/tester](https://github.com/bpopovic42/ft_ls/tree/master/testing/tester)  
  
Most of its test cases were taken from the [42FileChecker](https://github.com/jgigault/42FileChecker)  
Although I did not manage to make them work as is, therefore I rewrote them my own way using python in its 3.8 version.  
  
Feel free to reuse it and to contact me if you have any questions about it.
