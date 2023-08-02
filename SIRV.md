## SIRV

Since this is an agent-based SIRV model, each agent is an independent entity and will have a status based on SIRV. SIRV stands for:
* **S** usceptible
* **I** nfectious
* **R** emoved/Recovered (or Immune)
* **V** accinated

### Susceptible

Agents that are susceptible are not infected with the virus, but can become infected.

### Infectious

Agents that are infectious are infected with the virus and can spread it to the agents that are susceptible for the length of their infectious period

### Removed/Recovered

Agents that are removed/recovered are not infectious anymore and are now immune to the virus

### Vaccinated

Agents that are vaccinated are immune to the virus and cannot ever become infectious

### Virus Spread

* Each vaccine distribution simulation will start with a single infected agent on Day 0. Day 0 will also coaunt as a day for the agent's infectious period.
* Every day, the infectious population will infect the susceptible population at the rate specified by the contact rate, per agent.
  * However, the newly infected agents will not become infectious until the next day.'
* At the end of a day, any infectious agents that have been infected for the same number of days as specified by the infectious period will become removed/recovered the next day.
* Recovered/removed and vaccinated agents will not change states
* If a region is more than 50% infectious through any day, then that region will infect a single person in each of the regions it is connected to.
  * Just like the spread between agents, the single, newly infected agent in each connected region will not become infectious until the next day.
* The simulation ends when there are not anymore infectious in any region.
