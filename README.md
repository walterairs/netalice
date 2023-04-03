# netalice #
net analysis tool project by Niklas Suvitie and Valtteri Äyräs @Turku University of Applied Sciences.

## Features in 1.0.0 ##

* Measure network speed(download)
* Ping hosts in network
* Output results in user-friendly formats

## Requirements: ##
```
sudo apt-get install libncurses5-dev libncursesw5-dev
sudo apt-get install libcurl4-openssl-dev
sudo apt install gcc-9
```

## Installation ##
```
git clone https://github.com/walterairs/netalice.git
cd netalice
make
```

## Usage ##
```
./netalice
```

## color coding ##
Color | meaning
------|--------
red   | Error
green | Success/measures
yellow| Missing input

## License ##
This project is under MIT Lisence.
