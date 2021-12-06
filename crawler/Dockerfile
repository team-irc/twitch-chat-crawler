FROM frolvlad/alpine-glibc:alpine-3.13_glibc-2.33

# makefile
RUN apk add --no-cache make
# include <iostream>
RUN apk add --no-cache g++
# clang++
RUN apk add --no-cache clang

WORKDIR /crawler