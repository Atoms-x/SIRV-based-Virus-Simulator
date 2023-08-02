## Vaccines

Vaccines are broken down into four different distribution models

### Closeness Centrality

A measure of how close a region is to all other regions. The priority is set to distribute the vaccines first to the regions that are closest to all other regions, then to other regions as determined by their calculated relative closeness centrality score.

### Degree Centrality

A measure of the degree for a region (the amount of directly connected regions). Priority is set to regions that have the largest degree (connected directly with the most number of regions), then to other regions as deteremined by their calculated relative degree centrality score.

### Random

The vaccines are distributed randomly. However, in this simulation, it is assumed that the region label codes have been assigned randomly, so vaccines are then just filled from lowest region number to largest, until none are left.

### Equal

An equal distribution of vaccines is conducted. However, some regions may have more if a regions population is lower than the equal avaiable number of vaccines. In the case of the last vaccines being distributed, the lower region numbers have priority.
