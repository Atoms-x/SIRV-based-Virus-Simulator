<p align="center">
  <img src="https://github.com/SgtR0ck/City_Simulator/assets/8111664/ac60bc95-3be6-4110-99d3-74146b0a4892"
</p>
<h1 align="center"> 
  SIRV-based Virus Simulator 
</h1>

<p align="center">
  <a href="https://github.com/SgtR0ck/City_Simulator">
    <img src="https://img.shields.io/badge/version-1.0.0-green.svg?style=plastic">
  </a>
  <img src="https://img.shields.io/badge/language-C%2B%2B-%2300599C.svg?style=plastic&logo=C%2B%2B">
  <img src="https://img.shields.io/badge/code%20style-ANSI-orange.svg?style=plastic">
  <a href="https://github.com/SgtR0ck/City_Simulator/blob/main/LICENSE.md">
    <img src="https://img.shields.io/badge/license-MIT-green.svg?style=plastic">
  </a>
</p>

## Table of Contents
  - [Introduction](#introduction)
    - [SIRV Growth Model](#sirv-growth-model)
    - [Vaccine Distribution Models](#vaccine-distribution-models)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Formatting](#formatting)
    - [Running](#running)
  - [Authors](#authors)
  - [License](#license)
  - [Acknowledgments](#acknowledgments)


## Introduction

This is a C++ based program that can be used to simulate the spread of a virus using a SIRV growth model in agent-based populations within specified regions and between those regions.

### SIRV Growth Model

SIRV stands for:
* **S** usceptible
* **I** nfectious
* **R** emoved/Recovered (or Immune)
* **V** accinated

See [SIRV.md]() for a complete description.

### Vaccine Distribution Models

The Vaccine is distributed based on four differet models:

* Closeness Centrality
* Degree Centrality
* Randomly
* Equally

See [VACCINE.md]() for a complete description.

### Prerequisites

Be sure to have a C++ compiler installed. Additionally, an IDE is recommended.
Try following this guide for [Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp)

![image](https://github.com/SgtR0ck/City_Simulator/assets/8111664/73855d8b-0999-4c9b-8434-73d49ee4a338)

### Formatting

Before you run the program, ensure you have at least one txt config file, one txt population file and one CSV region file.

The **config** txt should be formatted as such:

![image](https://github.com/SgtR0ck/SIRV-based-Virus-Simulator/assets/8111664/e605ce99-eec8-4e04-9e52-76dc35549670)

The population specifies the name of the txt population file.
The region specifies the name of the CSV region file.

The infected area specifies the starting area of the infection.
The infectious period specifies the number of turns that an infected agent is infectious.
The contact rate specifies the number of other agents that become infected by this agent per turn.
The number of vaccines specifies how many total vaccines are distributed across the various regions.

The **population** txt should be formatted as such:

![image](https://github.com/SgtR0ck/SIRV-based-Virus-Simulator/assets/8111664/3e8df006-99ca-41c5-b2ce-9f3e5667d124)

The numbers to the left of the colon represent a given area, and the numbers to the right specify the size of the population

The **region** CSV should be formatted as such:

![image](https://github.com/SgtR0ck/SIRV-based-Virus-Simulator/assets/8111664/eb04ec70-6af4-4463-9cc6-7b7f76a25ace)

This is an adjacency matrix. The numbers along the far left and across the top are the regions. A '0' between two regions means they do not connect. Conversely, a '1' means that they do connect.

### Running

Once you've executed the program, your CLI should present a prompt for a config txt file

![image](https://github.com/SgtR0ck/SIRV-based-Virus-Simulator/assets/8111664/a0a4a8b6-a736-40b7-975b-d770a2660f43)

Give the name of your config txt file as prompted (make sure that the file is local to the executable)

![image](https://github.com/SgtR0ck/SIRV-based-Virus-Simulator/assets/8111664/278e5b8a-3620-418e-bbaf-42b7361e8acc)

After inputing your config file name, you will be presented with the specified population distribution and adjacency list

![image](https://github.com/SgtR0ck/SIRV-based-Virus-Simulator/assets/8111664/a4c52bf1-2cc9-46e0-98cd-3f4f1ca00556)

Watch the virus spread through four different vaccine distribution models!

![image](https://github.com/SgtR0ck/SIRV-based-Virus-Simulator/assets/8111664/4665dd6d-6abe-4b5a-9cf9-a5056b09bec6)

Until you reach the final state for each (indicated by the start of the next distribution model, or the final outcome statement).

![image](https://github.com/SgtR0ck/SIRV-based-Virus-Simulator/assets/8111664/019dec44-1644-469b-be37-1215c7eeacb8)

A final outcome statement will be generated, indicated what the vaccine distribution model was, the peak number of infected and on what day, when the outbreak ended, and how many total agents were infected

![image](https://github.com/SgtR0ck/SIRV-based-Virus-Simulator/assets/8111664/84f760bb-b770-412b-82f9-21ad78fe2adb)

## Authors

* **Chet Lockwood** - [SgtR0ck](https://github.com/SgtR0ck)

## License

This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/SgtR0ck/City_Simulator/blob/main/LICENSE.md) file for details

## Acknowledgments

* Thank you to the many guides across the internet on C++
