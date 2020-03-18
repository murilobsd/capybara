# <img alt="Capybara" src="https://m0x.ru/capybara/capybara.png" height="150">

![Travis (.org) branch](https://img.shields.io/travis/murilobsd/capybara/master?style=for-the-badge)
[![license](https://img.shields.io/badge/License-BSD-blue.svg?style=for-the-badge)](LICENSE)

Capybara is the Dataframe in C

- **Website:** https://m0x.ru/capybara/
- **Source code:** https://github.com/murilobsd/capybara
- **Bug reports:** https://github.com/murilobsd/capybara/issues
- **Contact:** irc.freenode.com ##capybara

## Features

- Multiple platforms: OpenBSD, Linux, MacOS.

## Install

### Download the sources

```sh
git clone https://github.com/murilobsd/capybara
cd capybara
git submodule update --init --recursive
```

### Configuration

```sh
mkdir build
cd build
cmake ..
```

### Build

```sh
make
```

### Run the tests

```sh
make test
```

### Create package

```sh
make package
```
