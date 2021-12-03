FROM frolvlad/alpine-glibc:alpine-3.14_glibc-2.33

# makefile
RUN apk add --no-cache make
# include <iostream>
RUN apk add --no-cache g++
# clang++
RUN apk add --no-cache clang

COPY . /crawler

WORKDIR /crawler