# ft_ls
42 school project

## Description

Classical 42 school project aiming at reproducing the 'ls' command.  
  
Available options reproduced are '-alrRt'

### Specificities
I handled the memory in a uncommon way for this project,  
Reducing the amount of malloc calls by regrouping them into single memory blocks for all data inside linked-list nodes.
  
This ls version is pretty slow that being said, as I reused my sub-optimal printf version in order to handle the display.
I did not try to implement any sort of output bufferization as it seemed to me as quite time consuming task for a very minor ROI.
