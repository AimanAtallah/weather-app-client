# Weather App Client

A C++ command-line client that requests current weather for a city and prints a compact report.

**C++ · libcurl · WeatherAPI**

---

## Features

- Look up a city by name, including names containing spaces.
- Display temperature in Fahrenheit, current condition, feels-like temperature, and wind chill.
- Look up additional cities in the same session.
- Enter **E** to exit.

## Requirements

- A C++ compiler.
- libcurl headers and library.
- A WeatherAPI API key and an internet connection.

## Setup

```sh
git clone https://github.com/AimanAtallah/weather-app-client.git
cd weather-app-client
```

In `main.cpp`, set the currently empty `API_KEY` constant to your own key for local use. Keep that value out of commits; the checked-in source intentionally omits it. Moving the key to an environment variable is a future improvement.

## Build and run

When libcurl is available on the compiler's default search paths:

```sh
c++ -std=c++17 main.cpp -lcurl -o weather
./weather
```

If libcurl is installed elsewhere, provide its include and library paths for your environment.

Enter a city at the prompt, then repeat with another city or enter `E` to finish.

## How it works

`userCityFormat()` prepares the city query. libcurl sends the request to WeatherAPI, and `writeToString()` collects the response. The program extracts weather values from the returned text and prints them in the terminal.

## Status

This is an early API-client project. Response parsing currently uses string positions rather than a JSON parser. Missing keys, invalid city names, network failures, or unexpected responses may not be handled safely. A Swift interface and Objective-C bridge are listed as future work in the source; the current app is terminal-only.
