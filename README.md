# CombinedAlertOSINT

## Combined air alert system with OSINT analytics

This project aims to combine an air raid alert system with OSINT (Open Source Intelligence) data collection and analysis.

### Components

The system uses the following components:

- **Libcurl**: For making HTTP requests and fetching data from web sources.
- **SQLite**: For storing and managing data locally.
- **CMake**: For managing the build process.

### Getting Started

#### Prerequisites

Make sure you have the following dependencies installed on your system:

- [CMake](https://cmake.org/)
- [libcurl](https://curl.se/libcurl/)
- [SQLite](https://www.sqlite.org/index.html)
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

You can install them on Ubuntu using:

```sh
sudo apt-get update
sudo apt-get install cmake libcurl4-openssl-dev libsqlite3-dev libjsoncpp-dev
