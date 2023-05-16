# webcam car detector

A simple program to capture footage from campus webcams and detect cars
in the webcam footage captured from the page

You'll need cmake and OpenCV on Ubuntu 22.04 to install you should do:
`sudo apt-get install -y libopencv-dev cmake`

To run the Python script that gets the stream URL you'll need Python 3.x
and the requests module.

To get the requests module, which should be included by default on most
installs of python do:
`pip3 install requests`

After you've done all that, simply run the following commands to build
and start the recording/detecting executable (be sure you've cd'd to the
directory of the git repo)

```
# build the detection code
cmake .
make

# run the detection code on the stream
./test $(python3 ./getimage.py)
```
