#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

// Function to detect dynamic objects in a frame
void detectDynamicObjects(const Mat &frame, Mat &frame_out, Ptr<BackgroundSubtractorMOG2> &backSub)
{
    // Variables for processing
    Mat fg_mask, mask_thresh, mask_eroded;
    int min_contour_area = 500;
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));

    // Apply background subtraction
    backSub->apply(frame, fg_mask);
    // Apply global threshold to remove shadows
    threshold(fg_mask, mask_thresh, 180, 255, THRESH_BINARY);
    // Apply erosion to remove noise
    morphologyEx(mask_thresh, mask_eroded, MORPH_OPEN, kernel);

    // Find contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(mask_eroded, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Filter contours based on area
    vector<vector<Point>> large_contours;
    for (const auto &cnt : contours)
    {
        if (contourArea(cnt) > min_contour_area)
        {
            large_contours.push_back(cnt);
        }
    }

    // Draw bounding boxes around detected contours
    frame_out = frame.clone();
    for (const auto &cnt : large_contours)
    {
        Rect rect = boundingRect(cnt);
        rectangle(frame_out, rect.tl(), rect.br(), Scalar(0, 0, 200), 3);
    }
}

// Function to process video frames and detect dynamic objects
void processVideo(const string &input_video, const string &base_address)
{

    /**Memory Allocation Details and Appraoch is mentioned in the Project Documentation, Please Refer it for further details. */

    // Open input video file
    VideoCapture cap(input_video);
    if (!cap.isOpened())
    {
        cerr << "Error opening video file" << endl;
        return;
    }

    // Get input video properties
    double fps = cap.get(CAP_PROP_FPS);
    Size frame_size((int)cap.get(CAP_PROP_FRAME_WIDTH), (int)cap.get(CAP_PROP_FRAME_HEIGHT));

    // Create VideoWriter object for writing output video
    int fourcc = VideoWriter::fourcc('m', 'p', '4', 'v');
    VideoWriter out("output_recorded.mp4", fourcc, fps, frame_size);

    // Create a background subtractor object
    Ptr<BackgroundSubtractorMOG2> backSub = createBackgroundSubtractorMOG2();

    // Process each frame of the video
    Mat frame, frame_out;
    while (cap.read(frame))
    {
        // Perform dynamic object detection
        detectDynamicObjects(frame, frame_out, backSub);

        // Write processed frame to output video
        out.write(frame_out);

        // Show the processed frame (optional)
        imshow("Processed Frame", frame_out);
        if (waitKey(30) == 'q')
            break;
    }

    // Release resources
    cap.release();
    out.release();
    destroyAllWindows();
}

int main()
{
    // Input video file path
    string input_video;
    string base_address;

    cout << "Enter the input video file path: ";
    cin >> input_video;

    cout << "Enter the base address: ";
    cin >> base_address;

    // Process the video
    processVideo(input_video, base_address);

    return 0;
}
