# Dynamic Object Detection for Home Park Assist

This project was developed for the Bosch Global Software Technologies Hackathon 2024. It aims to enhance home park assist systems by implementing dynamic object detection using OpenCV for real-time video analysis. The system identifies and tracks moving objects in a scene to assist drivers in safely parking their vehicles.

## Features

- **Real-time Object Detection**: Utilizes OpenCV's BackgroundSubtractorMOG2 algorithm to detect and track moving objects in video frames.
- **Noise Reduction**: Applies morphological operations to minimize noise and improve detection accuracy.
- **Contour Analysis**: Filters contours based on area to focus on significant objects, drawing bounding boxes around detected entities.
- **Video Processing**: Supports processing of video files and live video feeds, providing immediate feedback on detected objects.

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/dynamic-object-detection.git
   cd dynamic-object-detection
   ```

2. **Install dependencies:**
   Ensure you have OpenCV installed. You can install it using pip:
   ```bash
   pip install opencv-python opencv-python-headless
   ```

3. **Compile and run the program:**
   Make sure you have a C++ compiler that supports OpenCV. Then compile and run the code:
   ```bash
   g++ -o detect_objects detect_objects.cpp `pkg-config --cflags --libs opencv4`
   ./detect_objects
   ```

## Usage

1. **Provide the input video file path:**
   You will be prompted to enter the path of the video file you wish to process.

2. **Enter the base address:**
   You will be asked to provide the base address where you wish to save the output video.

3. **View the processed video:**
   The program will process the video, highlighting detected dynamic objects with bounding boxes, and save the output video as `output_recorded.mp4`.

4. **Exit the program:**
   To stop the video processing and exit, press the 'q' key during the video display.

## Project Structure

- `detect_objects.cpp`: Main source file containing the implementation of dynamic object detection.
- `README.md`: Documentation file describing the project.

## Requirements

- OpenCV (version 4.x or later)
- C++11 or later
- Video file for input

## Contribution

Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

