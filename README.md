# Vehicle-Detection
C++/OpenCV Program to find and highlight all instances of cars &amp; other vehicles within an image file

# Section 1: Introduction

Automatic image detection is a very common topic in pattern analysis research
and computer vision. This application involves image processing, pattern
recognition, and object detection working concurrently. Image detection is
becoming a more familiar feature amongst apps and websites. Some examples
include Facebook’s facial recognition for tagging photos, Google’s image
comparison search, and Microsoft’s Kinect identification through facial detection.

Each of these useful applications involves comparing a specific image to a library
of pre-existing images, both positively or negatively correlated to the type of
image provided. For my vehicle detection project, I decided to focus on detection
of cars within images, since cars are very common object in real world settings.

Many research papers and existing open-source projects have tackled object
recognition + detection, ranging from detecting facial features to license plates.
However, besides faces, there are not many existing detection apps for specific
images such as cars and even less with an easy set-up for the user. Since I was
a one-man team for this project, I decided that it would be more feasible to build
upon existing detection algorithms provided by the OpenCV library and create an
effective way to present image results to the user. For my project I focused on
three primary features:

1. The user is able to run this program with any image he/she provides.
2. The program will run and display the original image with any instances of
car detection being individually highlighted.
3. Finally, the program will output the number of cars detected.
Section 2.1: Review of Previous Work
There are many open-source projects that have implemented object recognition
in various applications. Most projects that used OpenCV for object recognition
were for facial recognition based on training images, which is similar in concept
to my vehicle detection program. The algorithm for training classifiers and 
comparing user-inputted images with classifiers has been implemented by many
of these projects. Many facial detection programs I found were either built into
pre-existing applications or websites, working not just on photos but live video.
Other facial detection code came in the form of APIs, which is a bit difficult to use
and understand without background knowledge.

# Section 2.2: Project Comparison to Previous Work

Although my program is not groundbreaking by any means, I decided to mix it up
and pick an object not as popular as faces. The idea is similar, but the testing
images would be a lot different than the images provided for faces. In theory,
many of the algorithms and libraries provided by OpenCV can be used for
detection of any object, given enough data images for positive and negative
correlation. I picked cars since vehicle detection can come useful for many
applications such as CCTVs and traffic cameras.

Secondly, while setup is not as simple as downloading a facial recognition app,
my program is far less complicated than configuring a new API. This also allows
users to provide additional test images if they choose and run it from their
command line rather than an external program.

# Section 3.1: Technical Summary
My vehicle detector program is fairly simple to run and use for the user once
he/she has downloaded the necessary databases and OpenCV library. The user
simply puts the project code, classifiers, and images within one directory and
runs the program with my pre-written Makefile.

As for the implementation of the project, I first had to download several original
images as well as two car image databases (CMU + UIUC) for the training
images. By creating classifiers using the traincascade application provided by
OpenCV, I created a few cascade classifiers. Running the image provided with
those cascade classifiers, the program will detect any instances of images of
cars and output the results to the user’s screen.

# Section 3.2: Project Technical Details
Before being able to run my Vehicle Detection program, the user must download
the following:
1. OpenCV (Open source computer vision library)
2. Cmake (Open source build system)
The links to download both of the above resources are provided in the reference
section of the final report.

# Setup, Installation of OpenCV

The first step that I took was deciding on a compiler for the project. Since I am a
Mac user and use C++, I decided to use XCode as my code-editor and the built
in Terminal to run + compile my project.

Once I downloaded OpenCV into its own directory and the Cmake application, I
had to go through a surprisingly difficult process to get OpenCV working with my
Terminal (8 hours in fact due to technical issues + complicated instructions…). I
have posted a link to a somewhat helpful tutorial for installing OpenCV correctly
on Mac OSX systems in the reference section.

First I had to create a new folder within the OpenCV folder called “Static Library”
and used Cmake to build the libraries within the newly created folder. After this
step, I had to then install those static libraries on my computer using “make”.

# Program Breakdown
The main program, VehicleDetection.cpp, was coded in C++ for usage with
OpenCV. The program contains a single class called “Vehicle” which defines all
the functions necessary for finding cars within an image and printing out the
result. The code is provided in the source folder and is commented for reading.

List of Vehicle functions:

1. Read Input
- Simply reads in input image and creates copies for result image
2. Load Cascade Classifiers
- Loads the classifiers provided by user
3. Find Vehicles within Image
- First resize the image and then convert to grayscale
- Run detection using classifiers
- Get points for rectangle boundaries of car
- Run test classifier to see if car is within boundary
- Detect rectangle boundary over final result
- Mask the detected car to detect for more cars
- Keep track of number of vehicles
4. Output Image Result Window + Count
- Output a window titled “Vehicle Detection”
- Show user the result image with cars detected if any
- Print the number of cars onto the terminal

The main function simply creates an object called Vehicle and then goes through
the four functions listed above, taking in the user’s image as input.

# Compilation + Running

To compile the program itself, the user needs to use Terminal and navigate to
his/her directory containing my program files. The next step is to first call “cmake
.” in the command line to call cmake using the makefile I made from scratch.

Afterwards, the user can build the project by calling “make”. Running the
program is straightforward- after calling “make”, the user needs to type the
following:

./VehicleDetection “image.extension” trainCas.xml “cascade.xml” …
“image.extension” can be any image that is located within the program directory.
For example, helloworld.jpg would be a valid input.
“cascade.xml” can be any custom cascade classifier .xml file within the program
directory. For example, cascade3.xml would be a valid input.

# Results

Once successfully compiled and run on the command line, the program will
check the image with all of the cascade classifiers provided by the user. I have
included a few classifiers in the directory for usage. Obviously, the accuracy of
the program increases with more cascade classifiers to run with. The following
images are sample outputs of my project.



# Possible Improvements
The algorithm isn’t perfect for finding cars, and it fails to detect every car in some
images, especially those with cars in close proximity and not fully represented in
the image. This might be improved if I added more training images and created
more accurate cascade classifiers, but for the most part, my program works
accurately with typical images of cars. I could have tried to optimize the boundary
detection for more accuracy, but I do not know how much this would have
affected the accuracy for images such as the one below.
