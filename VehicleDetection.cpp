//Hyun Wuk Choe
//EECS 442
//Vehicle Detection Program

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <cstdlib>
#include <iterator>

using namespace cv;

using namespace std;

class Vehicle     
{
	public:	   
	
	//Image input, I decided to use Mat, a basic image container
	Mat image_input;          
	//Resulting image
	Mat vehicleDetectImage;    
	//Keeping track of previously detected cars to not repeat
	Mat previousDetect;              

	//Calling the CascadeClassifier class defined by openCV
	CascadeClassifier cascade;
	//A classifier that is trained with smallest size parameters(runs first before others)
	CascadeClassifier TrainCascade;  

	//Declaring number variable
	int Vehicle_Count;

	// Function for reading in the image input
	void readInput(Mat input) 
    {             
            image_input = input.clone();
            vehicleDetectImage = input.clone(); 
			previousDetect = input.clone();               
			
    }

    //Function to initialize the smallest parameter cascade for testing
    void trainCas_init(string checkcascade_string)               
	{
		TrainCascade.load(checkcascade_string);

		if( !TrainCascade.load(checkcascade_string) )
    	{
        	cout << "Error, could not initialize Train Cascade Classifier" << endl;
        	
    	}
	}
	
	//Function to initialize cascade classifier
	void cas_init(string cascade_string)            
	{
		cascade.load(cascade_string);

		if( !cascade.load(cascade_string) )
    	{
        	cout << endl << "Error, could not initialize cascade classifier" << endl;
        	
    	}

	}

	//Detection function
	void Vehicle_Detect()                 
	{
    	
    	//Declaring detect_point variables for x & y
    	int xCoord;                         
		int yCoord;
		//Initialize iterator
		int i = 0;
		//Initializing rectangle vector
    	vector<Rect> Vehicle;
    	
    	//Initializing image contrainer
		Mat Vehicle_Image = previousDetect.clone();
		Mat temp_Vehicle;    
		Mat greyscale;                 
		
    	const static Scalar RectColor[] =  { CV_RGB(255,0,255),CV_RGB(0,175,255),CV_RGB(150,0,0),CV_RGB(255,255,0),
    										CV_RGB(0,128,0),CV_RGB(50,50,128),CV_RGB(128,128,128),CV_RGB(0,0,0),
    										CV_RGB(175,0,255),CV_RGB(125,255,125), CV_RGB(0,125,255)
    									};                   

    	//Convert image to gray and copy into greyscale
    	cvtColor( Vehicle_Image, greyscale, CV_BGR2GRAY );
    	//Use OpenCV unsigned 8 bit pixel
		Mat resize_image(cvRound(Vehicle_Image.rows), cvRound(Vehicle_Image.cols), CV_8UC1);		

    	resize(greyscale, resize_image, resize_image.size(), 0, 0, INTER_LINEAR);
    	equalizeHist(resize_image, resize_image);

    	cascade.detectMultiScale(resize_image, Vehicle, 1.1,2,0, Size(15,15));                
		
		//We will scan the regions of interest and if a car is detected, we will not repeat for other
		//classifiers
		for(vector<Rect>::const_iterator img = Vehicle.begin(); img != Vehicle.end(); img++, i++)
    	{
       		Mat DetectionRegion;

        	vector<Rect> mult_cars;

        	Point detect_point;

        	//Rectangle border color will be randomized
        	Scalar border = RectColor[i % 7];
        	
			//Rectangle boundary points
			int cornerX = cvRound(img->x);       
			int cornerX1 = cvRound((img->x + img->width-1));                       
			int cornerY = cvRound(img->y);
			int cornerY1 = cvRound((img->y + img->height-1));

        	DetectionRegion = resize_image(*img);

        	TrainCascade.detectMultiScale(DetectionRegion, mult_cars,1.1,2,0,Size(30,30));
            //Here we test the image using our first TrainCascade
        	for(vector<Rect>::const_iterator sect = mult_cars.begin(); sect != mult_cars.end(); sect++)      
        	{	
        		//Here we find the x boundary of a circle for area of car detection
           		detect_point.x = cvRound((img->x + sect->x + sect->width * 0.5));        
				xCoord = detect_point.x;
				//Here we find the y boundary of circle for area of car detection
			   	detect_point.y = cvRound((img->y + sect->y + sect->height * 0.5));
				yCoord = detect_point.y;
				//We check if the middle of the circle is located within boundaries of the detected rectangle
				if(yCoord > (cornerY + 15) && yCoord < (cornerY1 - 15) && xCoord > (cornerX + 15) && xCoord < (cornerX1 - 15))         
				{		
					//If so, we can verify detection of car				
					//Finding the boundary of final rectangle
					rectangle(vehicleDetectImage, cvPoint(cornerX,cornerY), cvPoint(cornerX1,cornerY1), border, 3, 8, 0);               
					Rect interestRegion = Rect(cornerX, cornerY, cornerX1 - cornerX, cornerY1 - cornerY);

					//We need to mask the location of detected car before moving on to next one
					temp_Vehicle = previousDetect(interestRegion);
					//Mask it completely
					temp_Vehicle = Scalar(255,255,255);

					//Increment the count of cars by 1 each successful find
					Vehicle_Count = Vehicle_Count + 1;     
				
				}
			}      
				
		}							
			
    } 

    //Outputting the resulting image
    void imageResult()            
	{
		
		if(!vehicleDetectImage.empty() )
        {
			namedWindow("Vehicle_Detection");

			imshow("Vehicle_Detection", vehicleDetectImage);

			waitKey(0);
		}
	}
     			
};
		    	
int main(int argc, const char** argv)
{
	//Initializing image containers
	Mat image;
    Mat usr_image = imread(argv[1],1);
	
	//resizing image to get best experimental results
	resize(usr_image,image,Size(300,150), 0, 0, INTER_LINEAR); 

	//Initialize the number of cars
	int Vehicle_Count = 0;    
	// Initializing object
	Vehicle vehicle;                      

	string trainCascade = argv[2];

	//Read in the user provided image
	vehicle.readInput(image);           
	        
	vehicle.trainCas_init(trainCascade);      
	
	//Improving results with several cascade classifiers
	if(argc > 3)
	{
		for(int i = 3; i < argc; i++)
		{
			// Take input from command line argument
			string cascade = argv[i];	

			vehicle.cas_init(cascade); 

			// Search using cascade classifiers
			vehicle.Vehicle_Detect();
		}
	}
	else
	{	
		cout << endl << "Error! Need cascade .xml" << endl;
		exit(1);
	}

	//If no cars are found, print this message
	if(vehicle.Vehicle_Count == 0)
	{
		cout << endl;
		cout << "No Vehicles detected" << endl;
	}

	//If cars are found, print number of cars
	else
	{
		cout << endl;
		cout << "Number of Vehicles detected: " << vehicle.Vehicle_Count  << endl;
	}     

	 // Print the output image 
	vehicle.imageResult();     
	
	return 0;
}
