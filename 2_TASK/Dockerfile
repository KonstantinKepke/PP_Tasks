FROM gcc:latest

COPY . /usr/src/1_task

WORKDIR /usr/src/1_task

RUN g++ --std=c++20 -O0 -o ping-pong ping-pong.cpp
 
CMD [ "./ping-pong" ]