# Portable-MP3-Player

This project implements a portable MP3 player using the Arduino framework in C++. 
It uses FreeRTOS tasks along with message queues, semaphores, and event groups 
to coordinate input, audio, and display. A joystick is used for user 
interactions such as Play/Pause, Next, Previous and track selection. The audio manager handles MP3 playback, while the display manager shows the current track status.