# webcam-trng
A C++ program that utilizes OpenCV to turn your webcam into a true random number generator
##The lowdown
Not all video sources are created equal, those video sources that work well with this program will already have some (hopefully unpredictable) motion occuring within frame.
The program comes equipped with a chi-squared test for evaluating whether what you point your webcam at is truly random. 
##Other features
In addition to evaluating video sources, the program also features a random number generator in addition to an image scrambler (which if your video source is truly random, your 
provided image should be nearly indistinguishible from a "white noise" image)
