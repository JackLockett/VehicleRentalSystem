# Vehicle Rental System

## Overview

The Vehicle Rental System is a C++ program I developed for the Advanced Programming module in my second year at Sheffield Hallam University. It allows users to manage vehicle rentals, specifically cars and bikes, featuring functionalities such as adding, removing, and searching for vehicles, as well as viewing rental histories. This application illustrates my understanding of good practices in object-oriented programming and memory management.

## Features

- **Vehicle Management**: Add, remove, and search for vehicles (cars and bikes) with unique registration numbers.
- **Vehicle Types**: Support for two vehicle types:
  - **Cars**: Includes properties like registration number, make, model, age, number of doors, and number of seats.
  - **Bikes**: Includes properties like registration number, make, model, age, engine size, and number of wheels.
- **Cost Calculation**: Dynamic calculation of rental costs based on vehicle type and properties, with a minimum rental cost cap.
- **Rental History**: Maintain and manage a complete rental history for each vehicle, including total income and days rented.
- **Data Persistence**: Vehicles and their rental histories are loaded from and saved to disk only when the application exits.
- **User Interaction**: Clear and user-friendly menu options with error handling for user inputs.

## Requirements

- **C++ Compiler**: The application is developed in C++ and requires a compatible compiler (e.g., Visual Studio 2022).
- **Standard Template Library (STL)**: Utilises STL containers and algorithms for efficient data handling.

## Getting Started

1. Clone the repository or download the ZIP file containing the project files.
2. Open the project in Visual Studio 2022.
3. Build the project to ensure all dependencies are met.
4. Run the application to begin managing vehicle rentals.

## Usage

- **Main Menu**: On startup, the application presents a main menu for vehicle management.
- **Adding Vehicles**: Users can add new vehicles by providing the necessary details.
- **Searching Vehicles**: Search options are available based on various criteria depending on the vehicle type.
- **Viewing Rental History**: Users can view and manage rental histories for selected vehicles.
- **Exiting the Application**: Data is saved to disk upon exiting the application.

## Coding Standards

The application follows best practices in:
- Object-oriented programming (OOP)
- Dynamic memory management
- Error handling
- Code clarity and maintainability
